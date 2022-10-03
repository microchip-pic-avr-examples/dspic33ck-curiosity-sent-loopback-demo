/**
 * SENT Generated Driver Types Header File
 * 
 * @file       sent_rx_types.h 
 *            
 * @ingroup   sentrxdriver
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

#ifndef SENT_RX_TYPES_H
#define SENT_RX_TYPES_H
// Section: Structure Declarations
 
/** 
  @ingroup  sentrxdriver
  @struct   SENT_DATA_RECEIVE
  @brief    This data structure used to configure the SENT data packet
*/
struct SENT_DATA_RECEIVE
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


/**
 @ingroup  sentrxdriver
 @enum     SENT_RECEIVE_STATUS 
 @brief    Defines the SENT receive status.
           More than one of these values may be OR'd together to create a complete
           status value.  To test a value of this type, the bit of interest must be
           AND'ed with value and checked to see if the result is non-zero.
*/
enum SENT_RECEIVE_STATUS
{
    SENT_RECEIVE_SYNCTXEN = (1U << 0U),      /**< Synchronization Period Receive Enable bit */
    SENT_RECEIVE_RXIDLE = (1U << 1U),        /**< Indicates whether The SENTx data bus has been Idle (high) for a period of SYNCMAX or greater */
    SENT_RECEIVE_FRAMEERR = (1U << 2U),      /**< Indicates whether data nibble was received with less than 12 Tick periods or greater than 27 Tick periods */
    SENT_RECEIVE_CRCERR = (1U << 3U),        /**< Indicates whether a CRC error occurred for the data nibbles in SENTxDATH/L */
    SENT_RECEIVE_NIBBLE1 = (1U << 4U),       /**< Module is receiving Data Nibble 1*/
    SENT_RECEIVE_NIBBLE2 = (1U << 5U),       /**< Module is receiving Data Nibble 2*/
    SENT_RECEIVE_NIBBLE3 = (3U << 4U),       /**< Module is receiving Data Nibble 3*/
    SENT_RECEIVE_NIBBLE4= (1U << 6U),        /**< Module is receiving Data Nibble 4*/
    SENT_RECEIVE_NIBBLE5= (5U << 4U),        /**< Module is receiving Data Nibble 5*/
    SENT_RECEIVE_NIBBLE6= (6U << 4U),        /**< Module is receiving Data Nibble 6*/
    SENT_RECEIVE_CRC= (7U << 4U),            /**< Module is receiving Data CRC*/
    SENT_RECEIVE_PAUSEPERIOD = (1U << 7U)    /**< Indicates whether the module is receiving a Pause period */
    
};

#endif    /* SENT_RX_TYPES_H */ 
            