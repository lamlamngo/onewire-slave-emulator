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

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 * This file defines a series of macros which provide GPIO and related configuration for
 * each pin of a given PIC24/dsPIC33. Configuration is first defined at a low level,
 * by providing the following:
 *
 * * Analog/digital configuration: ENABLE/DISABLE_Rxy_ANALOG(). The DISABLE version
 *   will always exist; the ENABLE version exists only if the given pin has analog
 *   capability.
 * * Input/output configuration: CONFIG_Rxy_AS_INPUT/OUTPUT(). This exists for every pin.
 * * Open collector/normal (totem-pole) output driver configuration:
 *   ENABLE/DISABLE_Rxy_OPENDRAIN().  The DISABLE version
 *   will always exist; the ENABLE version exists only if the given pin has open-drain
 *   capability.
 * * Pullup/pulldown configuration: ENABLE/DISABLE_Rxy_PULLUP/DOWN().  The DISABLE version
 *   will always exist; the ENABLE version exists only if the given pin has pullup/pulldown
 *   capability.
 *
 * Related low-level configuration:
 * * Change notification interrupts: ENABLE/DISABLE_Rxy_CN_INTERRUPT().  The DISABLE version
 *   will always exist; the ENABLE version exists only if the given pin has change notification
 *   capability.
 * * Remappable pin to Rxy translation: the Rxy_RP macro identifies the RPy value for
 *   the given Rxy port. Typical usage with the remappable macros: CONFIG_INT1_TO(RB4_RP);
 * * Analog port to Rxy translation: The Rxy_AN macro identifies the ANn value for
 *   the given Rxy port. Typical usage: configADC1_ManualCH0(RB4_AN, 31, 0).
 * * Change notification pin to Rxy translation: The Rxy_CN macro identifies the CNm value for
 *   the given Rxy port. Rather than directly using this value, the ENABLE/DISABLE_Rxy_PULLUP/DOWN()
 *   and ENABLE/DISABLE_Rxy_CN_INTERRUPT() are typically used.
 *
 * Combining these produces higher-level configuration:
 * * CONFIG_Rxy_AS_ANALOG(): disables pullups/pulldowns, makes pin an input, and
 *   of course enables analog.
 * * CONFIG_Rxy_AS_DIG_INPUT/OUTPUT(): disables analog, pullups/pulldowns, and
 *   open-drain.
 *
 * Implementation notes
 * --------------------
 * \todo Explain double macros
 */


// Port configuration
// ==================
// Port configuration macros
// -------------------------
// The macros below are used by the following include files to define GPIO macros.
//
// Analog
// ^^^^^^
// Return the PCFG pin for the given Rxy_AN value.
#define RXY_GPIO_PCFG(Rxy_AN) _RXY_GPIO_PCFG(Rxy_AN)
#define _RXY_GPIO_PCFG(Rxy_AN) (_PCFG ## Rxy_AN)

// Change notification / pullups and pulldowns
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Return the _CNmPUE pin for the given Rxy_CN value.
#define RXY_GPIO_CNPUE(Rxy_CN) _RXY_GPIO_CNPUE(Rxy_CN)
#define _RXY_GPIO_CNPUE(Rxy_CN) (_CN ## Rxy_CN ## PUE)
// Return the _CNmIE pin  for the given Rxy_CN value.
#define RXY_GPIO_CNIE(Rxy_CN) _RXY_GPIO_CNIE(Rxy_CN)
#define _RXY_GPIO_CNIE(Rxy_CN) (_CN ## Rxy_CN ## IE)

// Return true if the given Rxy_CN pin has pulldown capabilities.
#define RXY_HAS_CNPDE(Rxy_CN) _RXY_HAS_CNPDE(Rxy_CN)
#define _RXY_HAS_CNPDE(Rxy_CN) defined(_CN ## Rxy_CN ## PDE)
// Return the _CNmPDE pin for the given Rxy_GPIO value.
#define RXY_GPIO_CNPDE(Rxy_CN) _RXY_GPIO_CNPDE(Rxy_CN)
#define _RXY_GPIO_CNPDE(Rxy_CN) (_CN ## Rxy_CN ## PDE)

// Include the table data used to drive GPIO config.
#include "pic24_ports_mapping.h"

// Using the above macros, transform the table data into GPIO config.
#include "pic24_ports_config.h"



