#pragma once

#include "core.h"

#include <array>
#include <cstdint>
#include <functional>
#include <utility>

namespace scanner {

class MD5 final {
public:
    struct Buffer {
        std::array<uint8_t, 128> data;
        uint32_t size{0};
    };

    MD5();

    void update(const uint8_t *data, uint32_t size);

    Hash finish();

    Hash get_state() const;

private:
    void process_block(const uint8_t *data);

    void init_abcd();

    void init_t_consts();

    static uint32_t cicle_shift(uint32_t x, uint32_t s);

    std::array<std::function<uint32_t(uint32_t, uint32_t, uint32_t)>, 4> func =
    {
        [](uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); },
        [](uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (~z & y); },
        [](uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; },
        [](uint32_t x, uint32_t y, uint32_t z) { return y ^ (~z | x); }
    };

    std::array<std::pair<uint32_t, uint32_t>, 4> index_params = {{
        {1u, 0u}, {5u, 1u}, {3u, 5u}, {7u, 0u}
    }};

    const uint32_t s[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };

    const static uint32_t block_size{64u};

    uint32_t t[64];
    uint32_t a{0};
    uint32_t b{0};
    uint32_t c{0};
    uint32_t d{0};

    uint64_t data_size{0};
    Buffer buf;
};

} // namespace scanner
