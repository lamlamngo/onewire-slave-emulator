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

// Documentation placed on the PIC24 support library page. This file only
// include comments for Doxygen; it does not contain any
// code.
/**
 * \page PIC24_support PIC24 support library
 * The PIC24 support library is divided into
 * \ref external "external components", \ref internal "internal components",
 * and \ref codeUtils "utilities" used in creating the library.
 * External components should be called by
 * the typical user to set up the PIC, communicate over the UART,
 * I<sup>2</sup>C bus, etc. Internal components include both
 * implementation details and information on adding support for
 * PIC24 processors not currently supported by this library.
 *
 * A simple example which echos characters via the UART:
\code
#include "pic24_all.h"
int main(void) {
  // Set up clock, heartbeat, UART, print welcome message
  configBasic(HELLO_MSG);
  while (1) {
    // Echo characters
    outChar(inChar());
  }
  return 0;
}
\endcode
 *
 * \section libraryComponents Library components
 *
 * \subsection external External library components
 * - Development support
 *   - A single header file to include all the files below,
 *     in pic24_all.h
 *   - Delay routines in pic24_delay.h
 *   - Setup of IO ports in pic24_ports.h
 *   - Unit testing / assertions, in pic24_unittest.h
 *   - Miscellanous utilities in pic24_util.h
 *   - Processor-specific information in pic24_chip.h
 *   - Debug/data tranfer abilities in dataXfer.h
 *   - A byte-wise access to multibyte data in pic24_unions.h
 * - Peripheral support
 *   - Analog to digital converter routines, in pic24_adc.h
 *   - Direct memory access (DMA) routines, in pic24_dma.h
 *   - Enhanced controller area network (ECAN) routines, in pic24_ecan.h
 *   - Read/write of FLASH, in pic24_flash.h
 *   - Setup of timers, in pic24_timer.h
 *   - Serial communication support, in pic24_serial.h
 *   - I<sup>2</sup>C support, in pic24_i2c.h
 *   - SPI support, in pic24_spi.h
 *
 * \subsection internal Internal library components
 * - User-configurable library settings, in pic24_libconfig.h
 * - Clock configuration, in pic24_clockfreq.h and
 *   pic24_clockfreq.c
 * - Configuration bit settings, in pic24_configbits.c
 * - UART support in pic24_uart.h and pic24_uart.c, which
 *   is typically called by routines in pic24_serial.h.
 *
 * \subsection codeUtils Utilities
 * The <a href="sphinx/utilities.html">utilities</a> page documents tools for library development and maintenance.
 */
