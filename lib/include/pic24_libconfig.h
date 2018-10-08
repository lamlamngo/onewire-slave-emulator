/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  This file consolidates all the user-configurable \#defines
 *  scattered throughout the \ref PIC24_support
 *  "PIC24 support library". These may be changed by
 *  editing the \#defines below, or by defining them via passing
 *  a <code>-Dname=value</code> flag to the compiler.
 */

#pragma once

// Needed by HB_LED config.
#include <xc.h>


/** @name Supported hardware platforms
 *  This library supports the following hardware platforms.
 *  More can easily be added.
 *
 * Note: Do NOT \#define MY_HARDWARE_PLATFORM (0). If the user then tries
 * -D HARDWARE_PLATFORM=FOO, FOO will evaluate to 0, making it an
 * accidentally default choice.
 */
//@{
/** The Microchip Explorer 16 Development Board
 *  with a 100-pin plug-in module, part number DM240001.
 */
#define EXPLORER16_100P (-1)

/** The Dangerous Prototypes web platform.
 *  See http://dangerousprototypes.com/docs/Web_platform_hardware_design
 */
#define DANGEROUS_WEB (1)

/** The Microchip 16-bit 28-pin Starter Board,
 *  Part number DM300027. Thanks to István for contributing this!
 *
 *  Note: When you use a Microchip 16-bit 28-pin Starter Board with this
 *  library collection or just try out the example programs of the
 *  texbook, the SW2 switch shoud be set in the USB/debug state.
 */
#define STARTER_BOARD_28P (2)

/** Any of three targets, which share the same hardware configuration:
 *  1. The schematic on pg. 255 of the book
 *     "Microcontrollers: From Assembly Language to C Using the PIC24 Family"
 *  2. The Microchip Microstik for dsPIC33F and PIC24H Development Board,
 *     part number DM330013.
 *  3. The Sparkfun Breakout Board for PIC24HJ32 - mini-Bully
 *     sku: BOB-08787
 */
#define DEFAULT_DESIGN (3)

/** A device with hard-mapped pins for UART TX and RX. */
#define HARDMAPPED_UART (4)

/**
 * Microchip part number: dm330013-2
 *
 * Microstick II delivers a complete development hardware platform for Microchip’s 16-bit and 32-bit
 * microcontrollers and digital signal controllers. It’s the perfect solution to those looking for a
 * low-cost, easy-to-use development platform.
 * The USB-powered kit includes an on-board debugger/programmer, a DUT socket for easy device swapping,
 * a user LED and reset button. It is designed for insertion into a standard prototyping board for easy
 * connection to additional circuitry. The kit is extremely portable as well and is still about the size
 * of a stick of gum!
 *
 * Supported Parts: All 3.3V PIC24FJ, PIC24E, PIC24H, dsPIC33, and PIC32 28-pin SPDIP packaged devices.
 */
#define MICROSTICK2 (5)

/** The CAN2 rev C1 board used for Embedded Systems, ECE 4723, at Mississippi State University (Fall 2013) */
#define EMBEDDED_C1 (472313)

/** The CAN2 rev C1 board used for Embedded Systems, ECE 4723, at Mississippi State University (Fall 2014) */
#define EMBEDDED_F14 (472314)

/** Select one of the hardware platform above to compile for. */
#ifndef HARDWARE_PLATFORM
# define HARDWARE_PLATFORM DEFAULT_DESIGN
#endif
// Verify that a valid hardware platform is selectd
#if (HARDWARE_PLATFORM != EXPLORER16_100P)   && \
    (HARDWARE_PLATFORM != DANGEROUS_WEB)     && \
    (HARDWARE_PLATFORM != STARTER_BOARD_28P) && \
    (HARDWARE_PLATFORM != MICROSTICK2)       && \
    (HARDWARE_PLATFORM != DEFAULT_DESIGN)    && \
    (HARDWARE_PLATFORM != HARDMAPPED_UART)   && \
    (HARDWARE_PLATFORM != EMBEDDED_C1)       && \
    (HARDWARE_PLATFORM != EMBEDDED_F14)
# error "Invalid hardware platform selected."
#endif
//@}

// Defines for compiling the bootloader
#ifdef BOOTLOADER
# define USE_HEARTBEAT (1)
# define USE_CLOCK_TIMEOUT (0)
# define _NOASSERT
# define _NOFLOAT
#endif

// Defines for compiling ESOS.
#ifdef BUILT_ON_ESOS
# define USE_HEARTBEAT (0)
# define _NOASSERT
# define _NOFLOAT
#endif

/** @{
 *  \name Defines configuring pic24_clockfreq.h
 */

