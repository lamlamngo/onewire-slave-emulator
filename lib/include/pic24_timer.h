/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  To do.
 */

#pragma once

#include <stdint.h>
#include "pic24_chip.h"
#include "pic24_clockfreq.h"

/** Given the TxCON register as a bitfield, determines the prescale
 *  based on the TCKPS bitfield. Works for PIC24H, PIC24F timers.
 *  Simply accesses the TCKPS bitfield then calls
 *  \ref getTimerPrescaleBits with the bitfield.
 *  \param TxCONbits The TxCONbits for the timer in question
 *  \return Prescale value.
 */
#define getTimerPrescale(TxCONbits) getTimerPrescaleBits(TxCONbits.TCKPS)

#define MS_TO_TICKS(ms, pre) ((FCY/1000L/(pre))*(ms))

#ifndef _NOFLOAT
uint16_t msToU16Ticks(uint16_t u16_ms, uint16_t u16_pre);
uint16_t usToU16Ticks(uint16_t u16_us, uint16_t u16_pre);
uint32_t usToU32Ticks(uint32_t u32_us, uint16_t u16_pre);
uint32_t ticksToMs (uint32_t u32_ticks, uint16_t u16_tmrPre);
uint32_t ticksToUs (uint32_t u32_ticks, uint16_t u16_tmrPre);
uint32_t ticksToNs (uint32_t u32_ticks, uint16_t u16_tmrPre);
#endif
uint16_t getTimerPrescaleBits(uint8_t u8_TCKPS);
uint32_t computeDeltaTicksLong(uint16_t u16_start, uint16_t u16_end, uint16_t u16_tmrPR, uint16_t u16_oflows);
uint16_t computeDeltaTicks(uint16_t u16_start, uint16_t u16_end, uint16_t u16_tmrPR);

/*
The following macros are a subset of the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/timer.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/timer.h header.

Edits have been made in the comments to correct some
minor typos.
*/

/* T1CON: TIMER1 CONTROL REGISTER */
#define T1_ON               0x8000 /* Timer1 ON */
#define T1_OFF              0x0000 /* Timer1 OFF */
#define T1_OFF_ON_MASK      (~T1_ON)

#define T1_IDLE_STOP        0x2000 /* stop operation during sleep */
#define T1_IDLE_CON         0x0000 /* operate during sleep */
#define T1_IDLE_MASK        (~T1_IDLE_STOP)

#define T1_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T1_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T1_GATE_MASK        (~T1_GATE_ON)

#define T1_PS_1_1           0x0000 /* Prescaler 1:1 */
#define T1_PS_1_8           0x0010 /*           1:8 */
#define T1_PS_1_64          0x0020 /*          1:64 */
#define T1_PS_1_256         0x0030 /*         1:256 */
#define T1_PS_MASK          (~T1_PS_1_256)

#define T1_SYNC_EXT_ON      0x0004 /* Synch external clk input */
#define T1_SYNC_EXT_OFF     0x0000 /* Do not synch external clk input */
#define T1_SYNC_EXT_MASK    (~T1_SYNC_EXT_ON)

#define T1_SOURCE_EXT       0x0002 /* External clock source */
#define T1_SOURCE_INT       0x0000 /* Internal clock source */
#define T1_SOURCE_MASK      (~T1_SOURCE_EXT)

#ifdef _T2IF
/* T2CON: TIMER2 CONTROL REGISTER */
#define T2_ON               0x8000      /* Timer2 ON */
#define T2_OFF              0x0000      /* Timer2 OFF */
#define T2_OFF_ON_MASK      (~T2_ON)

#define T2_IDLE_STOP        0x2000 /* stop operation during sleep */
#define T2_IDLE_CON         0x0000 /* operate during sleep */
#define T2_IDLE_MASK        (~T2_IDLE_STOP)

#define T2_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T2_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T2_GATE_MASK        (~T2_GATE_ON)

#define T2_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T2_PS_1_8           0x0010      /*           1:8 */
#define T2_PS_1_64          0x0020      /*          1:64 */
#define T2_PS_1_256         0x0030      /*         1:256 */
#define T2_PS_MASK          (~T2_PS_1_256)