/** \name Remappable peripheral input support
 *  <a name="remappableInputs">These</a> funcions map an input internal
 *  to the PIC to an input pin.
 *  For example, CONFIG_INT1_TO_RP(10) maps the INT1 edge-triggered
 *  interrupt to port P, pin 10.
 */
//@{

#if defined(_INT1R) || defined(__DOXYGEN__)
/// Maps INT1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more information.
# define CONFIG_INT1_TO_RP(pin) _INT1R = pin
#endif

/// Maps INT2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INT2R) || defined(__DOXYGEN__)
# define CONFIG_INT2_TO_RP(pin) _INT2R = pin
#endif

/// Maps INT3 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INT3R) || defined(__DOXYGEN__)
# define CONFIG_INT3_TO_RP(pin) _INT3R = pin
#endif

/// Maps INT4 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INT4R) || defined(__DOXYGEN__)
#define CONFIG_INT4_TO_RP(pin) _INT4R = pin
#endif

/// Maps T1CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T1CKR) || defined(__DOXYGEN__)
#define CONFIG_T1CK_TO_RP(pin) _T1CKR = pin
#endif

/// Maps T2CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T2CKR) || defined(__DOXYGEN__)
#define CONFIG_T2CK_TO_RP(pin) _T2CKR = pin
#endif

/// Maps T3CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T3CKR) || defined(__DOXYGEN__)
#define CONFIG_T3CK_TO_RP(pin) _T3CKR = pin
#endif

/// Maps T4CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T4CKR) || defined(__DOXYGEN__)
#define CONFIG_T4CK_TO_RP(pin) _T4CKR = pin
#endif

/// Maps T5CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T5CKR) || defined(__DOXYGEN__)
#define CONFIG_T5CK_TO_RP(pin) _T5CKR = pin
#endif

/// Maps T6CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T6CKR) || defined(__DOXYGEN__)
#define CONFIG_T6CK_TO_RP(pin) _T6CKR = pin
#endif

/// Maps T7CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T7CKR) || defined(__DOXYGEN__)
#define CONFIG_T7CK_TO_RP(pin) _T7CKR = pin
#endif

/// Maps T8CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T8CKR) || defined(__DOXYGEN__)
#define CONFIG_T8CK_TO_RP(pin) _T8CKR = pin
#endif

/// Maps T9CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T9CKR) || defined(__DOXYGEN__)
#define CONFIG_T9CK_TO_RP(pin) _T9CKR = pin
#endif

/// Maps IC1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC1R) || defined(__DOXYGEN__)
#define CONFIG_IC1_TO_RP(pin) _IC1R = pin
#endif

/// Maps IC2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC2R) || defined(__DOXYGEN__)
#define CONFIG_IC2_TO_RP(pin) _IC2R = pin
#endif

/// Maps IC3 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC3R) || defined(__DOXYGEN__)
#define CONFIG_IC3_TO_RP(pin) _IC3R = pin
#endif

/// Maps IC4 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC4R) || defined(__DOXYGEN__)
#define CONFIG_IC4_TO_RP(pin) _IC4R = pin
#endif

/// Maps IC5 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC5R) || defined(__DOXYGEN__)
#define CONFIG_IC5_TO_RP(pin) _IC5R = pin
#endif

/// Maps IC6 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC6R) || defined(__DOXYGEN__)
#define CONFIG_IC6_TO_RP(pin) _IC6R = pin
#endif

/// Maps IC7 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC7R) || defined(__DOXYGEN__)
#define CONFIG_IC7_TO_RP(pin) _IC7R = pin
#endif

/// Maps IC8 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC8R) || defined(__DOXYGEN__)
#define CONFIG_IC8_TO_RP(pin) _IC8R = pin
#endif

/// Maps OCFA to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFAR) || defined(__DOXYGEN__)
#define CONFIG_OCFA_TO_RP(pin) _OCFAR = pin
#endif

/// Maps OCFB to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFBR) || defined(__DOXYGEN__)
#define CONFIG_OCFB_TO_RP(pin) _OCFBR = pin
#endif

/// \todo More mapping for dsPIC33E missing here, starting with FLT1.

/// Maps U1RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1RXR) || defined(__DOXYGEN__)
#define CONFIG_U1RX_TO_RP(pin) _U1RXR = pin
#endif

/// Maps U1CTS to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1CTSR) || defined(__DOXYGEN__)
#define CONFIG_U1CTS_TO_RP(pin) _U1CTSR = pin
#endif

