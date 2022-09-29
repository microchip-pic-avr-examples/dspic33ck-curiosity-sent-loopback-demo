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
#include <p33CK256MP508.h>

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/sent_tx/sent1.h"
#include "mcc_generated_files/sent_rx/sent2.h"

//Structure Variables
const volatile struct SENT_TRANSMIT_INTERFACE *sentTx = &SENT_Transmitter;
const volatile struct SENT_RECEIVE_INTERFACE *sentRx = &SENT_Receiver;
struct SENT_DATA_TRANSMIT sentDataTransmit;
struct SENT_DATA_RECEIVE sentDataReceive;

//Functions
void SENT_TxRxInitialization();
void SENT_TxRxDeInitialization();
void SENT_AsyncPayloadConfiguration();
bool SENT_AsyncTransmitReceive();
bool SENT_SyncTransmitReceive();

bool printPayloadData(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata);
bool compare(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata);
bool waitForCallbackTimeout(bool (*handler)(bool *status), uint32_t timeOut);

static bool softTimeOut(uint32_t intVal);
static bool (*callbackResponseWaitHandler)(bool *status) = NULL;

void TxComplete_CB();
void RxComplete_CB();

//Variables
bool isTxCompleteFlag = false;
bool isRxCompleteFlag = false;

//Enums
enum SENT_STATE{
    SENT_INIT_STATE = 0,
    SENT_ASYNC_STATE = 1,
    SENT_SYNC_STATE = 2,
    SENT_DEINIT_STATE = 3,
    SENT_IDLE_STATE = 4,
};

/*
    Main application
*/
int main(void)
{
    bool sent_status = false;
    uint8_t current_state = (uint8_t)SENT_INIT_STATE;
    
    SYSTEM_Initialize();

    while(1)
    {
        switch(current_state) 
       {    
            case SENT_INIT_STATE:
                //Init State
                printf("#########################################\r\n");
                printf("           SENT LOOPBACK DEMO            \r\n");
                printf("#########################################\r\n\r\n");
                printf("SENT Initialization Successful\r\n");
                printf("------------------------------------------\r\n\r\n");
                SENT_TxRxInitialization();
                SENT_AsyncPayloadConfiguration();   //Set Payload Data for SENT (User Configurable)
                sentTx->TransmitCompleteCallbackRegister(&TxComplete_CB);   //Register Callback Function for Transmit Complete
                sentRx->ReceiveCompleteCallbackRegister(&RxComplete_CB);    //Register Callback Function for Receive Complete
                current_state = SENT_ASYNC_STATE;
                break;
            case SENT_ASYNC_STATE:
                //Async State
               sentTx->TransmitModeSet(SENT_TRANSMIT_ASYNCHRONOUS); //Set Transmit Mode to ASYNCHRONOUS
               sent_status = waitForCallbackTimeout(&SENT_AsyncTransmitReceive,100); //SENT Transmit & Receive 
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Asynchronous Communication Success\r\n") : printf("SENT Asynchronous Communication Unsuccessful\r\n"); 
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_SYNC_STATE;
               sent_status = false;   
               break;
           case SENT_SYNC_STATE:
               //Sync State
               SENT_TxRxInitialization();   //Initialize SENT again
               SENT_SyncPayloadConfiguration();  //Update new set of SENT Payload values (User Configurable)
               sentTx->TransmitModeSet(SENT_TRANSMIT_SYNCHRONOUS); //Set Transmit Mode to SYNCHRONOUS
               sent_status = waitForCallbackTimeout(&SENT_SyncTransmitReceive,100); //SENT Transmit & Receive 
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Synchronous Communication Success\r\n") : printf("SENT Synchronous Communication Unsuccessful\r\n");
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_DEINIT_STATE;
               sent_status = false;
               break;
           case SENT_DEINIT_STATE:
               //Deinit State
               SENT_TxRxDeInitialization();
               printf("SENT De-Initialization Successful\r\n");
               printf("------------------------------------------\r\n\r\n");
               printf("#########################################\r\n");
               current_state = SENT_IDLE_STATE;
               break;
            case SENT_IDLE_STATE:
                //Idle State
                break;    
            default:
                //Default State
                break;
       }
    }    
}

void TxComplete_CB()
{
    isTxCompleteFlag = true;
}

void RxComplete_CB()
{
    isRxCompleteFlag = true; 
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

void SENT_AsyncPayloadConfiguration()
{
    sentDataTransmit.status = 7;  //User Configurable
    sentDataTransmit.data1 = 1;   //User Configurable
    sentDataTransmit.data2 = 2;   //User Configurable
    sentDataTransmit.data3 = 3;   //User Configurable
    sentDataTransmit.data4 = 4;   //User Configurable
    sentDataTransmit.data5 = 5;   //User Configurable
    sentDataTransmit.data6 = 6;   //User Configurable
}

void SENT_SyncPayloadConfiguration()
{
    sentDataTransmit.status = 9;  //User Configurable
    sentDataTransmit.data1 = 6;   //User Configurable
    sentDataTransmit.data2 = 5;   //User Configurable
    sentDataTransmit.data3 = 4;   //User Configurable
    sentDataTransmit.data4 = 3;   //User Configurable
    sentDataTransmit.data5 = 2;   //User Configurable
    sentDataTransmit.data6 = 1;   //User Configurable
}

bool SENT_AsyncTransmitReceive(bool *result)
{
    sentTx->Transmit(&sentDataTransmit);
    
    if((isTxCompleteFlag && isRxCompleteFlag) == true)
    {
        sentDataReceive = sentRx->Receive();
        *result = compare(&sentDataTransmit, &sentDataReceive);
        printPayloadData(&sentDataTransmit, &sentDataReceive);
        isTxCompleteFlag = false;
        isRxCompleteFlag = false;
        return *result;
    }
    *result = false;
    return false;
}

bool SENT_SyncTransmitReceive(bool *result)
{
    
    bool isSyncTxComplete = false;
    bool isSyncRxComplete = false;
    sentTx->Transmit(&sentDataTransmit);

    isSyncTxComplete = sentTx->IsTransmissionComplete();
    isSyncRxComplete = sentRx->IsDataReceived();

    if((isSyncTxComplete && isSyncRxComplete) == true)
    {
        sentDataReceive = sentRx->Receive();
        *result = compare(&sentDataTransmit, &sentDataReceive);
        printPayloadData(&sentDataTransmit, &sentDataReceive);
        isSyncTxComplete = false;
        isSyncRxComplete = false;
        return *result;
    }
    *result = false;
    return false;
}

bool printPayloadData(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata)
{
    printf("-------------------------------------------------\r\n");
    printf("|  PAYLOAD   |   DATA SENT    |  DATA RECEIVED  |\r\n");
    printf("-------------------------------------------------\r\n");
    printf("|   Status   |       %u        |        %u        |\r\n",txdata->status, rxdata->status);
    printf("|   Data_1   |       %u        |        %u        |\r\n",txdata->data1, rxdata->data1);
    printf("|   Data_2   |       %u        |        %u        |\r\n",txdata->data2, rxdata->data2);
    printf("|   Data_3   |       %u        |        %u        |\r\n",txdata->data3, rxdata->data3);
    printf("|   Data_4   |       %u        |        %u        |\r\n",txdata->data4, rxdata->data4);
    printf("|   Data_5   |       %u        |        %u        |\r\n",txdata->data5, rxdata->data5);
    printf("|   Data_6   |       %u        |        %u        |\r\n",txdata->data6, rxdata->data6);
    printf("-------------------------------------------------\r\n\r\n");
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

static bool softTimeOut(uint32_t intVal)
{
    static uint32_t count = 0;
    
    if(count >= intVal)
    {
        count = 0;
        return true;
    }
    
    count++;
    return false;
}

bool waitForCallbackTimeout(bool (*handler)(bool *status), uint32_t timeOut)
{
    callbackResponseWaitHandler = handler;
    bool res = false;
    
    while(1) 
    {
        if(handler != NULL) {
            if(handler(&res) == true)
            {
                res = true;
                break;
            }
        } 
        else 
        {
            printf("[!] Did not registered test callback function...\r\n");
            break;
        }

        if(softTimeOut(timeOut) == true)
        {
            printf("[!] Timeout occurred!.Check your loopback connection.\r\n");
            break;
        }
    }

    return res;
}