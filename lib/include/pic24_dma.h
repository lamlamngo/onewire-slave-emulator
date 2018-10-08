/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/


// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  DMA module support functions.
 */

#pragma once

/* And/OR Macros */
#define DMA_MODULE_ON               0x8000 /* A/D Converter on */
#define DMA_MODULE_OFF              0x0000 /* A/D Converter off */
#define DMA_MODULE_MASK             (~DMA_MODULE_ON)

#define DMA_SIZE_BYTE               0x4000 /* DMA data size is byte */
#define DMA_SIZE_WORD               0x0000 /* DMA data size is word */
#define DMA_SIZE_MASK               (~DMA_SIZE_BYTE);

#define DMA_DIR_WRITE_PERIPHERAL    0x2000 /* Read from DMA RAM address, write to peripheral*/
#define DMA_DIR_READ_PERIPHERAL    0x0000 /* Read from peripheral address, write to DMA RAM*/
#define DMA_DIR_MASK                (~DMA_DIR_WRITE_PERIPHERAL)

#define DMA_INTERRUPT_HALF          0x1000 /* interrupt on half full */
#define DMA_INTERRUPT_FULL          0x0000 /* interrupt on full */
#define DMA_INTERRUPT_MASK          (~DMA_INTERRUPT_HALF)

#define DMA_NULLW_ON                0x0800 /* Null data write to peripheral in addition to DMA RAM write*/
#define DMA_NULLW_OFF               0x0000 /* Normal operation*/
#define DMA_NULLW_MASK              (~DMA_NULLW_ON)

#define DMA_AMODE_PERIPHERAL_INDIRECT 0x0020 /* Peripheral indirect addressing mode*/
#define DMA_AMODE_REGISTER_INDIRECT   0x0010  /* Register indirect without post increment*/
#define DMA_AMODE_REGISTER_POSTINC    0x0000  /* Register indirect with post-incrmenent mode*/
#define DMA_AMODE_MASK             (~DMA_AMODE_PERIPHERAL_INDIRECT)


#define DMA_MODE_ONE_SHOT_PING_PONG      0x0003 /* One-Shot, Ping-Pong modes enabled*/
#define DMA_MODE_CONTINUOUS_PING_PONG    0x0002 /* Continuous Ping-Pong modes enabled*/
#define DMA_MODE_ONE_SHOT                0x0001 /* One-shot Ping-Pong mode disabled*/
#define DMA_MODE_CONTINUOUS              0x0000 /* Continuous, Ping-pong modes disabled */
#define DMA_MODE_MASK              (~DMA_MODE_ONE_SHOT_PING_PONG)

// constants for DMAxREQ register
#define DMA_IRQ_INT0        0x0000
#define DMA_IRQ_IC1         0x0001
#define DMA_IRQ_OC1         0x0002
#define DMA_IRQ_IC2         0x0005
#define DMA_IRQ_OC2         0x0006
#define DMA_IRQ_IC3         0x0025
#define DMA_IRQ_OC3         0x0019
#define DMA_IRQ_IC4         0x0026
#define DMA_IRQ_OC4         0x001A
#define DMA_IRQ_TMR2        0x0007
#define DMA_IRQ_TMR3        0x0008
#define DMA_IRQ_TMR4        0x001B
#define DMA_IRQ_TMR5        0x001C
#define DMA_IRQ_SPI1        0x000A
#define DMA_IRQ_SPI2        0x0021
#define DMA_IRQ_SPI3        0x005B
#define DMA_IRQ_SPI4        0x007B
#define DMA_IRQ_U1RX        0x000B
#define DMA_IRQ_U1TX        0x000C
#define DMA_IRQ_U2RX        0x001E
#define DMA_IRQ_U2TX        0x001F
#define DMA_IRQ_U3RX        0x0052
#define DMA_IRQ_U3TX        0x0053
#define DMA_IRQ_U4RX        0x0058
#define DMA_IRQ_U4TX        0x0059
#define DMA_IRQ_ADC1        0x000D
#define DMA_IRQ_ADC2        0x0015
#define DMA_IRQ_ECAN1RX     0x0022
#define DMA_IRQ_ECAN2RX     0x0037
#define DMA_IRQ_ECAN1TX     0x0046
#define DMA_IRQ_ECAN2TX     0x0047
#define DMA_IRQ_PMP         0x002D

// constants for DMAxPAD register
#define DMA_PAD_IC1BUF      0x0144
#define DMA_PAD_OC1R        0x0906
#define DMA_PAD_OC1RS       0x0904
#define DMA_PAD_IC2BUF      0x014C
#define DMA_PAD_OC2R        0x0910
#define DMA_PAD_OC2RS       0x090E
#define DMA_PAD_IC3BUF      0x0154
#define DMA_PAD_OC3R        0x091A
#define DMA_PAD_OC3RS       0x0918
#define DMA_PAD_IC4BUF      0x015C
#define DMA_PAD_OC4R        0x0924
#define DMA_PAD_OC4RS       0x0922
#define DMA_PAD_SPI1BUF     0x0248
#define DMA_PAD_SPI2BUF     0x0268
#define DMA_PAD_SPI3BUF     0x02A8
#define DMA_PAD_SPI4BUF     0x02C8
#define DMA_PAD_U1RXREG     0x0226
#define DMA_PAD_U1TXREG     0x0224
#define DMA_PAD_U2RXREG     0x0236
#define DMA_PAD_U2TXREG     0x0234
#define DMA_PAD_U3RXREG     0x0256
#define DMA_PAD_U3TXREG     0x0254
#define DMA_PAD_U4RXREG     0x02B6
#define DMA_PAD_U4TXREG     0x02B4
#define DMA_PAD_ADC1BUF0    0x0300
#define DMA_PAD_ADC2BUF0    0x0340
#define DMA_PAD_C1RXD       0x0440
#define DMA_PAD_C2RXD       0x0540
#define DMA_PAD_C1TXD       0x0442
#define DMA_PAD_C2TXD       0x0542
#define DMA_PAD_PMDIN1      0x0608


