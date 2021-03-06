// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWCoinType.h>

#include "../Coin.h"

enum TWPurpose TWCoinTypePurpose(enum TWCoinType coin) {
    return TW::purpose(coin);
}

enum TWCurve TWCoinTypeCurve(enum TWCoinType coin) {
    return TW::curve(coin);
}

bool TWCoinTypeValidate(enum TWCoinType coin, TWString *_Nonnull address) {
    return TW::validateAddress(coin, *reinterpret_cast<const std::string*>(address));
}

TWString *_Nonnull TWCoinTypeDerivationPath(enum TWCoinType coin) {
    const auto path = TW::derivationPath(coin);
    const auto string = path.string();
    return TWStringCreateWithUTF8Bytes(string.c_str());
}

TWString *_Nonnull TWCoinTypeDeriveAddress(enum TWCoinType coin, struct TWPrivateKey *_Nonnull privateKey) {
    const auto string = TW::deriveAddress(coin, privateKey->impl);
    return TWStringCreateWithUTF8Bytes(string.c_str());
}
