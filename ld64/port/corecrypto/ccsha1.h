#ifndef LD64_CORECRYPTO_CCSHA1_H_
#define LD64_CORECRYPTO_CCSHA1_H_

#include <openssl/sha.h>

#include "ccdigest.h"

static void ccsha1_init(struct ccdigest_ctx *ctx_) {
    SHA_CTX *ctx = (SHA_CTX *) ctx_;
    SHA1_Init(ctx);
}

static void ccsha1_update(struct ccdigest_ctx *ctx_, size_t size, const void *data) {
    SHA_CTX *ctx = (SHA_CTX *) ctx_;
    SHA1_Update(ctx, (const uint8_t *) data, size);
}

static void ccsha1_final(struct ccdigest_ctx *ctx_, void *digest) {
    SHA_CTX *ctx = (SHA_CTX *) ctx_;
    SHA1_Final(ctx, digest);
}

static const struct ccdigest_info ccsha1_info = {
    sizeof(SHA_CTX),
    ccsha1_init,
    ccsha1_update,
    ccsha1_final
};

static const struct ccdigest_info *ccsha1_di(void) {
    return &ccsha1_info;
}

#endif // LD64_CORECRYPTO_CCSHA1_H_
