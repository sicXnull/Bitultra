// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2b;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0x1e;
        pchMessageStart[3] = 0x41;
        vAlertPubKey = ParseHex("04c835a84cabc3f0fc10b9b7f5ac4ccfbc1634ae706d9181e83ccef89033ec7d9f3345786fd097bad12a8d980904ac55dbc95b48d332db406fb941d0ba5f45c4f2");
        nDefaultPort = 28654;
        nRPCPort = 28655;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9

        const char* pszTimestamp = "CoinTelegraph.com 6/30/2018 Recently Found Double Spending Vulnerability Is Not Tether’s Own, SlowMist Confirms";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1518608600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1530423552; //GMT: Wed, 14 Feb 2018 11:43:20 GMT
        genesis.nBits    = 520159231;//0x1f00ffff;
        genesis.nNonce   = 66576;

        //Generating genesis block. QT GUI segfaults if this is enabled
        /*genesis.nNonce   = 0;
        do {
            genesis.nNonce++;
            hashGenesisBlock = genesis.GetHash();
        } while(hashGenesisBlock > uint256("0x0001000000000000000000000000000000000000000000000000000000000000"));
        LogPrintStr("txNew:\n\n");
        LogPrintStr(txNew.ToString());
        LogPrintStr("\n\n");
        LogPrintStr("hashGenesisBlock:\n\n");
        LogPrintStr(hashGenesisBlock.ToString());
        LogPrintStr("\n\n");
        LogPrintStr("genesis:\n\n");
        LogPrintStr(genesis.ToString());
        //End generating genesis block*/

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000017d86a3f8b614c4db3284c69f238e75af3d8642cab63cb8ba48f1995f839"));
        assert(genesis.hashMerkleRoot == uint256("0x7786a6b34bc883f789bf523fde032da4729cb7f33ff232676ee2c9892f981314"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,26);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,111);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,95);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("149.28.236.13",  "149.28.236.13"));
        vSeeds.push_back(CDNSSeedData("140.82.61.65",  "140.82.61.65"));
		
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "BhTQDopxuQQ15ho3GV64kBcWtFbBUwqMhP";
        nLastPOWBlock = 100;
        nPOSStartBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2b;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x12;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04ff8ce7e878068bcacc543e295f7937aa417468898928ebe7b34886dd63dbecc2161dc9a6d172e0df34168b4d2c0188f5b451bf6ef4d278a14ae05eff95d5c8eb");
        nDefaultPort = 28650;
        nRPCPort = 28651;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 0x1f00ffff;
        genesis.nNonce = 0;

        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,131);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,120);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,94);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