/// Maps U2RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2RXR) || defined(__DOXYGEN__)
#define CONFIG_U2RX_TO_RP(pin) _U2RXR = pin
#endif

/// Maps U2CTS to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2CTSR) || defined(__DOXYGEN__)
#define CONFIG_U2CTS_TO_RP(pin) _U2CTSR = pin
#endif

/// Maps SDI1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SDI1R) || defined(__DOXYGEN__)
#define CONFIG_SDI1_TO_RP(pin) _SDI1R = pin
#endif

/// Maps SCK1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SCK1R) || defined(__DOXYGEN__)
#define CONFIG_SCK1IN_TO_RP(pin) _SCK1R = pin
#endif

/// Maps SS1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SS1R) || defined(__DOXYGEN__)
#define CONFIG_SS1IN_TO_RP(pin) _SS1R = pin
#endif

/// Maps SDI2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SDI2R) || defined(__DOXYGEN__)
#define CONFIG_SDI2_TO_RP(pin) _SDI2R = pin
#endif

/// Maps SCK2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SCK2R) || defined(__DOXYGEN__)
#define CONFIG_SCK2IN_TO_RP(pin) _SCK2R = pin
#endif

/// Maps SS2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SS2R) || defined(__DOXYGEN__)
#define CONFIG_SS2IN_TO_RP(pin) _SS2R = pin
#endif

/// Maps CSDI to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_CSDIR) || defined(__DOXYGEN__)
#define CONFIG_CDSI_TO_RP(pin) _CSDIR = pin
#endif

/// Maps CSCKIN to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_CSCKINR) || defined(__DOXYGEN__)
#define CONFIG_CSCKIN_TO_RP(pin) _CSCKINR = pin
#endif

/// Maps COFSIN to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_COFSINR) || defined(__DOXYGEN__)
#define CONFIG_COFSIN_TO_RP(pin) _COFSINR = pin
#endif

/// Maps C1RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_C1RXR) || defined(__DOXYGEN__)
#define CONFIG_C1RX_TO_RP(pin) _C1RXR = pin
#endif

/// Maps C2RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_C2RXR) || defined(__DOXYGEN__)
#define CONFIG_C2RX_TO_RP(pin) _C2RXR = pin
#endif

/// \todo More mappings, starting with U3RX for the dsPIC33E.
//@}


/** \name Remappable peripheral output support
 *  <a name="remappableOutputs">These</a> functions maps an output
 *  internal to the PIC to an output pin.
 *  For example, CONFIG_C1OUT_TO_RP(10) maps the C1OUT comparator
 *  output to port P, pin 10.
 *
 *  Not all devices support remappable peripherals. In these cases,
 *  the macros below evalaute to nothing: CONFIG_C1OUT_TO_RP(10) is
 *  a valid C statement which does nothing.
 */
//@{

/*****************************************************************************
***
*** Look for a way so that the compiler can determine whether or not the
*** target chip supports remappable perihperals.  So, we will look for
*** a bit field in the lowest possible RPORx registers.  Unfortunately,
*** Microchip has redefined these over the families and even within families.
***
***  xxxxxx       devices start with _RP0R
***  dsPIC33E 50x devices start with _RP20R
***  dsPIC33E 80x devices start with _RP64R
***
*****************************************************************************/
#if defined(_RP0R) || defined(_RP20R)  || defined(_RP64R) || defined(__DOXYGEN__)
///  CONFIG_NULL_TO_RP(n) returns RPn to an 'unmapped' state
/// (i.e, the reset condition).
# define CONFIG_NULL_TO_RP(Rxy_RP)  _CONFIG_NULL_TO_RP(Rxy_RP)
# define _CONFIG_NULL_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = 0)
#endif

/// Maps C1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_C1OUT) || defined(__DOXYGEN__)
# define CONFIG_C1OUT_TO_RP(Rxy_RP)  _CONFIG_C1OUT_TO_RP(Rxy_RP)
# define _CONFIG_C1OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_C1OUT)
#endif

/// Maps C2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_C2OUT) || defined(__DOXYGEN__)
# define CONFIG_C2OUT_TO_RP(Rxy_RP)  _CONFIG_C2OUT_TO_RP(Rxy_RP)
# define _CONFIG_C2OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_C2OUT)
#endif

/// Maps U1TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_U1TX) || defined(__DOXYGEN__)
# define CONFIG_U1TX_TO_RP(Rxy_RP)  _CONFIG_U1TX_TO_RP(Rxy_RP)
# define _CONFIG_U1TX_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_U1TX)
#endif

