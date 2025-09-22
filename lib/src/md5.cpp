#include "core.h"
#include "md5.h"

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

MD5::MD5() : data_size(0) {
    init_abcd();
    init_t_consts();
}

void MD5::update(const uint8_t *data, uint32_t size) {
    /// TODO: proces if size <= 64
    data_size += size * 8u;
    while (size >= 64u) {
        process_block(data);
        data += 64;
        size -= 64;
    }
    memcpy(buf.data.data(), data, size);
    buf.size = size;
}

Hash MD5::finish() {
    buf.data[buf.size++] = 0x80;
    while ((buf.size & 0b111111) != 56) {
        buf.data[buf.size++] = 0u;
    }
    std::memcpy(buf.data.data() + buf.size, &data_size, sizeof(data_size));
    buf.size += 8u;
    assert(buf.size == 64 || buf.size == 128);
    process_block(buf.data.data());
    if (buf.size > block_size) {
        process_block(buf.data.data() + block_size);
    }
    return get_state();
}

Hash MD5::get_state() const {
    std::ostringstream result;
    result << std::hex << std::setfill('0');

    auto append_hash = [&result](uint32_t val) {
        for (int i = 0; i < 4; ++i) {
            result << std::setw(2) << ((val >> (8 * i)) & 0xff);
        }
    };

    append_hash(a);
    append_hash(b);
    append_hash(c);
    append_hash(d);

    return result.str();
}

void MD5::process_block(const uint8_t *data) {
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

void MD5::init_abcd() {
    a = 0x67452301; b = 0xefcdab89; c = 0x98badcfe; d = 0x10325476;
}

void MD5::init_t_consts() {
    for (uint32_t i{0}; i < block_size; ++i) {
        t[i] = static_cast<uint32_t>(
            std::floor(4294967296.0 * std::abs(std::sin(i + 1)))
        );
    }
}

uint32_t MD5::cicle_shift(uint32_t x, uint32_t s) {
    return (x << s) | (x >> (32u - s));
}

} // namespace scanner
