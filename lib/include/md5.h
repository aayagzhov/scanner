#pragma once

#include "core.h"

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <sstream>
#include <utility>

namespace scanner {

class MD5 final {
public:
    struct Remains {
        std::array<uint8_t, 64> data;
        uint32_t size{0};
    };

    MD5() : data_size(0) {
        init_abcd();
        init_t_consts();
    }

    void update(const uint8_t *data, uint32_t size) {
        /// TODO: proces if size <= 64
        data_size += size * 8u;
        while (size >= 64u) {
            process_block(data);
            data += 64;
            size -= 64;
        }
        memcpy(remains.data.data(), data, size);
        remains.size = size;
    }

    Hash finish() {
        std::array<uint8_t, block_size * 2> data;
        uint32_t size = remains.size;
        std::memcpy(data.data(), remains.data.data(), size);
        data[size++] = 0x80;
        while ((size & 0b111111) != 56) {
            data[size++] = 0u;
        }
        std::memcpy(data.data() + size, &data_size, sizeof(data_size));
        size += 8u;
        assert(size == 64 || size == 128);
        process_block(data.data());
        if (size > block_size) {
            process_block(data.data() + block_size);
        }
        return get_state();
    }

    Hash get_state() const {
        std::ostringstream result;
        result << std::hex << std::setfill('0');

        auto append_le32 = [&result](uint32_t val) {
            for (int i = 0; i < 4; ++i) {
                result << std::setw(2) << ((val >> (8 * i)) & 0xff);
            }
        };

        append_le32(a);
        append_le32(b);
        append_le32(c);
        append_le32(d);

        return result.str();
    }

private:
    void process_block(const uint8_t *data) {
        // 1. devide data to 16 word of 32 bits
        std::array<uint32_t, 16> words;
        for (uint32_t i{0}; i < block_size; i += 4) {
            std::memcpy(&words[i >> 2u], data + i, sizeof(uint32_t));
        }
        // 2. copy abcd
        uint32_t aa{a};
        uint32_t bb{b};
        uint32_t cc{c};
        uint32_t dd{d};
        // 3. cicle of 64 culculations
        for (uint32_t i{0}; i < 64u; ++i) {
            uint32_t f = func[i >> 4u](bb, cc, dd);
            auto id_p = index_params[i >> 4u];
            uint32_t id = (i * id_p.first + id_p.second) & 0b1111;
            f = f + aa + t[i] + words[id];
            aa = dd;
            dd = cc;
            cc = bb;
            bb = bb + cicle_shift(f, s[i]);
        }
        // 4. update abcd
        a += aa;
        b += bb;
        c += cc;
        d += dd;
    }

    void init_abcd() {
        a = 0x67452301; b = 0xefcdab89; c = 0x98badcfe; d = 0x10325476;
    }

    void init_t_consts() {
        for (uint32_t i{0}; i < block_size; ++i) {
            t[i] = static_cast<uint32_t>(
                std::floor(4294967296.0 * std::abs(std::sin(i + 1)))
            );
        }
    }

    uint32_t cicle_shift(uint32_t x, uint32_t s) {
        return (x << s) | (x >> (32u - s));
    }

    std::array<std::function<uint32_t(uint32_t, uint32_t, uint32_t)>, 4> func = {
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
    Remains remains;
};

} // namespace scanner
