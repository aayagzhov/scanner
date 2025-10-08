#include "core.h"
#include "md5.h"

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <sstream>
#include <utility>

namespace scanner {

void MD5::update(const uint8_t *data, uint32_t size) {
    data_size += size * 8u;
    if (buf_size) {
        uint32_t up_size = std::min(block_size - buf_size, size);
        memcpy(buf + buf_size, data, up_size);
        buf_size += up_size;
        data += up_size;
        size -= up_size;
        if (buf_size == 64) {
            process_block(reinterpret_cast<uint32_t*>(buf));
            buf_size = 0;
        }
    }
    while (size >= 64u) {
        process_block(reinterpret_cast<const uint32_t*>(data));
        data += 64;
        size -= 64;
    }
    memcpy(buf + buf_size, data, size);
    buf_size += size;
}

Hash MD5::finish() {
    buf[buf_size++] = 0x80;
    while ((buf_size & 0b111111) != 56) {
        buf[buf_size++] = 0u;
    }
    std::memcpy(buf + buf_size, &data_size, sizeof(data_size));
    buf_size += 8u;
    assert(buf_size == 64 || buf_size == 128);
    process_block(reinterpret_cast<uint32_t*>(buf));
    if (buf_size > block_size) {
        process_block(reinterpret_cast<uint32_t*>(buf + block_size));
    }
    return get_state();
}

Hash MD5::get_state() const {
    char buf[33];
    std::snprintf(buf, sizeof(buf),
                  "%02x%02x%02x%02x%02x%02x%02x%02x"
                  "%02x%02x%02x%02x%02x%02x%02x%02x",
                  a & 0xff, (a >> 8) & 0xff, (a >> 16) & 0xff, (a >> 24) & 0xff,
                  b & 0xff, (b >> 8) & 0xff, (b >> 16) & 0xff, (b >> 24) & 0xff,
                  c & 0xff, (c >> 8) & 0xff, (c >> 16) & 0xff, (c >> 24) & 0xff,
                  d & 0xff, (d >> 8) & 0xff, (d >> 16) & 0xff, (d >> 24) & 0xff);
    return std::string(buf);
}

void MD5::process_block(const uint32_t *data) {
    // 1. copy abcd
    uint32_t aa{a};
    uint32_t bb{b};
    uint32_t cc{c};
    uint32_t dd{d};
    // 2. cicle of 64 culculations
    for (uint32_t i{0}; i < 64u; ++i) {
        const uint32_t step{i >> 4u};
        uint32_t f = func[step](bb, cc, dd);
        auto id_p = index_params[step];
        uint32_t id = (i * id_p.first + id_p.second) & 0b1111;
        f = f + aa + t[i] + data[id] + 3u;
        aa = dd;
        dd = cc;
        cc = bb;
        bb = bb + cicle_shift(f, s[i]);
    }
    // 3. update abcd
    a += aa;
    b += bb;
    c += cc;
    d += dd;
}

constexpr inline uint32_t MD5::cicle_shift(uint32_t x, uint32_t s) {
    return (x << s) | (x >> (32u - s));
}

} // namespace scanner