#define T2_32BIT_MODE_ON    0x0008      /* Timer 2 and Timer 3 form a 32 bit Timer */
#define T2_32BIT_MODE_OFF   0x0000
#define T2_32BIT_MODE_MASK   (~T2_32BIT_MODE_ON)

#define T2_SOURCE_EXT       0x0002 /* External clock source */
#define T2_SOURCE_INT       0x0000 /* Internal clock source */
#define T2_SOURCE_MASK      (~T2_SOURCE_EXT)
#endif

#ifdef _T3IF
/* T3CON: TIMER3 CONTROL REGISTER */
#define T3_ON               0x8000      /* Timer3 ON */
#define T3_OFF              0x0000      /* Timer3 OFF */
#define T3_OFF_ON_MASK      (~T3_ON)

#define T3_IDLE_STOP        0x2000 /* operate during sleep */
#define T3_IDLE_CON         0x0000 /* stop operation during sleep */
#define T3_IDLE_MASK        (~T3_IDLE_STOP)

#define T3_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T3_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T3_GATE_MASK        (~T3_GATE_ON)

#define T3_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T3_PS_1_8           0x0010      /*           1:8 */
#define T3_PS_1_64          0x0020      /*          1:64 */
#define T3_PS_1_256         0x0030      /*         1:256 */
#define T3_PS_MASK          (~T3_PS_1_256)

#define T3_SOURCE_EXT       0x0002 /* External clock source */
#define T3_SOURCE_INT       0x0000 /* Internal clock source */
#define T3_SOURCE_MASK      (~T3_SOURCE_EXT)
#endif

#ifdef _T4IF
/* T4CON: TIMER4 CONTROL REGISTER */
#define T4_ON               0x8000      /* Timer4 ON */
#define T4_OFF              0x0000      /* Timer4 OFF */
#define T4_OFF_ON_MASK      (~T4_ON)

#define T4_IDLE_STOP        0x2000 /* operate during sleep */
#define T4_IDLE_CON         0x0000 /* stop operation during sleep */
#define T4_IDLE_MASK        (~T4_IDLE_STOP)

#define T4_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T4_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T4_GATE_MASK        (~T4_GATE_ON)

#define T4_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T4_PS_1_8           0x0010      /*           1:8 */
#define T4_PS_1_64          0x0020      /*          1:64 */
#define T4_PS_1_256         0x0030      /*         1:256 */
#define T4_PS_MASK          (~T4_PS_1_256)

#define T4_32BIT_MODE_ON    0x0008      /* Timer 4 and Timer 5 form a 32 bit Timer */
#define T4_32BIT_MODE_OFF   0x0000
#define T4_32BIT_MODE_MASK   (~T4_32BIT_MODE_ON)

#define T4_SOURCE_EXT       0x0002 /* External clock source */
#define T4_SOURCE_INT       0x0000 /* Internal clock source */
#define T4_SOURCE_MASK      (~T4_SOURCE_EXT)
#endif

#ifdef _T5IF
/* T5CON: TIMER5 CONTROL REGISTER */
#define T5_ON               0x8000      /* Timer5 ON */
#define T5_OFF              0x0000      /* Timer5 OFF */
#define T5_OFF_ON_MASK      (~T5_ON)

#define T5_IDLE_STOP        0x2000 /* operate during sleep */
#define T5_IDLE_CON         0x0000 /* stop operation during sleep */
#define T5_IDLE_MASK        (~T5_IDLE_STOP)

#define T5_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T5_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T5_GATE_MASK        (~T5_GATE_ON)

#define T5_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T5_PS_1_8           0x0010      /*           1:8 */
#define T5_PS_1_64          0x0020      /*          1:64 */
#define T5_PS_1_256         0x0030      /*         1:256 */
#define T5_PS_MASK          (~T5_PS_1_256)

#define T5_SOURCE_EXT       0x0002 /* External clock source */
#define T5_SOURCE_INT       0x0000 /* Internal clock source */
#define T5_SOURCE_MASK      (~T5_SOURCE_EXT)
#endif

#ifdef _T6IF
/* T6CON: TIMER6 CONTROL REGISTER */
#define T6_ON               0x8000      /* Timer6 ON */
#define T6_OFF              0x0000      /* Timer6 OFF */
#define T6_OFF_ON_MASK      (~T6_ON)

