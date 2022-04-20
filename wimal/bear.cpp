#include "bear.hpp"

#include <uv.h>
#include <json/json.h>
#include <list>

#include "context.hpp"

namespace wimal {

struct BearCache {
    int status{0};
    std::list<std::string> commands{};
    uv_udp_t udp{};
    uv_process_t process{};
};

static inline void Serve(BearCache *cache) {
    auto &udp = cache->udp;
    udp.data = cache;
    uv_udp_init(uv_default_loop(), &udp);
    sockaddr_in address{};
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(0);
    if (uv_udp_bind(&udp, (sockaddr *) &address, 0)) {
        return;
    }
    int length = sizeof(address);
    if (uv_udp_getsockname(&udp, (sockaddr *) &address, &length)) {
        return;
    }
    auto port = ntohs(address.sin_port);
    setenv("WIMAL_BEAR_PORT", std::to_string(port).data(), 1);
    static char kBuffer[65536];
    uv_udp_recv_start(&udp, [](uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf) {
        buf->base = kBuffer;
        buf->len = sizeof(kBuffer);
    }, [](uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *, unsigned) {
        if (nread <= 0) {
            return;
        }
        auto cache = (BearCache *) handle->data;
        cache->commands.emplace_back(std::string(buf->base, nread));
    });
}

static inline void Spawn(BearCache *cache, const Context *context, const std::vector<std::string> &extraArgs) {
    std::vector<char *> arguments;
    arguments.reserve(context->args.size() + extraArgs.size() + 1);
    if (context->args.empty()) {
        return;
    }
    ghc::filesystem::path command;
    for (const auto &arg : context->args) {
        if (command.empty()) {
            if (arg.empty() || arg[0] == '-') {
                continue;
            }
            command = ghc::filesystem::path(arg);
        }
        arguments.emplace_back(const_cast<char *>(arg.data()));
    }
    if (command.empty()) {
        return;
    }
    for (const auto &arg : extraArgs) {
        arguments.emplace_back(const_cast<char *>(arg.data()));
    }
    arguments.emplace_back(nullptr);
    uv_process_options_t options{};
    memset(&options, 0, sizeof(options));
    options.exit_cb = [](uv_process_t *handle, int64_t status, int) {
        auto cache = (BearCache *) handle->data;
        uv_udp_recv_stop(&cache->udp);
        cache->status = (int) status;
        uv_close((uv_handle_t *) &cache->udp, [](uv_handle_t *) {});
    };
    options.args = arguments.data();
    options.file = command.c_str();
    options.stdio_count = 3;
    uv_stdio_container_t stdio[3];
    stdio[0].flags = UV_INHERIT_FD;
    stdio[0].data.fd = 0;
    stdio[1].flags = UV_INHERIT_FD;
    stdio[1].data.fd = 1;
    stdio[2].flags = UV_INHERIT_FD;
    stdio[2].data.fd = 2;
    options.stdio = stdio;
    cache->process.data = cache;
    uv_spawn(uv_default_loop(), &cache->process, &options);
}

static inline void Save(BearCache *cache) {
    constexpr const char *kCompileCommandsFile = "compile_commands.json";
    std::list<Json::Value> commands;
    std::unordered_map<std::string, std::list<Json::Value>::iterator> fileCommands;
    // Read existing compile_commands.json
    Json::Reader reader;
    Json::Value allCommands(Json::arrayValue);
    std::ifstream istream(kCompileCommandsFile);
    if (istream) {
        if (!reader.parse(istream, allCommands) || !allCommands.isArray()) {
            allCommands = Json::Value(Json::arrayValue);
        }
        istream.close();
    }
    // Parse collected commands
    for (auto &command : cache->commands) {
        Json::Value object;
        if (reader.parse(command, object) && object.isObject()) {
            allCommands.append(std::move(object));
        }
    }
    // Merge commands
    for (auto &command : allCommands) {
        auto &object = command;
        auto &iFile = object["file"];
        if (!iFile.isString()) {
            continue;
        }
        auto file = iFile.asString();
        auto entry = commands.emplace(commands.end(), object);
        auto it = fileCommands.find(file);
        if (it != fileCommands.end()) {
            commands.erase(it->second);
            it->second = entry;
        } else {
            fileCommands.emplace(file, entry);
        }
    }
    allCommands.clear();
    for (auto &command : commands) {
        allCommands.append(std::move(command));
    }
    // Write compile_commands.json
    std::ofstream stream(kCompileCommandsFile);
    auto writer = Json::StreamWriterBuilder().newStreamWriter();
    writer->write(allCommands, &stream);
    stream.close();
}

void Bear::Run(const Context *context, std::vector<std::string> extraArgs) {
    BearCache cache;
    Serve(&cache);
    Spawn(&cache, context, extraArgs);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    Save(&cache);
    exit(cache.status);
}

}