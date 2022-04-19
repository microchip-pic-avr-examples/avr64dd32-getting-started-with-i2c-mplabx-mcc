/**
 * TWI0 Generated Driver API Header File
 *
 * @file twi0_host_types.h
 *
 * @defgroup twi0 TWI0
 *
 * @brief This header file provides APIs for the TWI0 driver.
 *
 * @version TWI0 Driver Version 2.0.1
*/

/*
� [2022] Microchip Technology Inc. and its subsidiaries.

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

#ifndef I2C_HOST_TYPES_H
#define	I2C_HOST_TYPES_H

/**
 * @ingroup twi0
 * @typedef enum i2c_host_error_t
 * @brief Enumeration for I2C_ERROR code
 */ 
typedef enum
{
    I2C_ERROR_NONE,             /* No Error */
    I2C_ERROR_ADDR_NACK,
    I2C_ERROR_DATA_NACK,
    I2C_ERROR_BUS_COLLISION,    /* Bus Collision Error */
}i2c_host_error_t;

/**
 * @ingroup twi0
 * @struct I2C_TRANSFER_SETUP structure
 * @brief Structure for I2C Clock Speed (100KHZ to 1MHZ)
 */
struct I2C_TRANSFER_SETUP
{
  uint32_t clkSpeed;            // I2C Clock Speed 
};

#endif // end of I2C_HOST_TYPES_H