#define T6_IDLE_STOP        0x2000 /* operate during sleep */
#define T6_IDLE_CON         0x0000 /* stop operation during sleep */
#define T6_IDLE_MASK        (~T6_IDLE_STOP)

#define T6_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T6_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T6_GATE_MASK        (~T6_GATE_ON)

#define T6_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T6_PS_1_8           0x0010      /*           1:8 */
#define T6_PS_1_64          0x0020      /*          1:64 */
#define T6_PS_1_256         0x0030      /*         1:256 */
#define T6_PS_MASK          (~T6_PS_1_256)

#define T6_32BIT_MODE_ON    0x0008      /* Timer 6 and Timer 7 form a 32 bit Timer */
#define T6_32BIT_MODE_OFF   0x0000
#define T6_32BIT_MODE_MASK   (~T6_32BIT_MODE_ON)

#define T6_SOURCE_EXT       0x0002 /* External clock source */
#define T6_SOURCE_INT       0x0000 /* Internal clock source */
#define T6_SOURCE_MASK      (~T6_SOURCE_EXT)
#endif

#ifdef _T7IF
/* T7CON: TIMER7 CONTROL REGISTER */
#define T7_ON               0x8000      /* Timer7 ON */
#define T7_OFF              0x0000      /* Timer7 OFF */
#define T7_OFF_ON_MASK      (~T7_ON)

#define T7_IDLE_STOP        0x2000 /* operate during sleep */
#define T7_IDLE_CON         0x0000 /* stop operation during sleep */
#define T7_IDLE_MASK        (~T7_IDLE_STOP)

#define T7_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T7_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T7_GATE_MASK        (~T7_GATE_ON)

#define T7_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T7_PS_1_8           0x0010      /*           1:8 */
#define T7_PS_1_64          0x0020      /*          1:64 */
#define T7_PS_1_256         0x0030      /*         1:256 */
#define T7_PS_MASK          (~T7_PS_1_256)

#define T7_SOURCE_EXT       0x0002 /* External clock source */
#define T7_SOURCE_INT       0x0000 /* Internal clock source */
#define T7_SOURCE_MASK      (~T7_SOURCE_EXT)
#endif

#ifdef _T8IF
/* T8CON: TIMER8 CONTROL REGISTER */
#define T8_ON               0x8000      /* Timer8 ON */
#define T8_OFF              0x0000      /* Timer8 OFF */
#define T8_OFF_ON_MASK      (~T8_ON)

#define T8_IDLE_STOP        0x2000 /* operate during sleep */
#define T8_IDLE_CON         0x0000 /* stop operation during sleep */
#define T8_IDLE_MASK        (~T8_IDLE_STOP)

#define T8_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T8_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T8_GATE_MASK        (~T8_GATE_ON)

#define T8_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T8_PS_1_8           0x0010      /*           1:8 */
#define T8_PS_1_64          0x0020      /*          1:64 */
#define T8_PS_1_256         0x0030      /*         1:256 */
#define T8_PS_MASK          (~T8_PS_1_256)

#define T8_32BIT_MODE_ON    0x0008      /* Timer 8 and Timer 9 form a 32 bit Timer */
#define T8_32BIT_MODE_OFF   0x0000
#define T8_32BIT_MODE_MASK   (~T8_32BIT_MODE_ON)

#define T8_SOURCE_EXT       0x0002 /* External clock source */
#define T8_SOURCE_INT       0x0000 /* Internal clock source */
#define T8_SOURCE_MASK      (~T8_SOURCE_EXT)
#endif

#ifdef _T9IF
/* T9CON: TIMER9 CONTROL REGISTER */
#define T9_ON               0x8000      /* Timer9 ON */
#define T9_OFF              0x0000      /* Timer9 OFF */
#define T9_OFF_ON_MASK      (~T9_ON)

#define T9_IDLE_STOP        0x2000 /* operate during sleep */
#define T9_IDLE_CON         0x0000 /* stop operation during sleep */
#define T9_IDLE_MASK        (~T9_IDLE_STOP)

