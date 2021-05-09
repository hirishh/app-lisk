//
// Created by andrea on 09/12/18.
//
#include "../../../io.h"
#include "../old_signTx.h"

#ifndef PROJECT_CREATEMULTISIG_H
#define PROJECT_CREATEMULTISIG_H

void tx_init_multisig();
void tx_chunk_multisig(uint8_t * data, uint8_t length, commPacket_t *sourcePacket, transaction_t *tx);
void tx_end_multisig(transaction_t *tx);

#endif //PROJECT_CREATEMULTISIG_H
