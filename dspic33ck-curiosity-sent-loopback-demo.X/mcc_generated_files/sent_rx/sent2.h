/**
 * SENT2 Generated Driver Header File 
 * 
 * @file      sent2.h
 *            
 * @ingroup   sentrxdriver
 *            
 * @brief     This is the generated driver header file for the SENT2 driver
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

#ifndef SENT2_H
#define SENT2_H

// Section: Included Files

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "sent_rx_types.h"
#include "sent_rx_interface.h"
// Section: Data Type Definitions
/**
 @ingroup  sentrxdriver
 @brief    Structure object of type SENT_RECEIVE_INTERFACE with the 
           custom name given by the user in the Melody Driver User interface. 
           The default name e.g. SENT_Receiver can be changed by the 
           user in the SENT user interface. 
           This allows defining a structure with application specific name 
           using the 'Custom Name' field. Application specific name allows the 
           API Portability.
*/
extern const struct SENT_RECEIVE_INTERFACE SENT_Receiver;
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Initialize API
 */
#define SENT_Receiver_Initialize SENT2_Initialize
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Deinitialize API
 */
#define SENT_Receiver_Deinitialize SENT2_Deinitialize
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Enable API
 */
#define SENT_Receiver_Enable SENT2_Enable
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Disable API
 */
#define SENT_Receiver_Disable SENT2_Disable
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Receive API
 */
#define SENT_Receiver_Receive SENT2_Receive
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_IsDataReceived API
 */
#define SENT_Receiver_IsDataReceived SENT2_IsDataReceived
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_ReceiveStatusGet API
 */
#define SENT_Receiver_ReceiveStatusGet SENT2_ReceiveStatusGet
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_ReceiveCompleteCallbackRegister API
 */
#define SENT_Receiver_ReceiveCompleteCallbackRegister SENT2_ReceiveCompleteCallbackRegister
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_ErrorCallbackRegister API
 */
#define SENT_Receiver_ErrorCallbackRegister SENT2_ErrorCallbackRegister
/**
 * @ingroup  sentrxdriver
 * @brief    This macro defines the Custom Name for \ref SENT2_Tasks API
 */
#define SENT_Receiver_Tasks SENT2_Tasks
// Section: SENT2 Module APIs
 
/**
 * @ingroup  sentrxdriver
 * @brief    Initializes the SENT module
 * @return   none  
 */
void SENT2_Initialize(void);

/**
 * @ingroup  sentrxdriver
 * @brief    Deinitializes the SENT2 to POR values
 * @return   none  
 */
void SENT2_Deinitialize(void);

/**
 * @ingroup  sentrxdriver
 * @brief    Enables the SENT2 module
 * @return   none  
 */
void SENT2_Enable(void);

/**
 * @ingroup  sentrxdriver
 * @brief    Disables the SENT2 module
 * @return   none  
 */
void SENT2_Disable(void);


/**
 * @ingroup  sentrxdriver
 * @brief    Reads the received data from transmitter
 * @return   \ref SENT_DATA_RECEIVE - Received data structure
 */
struct SENT_DATA_RECEIVE SENT2_Receive(void);

/**
 * @ingroup  sentrxdriver
 * @brief    Returns the receive complete status
 * @return   true   - SENT receive completed
 * @return   false  - SENT receive not completed
 */
bool SENT2_IsDataReceived(void);
/**
 * @ingroup  sentrxdriver
 * @brief    Gets the reception status of the SENT module
 * @return   Returns the SENT module reception status \ref SENT_RECEIVE_STATUS
 */
enum SENT_RECEIVE_STATUS SENT2_ReceiveStatusGet(void);

/**
 * @ingroup    sentrxdriver
 * @brief      This function can be used to override default callback and to 
 *             define custom callback for SENT2 ReceiveComplete event
 * @param[in]  handler - Address of the callback function 
 * @return     none  
 */
void SENT2_ReceiveCompleteCallbackRegister(void* handler);

/**
 * @ingroup  sentrxdriver
 * @brief    This is the default callback with weak attribute. 
 *           The user can override and implement the default callback without 
 *           weak attribute or can register a custom callback function using 
 *           SENT2_ReceiveCompleteCallbackRegister
 * @return   none  
 */
void SENT2_ReceiveCompleteCallback(void);

/**
 * @ingroup    sentrxdriver
 * @brief      This function can be used to override default callback and to 
 *             define custom callback for SENT2 Error event
 * @param[in]  handler - Address of the callback function 
 * @return     none  
 */
void SENT2_ErrorCallbackRegister(void* handler);

/**
 * @ingroup  sentrxdriver
 * @brief    This is the default callback with weak attribute. 
 *           The user can override and implement the default callback without 
 *           weak attribute or can register a custom callback function using 
 *           SENT2_ErrorCallbackRegister
 * @return   none  
 */
void SENT2_ErrorCallback(void);


/**
 * @ingroup  sentrxdriver
 * @brief    This function is used to implement the tasks for polled implementations
 * @return   none  
 */
void SENT2_Tasks(void);

#endif  // SENT2_H
/**
 End of File
*/


