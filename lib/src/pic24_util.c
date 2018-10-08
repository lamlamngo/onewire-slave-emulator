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
 *  This file contains implementations for functions prototyped
 *  in pic24_util.h.
 */

#include "pic24_util.h"
#include "pic24_serial.h"
#include "pic24_clockfreq.h"
#include "pic24_ports.h"
#include "pic24_delay.h"
#include "pic24_unittest.h"
#include <stdio.h>        // To define NULL


#if !USE_HEARTBEAT && !defined(__DOXYGEN__)
// No heartbeat; instead, just define empty functions.
void configHeartbeat(void) {
}

void doHeartbeat(void) {
}

void toggleHeartbeat(void) {
}
#else

/** \name Heartbeat
 *  @{
 *  These routines provide heartbeat support by blinking a LED
 *  on a regular basis. See doHeartbeat() for more information.
 *
 */
/** The current heartbeat count. When this value reaches
 *  \ref HEARTBEAT_MAX, the heartbeat LED is toggled by
 *   doHeartbeat().
 * \see doHeartbeat
 */
_PERSISTENT uint32_t u32_heartbeatCount;
/** When u32_heartbeatCount reaches this maximum, the
 *  heartbeat LED is toggled by doHeartbeat().
 */
#ifdef BOOTLOADER
# define MS_PER_HEARTBEAT (1)
#else
# define MS_PER_HEARTBEAT (10)
#endif

/// The approximate half period, in processor cycles, of the heartbeat.
#define HEARTBEAT_MAX (CYCLES_PER_MS * MS_PER_HEARTBEAT)


/** Configures a GPIO pin for use with the heartbeat and sets
 *  up the heartbeat counter.
 *  \see doHeartbeat
 */
void configHeartbeat(void) {
  CONFIG_HB_LED();
  /* long enough to see LED toggle. Incrementing the heartbeat
  takes several cycles - CYCLES_PER_MS used as the multiplier so that
  we are tied to FCY.
  */
  u32_heartbeatCount = HEARTBEAT_MAX;
  // Turn LED off to show we started running
  HB_LED = 0;
}

/** This heartbeat function should be called
 *  repeatedly in any sort of blocking wait loop. It will
 *  periodically toggle an LED after \ref HEARTBEAT_MAX increments.
 */
void doHeartbeat(void) {
  --u32_heartbeatCount;
  if (u32_heartbeatCount == 0) {
    toggleHeartbeat();
    u32_heartbeatCount = HEARTBEAT_MAX;
  }
}


/** A function which toggles the heartbeat LED.
    \see doHeartbeat
  */
void toggleHeartbeat(void) {
  HB_LED = !HB_LED;
}
/// @}
#endif


#ifndef BOOTLOADER

/** Persistent storage for an error message, typically
 *  set by \ref reportError and reported at reset by
 *  \ref printResetCause.
 */
static _PERSISTENT const char* sz_lastError;

/** Persistent storage for a timeout error, to be reported
 *  if a watchdog reset occurs.
 */
_PERSISTENT const char* sz_lastTimeoutError;

/** Store a copy of the INTTREG register as a bitfield.
 *  This is not defined for all PICs, so work around
 *  with an \#ifdef of ILR, one of the bitfields in this register.
 *  This is _PERSISTENT so that it
 *  survives the resets which occurs immeidately after
 *  the default interrupt handler \ref _DefaultInterrupt
 *  copies INTTREG to this variable.
 */
# ifdef _ILR
static _PERSISTENT INTTREGBITS INTTREGBITS_last;

/** Make the \ref INTTREGBITS_last also accessible as
 *  a word. This is like <code>uint16_t u16_INTTREGlast</code>
 *  except that INTTREGBITS_last and u16_INTTREGlast
 *  refer to the same data.
 */
#   define u16_INTTREGlast BITS2WORD(INTTREGBITS_last)
# else
static uint16_t u16_INTTREGlast;
# endif

/** Provide a default interrupt handler which records what
 *  interrupt was not handled then resets the chip. Typically,
 *  a call to \ref printResetCause during chip startup will then
 *  print the error.
 */
void _ISR _DefaultInterrupt(void) {
# ifdef _ILR
  // Record the interrupt vector and priority of the
  // unhandled interrupt.
  u16_INTTREGlast = INTTREG;
# else
  // Any non-zero value causes reportError to report
  // this. This register doesn't exist on the PIC24F.
  u16_INTTREGlast = 1;
# endif
  reportError("Unhandled interrupt, ");
}


/** Report a critical error by recording a message
 *  in \ref sz_lastError then resetting the chip,
 *  assuming hat \ref printResetCause will be called
 *  during chip initialization.
 *  \param sz_errorMessage Error message to report.
 *  \see REPORT_ERROR
 */
void reportError(const char* sz_errorMessage) {
  //ignore if a previous error has already been triggerred
  if (sz_lastError == NULL) {
    sz_lastError = sz_errorMessage;
    asm("reset");
  }
}

