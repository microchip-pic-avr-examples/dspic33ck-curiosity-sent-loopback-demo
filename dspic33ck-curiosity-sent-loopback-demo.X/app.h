/* 
 * File:   app.h
 * Author: X54054
 *
 * Created on July 27, 2022, 3:21 PM
 */

#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "mcc_generated_files/sent_tx/sent_tx_types.h"
#include "mcc_generated_files/sent_tx/sent1.h"
#include "mcc_generated_files/sent_rx/sent2.h"

void SENT_TxRxInitialization();
bool compare(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata);
bool SENT_AsynchronousTxandRx();
bool SENT_SynchronousTxandRx() 

#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */

