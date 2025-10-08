/**
 * @file md5.h
 * @brief MD5 hash algorithm implementation
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file contains a complete implementation of the MD5 message-digest algorithm
 * as specified in RFC 1321. The class provides incremental hash calculation.
 */

#pragma once

#include "core.h"

#include <array>
#include <cstdint>
#include <functional>
#include <utility>

namespace scanner {
/**
 * @class MD5
 * @brief MD5 hash algorithm implementation
 * 
 * @details
 * This class implements the MD5 algorithm for calculating 128-bit cryptographic hashes.
 * It supports incremental updates and can process data in chunks.
 */
class MD5 final {
public:
    /**
     * @brief Default constructor - initializes MD5 context
     */
    MD5() { };

    /**
     * @brief Updates the hash calculation with new data
     * @param data Pointer to the input data buffer
     * @param size Size of the input data in bytes
     */
    void update(const uint8_t *data, uint32_t size);

    /**
     * @brief Finalizes the hash calculation and returns the result
     * @return The final MD5 hash as a Hash object
     */
    Hash finish();

    /**
     * @brief Gets the current hash state
     * @return Current intermediate hash state
     */
    Hash get_state() const;

private:
    /**
     * @brief Processes a 512-bit block of data
     * @param data Pointer to the 512-bit data block
     */
    void process_block(const uint32_t *data);

    /**
     * @brief Performs a cyclic left shift operation
     * @param x Value to shift
     * @param s Number of bits to shift
     * @return The shifted value
     */
    constexpr inline uint32_t cicle_shift(uint32_t x, uint32_t s);

    /// MD5 logical functions F, G, H, I
    std::array<std::function<uint32_t(uint32_t, uint32_t, uint32_t)>, 4> func =
    {
        [](uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); },
        [](uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (~z & y); },
        [](uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; },
        [](uint32_t x, uint32_t y, uint32_t z) { return y ^ (~z | x); }
    };

    /// Index parameters for MD5 rounds
    std::array<std::pair<uint32_t, uint32_t>, 4> index_params = {{
        {1u, 0u}, {5u, 1u}, {3u, 5u}, {7u, 0u}
    }};

    /// MD5 shift constants
    static constexpr uint32_t s[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };

    /// MD5 sine constants
    static constexpr uint32_t t[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    const static uint32_t block_size{64u};  ///< MD5 block size in bytes

    /// MD5 initial state (A, B, C, D registers)
    uint32_t a{0x67452301};
    uint32_t b{0xefcdab89};
    uint32_t c{0x98badcfe};
    uint32_t d{0x10325476};

    uint64_t data_size{0ll};    ///< Total data size processed
    uint8_t buf[128];           ///< Input buffer for partial blocks
    uint32_t buf_size{0ul};     ///< Current size of data in buffer
};

} // namespace scanner