/** Reads a 24-bit program memory word at the given address.
 *  \param u32_address Address of program memory to read.
 *  \return The 24-bit program memory word at u32_address.
 *          The upper 8 bits are 0.
 */
uint32_t readProgramMemory(uint32_t u32_address) {
  uint16_t u16_offset = u32_address;
  TBLPAG = u32_address >> 16;
  return ( ((uint32_t) __builtin_tblrdh(u16_offset)) << 16) |
         __builtin_tblrdl(u16_offset);
}

/** Determines the device and revision of the PIC this program
 *  is executing on. This information is then output via the default
 *  UART. A warning message is issued if this program was not compiled
 *  for the chip it is running on.
 */
void checkDeviceAndRevision(void) {
# ifdef SIM
  outString("**** SIMULATION MODE: cannot read device and revision ID ****\n");
# else
  uint32_t devID = readProgramMemory(DEV_ID_LOCATION);
  uint32_t revision = readProgramMemory(REVISION_LOCATION);
  uint8_t correctChip = 1;
  const char* devIDStr = "unknown";
  const char* revisionStr = "unknown";

  if (devID == DEV_ID)
    devIDStr = DEV_ID_STR;
  else
    correctChip = 0;

  switch (revision) {
    case EXPECTED_REVISION1 :
      revisionStr = EXPECTED_REVISION1_STR;
      break;
#   ifdef EXPECTED_REVISION2
    case EXPECTED_REVISION2 :
      revisionStr = EXPECTED_REVISION2_STR;
      break;
#   endif
#   ifdef EXPECTED_REVISION3
    case EXPECTED_REVISION3 :
      revisionStr = EXPECTED_REVISION3_STR;
      break;
#   endif
#   ifdef EXPECTED_REVISION4
    case EXPECTED_REVISION4 :
      revisionStr = EXPECTED_REVISION4_STR;
      break;
#   endif
#   ifdef EXPECTED_REVISION5
    case EXPECTED_REVISION5 :
      revisionStr = EXPECTED_REVISION5_STR;
      break;
#   endif
  }

  outString("Device ID = ");
  outUint32(devID);
  outString(" (");
  outString(devIDStr);
  outString("), revision ");
  outUint32(revision);
  outString(" (");
  outString(revisionStr);
  outString(")\n");

  if (!correctChip)
    outString("\n\n"
              "******************************************************\n"
              "* WARNING - this program was compiled for the wrong  *\n"
              "* chip. This program may produce unexpected behvior! *\n"
              "* Edit the header files to properly define this chip *\n"
              "* and to insure correct operation.                   *\n"
              "*                                                    *\n"
              "* NOTE: If this was compiled for the correct chip,   *\n"
              "* and only occurs at power-on (not during a MCLR     *\n"
              "* reset), verify that AVDD and AVSS are connected.   *\n"
              "* On the PIC24H32GP202, not connecting AVDD          *\n"
              "* produces this message only at power-up.            *\n"
              "******************************************************\n");
# endif
}

/** Reports the oscillator currently in use to the default
 *  serial port. See \ref FNOSC_SEL for a table of which chips support which
 *  clocks.
 */
void checkOscOption(void) {
  switch (_COSC) {
    case 0:
      outString("Fast RC Osc\n");
      break;
    case 1:
      outString("Fast RC Osc with PLL\n");
      break;
    case 2:
      outString("Primary Osc (XT, HS, EC)\n");
      break;
    case 3:
      outString("Primary Osc (XT, HS, EC) with PLL\n");
      break;
    case 4:
      outString("Secondary Osc\n");
      break;
    case 5:
      outString("Low Power RC Osc\n");
      break;
# if defined(__PIC24H__) || defined(__dsPIC33F__) || defined(__PIC24E__) || defined(__dsPIC33E__)
    case 6:
      outString("Fast RC Osc/16\n");
      break;
    case 7:
      outString("Fast RC Osc/N\n");
      break;
# elif defined(__PIC24F__) || defined(__PIC24FK__)
#   ifdef __PIC24FK__
    case 6:
      outString("Low power fast RC Osc with Postscaler\n");
      break;
#   endif
    case 7 :
      outString("Fast RC Osc with Postscaler\n");
      break;
# else
# error "Unknown processor."
# endif
    default :
      reportError("Unknown oscillator type.");
      break;
  }
}

/** Determines and prints the cause of a CPU reset. This should
 *  be called when the chip first starts up. For an example, see
 *  the \ref configBasic function.
 */
