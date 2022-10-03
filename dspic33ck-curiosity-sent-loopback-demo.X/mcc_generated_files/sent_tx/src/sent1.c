/**
 * SENT1 Generated Driver Source File
 * 
 * @file      sent1.c
 *            
 * @ingroup   senttxdriver
 *            
 * @brief     This is the generated driver source file for SENT1 driver
 *            
 * @version   Driver Version 1.1.1
 *            
 * @skipline  Device : dsPIC33CK256MP508
*/


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

// Section: Included Files

#include <stddef.h>
#include "../sent1.h"

// Section: File specific functions

void (*SENT1_TransmitCompleteHandler)(void) = NULL;
void (*SENT1_ErrorHandler)(void) = NULL;

// Section: Data Type Definitions

static volatile bool bDataTransmitted = 1;

// Section: Driver Interface
const struct SENT_TRANSMIT_INTERFACE SENT_Transmitter = {
    .Initialize             = &SENT1_Initialize,
    .Deinitialize           = &SENT1_Deinitialize,
    .Enable                 = &SENT1_Enable,
    .Disable                = &SENT1_Disable,
    .TransmitModeSet        = &SENT1_TransmitModeSet,
    .Transmit = &SENT1_Transmit,
    .IsTransmissionComplete = &SENT1_IsTransmissionComplete,
    .TransmitStatusGet      = &SENT1_TransmitStatusGet,
    .TransmitCompleteCallbackRegister = &SENT1_TransmitCompleteCallbackRegister,
    .ErrorCallbackRegister = &SENT1_ErrorCallbackRegister,
    .Tasks                  = NULL,
};

// Section: SENT1 Module APIs

void SENT1_Initialize(void)
{
    // PPP disabled; TXPOL Inverted; SNTSIDL disabled; PS Divide-by-1; SNTEN disabled; SPCEN disabled; TXM Asynchronous; CRCEN enabled; RCVEN Transmitter; NIBCNT 6; 
    SENT1CON1 = 0x306;
    // SENTCON2 11; 
    SENT1CON2 = 0xB;
    // SENTCON3 0x0; 
    SENT1CON3 = 0x0;
    // clear the rx/tx interrupt flag
    IFS5bits.SENT1IF = 0;
    // enable the rx/tx interrupt
    IEC5bits.SENT1IE = 1;
    // clear the error interrupt flag
    IFS5bits.SENT1EIF = 0;
    // enable the error interrupt
    IEC5bits.SENT1EIE = 1;
    
    SENT1_TransmitCompleteCallbackRegister(&SENT1_TransmitCompleteCallback);
    SENT1_ErrorCallbackRegister(&SENT1_ErrorCallback);
    
    SENT1_Enable(); 
}

void SENT1_Deinitialize(void)
{
    SENT1_Disable(); 
    
    IFS5bits.SENT1IF = 0;
    IEC5bits.SENT1IE = 0;
    
    IFS5bits.SENT1EIF = 0;
    IEC5bits.SENT1EIE = 0;
    
    SENT1CON1 = 0x0;
    SENT1CON2 = 0x0;
    SENT1CON3 = 0x0;
}

void SENT1_Enable(void)
{
  SENT1CON1bits.SNTEN = 1;
}

void SENT1_Disable(void)
{
  SENT1CON1bits.SNTEN = 0;
}

void SENT1_TransmitModeSet(enum SENT_TRANSMIT_MODE mode)
{
  SENT1CON1bits.TXM = mode;
}

void SENT1_Transmit(const struct SENT_DATA_TRANSMIT *sentData)
{
    bDataTransmitted = false;
    SENT1DATHbits.STAT = sentData->status;
    SENT1DATHbits.DATA1 = sentData->data1;
    SENT1DATHbits.DATA2 = sentData->data2;
    SENT1DATHbits.DATA3 = sentData->data3;
    SENT1DATLbits.DATA4 = sentData->data4;
    SENT1DATLbits.DATA5 = sentData->data5;
    SENT1DATLbits.DATA6 = sentData->data6;
    if(!SENT1CON1bits.CRCEN)
    {
        SENT1DATLbits.CRC = sentData->crc;
    }
    if(SENT1CON1bits.TXM == 1)
    {
        SENT1STATbits.SYNC = 1;
    }
}

bool SENT1_IsTransmissionComplete(void)
{
    return bDataTransmitted;
}

enum SENT_TRANSMIT_STATUS SENT1_TransmitStatusGet(void)
{
    return (SENT1STAT);
}

void SENT1_TransmitCompleteCallbackRegister(void* handler)
{
    if(NULL != handler)
    {
        SENT1_TransmitCompleteHandler = handler;
    }
}

void __attribute__ ((weak)) SENT1_TransmitCompleteCallback(void)
{ 
   
} 
void SENT1_ErrorCallbackRegister(void* handler)
{
    if(NULL != handler)
    {
        SENT1_ErrorHandler = handler;
    }
}

void __attribute__ ((weak)) SENT1_ErrorCallback(void)
{ 
   
} 

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SENT1Interrupt( void )
{
    if(SENT1_TransmitCompleteHandler != NULL )
    {
        (*SENT1_TransmitCompleteHandler)();
    }
    if(SENT1CON1bits.TXM == 0)
    {
        bDataTransmitted = true;
    }
    else if(SENT1STATbits.SYNC == 0)
    {
        bDataTransmitted = true;
    }    
    else
    {
        bDataTransmitted = false;
    }
    IFS5bits.SENT1IF = 0;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SENT1EInterrupt (void)
{
    if(SENT1_ErrorHandler != NULL )
    {
        (*SENT1_ErrorHandler)();
    }
    if(SENT1STATbits.FRMERR == 1)
    {
        SENT1STATbits.FRMERR = 0;
    }
    if(SENT1STATbits.CRCERR == 1)
    {
        SENT1STATbits.CRCERR = 0;
    }
    IFS5bits.SENT1EIF = 0;
}


/**
 End of File
*/
