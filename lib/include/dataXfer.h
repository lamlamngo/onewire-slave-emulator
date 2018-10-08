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

#pragma once

/** \file
 *  \brief Routines which implement the \ref dataXfer "uC comm protocol".
 */

#include "dataXferImpl.h"

// Specify that this is C code for proper C++ linking
#ifdef __cplusplus
extern "C" {
#endif

/// Number of for loop iterations which equal a timeout for the microcontroller.
///     # loops   =      instructions/sec * loops/instruction * seconds
#define RECEIVE_TIMEOUT (FCY              * 1/20              * 0.1)

/// Send one character to the uC, escaping if necessary.
/// \param c Character to send.
void
outCharXfer(char c);


/// A system-dependent macro to output one character.
#ifndef OUT_CHAR
void outChar(uint8_t c);
# define OUT_CHAR(c) outChar(c)
#else
// Hack: a command line of -DOUT_CHAR(c)=testOutChar(c) doesn't work. Just -DOUT_CHAR then
// redefine it here.
# undef OUT_CHAR
# define UNIT_TESTS
void testOutChar(uint8_t c);
# define OUT_CHAR(c) testOutChar(c)
#endif

/// Initialize the data transfer system. This must be called before calling
/// any of the data transfer functions in the library.
void
initDataXfer();

#if defined(MICROCONTROLLER) || defined(__DOXYGEN__) || defined(UNIT_TESTS)
/** Specify a variable to be sent or received. <b>uC only.</b>
 *  \param u_varIndex       A value from 0-\ref NUM_XFER_VARS, unique for each var
 *  \param pv_data          A pointer to the data to be sent
 *  \param u_size           Size of the data in bytes; must be from 1 to 256.
 *  \param b_isWriteable    True if the PC is allowed to change this
 *                            variable; false otherwise. This does *NOT*
 *                            restrict the microcontroller to read-only access to this
 *                            variable.
 *  \param psz_format       printf format string to use in displaying the
 *                            Variable.
 *  \param psz_name         Name of this variable, typically the same as used
 *                            in the code
 *  \param psz_desc         Description of this variable.
 */
void
specifyVar(uint u_varIndex, volatile void* pv_data, uint u_size,
           BOOL b_isWriteable, char* psz_format, char* psz_name,
           char* psz_desc);

/** For simplicity, define a macro that specifies a variable with
 *  default names. <b>uC only.</b>
 *  \param u_varIndex    A value from 0-\ref NUM_XFER_VARS, unique for each var
 *  \param data          A pointer to the data to be sent
 *  \param isWriteable   True if the PC is allowed to change this
 *                        variable; false otherwise. This does *NOT*
 *                        restrict the microcontroller to read-only access to this
 *                        variable.
 *  \param format        printf format string to use in displaying the
 *                        variable
 *  \param desc          Description of this variable.
 */
#define SPECIFY_VAR(u_varIndex, data, isWriteable, format, desc) \
specifyVar(u_varIndex, &data, sizeof(data), isWriteable, format, #data, desc)
#endif

/// Send an already-specified variable; \see specifyVar.
/// \param u_varIndex The index of the variable to send; must be from 0 to
///                    \ref NUM_XFER_VARS.
void
sendVar(uint u_varIndex);

#if !defined(MICROCONTROLLER) || defined(__DOXYGEN__)
/** Return a string with the data stored in the given variable formatted using
 *  the format string contained in the variable. <b>PC only.</b>
 *  \param u_varIndex The index of the variable to send; must be from 0 to
 *                    \ref NUM_XFER_VARS.
 *  \param psz_buf Buffer to contain the formatted string.
 *  \param s_len Length of the buffer.
 *  \return On success, the total number of characters written is returned.
 *          This count does not include the additional null-character
 *          automatically appended at the end of the string.
 *          On failure, a negative number is returned.
 */
int
formatVar(uint u_varIndex, char* psz_buf, size_t s_len);
#endif


#if defined(MICROCONTROLLER) || defined(__DOXYGEN__)
/** Receive a character or a variable. Any errors that occur are
  *  reported via outString. <b>uC only.</b>
  *  \param c Pointer to space for storing the received character, if
  *             a character was received (see return value).
  *  \return  An index to the variable, if a variable was received, or
  *             \ref CHAR_RECEIVED_INDEX if a character was received.
  */
uint
receiveVar(char* c);

/** Receive a character, while transparently processing any
 *  variables sent by the PC. Variables are assigned, but
 *  this simple interface does not report these assignments
 *  to its caller. This provides a simple wrapper around \ref receiveVar,
 *  which also reports on received variables.  <b>uC only.</b>
 *  \return The character received.
 */
char
inCharXfer();
#else
/** Receive a character or a variable. Any errors that occur are
*  reported via outString. <b>PC only.</b>
*  \param c_in  Character just received, which will be processed.
*  \param pc_out Pointer to space for storing the received character, if
*                a character was received (see pu16_index).
*  \param pu_index A pointer to the index to the variable, if a variable was received;
*                    \ref CHAR_RECEIVED_INDEX if a character was received.
*  \param u64_timeMs Current system time, in ms.
*  \param psz_error NULL if no error occurred; otherwise, a pointer to the
*                  error string.
*  \return True if a character or variable was received. True also implies that
*          pu_index is valid.
*/
BOOL receiveVar(char c_in, char* pc_out, uint* pu_index,
                uint64_t u64_timeMs, const char** psz_error);
#endif


#ifdef __cplusplus
}
#endif
