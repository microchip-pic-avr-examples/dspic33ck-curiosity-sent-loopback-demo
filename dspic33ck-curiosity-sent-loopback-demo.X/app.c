#include "app.h"
#include "xc.h"
#include <libpic30.h>
#define FCY CLOCK_SystemFrequencyGet()

const volatile struct SENT_TRANSMIT_INTERFACE *sentTx = &SENT_Transmitter;
const volatile struct SENT_RECEIVE_INTERFACE *sentRx = &SENT_Receiver;
bool txComplete, rxComplete;

void IsTxComplete()
{
    txComplete = true;
}

void IsRxComplete()
{
    rxComplete = true;
}

bool compare(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata)
{
    bool status = true;
    if (txdata->status != rxdata->status) {
        status = false;
    }
    
    if (txdata->data1 != rxdata->data1) {
        status = false;
    }
    
    if (txdata->data2 != rxdata->data2) {
        status = false;
    }
    
    if (txdata->data3 != rxdata->data3) {
        status = false;
    }
    
    if (txdata->data4 != rxdata->data4) {
        status = false;
    }
    
    if (txdata->data5 != rxdata->data5) {
        status = false;
    }
    
    if (txdata->data6 != rxdata->data6) {
        status = false;
    }
    
    return status;
}

void SENT_TxRxInitialization()
{
    sentTx->Initialize();
    sentRx->Initialize();
}

bool SENT_AsynchronousTxandRx()
{
    bool result = false;
    struct SENT_DATA_TRANSMIT sentDataTransmit;
    struct SENT_DATA_RECEIVE sentDataReceive;
//    sentTx->TransmitCompleteCallbackRegister(&IsTxComplete);
//    sentRx->ReceiveCompleteCallbackRegister(&IsRxComplete);
    sentDataTransmit.status = 7;
    sentDataTransmit.data1 = 1;
    sentDataTransmit.data2 = 2;
    sentDataTransmit.data3 = 3;
    sentDataTransmit.data4 = 4;
    sentDataTransmit.data5 = 5;
    sentDataTransmit.data6 = 6;

    sentTx->Transmit(&sentDataTransmit);
    
    while (sentTx->IsTransmissionComplete() == false);
    while (sentRx->IsDataReceived() == false);

    sentDataReceive = sentRx->Receive();
    result = compare(&sentDataTransmit, &sentDataReceive);

    return result;
}
//
//bool SENT_SynchronousTxandRx() 
//{
//    struct SENT_DATA_TRANSMIT sentDataTransmit;
//    struct SENT_DATA_RECEIVE sentDataReceive;
//
//    sentDataTransmit.status = 2;
//    sentDataTransmit.data1 = 1;
//    sentDataTransmit.data2 = 2;
//    sentDataTransmit.data3 = 3;
//    sentDataTransmit.data4 = 4;
//    sentDataTransmit.data5 = 5;
//    sentDataTransmit.data6 = 6;
//
//    sentTx->TransmitModeSet(SENT_TRANSMIT_SYNCHRONOUS);
//    sentTx->Transmit(&sentDataTransmit);
//    while (sentTx->IsTransmissionComplete() == false);
//    while (sentRx->IsDataReceived() == false);
//    sentDataReceive = sentRx->Receive();
//    
//    return compare(&sentDataTransmit, &sentDataReceive);
//
//}
//