#define T9_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T9_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T9_GATE_MASK        (~T9_GATE_ON)

#define T9_PS_1_1           0x0000      /* Prescaler 1:1 */
#define T9_PS_1_8           0x0010      /*           1:8 */
#define T9_PS_1_64          0x0020      /*          1:64 */
#define T9_PS_1_256         0x0030      /*         1:256 */
#define T9_PS_MASK          (~T9_PS_1_256)

#define T9_SOURCE_EXT       0x0002 /* External clock source */
#define T9_SOURCE_INT       0x0000 /* Internal clock source */
#define T9_SOURCE_MASK      (~T9_SOURCE_EXT)
#endif

//Input Capture macros

/*
The following macros are a subset of the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/incap.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/incap.h header.
*/
#if (defined(__dsPIC33E__) || defined(__PIC24E__))
#define IC_IDLE_STOP            0x2000 /* IC stop in sleep mode */
#define IC_IDLE_CON             0x0000 /* IC operate in sleep mode */
#define IC_IDLE_MASK            (~IC_IDLE_STOP)

#define IC_FP_SRC               (7 << 10) /* Peripheral Clock is the clock source for Capture */
#define IC_TIMER1_SRC           (4 << 10) /* Timer1 is the clock source for Capture */
#define IC_TIMER5_SRC           (3 << 10) /* Timer5 is the clock source for Capture */
#define IC_TIMER4_SRC           (2 << 10) /* Timer4 is the clock source for Capture */
#define IC_TIMER2_SRC           (1 << 10) /* Timer2 is the clock source for Capture */
#define IC_TIMER3_SRC           0x0000 /* Timer3 is the clock source for Capture */
#define IC_TIMER_SRC_MASK       (~ (7 << 10) )

#define IC_INT_4CAPTURE         0x0060  /* Interrupt on fourth Capture*/
#define IC_INT_3CAPTURE         0x0040 /* Interrupt on third Capture */
#define IC_INT_2CAPTURE         0x0020 /* Interrupt on second Capture*/
#define IC_INT_1CAPTURE         0x0000 /* Interrupt on first Capture */
#define IC_INT_CAPTURE_MASK     (~IC_INT_4CAPTURE)

#define IC_INTERRUPT            0x0007 /* Interrupt pin only in CPU sleep and idle mode */
#define IC_EVERY_16_RISE_EDGE   0x0005 /* Every 16th rising edge */
#define IC_EVERY_4_RISE_EDGE    0x0004 /* Every 4th rising edge  */
#define IC_EVERY_RISE_EDGE      0x0003 /* Every rising edge      */
#define IC_EVERY_FALL_EDGE      0x0002 /* Every falling edge      */
#define IC_EVERY_EDGE           0x0001 /* Every rising/falling edge */
#define IC_INPUTCAP_OFF         0x0000 /* Input Capture Off      */
#define IC_CAPTURE_MODE_MASK    (~IC_INTERRUPT)

//ICxCON2 register bits (dsPIC33E/PIC24E)
#define IC_IC32_ON             (0x01 << 8)
#define IC_IC32_OFF            (0x00 << 8)
#define IC_TRIG_MODE           (0x01 << 7)
#define IC_SYNC_MODE           (0x00 << 7)

//Sync/Trigger Bits for Input Capture
//these are device dependent, but this works for many devices
#define IC_SYNCSEL_NOSYNC          0x00
#define IC_SYNCSEL_OC1             0x01
#define IC_SYNCSEL_OC2             0x02
#define IC_SYNCSEL_OC3             0x03
#define IC_SYNCSEL_OC4             0x04
#define IC_SYNCSEL_PTGO            0x0A
#define IC_SYNCSEL_TIMER1          0x0B
#define IC_SYNCSEL_TIMER2          0x0C
#define IC_SYNCSEL_TIMER3          0x0D
#define IC_SYNCSEL_TIMER4          0x0E
#define IC_SYNCSEL_TIMER5          0x0F
#define IC_SYNCSEL_IC1             0x10
#define IC_SYNCSEL_IC2             0x11
#define IC_SYNCSEL_IC3             0x12
#define IC_SYNCSEL_IC4             0x13
#define IC_SYNCSEL_CMP1            0x18
#define IC_SYNCSEL_CMP2            0x19
#define IC_SYNCSEL_CMP3            0x1A
#define IC_SYNCSEL_ADC1            0x1B
#define IC_SYNCSEL_CTMU            0x1C