/** Clock configuration for the PIC24 - set CLOCK_CONFIG
 *  to one of the following. Naming convention is
 *  OSCTYPE_[PRIFREQ]_FCYFREQ where OSCTYPE gives the
 *  oscillator type (see \ref FNOSC_SEL for details),
 *  the optional PRIFREQ specifies primary oscillator frequency,
 *  and FCYFREQ determiens the processor clock
 *  (F<sub>CY</sub>) frequency. The "#defines for CLOCK_CONFIG"
 *  section gives the definition of the values below.
 *
 *  Name                           | uP
 *  ---------------                | ---
 *  SIM_CLOCK (simulator)          | any
 *  FRCPLL_FCY16MHz                | PIC24F, PIC24FK
 *  FRC_FCY4MHz                    | PIC24F, PIC24FK
 *  PRI_NO_PLL_7372KHzCrystal      | PIC24F, PIC24FK, PIC24H, dsPIC33F
 *  FRC_FCY3685KHz                 | PIC24H, dsPIC33F, PIC24E, dsPIC33E
 *  FRCPLL_FCY40MHz                | PIC24H, dsPIC33F
 *  PRIPLL_7372KHzCrystal_40MHzFCY | PIC24H, dsPIC33F
 *  PRIPLL_8MHzCrystal_40MHzFCY    | PIC24H, dsPIC33F, PIC24E, dsPIC33E
 *  PRIPLL_8MHzCrystal_16MHzFCY    | PIC24F, PIC24FK
 *  PRI_8MHzCrystal_4MHzFCY        | PIC24F, PIC24FK, PIC24H, dsPIC33F
 *  FRCPLL_FCY60MHz                | PIC24E, dsPIC33E
 *  FRCPLL_FCY70MHz                | PIC24E, dsPIC33E (limited temp. range)
 */
// Uncomment one of the #defines below to make
// a clock choice. If all the #defines below
// are commented out, code in below
// will pick a default clock choice.
#ifndef CLOCK_CONFIG
//#define CLOCK_CONFIG SIM_CLOCK
//#define CLOCK_CONFIG FRCPLL_FCY16MHz
//#define CLOCK_CONFIG FRC_FCY4MHz
//#define CLOCK_CONFIG PRI_NO_PLL_7372KHzCrystal
//#define CLOCK_CONFIG FRC_FCY3685KHz
//#define CLOCK_CONFIG FRCPLL_FCY40MHz
//#define CLOCK_CONFIG PRIPLL_7372KHzCrystal_40MHzFCY
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_40MHzFCY
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_16MHzFCY
//#define CLOCK_CONFIG PRI_8MHzCrystal_4MHzFCY
//#define CLOCK_CONFIG FRCPLL_FCY60MHz
//#define CLOCK_CONFIG FRCPLL_FCY70MHz
#endif

// If no clock was selected, pick a default: choose the fastest
// possible clock depending on which
// processor we're using. If simulation mode is
// selected, then use the simulation clock.
#ifndef CLOCK_CONFIG
# if defined(SIM)
#   define CLOCK_CONFIG SIM_CLOCK
# elif (HARDWARE_PLATFORM == EXPLORER16_100P) && defined(__PIC24H__)
#   define CLOCK_CONFIG PRIPLL_8MHzCrystal_40MHzFCY
# elif (HARDWARE_PLATFORM == EXPLORER16_100P) && defined(__PIC24F__)
#   define CLOCK_CONFIG PRIPLL_8MHzCrystal_16MHzFCY
# elif defined(__PIC24H__) || defined(__DOXYGEN__)
#   define CLOCK_CONFIG FRCPLL_FCY40MHz
# elif defined(__PIC24F__) || defined(__PIC24FK__)
#   define CLOCK_CONFIG FRCPLL_FCY16MHz
# elif defined(__dsPIC33F__)
#   define CLOCK_CONFIG FRCPLL_FCY40MHz
# elif defined(__PIC24E__) || defined(__dsPIC33E__)
//  60MHz clock is a conservative max choice for PIC24E, 70MHz has a more limited temp. range.
#   define CLOCK_CONFIG FRCPLL_FCY60MHz
# else
#   error "Unknown processor."
# endif
#endif

/// @}

/** \name Defines configuring pic24_delay.h
 *  @{
 */

/** Define a debounce delay for use in reading pushbutton
 *  switches. The value is specified in milliseconds.
 */
#ifndef DEBOUNCE_DLY
// In milliseconds.
# define DEBOUNCE_DLY  (15)
#endif

/// @}



/** \name outString() end-of-line behavior in pic24_serial.h
 *  @{
 */

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a CR with every LF in outString.
 *  PuTTY uses this, expects "\n\r".
 */
#define SERIAL_EOL_CR_LF (0)

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a carriage return only ("\r") to end a line.
 */
#define SERIAL_EOL_CR   (1)

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  sends a new line only ("\n"). This
 *  works for Bully Bootloader, MPLAB SIM, TeraTerm,
 *  RealTerm.
 */
#define SERIAL_EOL_LF   (2)

/** This macro defines end-of-line output behavior
 *  when the \ref outString() function is passed a new line ("\n").
 *  Set this to either \ref SERIAL_EOL_CR_LF, \ref SERIAL_EOL_CR, or
 *  \ref SERIAL_EOL_LF.
 */
