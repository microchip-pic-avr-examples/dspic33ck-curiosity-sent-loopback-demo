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


#define FCY CLOCK_SystemFrequencyGet()

const volatile struct SENT_TRANSMIT_INTERFACE *sentTx = &SENT_Transmitter;
const volatile struct SENT_RECEIVE_INTERFACE *sentRx = &SENT_Receiver;

//Functions
void SENT_TxRxInitialization();
void SENT_TxRxDeInitialization();
bool SENT_TransmitReceive();
bool SENT_WaitForTransmissionComplete(bool *result);
bool SENT_WaitForReceptionComplete(bool *result);
bool compare(struct SENT_DATA_TRANSMIT *txdata, struct SENT_DATA_RECEIVE *rxdata);
bool waitForCallbackTimeout(bool (*handler)(bool *status), uint32_t timeOut);

static bool softTimeOut(uint32_t intVal);
static bool (*callbackResponseWaitHandler)(bool *status) = NULL;

//Enums
enum SENT_STATE{
    SENT_START_STATE = 0,
    SENT_ASYNC_STATE = 1,
    SENT_SYNC_STATE = 2,
    SENT_DEINIT_STATE = 3,
    SENT_EXIT_STATE = 4,
};

/*
    Main application
*/
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
                //Start State
                printf("#########################################\r\n");
                printf("           SENT LOOPBACK DEMO            \r\n");
                printf("#########################################\r\n");
                __delay32(10000);
                current_state = SENT_ASYNC_STATE;
                break;
            case SENT_ASYNC_STATE:
                //Async State
               sentTx->TransmitModeSet(SENT_TRANSMIT_ASYNCHRONOUS);  //Set Transmit Mode to ASYNCHRONOUS
               sent_status = SENT_TransmitReceive(); //SENT Transmit & Receive 
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Asynchronous Communication Success\r\n") : printf("SENT Asynchronous Communication Unsuccessful\r\n"); 
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_SYNC_STATE;
               sent_status = false;             
               break;
           case SENT_SYNC_STATE:
               //Sync State
               sentTx->TransmitModeSet(SENT_TRANSMIT_SYNCHRONOUS); //Set Transmit Mode to SYNCHRONOUS
               sent_status = SENT_TransmitReceive(); //SENT Transmit & Receive 
               sent_status ? UserLEDGreen_SetHigh() : UserLEDRed_SetHigh();
               sent_status ? printf("SENT Synchronous Communication Success\r\n") : printf("SENT Synchronous Communication Unsuccessful\r\n");
               printf("------------------------------------------\r\n\r\n");
               current_state = SENT_DEINIT_STATE;
               sent_status = false;
               break;
           case SENT_DEINIT_STATE:
               //Deinit State
               SENT_TxRxDeInitialization();
               current_state = SENT_EXIT_STATE;
               printf("SENT De-Initialization Successful\r\n");
               printf("#########################################\r\n");
               break;
            case SENT_EXIT_STATE:
                //Exit State
                break;    
            default:
                //Default State
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

bool SENT_TransmitReceive()
{
    bool result = false;
    bool txCompleteFlag = false;
    bool rxCompleteFlag = false;
    
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
    
    txCompleteFlag = waitForCallbackTimeout(&SENT_WaitForTransmissionComplete,2000);
    rxCompleteFlag = waitForCallbackTimeout(&SENT_WaitForReceptionComplete,2000);
    
    __delay32(1000);
    
    if((txCompleteFlag & rxCompleteFlag) == true)
    {
        sentDataReceive = sentRx->Receive();
        result = compare(&sentDataTransmit, &sentDataReceive);
    
        return result;
    }

    return result;
}

bool SENT_WaitForTransmissionComplete(bool *result)
{
    if(sentTx->IsTransmissionComplete() == true)
    {
        *result = true;
        return true;
    }
    return false;
}

bool SENT_WaitForReceptionComplete(bool *result)
{
    if(sentRx->IsDataReceived() == true)
    {
        *result = true;
        return true;
    }
    return false;
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