/**
 * SENT2 Generated Driver Source File
 * 
 * @file      sent2.c
 *            
 * @ingroup   sentrxdriver
 *            
 * @brief     This is the generated driver source file for SENT2 driver
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
#include "../sent2.h"

// Section: File specific functions

void (*SENT2_ReceiveCompleteHandler)(void) = NULL;
void (*SENT2_ErrorHandler)(void) = NULL;

// Section: Data Type Definitions

static volatile bool bDataReceived = 0;

// Section: Driver Interface
const struct SENT_RECEIVE_INTERFACE SENT_Receiver = {
    .Initialize             = &SENT2_Initialize,
    .Deinitialize           = &SENT2_Deinitialize,
    .Enable                 = &SENT2_Enable,
    .Disable                = &SENT2_Disable,
    .Receive                = &SENT2_Receive,
    .IsDataReceived         = &SENT2_IsDataReceived,
    .ReceiveStatusGet       = &SENT2_ReceiveStatusGet,
    .ReceiveCompleteCallbackRegister = &SENT2_ReceiveCompleteCallbackRegister,
    .ErrorCallbackRegister = &SENT2_ErrorCallbackRegister,
    .Tasks                  = &SENT2_Tasks,
};

// Section: SENT2 Module APIs

void SENT2_Initialize(void)
{
    // PPP disabled; TXPOL Non Inverted; SNTSIDL disabled; PS Divide-by-1; SNTEN disabled; SPCEN disabled; TXM Asynchronous; CRCEN disabled; RCVEN Receiver; NIBCNT 6; 
    SENT2CON1 = 0x806;
    // SENTCON2 115; 
    SENT2CON2 = 0x73;
    // SENTCON3 77; 
    SENT2CON3 = 0x4D;
    
    SENT2_ReceiveCompleteCallbackRegister(&SENT2_ReceiveCompleteCallback);
    SENT2_ErrorCallbackRegister(&SENT2_ErrorCallback);
    
    SENT2_Enable(); 
}

void SENT2_Deinitialize(void)
{
    SENT2_Disable(); 
    
    SENT2CON1 = 0x0;
    SENT2CON2 = 0x0;
    SENT2CON3 = 0x0;
}

void SENT2_Enable(void)
{
  SENT2CON1bits.SNTEN = 1;
}

void SENT2_Disable(void)
{
  SENT2CON1bits.SNTEN = 0;
}

struct SENT_DATA_RECEIVE SENT2_Receive(void)
{
    struct SENT_DATA_RECEIVE sentData;
    sentData.status =  SENT2DATHbits.STAT;
    sentData.data1 = SENT2DATHbits.DATA1 ;
    sentData.data2 = SENT2DATHbits.DATA2 ;
    sentData.data3 = SENT2DATHbits.DATA3 ; 
    sentData.data4 = SENT2DATLbits.DATA4;
    sentData.data5 = SENT2DATLbits.DATA5; 
    sentData.data6 = SENT2DATLbits.DATA6; 
    if(!SENT2CON1bits.CRCEN)
    {
      sentData.crc = SENT2DATLbits.CRC;
    }
    return sentData;
}

bool SENT2_IsDataReceived(void)
{
   while(IFS5bits.SENT2IF == 0)
   {
   }
   IFS5bits.SENT2IF = 0;
   return true;
}

enum SENT_RECEIVE_STATUS SENT2_ReceiveStatusGet(void)
{
    return (SENT2STAT);
}

void SENT2_ReceiveCompleteCallbackRegister(void* handler)
{
    if(NULL != handler)
    {
        SENT2_ReceiveCompleteHandler = handler;
    }
}

void __attribute__ ((weak)) SENT2_ReceiveCompleteCallback(void)
{ 
   
} 
void SENT2_ErrorCallbackRegister(void* handler)
{
    if(NULL != handler)
    {
        SENT2_ErrorHandler = handler;
    }
}

void __attribute__ ((weak)) SENT2_ErrorCallback(void)
{ 
   
} 



void SENT2_Tasks ( void )
{
    if(IFS5bits.SENT2IF == 1)
    {
        // SENT2 callback function 
        if(SENT2_ReceiveCompleteHandler != NULL )
        {
            (*SENT2_ReceiveCompleteHandler)();
        }
        bDataReceived = true;
        // clear the SENT2 interrupt flag
        IFS5bits.SENT2IF = 0;
    }
    if(IFS5bits.SENT2EIF == 1)
    {
        // SENT2 Error callback function 
        if(SENT2_ErrorHandler != NULL )
        {
            (*SENT2_ErrorHandler)();
        }
        
        if(SENT2STATbits.FRMERR == 1)
        {
            SENT2STATbits.FRMERR = 0;
        }
        if(SENT2STATbits.CRCERR == 1)
        {
            SENT2STATbits.CRCERR = 0;
        }
        
        // clear the SENT2 IFS5bits.SENT2EIF interrupt flag
        IFS5bits.SENT2EIF = 0;
    }
}

/**
 End of File
*/
