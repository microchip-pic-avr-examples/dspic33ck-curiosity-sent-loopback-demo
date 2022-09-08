/**
 * SENT1 Generated Driver Header File 
 * 
 * @file      sent1.h
 *            
 * @ingroup   senttxdriver
 *            
 * @brief     This is the generated driver header file for the SENT1 driver
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

#ifndef SENT1_H
#define SENT1_H

// Section: Included Files

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "sent_tx_types.h"
#include "sent_tx_interface.h"
// Section: Data Type Definitions

/**
 @ingroup  senttxdriver
 @brief    Structure object of type SENT_TRANSMIT_INTERFACE with the
           custom name given by the user in the Melody Driver User interface.
           The default name can be changed by the user in the SENT
           user interface. This allows defining a structure with application
           specific name using the 'Custom Name' field. Application specific 
           name allows the API Portability.
*/
extern const struct SENT_TRANSMIT_INTERFACE SENT_Transmitter;
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Initialize API
 */
#define SENT_Transmitter_Initialize SENT1_Initialize
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Deinitialize API
 */
#define SENT_Transmitter_Deinitialize SENT1_Deinitialize
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Enable API
 */
#define SENT_Transmitter_Enable SENT1_Enable
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Disable API
 */
#define SENT_Transmitter_Disable SENT1_Disable
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_TransmitModeSet API
 */
#define SENT_Transmitter_TransmitModeSet SENT1_TransmitModeSet
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Transmit API
 */
#define SENT_Transmitter_Transmit SENT1_Transmit
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_IsTransmissionComplete API
 */
#define SENT_Transmitter_IsTransmissionComplete SENT1_IsTransmissionComplete
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_TransmitStatusGet API
 */
#define SENT_Transmitter_TransmitStatusGet SENT1_TransmitStatusGet
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_TransmitCompleteCallbackRegister API
 */
#define SENT_Transmitter_TransmitCompleteCallbackRegister SENT1_TransmitCompleteCallbackRegister
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_ErrorCallbackRegister API
 */
#define SENT_Transmitter_ErrorCallbackRegister SENT1_ErrorCallbackRegister
/**
 * @ingroup  senttxdriver
 * @brief    This macro defines the Custom Name for \ref SENT1_Tasks API
 */
#define SENT_Transmitter_Tasks SENT1_Tasks
// Section: SENT1 Module APIs
 
/**
 * @ingroup  senttxdriver
 * @brief    Initializes the SENT module
 * @return   none  
 */
void SENT1_Initialize(void);

/**
 * @ingroup  senttxdriver
 * @brief    Deinitializes the SENT1 to POR values
 * @return   none  
 */
void SENT1_Deinitialize(void);

/**
 * @ingroup  senttxdriver
 * @brief    Enables the SENT1 module
 * @return   none  
 */
void SENT1_Enable(void);

/**
 * @ingroup  senttxdriver
 * @brief    Disables the SENT1 module
 * @return   none  
 */
void SENT1_Disable(void);

/**
 * @ingroup    senttxdriver
 * @brief      Sets the SENT transmit mode
 * @param[in]  mode - SENT Synchronous or Asynchronous  
 * @return     none  
 */
void SENT1_TransmitModeSet(enum SENT_TRANSMIT_MODE mode);

/**
 * @ingroup    senttxdriver
 * @brief      Writes the SENT data to receiver
 * @param[in]  sentData - Structure which contains the data to be sent 
 * @return     none  
 */
void SENT1_Transmit(const struct SENT_DATA_TRANSMIT *sentData);

/**
 * @ingroup  senttxdriver
 * @brief    Returns the transmit complete status
 * @return   true   - SENT transmit completed
 * @return   false  - SENT transmit not completed 
 */
bool SENT1_IsTransmissionComplete(void);
/**
 * @ingroup  senttxdriver
 * @brief    Gets the transmission status of the SENT module
 * @return   Returns the SENT module transmission status \ref SENT_TRANSMIT_STATUS
 */
enum SENT_TRANSMIT_STATUS SENT1_TransmitStatusGet(void);

/**
 * @ingroup    senttxdriver
 * @brief      This function can be used to override default callback and to 
 *             define custom callback for SENT1 TransmitComplete event
 * @param[in]  handler - Address of the callback function 
 * @return     none  
 */
void SENT1_TransmitCompleteCallbackRegister(void* handler);

/**
 * @ingroup  senttxdriver
 * @brief    This is the default callback with weak attribute. 
 *           The user can override and implement the default callback without 
 *           weak attribute or can register a custom callback function using 
 *           SENT1_TransmitCompleteCallbackRegister
 * @return   none  
 */
void SENT1_TransmitCompleteCallback(void);

/**
 * @ingroup    senttxdriver
 * @brief      This function can be used to override default callback and to 
 *             define custom callback for SENT1 Error event
 * @param[in]  handler - Address of the callback function 
 * @return     none  
 */
void SENT1_ErrorCallbackRegister(void* handler);

/**
 * @ingroup  senttxdriver
 * @brief    This is the default callback with weak attribute. 
 *           The user can override and implement the default callback without 
 *           weak attribute or can register a custom callback function using 
 *           SENT1_ErrorCallbackRegister
 * @return   none  
 */
void SENT1_ErrorCallback(void);


/**
 * @ingroup  senttxdriver
 * @brief    This function is used to implement the tasks for polled implementations
 * @return   none  
 */
void SENT1_Tasks(void);

#endif  // SENT1_H
/**
 End of File
*/


