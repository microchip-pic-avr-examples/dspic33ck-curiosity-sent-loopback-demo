/**
 * SENT Generated Driver Interface Header File for transmit mode
 * 
 * @file      sent_transmit_interface.h
 *            
 * @defgroup  senttxdriver SENT TX Driver
 *            
 * @brief     SENT Transmit driver. The Single-Edge Nibble Transmission for 
 *            Automotive Applications is based on the SAE J2716. It is intended
 *            for use in applications where high-resolution sensor data need to
 *            be communicated using dsPIC MCUs.
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

#ifndef SENT_TRANSMIT_INTERFACE_H
#define SENT_TRANSMIT_INTERFACE_H

// Section: Included Files

#include <stdbool.h>
#include <stdint.h>
#include "sent_tx_types.h"

// Section: Data Type Definitions
        
/**
 @ingroup  senttxdriver
 @struct   SENT_TRANSMIT_INTERFACE
 @brief    Structure containing the function pointers of SENT driver in transmit mode
*/
 
struct SENT_TRANSMIT_INTERFACE
{
    void (*Initialize)(void);
    ///< Pointer to SENTx_Initialize e.g. \ref SENT1_Initialize
    
    void (*Deinitialize)(void);
    ///< Pointer to SENTx_Deinitialize e.g. \ref SENT1_Deinitialize
    
    void (*Enable)(void);
    ///< Pointer to SENTx_Enable e.g. \ref SENT1_Enable
    
    void (*Disable)(void);
    ///< Pointer to SENTx_Disable e.g. \ref SENT1_Disable
    
    void (*TransmitModeSet)(enum SENT_TRANSMIT_MODE mode);
    ///< Pointer to SENTx_TransmitModeSet e.g. \ref SENT1_TransmitModeSet
    
    void (*Transmit)(const struct SENT_DATA_TRANSMIT *sentData);
    ///< Pointer to SENTx_Transmit e.g. \ref SENT1_Transmit
    
    bool (*IsTransmissionComplete)(void);
    ///< Pointer to SENTx_IsTransmissionComplete e.g. \ref SENT1_IsTransmissionComplete
    
    enum SENT_TRANSMIT_STATUS (*TransmitStatusGet)(void);
    ///< Pointer to SENTx_TransmitStatusGet e.g. \ref SENT1_TransmitStatusGet

    void (*TransmitCompleteCallbackRegister)(void* handler);
    ///< Pointer to SENTx_TransmitCompleteCallbackRegister e.g. \ref SENT1_TransmitCompleteCallbackRegister
    
    void (*ErrorCallbackRegister)(void* handler);
    ///< Pointer to SENTx_ErrorCallbackRegister e.g. \ref SENT1_ErrorCallbackRegister
    
    void (*Tasks)(void);
    ///< Pointer to SENTx_Tasks e.g. \ref SENT1_Tasks (Supported only in polling mode)
};

#endif