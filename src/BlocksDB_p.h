/*
 * This file is part of the bitcoin-classic project
 * Copyright (C) 2017 Tom Zander <tomz@freedommail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITCOIN_BLOCKCHAIN_BLOCK_P_H
#define BITCOIN_BLOCKCHAIN_BLOCK_P_H

#include "chain.h"

#include <list>

class CBlockIndex;

namespace Blocks {

class DBPrivate {
public:
    DBPrivate();

    void updateUahfProperties();

    bool isReindexing;

    CChain headersChain;
    std::list<CBlockIndex*> headerChainTips;
    CBlockIndex *uahfStartBlock;

    std::vector<std::string> blocksDataDirs;
};
}

#endif
