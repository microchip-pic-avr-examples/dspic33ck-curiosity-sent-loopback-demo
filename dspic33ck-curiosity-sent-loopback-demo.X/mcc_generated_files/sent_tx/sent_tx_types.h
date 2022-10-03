/**
 * SENT Generated Driver Types Header File
 * 
 * @file       sent_tx_types.h 
 *            
 * @ingroup   senttxdriver
 *            
 * @brief     This is the generated driver types header file for the SENT driver
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

#ifndef SENT_TX_TYPES_H
#define SENT_TX_TYPES_H
// Section: Structure Declarations
 
/** 
  @ingroup  senttxdriver
  @struct   SENT_DATA_TRANSMIT
  @brief    This data structure used to configure the SENT data packet
*/
struct SENT_DATA_TRANSMIT
{  
    unsigned crc:4;     /**< Defines the CRC field */
    unsigned data1:4;   /**< Defines the first data nibble field */       
    unsigned data2:4;   /**< Defines the second data nibble field */
    unsigned data3:4;   /**< Defines the third data nibble field */
    unsigned data4:4;   /**< Defines the fourth data nibble field */
    unsigned data5:4;   /**< Defines the fifth data nibble field */
    unsigned data6:4;   /**< Defines the sixth data nibble field */
    unsigned status:4;  /**< Defines the status field */
};


// Section: Enum Declarations

/**
 @ingroup senttxdriver
 @enum    SENT_TRANSMIT_MODE 
 @brief   Defines the SENT transmission mode (Asynchronous and Synchronous)
*/
enum SENT_TRANSMIT_MODE
{
  SENT_TRANSMIT_ASYNCHRONOUS,
  SENT_TRANSMIT_SYNCHRONOUS
};

/**
 @ingroup  senttxdriver
 @enum     SENT_TRANSMIT_STATUS 
 @brief    Defines the SENT transmit status.
           More than one of these values may be OR'd together to create a complete
           status value.  To test a value of this type, the bit of interest must be
           AND'ed with value and checked to see if the result is non-zero.
*/
enum SENT_TRANSMIT_STATUS
{
    SENT_TRANSMIT_SYNCTXEN = (1U << 0U),     /**< Synchronization Period Status Transmit Enable bit */    
    SENT_TRANSMIT_NIBBLE1 = (1U << 4U),      /**< Module is transmitting Data Nibble 1 */
    SENT_TRANSMIT_NIBBLE2 = (1U << 5U),      /**< Module is transmitting Data Nibble 2 */   
    SENT_TRANSMIT_NIBBLE3 = (3U << 4U),      /**< Module is transmitting Data Nibble 3 */
    SENT_TRANSMIT_NIBBLE4 = (1U << 6U),      /**< Module is transmitting Data Nibble 4 */
    SENT_TRANSMIT_NIBBLE5 = (5U << 4U),      /**< Module is transmitting Data Nibble 5 */ 
    SENT_TRANSMIT_NIBBLE6 = (6U << 4U),      /**< Module is transmitting Data Nibble 6 */
    SENT_TRANSMIT_CRC = (7U << 4U),          /**< Module is transmitting Data CRC */
    SENT_TRANSMIT_PAUSEPERIOD = (1U << 7U)   /**< Indicates whether the module is transmitting a Pause period */
    
};

#endif    /* SENT_TX_TYPES_H */  
            