/// Maps U1RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_U1RTS) || defined(__DOXYGEN__)
# define CONFIG_U1RTS_TO_RP(Rxy_RP)  _CONFIG_U1RTS_TO_RP(Rxy_RP)
# define _CONFIG_U1RTS_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_U1RTS)
#endif

/// Maps U2TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_U2TX) || defined(__DOXYGEN__)
# define CONFIG_U2TX_TO_RP(Rxy_RP)  _CONFIG_U2TX_TO_RP(Rxy_RP)
# define _CONFIG_U2TX_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_U2TX)
#endif

/// Maps U2RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_U2RTS) || defined(__DOXYGEN__)
# define CONFIG_U2RTS_TO_RP(Rxy_RP)  _CONFIG_U2RTS_TO_RP(Rxy_RP)
# define _CONFIG_U2RTS_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_U2RTS)
#endif

/// Maps SDO1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SDO1) || defined(__DOXYGEN__)
# define CONFIG_SDO1_TO_RP(Rxy_RP)  _CONFIG_SDO1_TO_RP(Rxy_RP)
# define _CONFIG_SDO1_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SDO1)
#endif

/// Maps SCK1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SCK1OUT) || defined(__DOXYGEN__)
# define CONFIG_SCK1OUT_TO_RP(Rxy_RP)  _CONFIG_SCK1OUT_TO_RP(Rxy_RP)
# define _CONFIG_SCK1OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SCK1OUT)
#endif

/// Maps SS11OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SS1OUT) || defined(__DOXYGEN__)
# define CONFIG_SS1OUT_TO_RP(Rxy_RP)  _CONFIG_SS1OUT_TO_RP(Rxy_RP)
# define _CONFIG_SS1OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SS1OUT)
#endif

/// Maps SDO2 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SDO2) || defined(__DOXYGEN__)
# define CONFIG_SDO2_TO_RP(Rxy_RP)  _CONFIG_SDO2_TO_RP(Rxy_RP)
# define _CONFIG_SDO2_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SDO2)
#endif

/// Maps SCK2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SCK2OUT) || defined(__DOXYGEN__)
# define CONFIG_SCK2OUT_TO_RP(Rxy_RP)  _CONFIG_SCK2OUT_TO_RP(Rxy_RP)
# define _CONFIG_SCK2OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SCK2OUT)
#endif

/// Maps SS2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_SS2OUT) || defined(__DOXYGEN__)
# define CONFIG_SS2OUT_TO_RP(Rxy_RP)  _CONFIG_SS2OUT_TO_RP(Rxy_RP)
# define _CONFIG_SS2OUT_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_SS2OUT)
#endif

/// Maps C1TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_C1TX) || defined(__DOXYGEN__)
# define CONFIG_C1TX_TO_RP(Rxy_RP)  _CONFIG_C1TX_TO_RP(Rxy_RP)
# define _CONFIG_C1TX_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_C1TX)
#endif

/// Maps OC1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_OC1) || defined(__DOXYGEN__)
# define CONFIG_OC1_TO_RP(Rxy_RP)  _CONFIG_OC1_TO_RP(Rxy_RP)
# define _CONFIG_OC1_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_OC1)
#endif

/// Maps OC2 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_OC2) || defined(__DOXYGEN__)
# define CONFIG_OC2_TO_RP(Rxy_RP)  _CONFIG_OC2_TO_RP(Rxy_RP)
# define _CONFIG_OC2_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_OC2)
#endif

/// Maps OC3 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_OC3) || defined(__DOXYGEN__)
# define CONFIG_OC3_TO_RP(Rxy_RP)  _CONFIG_OC3_TO_RP(Rxy_RP)
# define _CONFIG_OC3_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_OC3)
#endif

/// Maps OC4 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_OC4) || defined(__DOXYGEN__)
# define CONFIG_OC4_TO_RP(Rxy_RP)  _CONFIG_OC4_TO_RP(Rxy_RP)
# define _CONFIG_OC4_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_OC4)
#endif

/// Maps OC5 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RPOUT_OC5) || defined(__DOXYGEN__)
# define CONFIG_OC5_TO_RP(Rxy_RP)  _CONFIG_OC5_TO_RP(Rxy_RP)
# define _CONFIG_OC5_TO_RP(Rxy_RP) (_RP##Rxy_RP##R = _RPOUT_OC5)
#endif
//@}
