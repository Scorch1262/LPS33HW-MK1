/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"

/*
                         Main application
 */
void main(void){
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //Include this header file
    //#include "mcc_generated_files/examples/i2c_master_example.h"

    #define LPS33HW_ADDR    0x5C // oder 0xB8, 0xBB, 0xBA, 0xB9    0x5C 0x5D

    #define INTERRUPT_CFG   0x0b
    #define THS_P_L         0x0C
    #define THS_P_H         0x0d
    #define WHO_AM_I        0x0f
    #define CTRL_REG1       0x10
    #define CTRL_REG2       0x11
    #define CTRL_REG3       0x12
    #define FIFO_CTRL       0x14
    #define REF_P_XL        0x15
    #define REF_P_L         0x16
    #define REF_P_H         0x17
    #define RPDS_L          0x18
    #define RPDS_H          0x19
    #define RES_CONF        0x1A
    #define INT_SOURCE      0x25
    #define FIFO_STATUS     0x26
    #define STATUS          0x27
    #define PRESS_OUT_XL    0x28
    #define PRESS_OUT_L     0x29
    #define PRESS_OUT_H     0x2A
    #define TEMP_OUT_L      0x2B
    #define TEMP_OUT_H      0x2C
    #define LPFP_RES        0x33
            
    uint8_t  tempDataH;
    uint8_t  tempDataL;
    uint16_t tempData;
    float    tempDataAnz;
    
    uint8_t  pressDataXL;
    uint8_t  pressDataL;
    uint8_t  pressDataH;
    uint32_t pressLSBw;
    float    pressDataAnz;
    
    
    while (1){                                                          // Endlosscheife
        // Temperatur
        I2C_Write1ByteRegister(LPS33HW_ADDR,CTRL_REG2, 0b00000001);     // Write 1 to ONE_SHOT
        tempDataH = I2C_Read1ByteRegister(LPS33HW_ADDR,TEMP_OUT_H);     // "tempDataH" = inhalt von "TEMP_OUT_H"
        tempDataL = I2C_Read1ByteRegister(LPS33HW_ADDR,TEMP_OUT_L);     // "tempDataL" = inhalt von "TEMP_OUT_L"
        tempData = tempDataH | (tempDataL << 8);                        // 
        tempDataAnz = tempData / 1000.0f;                               // "tempDataAnz" gleich "tempData" / 1000
        printf("%4.2f °C\r\n",tempDataAnz);                             // schreibt den Inhalt von "tempDataAnz" an UART       
                
        // Luftdruck
        I2C_Write1ByteRegister(LPS33HW_ADDR,CTRL_REG2, 0b00000001);     // Write 1 to ONE_SHOT
        pressDataXL = I2C_Read1ByteRegister(LPS33HW_ADDR,PRESS_OUT_XL); // "pressDataXL" gleich I2C read (Temperatur-Register XL)
        pressDataL  = I2C_Read1ByteRegister(LPS33HW_ADDR,PRESS_OUT_L);  // "pressDataL" gleich I2C read (Temperatur-Register L)
        pressDataH  = I2C_Read1ByteRegister(LPS33HW_ADDR,PRESS_OUT_H);  // "pressDataH" gleich I2C read (Temperatur-Register H)
        uint32_t pressLSBw = (((uint32_t)pressDataH << 16) | ((uint32_t)pressDataL << 8) | ((uint32_t)pressDataXL));
        pressDataAnz = pressLSBw / 4096.0f;                             // "pressDataAnz" gleich "pressLSBw" / 4096
        printf("%4.2f hPa\r\n",pressDataAnz);                           // schreibt den Inhalt von "pressDataAnz" an UART   
        
        __delay_ms(500);                                                // warte 500ms
    }                                                                   // 
}                                                                       // 
/**
 End of File
*/