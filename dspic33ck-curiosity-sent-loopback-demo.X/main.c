/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <stdbool.h>
#include <libpic30.h>
#include <xc.h>

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/sent_tx/sent1.h"
#include "mcc_generated_files/sent_rx/sent2.h"


#define FCY CLOCK_SystemFrequencyGet()

const volatile struct SENT_TRANSMIT_INTERFACE *sentTx = &SENT_Transmitter;
const volatile struct SENT_RECEIVE_INTERFACE *sentRx = &SENT_Receiver;
/*
    Main application
*/

void SENT_TxRxInitialization();
void SENT_TxRxDeInitialization();
bool SENT_AsynchronousTxandRx();
bool SENT_SynchronousTxandRx();
bool compare(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata);

enum SENT_STATE{
    SENT_START_STATE = 0,
    SENT_ASYNC_STATE,
    SENT_SYNC_STATE,
    SENT_DEINIT_STATE,
    SENT_EXIT_STATE,
};

int main(void)
{
    bool sent_status = false;
    uint8_t current_state = (uint8_t)SENT_START_STATE;
    SYSTEM_Initialize();

    
    while(1)
    {
        switch(current_state) 
       {    
            case SENT_START_STATE:
                printf("#########################################\r\n");
                printf("           SENT LOOPBACK DEMO            \r\n");
                printf("#########################################\r\n");
                __delay32(10000);
                current_state = SENT_ASYNC_STATE;
                break;
            case SENT_ASYNC_STATE:
               sent_status = SENT_AsynchronousTxandRx();
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Asynchronous Success\r\n") : printf("SENT Asynchronous Unsuccessful\r\n");
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_SYNC_STATE;
               sent_status = false;             
               break;
           case SENT_SYNC_STATE:
               sent_status = SENT_SynchronousTxandRx();
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Synchronous Success\r\n") : printf("SENT Synchronous Unsuccessful\r\n");
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_DEINIT_STATE;
               sent_status = false;
               break;
           case SENT_DEINIT_STATE:
               SENT_TxRxDeInitialization();
               current_state = SENT_EXIT_STATE;
               printf("SENT DeInitialization Successful\r\n");
               printf("#########################################\r\n");
               break;
            case SENT_EXIT_STATE:
                break;    
       }
    }    
}

void SENT_TxRxInitialization()
{
    sentTx->Initialize();
    sentRx->Initialize();
}

void SENT_TxRxDeInitialization()
{
    sentTx->Deinitialize();
    sentRx->Deinitialize();
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

bool SENT_AsynchronousTxandRx()
{
    bool result = false;
    struct SENT_DATA_TRANSMIT sentDataTransmit;
    struct SENT_DATA_RECEIVE sentDataReceive;

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

bool SENT_SynchronousTxandRx() 
{
    bool result = false;
    struct SENT_DATA_TRANSMIT sentDataTransmit;
    struct SENT_DATA_RECEIVE sentDataReceive;

    sentDataTransmit.status = 2;
    sentDataTransmit.data1 = 1;
    sentDataTransmit.data2 = 2;
    sentDataTransmit.data3 = 3;
    sentDataTransmit.data4 = 4;
    sentDataTransmit.data5 = 5;
    sentDataTransmit.data6 = 6;

    sentTx->TransmitModeSet(SENT_TRANSMIT_SYNCHRONOUS);
    sentTx->Transmit(&sentDataTransmit);
    while (sentTx->IsTransmissionComplete() == false);
    while (sentRx->IsDataReceived() == false);
    
    sentDataReceive = sentRx->Receive();
    result = compare(&sentDataTransmit, &sentDataReceive);
    
    return result;

}