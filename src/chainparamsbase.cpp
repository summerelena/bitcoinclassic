// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparamsbase.h"

#include "tinyformat.h"
#include "util.h"

#include <assert.h>

const std::string CBaseChainParams::MAIN = "main";
const std::string CBaseChainParams::TESTNET = "test";
const std::string CBaseChainParams::FLEXTRANSTESTNET = "fttest";
const std::string CBaseChainParams::REGTEST = "regtest";

/**
 * Main network
 */
class CBaseMainParams : public CBaseChainParams
{
public:
    CBaseMainParams()
    {
        nRPCPort = 8332;
        nAdminServerPort = 1235;
    }
};
static CBaseMainParams mainParams;

/**
 * Testnet (v3)
 */
class CBaseTestNetParams : public CBaseChainParams
{
public:
    CBaseTestNetParams()
    {
        nRPCPort = 18332;
        nAdminServerPort = 11235;
        strDataDir = "testnet3";
    }
};
static CBaseTestNetParams testNetParams;

/**
 * Testnet (flextrans)
 */
class CBaseFTTestNetParams : public CBaseChainParams
{
public:
    CBaseFTTestNetParams()
    {
        nRPCPort = 18334;
        nAdminServerPort = 11236;
        strDataDir = "testnet-ft";
    }
};
static CBaseFTTestNetParams ftTestNetParams;

/*
 * Regression test
 */
class CBaseRegTestParams : public CBaseChainParams
{
public:
    CBaseRegTestParams()
    {
        nRPCPort = 18332;
        nAdminServerPort = 11235;
        strDataDir = "regtest";
    }
};
static CBaseRegTestParams regTestParams;

static CBaseChainParams* pCurrentBaseParams = 0;

const CBaseChainParams& BaseParams()
{
    assert(pCurrentBaseParams);
    return *pCurrentBaseParams;
}

CBaseChainParams& BaseParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::FLEXTRANSTESTNET)
        return ftTestNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectBaseParams(const std::string& chain)
{
    pCurrentBaseParams = &BaseParams(chain);
}

std::string ChainNameFromCommandLine()
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);
    bool fFTTestNet = GetBoolArg("-testnet-ft", false);

    if ((fTestNet?1:0) + (fRegTest?1:0) + (fFTTestNet?1:0) > 1)
        throw std::runtime_error("Invalid combination of -regtest and/or -testnet and/or -testnet-ft.");
    if (fRegTest)
        return CBaseChainParams::REGTEST;
    if (fTestNet)
        return CBaseChainParams::TESTNET;
    if (fFTTestNet)
        return CBaseChainParams::FLEXTRANSTESTNET;
    return CBaseChainParams::MAIN;
}

bool AreBaseParamsConfigured()
{
    return pCurrentBaseParams != NULL;
}
