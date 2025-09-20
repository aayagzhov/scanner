#pragma once

#include "core.h"

#include <unordered_map>
#include <string>

namespace scanner {

class Base final {
public:
    explicit Base(const std::string &file) {
        /// TODO: read base from file;
    }

    bool find_hash(const Hash &hash) const {
        return data.count(hash);
    }

    Verdict get_verdict(const Hash &hash) const {
        if (data.count(hash)) {
            return data.at(hash);
        }
        return "";
    }

private:
    std::unordered_map<Hash, Verdict> data;
};

} // namespace scanner
