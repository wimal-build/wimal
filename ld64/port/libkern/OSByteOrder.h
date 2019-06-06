#ifndef LD64_LIBKERN_OSBYTEORDER_H_
#define LD64_LIBKERN_OSBYTEORDER_H_

// https://github.com/apple/darwin-xnu/blob/master/libkern/libkern/OSByteOrder.h
// https://github.com/apple/darwin-xnu/blob/master/libkern/libkern/machine/OSByteOrder.h
#include <llvm/Support/Endian.h>

static inline uint16_t OSReadBigInt16(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read16be((uint8_t *) base + byteOffset);
}

static inline void OSWriteBigInt16(void *base, uintptr_t byteOffset, uint16_t data) {
    llvm::support::endian::write16be((uint8_t *) base + byteOffset, data);
}

static inline uint32_t OSReadBigInt32(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read32be((uint8_t *) base + byteOffset);
}

static inline void OSWriteBigInt32(void *base, uintptr_t byteOffset, uint32_t data) {
    llvm::support::endian::write32be((uint8_t *) base + byteOffset, data);
}

static inline uint64_t OSReadBigInt64(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read64be((uint8_t *) base + byteOffset);
}

static inline void OSWriteBigInt64(void *base, uintptr_t byteOffset, uint64_t data) {
    llvm::support::endian::write64be((uint8_t *) base + byteOffset, data);
}

static inline uint16_t OSReadLittleInt16(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read16le((uint8_t *) base + byteOffset);
}

static inline void OSWriteLittleInt16(void *base, uintptr_t byteOffset, uint16_t data) {
    llvm::support::endian::write16le((uint8_t *) base + byteOffset, data);
}

static inline uint32_t OSReadLittleInt32(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read32le((uint8_t *) base + byteOffset);
}

static inline void OSWriteLittleInt32(void *base, uintptr_t byteOffset, uint32_t data) {
    llvm::support::endian::write32le((uint8_t *) base + byteOffset, data);
}

static inline uint64_t OSReadLittleInt64(const void *base, uintptr_t byteOffset) {
    return llvm::support::endian::read64le((uint8_t *) base + byteOffset);
}

static inline void OSWriteLittleInt64(void *base, uintptr_t byteOffset, uint64_t data) {
    llvm::support::endian::write64le((uint8_t *) base + byteOffset, data);
}

static inline uint16_t OSSwapHostToBigInt16(uint16_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint32_t OSSwapHostToBigInt32(uint32_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint64_t OSSwapHostToBigInt64(uint64_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint16_t OSSwapBigToHostInt16(uint16_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint32_t OSSwapBigToHostInt32(uint32_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint64_t OSSwapBigToHostInt64(uint64_t data) {
    return llvm::support::endian::byte_swap(data, llvm::support::endianness::big);
}

static inline uint16_t OSSwapInt16(uint16_t data) {
    return llvm::sys::getSwappedBytes(data);
}

static inline uint32_t OSSwapInt32(uint32_t data) {
    return llvm::sys::getSwappedBytes(data);
}

static inline uint64_t OSSwapInt64(uint64_t data) {
    return llvm::sys::getSwappedBytes(data);
}

#endif // LD64_LIBKERN_OSBYTEORDER_H_
