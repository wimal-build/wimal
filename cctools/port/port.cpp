extern "C" const char apple_version[] = "cctools-921";

#ifndef __APPLE__
#include <mach/mach.h>

#define EMULATED_HOST_CPU_TYPE 16777223
#define EMULATED_HOST_CPU_SUBTYPE 3

kern_return_t host_info(
    host_t host,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
) {
    if (flavor == HOST_BASIC_INFO) {
        host_basic_info_t basic_info;

        basic_info = (host_basic_info_t) host_info_out;
        memset(basic_info, 0x00, sizeof(*basic_info));
        basic_info->cpu_type = EMULATED_HOST_CPU_TYPE;
        basic_info->cpu_subtype = EMULATED_HOST_CPU_SUBTYPE;
    }

    return 0;
}

host_name_port_t mach_host_self(void) {
    return 0;
}

mach_port_t mach_task_self(void) {
    return 0;
}

kern_return_t vm_allocate(
    vm_map_t target_task,
    vm_address_t *address,
    vm_size_t size,
    int anywhere
) {
    vm_address_t addr = 0;
    addr = (vm_address_t) calloc(size, sizeof(char));
    if (addr == 0) {
        return 1;
    }
    *address = addr;
    return 0;
}

kern_return_t vm_deallocate(vm_map_t target_task, vm_address_t address, vm_size_t size) {
    return 0;
}

kern_return_t mach_port_deallocate(ipc_space_t task, mach_port_name_t name) {
    return 0;
}

// _NSGetExecutablePath
#include <mach-o/dyld.h>
#include <sys/types.h> // for sysctl
#include <sys/sysctl.h> // for sysctl
#include <unistd.h> // for access / readlink

int _NSGetExecutablePath(char *epath, unsigned int *size) {
#if defined(__FreeBSD__) || defined(__DragonFly__)
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PATHNAME;
    mib[3] = -1;
    size_t cb = *size;
    if (sysctl(mib, 4, epath, &cb, NULL, 0) != 0) {
        return -1;
    }
    *size = cb;
    return 0;
#elif defined(__OpenBSD__)
    int mib[4];
    char **argv;
    size_t len;
    const char *comm;
    int ok = 0;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC_ARGS;
    mib[2] = getpid();
    mib[3] = KERN_PROC_ARGV;
    if (sysctl(mib, 4, NULL, &len, NULL, 0) < 0) {
        abort();
    }
    if (!(argv = malloc(len))) {
        abort();
    }
    if (sysctl(mib, 4, argv, &len, NULL, 0) < 0) {
        abort();
    }
    comm = argv[0];
    if (*comm == '/' || *comm == '.') {
        char *rpath;
        if ((rpath = realpath(comm, NULL))) {
          strlcpy(epath, rpath, *size);
          free(rpath);
          ok = 1;
        }
    } else {
        char *sp;
        char *xpath = strdup(getenv("PATH"));
        char *path = strtok_r(xpath, ":", &sp);
        struct stat st;
        if (!xpath) {
            abort();
        }
        while (path) {
            snprintf(epath, *size, "%s/%s", path, comm);
            if (!stat(epath, &st) && (st.st_mode & S_IXUSR)) {
                ok = 1;
                break;
            }
            path = strtok_r(NULL, ":", &sp);
        }
        free(xpath);
    }
    free(argv);
    if (ok) {
        *size = strlen(epath);
        return 0;
    }
    return -1;
#else
    int bufsize = *size;
    int ret_size;
    ret_size = readlink("/proc/self/exe", epath, bufsize - 1);
    if (ret_size != -1) {
        *size = ret_size;
        epath[ret_size] = 0;
        return 0;
    } else {
        return -1;
    }
#endif
}

__BEGIN_DECLS
// https://www.freebsd.org/cgi/man.cgi?query=strmode
extern void strmode(mode_t mode, char *bp);
__END_DECLS

void strmode(mode_t mode, char *p) {
    switch (mode & S_IFMT) {
        case S_IFDIR:
            *p++ = 'd';
            break;
        case S_IFCHR:
            *p++ = 'c';
            break;
        case S_IFBLK:
            *p++ = 'b';
            break;
        case S_IFREG:
            *p++ = '-';
            break;
        case S_IFLNK:
            *p++ = 'l';
            break;
        case S_IFSOCK:
            *p++ = 's';
            break;
#ifdef S_IFIFO
        case S_IFIFO:
            *p++ = 'p';
            break;
#endif
#ifdef S_IFWHT
        case S_IFWHT:
        *p++ = 'w';
        break;
#endif
        default:
            *p++ = '?';
            break;
    }
    if (mode & S_IRUSR) {
        *p++ = 'r';
    } else {
        *p++ = '-';
    }
    if (mode & S_IWUSR) {
        *p++ = 'w';
    } else {
        *p++ = '-';
    }
    switch (mode & (S_IXUSR | S_ISUID)) {
        case 0:
            *p++ = '-';
            break;
        case S_IXUSR:
            *p++ = 'x';
            break;
        case S_ISUID:
            *p++ = 'S';
            break;
        case S_IXUSR | S_ISUID:
            *p++ = 's';
            break;
    }
    if (mode & S_IRGRP) {
        *p++ = 'r';
    } else {
        *p++ = '-';
    }
    if (mode & S_IWGRP) {
        *p++ = 'w';
    } else {
        *p++ = '-';
    }
    switch (mode & (S_IXGRP | S_ISGID)) {
        case 0:
            *p++ = '-';
            break;
        case S_IXGRP:
            *p++ = 'x';
            break;
        case S_ISGID:
            *p++ = 'S';
            break;
        case S_IXGRP | S_ISGID:
            *p++ = 's';
            break;
    }
    if (mode & S_IROTH) {
        *p++ = 'r';
    } else {
        *p++ = '-';
    }
    if (mode & S_IWOTH) {
        *p++ = 'w';
    } else {
        *p++ = '-';
    }
    switch (mode & (S_IXOTH | S_ISVTX)) {
        case 0:
            *p++ = '-';
            break;
        case S_IXOTH:
            *p++ = 'x';
            break;
        case S_ISVTX:
            *p++ = 'T';
            break;
        case S_IXOTH | S_ISVTX:
            *p++ = 't';
            break;
    }
    *p++ = ' ';
    *p = '\0';
}

#endif // __APPLE__