void printResetCause(void) {
  uint8_t u8_resetIdentified;

  u8_resetIdentified = 0;
  if (_SLEEP) {
    outString("\nDevice has been in sleep mode\n");
    _SLEEP = 0;
  }
  if (_IDLE) {
    outString("\nDevice has been in idle mode\n");
    _IDLE = 0;
  }
  outString("\nReset cause: ");
  if (_POR) {
    u8_resetIdentified = 1;
    outString("Power-on.\n");
    _POR = 0;
    _BOR = 0; //clear both
    // Set the values below, which reset all the
    // error reporting variables to indicate that
    // no error has (yet) occurred.
    sz_lastError = NULL;
    sz_lastTimeoutError = NULL;
    u16_INTTREGlast = 0;
  } else {
    //non-POR
    if (_SWR) {
      outString("Software Reset.\n");
      u8_resetIdentified = 1;
      _SWR = 0;
      _EXTR = 0;  //also sets the EXTR bit
    }
    if (_WDTO) {
      u8_resetIdentified = 1;
      outString("Watchdog Timeout: ");
      if (sz_lastTimeoutError != NULL) {
        outString(sz_lastTimeoutError);
      }
      outString("\n");
      _WDTO = 0;
      _EXTR = 0; //also sets the EXTR bit
    }
    if (_EXTR) {
      u8_resetIdentified = 1;
      outString("MCLR assertion.\n");
      _EXTR = 0;
    }
    if (_BOR) {
      u8_resetIdentified = 1;
      outString("Brown-out.\n");
      _BOR = 0;
    }
    if (_TRAPR) {
      u8_resetIdentified = 1;
      outString("Trap Conflict.\n");
      _TRAPR = 0;
    }
    if (_IOPUWR) {
      u8_resetIdentified = 1;
      outString("Illegal Condition.\n");
      _IOPUWR = 0;
    }
# ifdef _CM
    if (_CM) {
      u8_resetIdentified = 1;
      outString("Configuration Mismatch.\n");
      _CM = 0;
    }
# endif
  } //end non-POR

  if (!u8_resetIdentified) {
    outString("Unknown reset.\n");
  }
  if (sz_lastError != NULL) {
    outString("Error trapped: ");
    outString(sz_lastError);
    if (u16_INTTREGlast != 0) {
# ifdef _ILR
      outString("Priority: ");
      outUint8(INTTREGBITS_last.ILR);
      outString(", Vector number: ");
      outUint8(INTTREGBITS_last.VECNUM);
# else
      outString("Unknown priority/vector");
# endif
    }
    outString("\n\n");
    sz_lastError = NULL;
    u16_INTTREGlast = 0;
  }

  checkDeviceAndRevision();
  checkOscOption();
}

/** Perform basic chip configuration:
 *  - Configure the heartbeat
 *  - Configure the clock
 *  - Configure UART1
 *  - Determine and print the cause of reset
 *  - Print a hello message.
 *
 *  \param sz_helloMsg Hello message to print.
 */
void configBasic(const char* sz_helloMsg) {
  configHeartbeat();
  configClock();
  configDefaultUART(DEFAULT_BAUDRATE);
  printResetCause();
  outString(sz_helloMsg);
}
#endif

#ifndef _NOFLOAT
/** Round a floating-point number to the nearest integer.
 *  \param f_x Floating-point value to round
 *  \return The nearest uint32_t to f_x.
 */
uint32_t roundFloatToUint32(float f_x) {
  uint32_t u32_y;

  u32_y = f_x;
  if ((f_x - u32_y) < 0.5) return u32_y;
  else return u32_y+1;
}

/** Round a floating-point number to the nearest integer.
 *  \param f_x Floating-point value to round
 *  \return The nearest uint16_t to f_x.
 */
uint16_t roundFloatToUint16(float f_x) {
  uint16_t u16_y;

  u16_y = f_x;
  if ((f_x - u16_y) < 0.5) return u16_y;
  else return u16_y+1;
}

/**  Choose UART baud rate, based on u32_fcy.
  *  NOTE: Be careful about using BRGH=1 - this uses only four clock
  *  periods to sample each bit and can be very intolerant of
  *  baud rate % error - you may see framing errors. BRGH is selected
  *  via the DEFAULT_BRGH1 define above.
  */
uint16_t compute_brg(uint32_t u32_fcy, uint16_t u16_brgh, uint32_t u32_baudrate) {
  float f_brg;

  // Make sure u16_brgh is valid (1 or 0)
  ASSERT(u16_brgh <= 1);
  if (u16_brgh == 0) {
    f_brg = (((float) u32_fcy)/((float) u32_baudrate)/16.0) - 1.0;
  } else {
    f_brg = (((float) u32_fcy)/((float) u32_baudrate)/4.0) - 1.0;
  }
  ASSERT(f_brg < 65535.5);
  return roundFloatToUint16(f_brg);
}

#else // #ifndef _NOFLOAT, so _NOFLOAT is defined.

uint16_t compute_brg(uint32_t u32_fcy, uint16_t u16_brgh, uint32_t u32_baudrate) {
  uint32_t u32_brg;

  // Make sure u16_brgh is valid (1 or 0)
  ASSERT(u16_brgh <= 1);
  u32_brg = u32_fcy/u32_baudrate;
  if (u16_brgh == 0) {
    if ((u32_brg & 0x0FL) >= 8) {
      u32_brg = u32_brg/16;
    } else {
      u32_brg = u32_brg/16 - 1;
    }
  } else {
    if ((u32_brg & 0x03L) >= 2) {
      u32_brg = u32_brg/4;
    } else {
      u32_brg = u32_brg/4 - 1;
    }
  }
  ASSERT(u32_brg < 65536);
  return u32_brg;
}

#endif