#ifndef SERIAL_EOL_DEFAULT   //can be overridden in project file
# define SERIAL_EOL_DEFAULT SERIAL_EOL_LF
#endif

#if (SERIAL_EOL_DEFAULT != SERIAL_EOL_CR_LF) && \
    (SERIAL_EOL_DEFAULT != SERIAL_EOL_CR)    && \
    (SERIAL_EOL_DEFAULT != SERIAL_EOL_LF)
# error "Invalid choice for SERIAL_EOF_DEFAULT."
#endif

/// @}

/** \name Defines from pic24_serial.h
 *  @{
 */
/** Defines the default UART which the configUART() function
 *  initializes and which serial I/O is directed to
 *  until the _C30_UART variable is changed.
 */
#ifndef DEFAULT_UART
# if (HARDWARE_PLATFORM == EXPLORER16_100P)
#   define DEFAULT_UART (2)
# else
#   define DEFAULT_UART (1)
# endif
#endif



/** Default baud rate used by \ref configBasic() to
 * configure the \ref DEFAULT_UART.
 */
#ifndef DEFAULT_BAUDRATE
// For convenience, common baud rates (uncomment one):
// If none are select, a default will be chosen below.
//# define DEFAULT_BAUDRATE  (230400)
//# define DEFAULT_BAUDRATE  (115200)
//# define DEFAULT_BAUDRATE   (57600)
//# define DEFAULT_BAUDRATE   (38400)
//# define DEFAULT_BAUDRATE   (19200)
//# define DEFAULT_BAUDRATE    (9600)
#endif

#ifndef DEFAULT_BAUDRATE
# if defined(__PIC24F__) || defined(__PIC24FK__)
// The PIC24F/FK's 16 MHz max frequency using the inaccurate FRC means a lower
// default baud rate is a safer choice.
#   define DEFAULT_BAUDRATE   (57600)
# else
#   define DEFAULT_BAUDRATE  (230400)
# endif
#endif

/** Default BRGH value used by \ref configUART1 to 4
 *  when configuring a UART. This value may be
 *  overridden on a per-UART basis by \#defineing
 *  DEFAULT_BRGHn (where n = the UART to override)
 *  to the values given below. Allowed values:
 *  - BRGH = 0 - the baud rate divisor is 16
 *  - BRGH = 1 - the baud rate divisor is 4
 */
#ifndef DEFAULT_BRGH
# define DEFAULT_BRGH  (0)
#endif

#if (DEFAULT_BRGH != 0) && (DEFAULT_BRGH != 1)
# error "Invalid value for DEFAULT_BRGH."
#endif

/// @}

/** \name Defines configuring pic24_util.h
 *  @{
 */

/** When set to 1, verify that calls to switchClock() do
 *  successfully switch the clock, reporting an error
 *  message on failure. See also checkClockTimeout().
 */
#ifndef USE_CLOCK_TIMEOUT
# ifdef BUILT_ON_ESOS
#   define USE_CLOCK_TIMEOUT (0)
# else
#   define USE_CLOCK_TIMEOUT (1)
# endif
#endif

/* \name Heartbeat
 *  These routines provide heartbeat support by blinking a LED
 *  on a regular basis. See doHeartbeat() for more information.
 */
//@{

#ifndef USE_HEARTBEAT
/** If this macro is true, heartbeat functionality is enabled.
 *  If false, heartbeat is disabled.
 */
# define USE_HEARTBEAT (1)
#endif


#ifndef HB_LED
# if (HARDWARE_PLATFORM == EXPLORER16_100P)
#   define HB_LED _LATA7
#   define CONFIG_HB_LED() CONFIG_RA7_AS_DIG_OUTPUT()
# elif (HARDWARE_PLATFORM == DANGEROUS_WEB)
#   define HB_LED _LATA8
#   define CONFIG_HB_LED() CONFIG_RA8_AS_DIG_OUTPUT()
# elif (HARDWARE_PLATFORM == MICROSTICK2)
#   define HB_LED _LATA0
#   define CONFIG_HB_LED() CONFIG_RA0_AS_DIG_OUTPUT()
# else // All other hardware platforms
/** Choose a pin for the heartbeat.
 *  If \ref USE_HEARTBEAT is false, the heartbeat is disabled.
 */
#   define HB_LED (_LATB15)
/** Define a config function for the heartbeat pin. */
#   if (defined(_ODCB15) || defined(_ODB15))
#     define CONFIG_HB_LED()            \
        do {                            \
          CONFIG_RB15_AS_DIG_OUTPUT();  \
          ENABLE_RB15_OPENDRAIN();      \
        } while (0)
#   else
#     define CONFIG_HB_LED() CONFIG_RB15_AS_DIG_OUTPUT()
#   endif
# endif
#endif // #ifndef HB_LED

/// @}
