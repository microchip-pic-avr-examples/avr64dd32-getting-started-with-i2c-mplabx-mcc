/*
    \file   main.c

    \brief  I2C Read Write Example

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

#include "mcc_generated_files/system/system.h"
#include <util/delay.h>
#include <avr/io.h>
#include "mcp23008.h"
#include "mcp3221.h"

#define I2C_SCAN_MIN   0x00
#define I2C_SCAN_MAX   0x7F

void    main_i2c_scan(uint8_t addr_min, uint8_t addr_max);
uint8_t getLedBar(uint16_t);
void    getBinaryString(char*, uint8_t);

int main(void) 
{
    SYSTEM_Initialize();
 
    _delay_ms(2000);
    printf("\n\r\n\r I2C - Two Wire Interface Demo\n\r");
    _delay_ms(1000);
    main_i2c_scan(I2C_SCAN_MIN, I2C_SCAN_MAX);
    _delay_ms(1000);
    
    printf("\n\r Configuring the IO Expander");
    /* Configure the IO Expander PORT pins as outputs */
    if (MCP23008_Write(MCP23008_IODIR_REG, MCP23008_IODIR_OUTPUT_CMD))
    {
        printf("\n\r IO Expander MCP23008 configured");
    }
    else
    {
        printf("\n\r IO Expander MCP23008 Write failed!");
    }
    
    while (1)
    {
        uint16_t adc_result = 0;
        uint8_t LED_bar = 0;
        char binary_string[9];

        /* Read the ADC result */
        if (MCP3221_Read(&adc_result))
        {
            LED_bar = getLedBar(adc_result);
            getBinaryString(binary_string, LED_bar);
            printf("\n\r ADC result: 0x%03X | LED bar: %s", adc_result, binary_string);
        }
        else
        {
            printf("\n\r AD Converter MCP3221 Read  failed!");
        }
        
        /* Drive the IO Expander outputs */
        if (!MCP23008_Write(MCP23008_PORT_REG, LED_bar))
        {
            printf("\n\r IO Expander MCP23008 Write failed!");
        }
        
        _delay_ms(500);
    }
}

/* Scans for I2C client devices on the bus - that have an address within the 
 *specified range [addr_min, addr_max]
 */
void main_i2c_scan(uint8_t addr_min, uint8_t addr_max)
{
    uint8_t client_address;
    printf("\n\r I2C Scan started from 0x%02X to 0x%02X:", addr_min, addr_max);
    for (client_address = addr_min; client_address <= addr_max; client_address++)
    {
        printf("\n\r Scanning client address = 0x%02X", (int)client_address);
        TWI0_Write(client_address, NULL, 0);
        
        do
        {
            TWI0_Tasks();
        }while(TWI0_IsBusy());
        
        if(TWI0_ErrorGet() == I2C_ERROR_NONE)
        {
            printf(" --> client ACKED");
        }
        
        _delay_ms(50);
    }
    printf("\n\r I2C Scan ended\n\r");
}

/* Returns the LED bar to be displayed on the IO Expander */
uint8_t getLedBar(uint16_t adc_value)
{
    uint8_t bar = 255;
    uint8_t shift;
    
    /* from the ADC value of 12 bits, the lower 9 are discarded and kept only the upper 3 */
    shift = 7 & (adc_value >> 9);
    bar >>= 7 - shift;
    
    return bar;
}

void getBinaryString(char *pString, uint8_t binary)
{
    uint8_t mask = 1, counter = 8; 
    if(pString == NULL)
        return;

    do{
        pString[--counter] = (binary & mask) ? '1' : '0';
        mask <<= 1;
    } while(counter != 0);
    pString[8] = '\0';
}