#else
#define IC_IDLE_STOP            0x2000 /* IC stop in sleep mode */
#define IC_IDLE_CON             0x0000 /* IC operate in sleep mode */
#define IC_IDLE_MASK            (~IC_IDLE_STOP)

#define IC_TIMER2_SRC           0x0080 /* Timer2 is the clock source for Capture */
#define IC_TIMER3_SRC           0x0000 /* Timer3 is the clock source for Capture */
#define IC_TIMER_SRC_MASK       (~IC_TIMER2_SRC)

#define IC_INT_4CAPTURE         0x0060  /* Interrupt on fourth Capture*/
#define IC_INT_3CAPTURE         0x0040 /* Interrupt on third Capture */
#define IC_INT_2CAPTURE         0x0020 /* Interrupt on second Capture*/
#define IC_INT_1CAPTURE         0x0000 /* Interrupt on first Capture */
#define IC_INT_CAPTURE_MASK     (~IC_INT_4CAPTURE)

#define IC_INTERRUPT            0x0007 /* Interrupt pin only in CPU sleep and idle mode */
#define IC_EVERY_16_RISE_EDGE   0x0005 /* Every 16th rising edge */
#define IC_EVERY_4_RISE_EDGE    0x0004 /* Every 4th rising edge  */
#define IC_EVERY_RISE_EDGE      0x0003 /* Every rising edge      */
#define IC_EVERY_FALL_EDGE      0x0002 /* Every falling edge      */
#define IC_EVERY_EDGE           0x0001 /* Every rising/falling edge */
#define IC_INPUTCAP_OFF         0x0000 /* Input Capture Off      */
#define IC_CAPTURE_MODE_MASK    (~IC_INTERRUPT)
#endif

//Output Compare macros

/*
The following macros are a subset of the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/outcompare.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/outcompare.h header.
*/

#if (defined(__dsPIC33E__) || defined(__PIC24E__))
#define OC_IDLE_CON                0x0000 /*  continue operation in idle mode */
#define OC_IDLE_STOP               0x2000 /* stop in idle mode */
#define OC_IDLE_MASK               (~OC_IDLE_STOP)
#define OC_TIMER2_SRC               (0 << 10)        /* Timer2 is the clock source for OutputCompare */
#define OC_TIMER3_SRC               (1 << 10)        /* Timer3 is the clock source for OutputCompare */
#define OC_TIMER4_SRC               (2 << 10)        /* Timer3 is the clock source for OutputCompare */
#define OC_TIMER5_SRC               (3 << 10)        /* Timer3 is the clock source for OutputCompare */
#define OC_TIMER1_SRC               (4 << 10)        /* Timer3 is the clock source for OutputCompare */
#define OC_FP_SRC                   (7 << 10)        /* Peripheral Clock is the clock source for OutputCompare */


#define OC_PWM_CENTER_ALIGN         0x0007 /* PWM Mode on OCx, fault pin enabled, (TxIF bit is set for PWM, OCxIF is set for fault)*/
#define OC_PWM_EDGE_ALIGN           0x0006 /* PWM Mode on OCx, fault pin disabled */
#define OC_CONTINUE_PULSE           0x0005 /* Generates Continuous Output pulse on OCx Pin */
#define OC_SINGLE_PULSE             0x0004 /* Generates Single Output pulse on OCx Pin */
#define OC_TOGGLE_PULSE             0x0003 /* Compare1 toggles  OCx pin*/
#define OC_HIGH_LOW                 0x0002 /* Compare1 forces   OCx pin Low*/
#define OC_LOW_HIGH                 0x0001 /* Compare1 forces  OCx pin High*/
#define OC_OFF                      0x0000 /* OutputCompare x Off*/
#define OC_PWM_MODE_MASK            (~OC_PWM_FAULT_PIN_ENABLE)

