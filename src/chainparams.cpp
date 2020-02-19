// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <genesis.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>
#include <arith_uint256.h>
#include <pthread.h>

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit =            uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 2 * 60; // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 24-minutes
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 240; // 240 * 2 minutes
        consensus.nModifierInterval = 10 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 100;

        // POW block consensus
        consensus.nPOWBlockEpoch = 131400;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.superBlockHeight = 15;
        consensus.superBlockReward = 17500000 * COIN;
        consensus.nTotalPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nStartMiningTime = 1581519900;
        consensus.nDgwPastBlocks = 30;
        consensus.nDGWStartHeight = 3450;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00"); // 350000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");  // 380000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0xb4;
        vAlertPubKey = ParseHex("04454522d6253511a5ad9bd959213d6081c19a2349e7739a84812f8ac509ce7eec2f827de314bbae866e9ffc12f534de29fec5931768cad978db66ade63baa4425");
        nDefaultPort = 9166;

        genesis = CreateGenesisBlock(1581426196, 600035180, 0x1e0fffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("854d7df4269fab0078483472fa0291affc0a767e51194021e04810fa8476be7e"));
        assert(genesis.hashMerkleRoot == uint256S("4020bcd641786e479392ef0b55aa17c00c39818a188edf8262a2c1ba1be62707"));

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("35.223.108.1");
        vSeeds.emplace_back("35.239.55.103");
        vSeeds.emplace_back("35.228.0.233");
        vSeeds.emplace_back("34.70.76.24");

        base58Prefixes[PUBKEY_ADDRESS] = {0x42}; // T
        base58Prefixes[SCRIPT_ADDRESS] = {0x3c};
        base58Prefixes[SECRET_KEY]     = {0x6c};

        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // xpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // xprv

        // human readable prefix to bench32 address
        bech32_hrp = "ts";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nMiningRequiresPeers = 3;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("854d7df4269fab0078483472fa0291affc0a767e51194021e04810fa8476be7e")},
            }
        };

        chainTxData = ChainTxData{
                // Data as of block ???
                0, // * UNIX timestamp of last known number of transactions
                0,     // * total number of transactions between genesis and that timestamp
                //   (the tx=... number in the SetBestChain debug.log lines)
                0 // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 2 * 60;  // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 24-minute
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 20; // test net min age is 200 confirms
        consensus.nModifierInterval = 10 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 10; // 50 confirmations

        // POW block consensus
        consensus.nPOWBlockEpoch = 200;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.superBlockHeight = 15;
        consensus.superBlockReward = 17500000 * COIN;
        consensus.nTotalPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nStartMiningTime = 1581440700;
        consensus.nDgwPastBlocks = 30;
        consensus.nDGWStartHeight = 2000;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 6166;
        vAlertPubKey = ParseHex("045c9535c555d667389c9c66f6444c37e70de313eb9e2b15216a6712e988cc66ee80f222bacb8164bdd4d604b8fc4e0ca968c43a70f710dc4db024da2bf6bd4fad");

        genesis = CreateGenesisBlock(1581425194, 4194982813, 0x1f00ffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("fb6945d0c081953e96fb3e173b844e459d950e560840015b7f303b8fdf996332"));
        assert(genesis.hashMerkleRoot == uint256S("3326e86c24cc19b4309d35d1190a688a7163afb9db9aacce90889ef174720e08"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("35.223.108.1");
        vSeeds.emplace_back("35.239.55.103");
        vSeeds.emplace_back("35.228.0.233");
        vSeeds.emplace_back("34.70.76.24");

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        // human readable prefix to bench32 address
        bech32_hrp = "tst";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        nMiningRequiresPeers = 2;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
                {
                        {0, uint256S("fb6945d0c081953e96fb3e173b844e459d950e560840015b7f303b8fdf996332")},
            }
        };

        chainTxData = ChainTxData{
                0,
                0,
                0
        };

    }
};

/**
 * Regression test
 */

class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.powLimit =            uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.nTargetTimespan = 3 * 24 * 60 * 60; // two weeks
        consensus.nStakeTargetSpacing = 2 * 60; // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 2-hour
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 2; // test net min age is 1 day
        consensus.nModifierInterval = 2 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 2;

        // POW block consensus
        consensus.nPOWBlockEpoch = 5;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.superBlockHeight = 2;
        consensus.superBlockReward = 17500000 * COIN;
        consensus.nTotalPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nStartMiningTime = 1581514320;
        consensus.nDgwPastBlocks = 30;
        consensus.nDGWStartHeight = 2000;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 3166;
        vAlertPubKey = ParseHex("045c9535c555d667389c9c66f6444c37e70de313eb9e2b15216a6712e988cc66ee80f222bacb8164bdd4d604b8fc4e0ca968c43a70f710dc4db024da2bf6bd4fad");

        genesis = CreateGenesisBlock(1565755822, 9443, 0x1f00ffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("123d7466cd1a465d0f18e1c34c967733e4827fd01bbc61144b86cca75613e1bc"));
        assert(genesis.hashMerkleRoot == uint256S("6d456c58908944c3c2a4fac345c8ab1501a9f392f2930661fe9f9ba916106379"));


        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        checkpointData = {
            {
                {0, uint256S("123d7466cd1a465d0f18e1c34c967733e4827fd01bbc61144b86cca75613e1bc")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        bech32_hrp = "tsrt";

        nMiningRequiresPeers = 0;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
    }
};

static std::unique_ptr <CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr <CChainParams> CreateChainParams(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
