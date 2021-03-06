// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import XCTest
import TrustWalletCore

class StellarTests: XCTestCase {

    func testAddressFromPrivateKey() {
        let key = PrivateKey(data: Data(hexString: "59a313f46ef1c23a9e4f71cea10fc0c56a2a6bb8a4b9ea3d5348823e5a478722")!)!
        let pubkey = key.getPublicKeyEd25519()
        let address = StellarAddress(publicKey: pubkey)

        XCTAssertEqual(pubkey.data.hexString, "0109A966BCAACC103E38896BAAE3F8C2F06C21FD47DD4F864FF0D33F9819DF5CA2".lowercased())
        XCTAssertEqual(address.description, "GAE2SZV4VLGBAPRYRFV2VY7YYLYGYIP5I7OU7BSP6DJT7GAZ35OKFDYI")
    }

    func testAddressFromPublicKey() {
        let pubkey = PublicKey(data: Data(hexString: "0303E20EC6B4A39A629815AE02C0A1393B9225E3B890CAE45B59F42FA29BE9668D")!)!
        let address = StellarAddress(publicKey: pubkey)

        XCTAssertEqual(address.description, "GAB6EDWGWSRZUYUYCWXAFQFBHE5ZEJPDXCIMVZC3LH2C7IU35FTI2NOQ")
    }
}