#define OC_PWM_FAULT_PIN_ENABLE     0x0007 /* PWM Mode on OCx, keep for compatibility with PIC24H source*/
#define OC_PWM_FAULT_PIN_DISABLE    0x0006 /* PWM Mode on OCx, keep for compatibility with PIC24H source */

//OCxCON2 register bits (dsPIC33E/PIC24E)
#define OC_FLTMD_ON               (0x01 << 15)
#define OC_FLTMD_OFF              (0x00 << 15)
#define OC_FLTOUT_ON               (0x01 << 14)
#define OC_FLTOUT_OFF              (0x00 << 14)
#define OC_FLTTRIEN_ON             (0x01 << 13)
#define OC_FLTTRIEN_OFF            (0x00 << 13)
#define OC_OCINV_ON                (0x01 << 12)
#define OC_OCINV_OFF               (0x00 << 12)

#define OC_IC32_ON             (0x01 << 8)
#define OC_IC32_OFF            (0x00 << 8)
#define OC_TRIG_MODE           (0x01 << 7)
#define OC_SYNC_MODE           (0x00 << 7)
#define OC_TRIS_ON             (0x01 << 5)
#define OC_TRIS_OFF            (0x00 << 5)

//Sync/Trigger Bits for Input Capture
//these are device dependent, but this works for many devices
#define OC_SYNCSEL_NOSYNC          0x00
#define OC_SYNCSEL_OC1             0x01
#define OC_SYNCSEL_OC2             0x02
#define OC_SYNCSEL_OC3             0x03
#define OC_SYNCSEL_OC4             0x04
#define OC_SYNCSEL_PTGO            0x0A
#define OC_SYNCSEL_TIMER1          0x0B
#define OC_SYNCSEL_TIMER2          0x0C
#define OC_SYNCSEL_TIMER3          0x0D
#define OC_SYNCSEL_TIMER4          0x0E
#define OC_SYNCSEL_TIMER5          0x0F
#define OC_SYNCSEL_IC1             0x10
#define OC_SYNCSEL_IC2             0x11
#define OC_SYNCSEL_IC3             0x12
#define OC_SYNCSEL_IC4             0x13
#define OC_SYNCSEL_CMP1            0x18
#define OC_SYNCSEL_CMP2            0x19
#define OC_SYNCSEL_CMP3            0x1A
#define OC_SYNCSEL_ADC1            0x1B
#define OC_SYNCSEL_CTMU            0x1C
#define OC_SYNCSEL_INT1            0x1D
#define OC_SYNCSEL_INT2            0x1E
#define OC_SYNCSEL_OCxRS           0x1F

#else
/* Section : Output Compare Stop in Idle mode Bit defines */
#define OC_IDLE_CON                0x0000 /*  continue operation in idle mode */
#define OC_IDLE_STOP               0x2000 /* stop in idle mode */
#define OC_IDLE_MASK               (~OC_IDLE_STOP)

/*Section :  Output Compare timer select Bit Defines */
#define OC_TIMER2_SRC               0x0000 /* Timer2 is the clock source for OutputCompare */
#define OC_TIMER3_SRC               0x0008 /* Timer3 is the clock source for OutputCompare */
#define OC_TIMER_SRC_MASK           (~OC_TIMER3_SRC)

#define OC_PWM_FAULT_PIN_ENABLE     0x0007 /* PWM Mode on OCx, fault pin enabled, (TxIF bit is set for PWM, OCxIF is set for fault)*/
#define OC_PWM_FAULT_PIN_DISABLE    0x0006 /* PWM Mode on OCx, fault pin disabled */
#define OC_CONTINUE_PULSE           0x0005 /* Generates Continuous Output pulse on OCx Pin */
#define OC_SINGLE_PULSE             0x0004 /* Generates Single Output pulse on OCx Pin */
#define OC_TOGGLE_PULSE             0x0003 /* Compare1 toggles  OCx pin*/
#define OC_HIGH_LOW                 0x0002 /* Compare1 forces   OCx pin Low*/
#define OC_LOW_HIGH                 0x0001 /* Compare1 forces  OCx pin High*/
#define OC_OFF                      0x0000 /* OutputCompare x Off*/
#define OC_PWM_MODE_MASK            (~OC_PWM_FAULT_PIN_ENABLE)
#endif
