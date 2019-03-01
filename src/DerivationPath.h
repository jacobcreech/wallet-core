// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWPurpose.h>

#include <cstdint>
#include <string>
#include <vector>

namespace TW {

struct DerivationPathIndex {
    uint32_t value;
    bool hardened;

    DerivationPathIndex() : value(), hardened(true) {}
    DerivationPathIndex(uint32_t value, bool hardened = true) : value(value), hardened(hardened) {}

    /// The derivation index.
    uint32_t derivationIndex() const {
        if (hardened) {
            return value | 0x80000000;
        } else {
            return value;
        }
    }

    std::string string() const {
        if (hardened) {
            return std::to_string(value) + "'";
        } else {
            return std::to_string(value);
        }
    }
};

/// A BIP32 HD wallet derivation path.
struct DerivationPath {
    std::vector<DerivationPathIndex> indices;

    TWPurpose purpose() const {
        return static_cast<TWPurpose>(indices[0].value);
    }

    void setPurpose(TWPurpose v) {    
        indices[0] = DerivationPathIndex(v, /* hardened: */true);
    }

    TWCoinType coinType() const {
        return static_cast<TWCoinType>(indices[1].value);
    }

    void setCoinType(TWCoinType v) {
        indices[1] = DerivationPathIndex(v, /* hardened: */true);
    }

    uint32_t account() const {
        return indices[2].value;
    }

    void setAccount(uint32_t v) {
        indices[2] = DerivationPathIndex(v, /* hardened: */true);
    }

    uint32_t change() const {
        return indices[3].value;
    }

    void setChange(uint32_t v) {
        indices[3] = DerivationPathIndex(v, /* hardened: */false);
    }
    
    uint32_t address() const {
        return indices[4].value;
    }

    void setAddress(uint32_t v) {
        indices[4] = DerivationPathIndex(v, /* hardened: */false);
    }

    DerivationPath() = default;
    DerivationPath(std::vector<DerivationPathIndex> indices) : indices(indices) {}

    /// Creates a `DerivationPath` by components.
    DerivationPath(TWPurpose purpose, TWCoinType coinType, uint32_t account = 0, uint32_t change = 0, uint32_t address = 0) {
        indices = std::vector<DerivationPathIndex>(5);
        setPurpose(purpose);
        setCoinType(coinType);
        setAccount(account);
        setChange(change);
        setAddress(address);
    }

    /// Creates a derivation path with a string description like `m/10/0/2'/3`
    ///
    /// @throws std::invalid_argument if the string is not a valid derivation path.
    DerivationPath(const std::string& string);

    /// String representation.
    std::string string() const noexcept;
};

bool operator==(const DerivationPathIndex& lhs, const DerivationPathIndex& rhs) {
    return lhs.value == rhs.value && lhs.hardened == rhs.hardened;
}

bool operator==(const DerivationPath& lhs, const DerivationPath& rhs) {
    return std::equal(lhs.indices.begin(), lhs.indices.end(), rhs.indices.begin(), rhs.indices.end());
}

} // namespace
