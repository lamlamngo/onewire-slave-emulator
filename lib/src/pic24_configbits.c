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
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */


// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  This file contains configuration bit settings. To add more chips:
 *
 *  1. Add the appropriate \#if __chip_name__ / \#endif pair (copy the format of
 *     other chips below.)
 *  2. Open the configuration bits editor in the MPLAB X IDE and select the
 *     appropriate bits for your chip.
 *  3. Click "Generate Source Code To Output", then copy and paste the output
 *     inside the \#if / \#endif pair you added.
 *  4. Delete the settings for FNOSC, POSCMD / POSCMOD, and OSCIOFNC; these
 *     will be set based on the clock configuration.
 *
 */
#include "pic24_clockfreq.h"

// *****************************************
// Settings based on clock choice begin here
// *****************************************
// These should not typically be edited.

#ifdef BOOTLOADER
// POSCMD_XT: Select bootloader config bits which allow user code to optionally
// use an XT oscillator. Change this for an HS crystal or an external clock (EC).
# undef POSCMD_SEL
# define POSCMD_SEL POSCMD_XT

// OSCIOFNC_OFF:  Reserve OSC2 as a potential crystal pin, instead of making it
// a digital I/O pin.
# define OSCIOFNC_SEL OSCIOFNC_OFF
#else
// Enable/disable OSC IO pins based on oscillator selection.
# if POSCMD_SEL == POSCMD_NONE
// Make the OSC2 pin a digital I/O.
#   define OSCIOFNC_SEL OSCIOFNC_ON
# else
// Reserve the OSC pins for use with an oscillator (HS and XT modes) or
// have it output the clock (EC mode).
#   define OSCIOFNC_SEL OSCIOFNC_OFF
# endif
#endif

/*   Note on clock choice: The processor is configured to always
 *   start up with the FRC, rather than what it will use after
 *   clock configuration. This guarantees a working clock at
 *   power-up, which can then be changed by the bootloader / user
 *   code / etc.
 */
// FOSCSEL
# pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))

// Translate the selected primary oscillator source to # pragma-style configs for the FOSC register.
#if defined(__PIC24F__) || defined(__PIC24FK__)
// The PIC24F/FK calls this config bit POSCMOD.
# if    POSCMD_SEL == POSCMD_EC
#   pragma config POSCMOD = EC              // Primary Oscillator Mode Select bits (EC Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_XT
#   pragma config POSCMOD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_HS
#   pragma config POSCMOD = HS              // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_NONE
#   pragma config POSCMOD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
# else
#   error "Unknown primary oscillator selection."
# endif
#else
// All other processors call it POSCMD.
# if    POSCMD_SEL == POSCMD_EC
#   pragma config POSCMD = EC              // Primary Oscillator Mode Select bits (EC Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_XT
#   pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_HS
#   pragma config POSCMD = HS              // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#  elif POSCMD_SEL == POSCMD_NONE
#   pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
# else
#   error "Unknown primary oscillator selection."
# endif
#endif

// Translate the OSCIOFNC_SEL to # pragma-style configs for the FOSC register.
#if OSCIOFNC_SEL == OSCIOFNC_OFF
# pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#elif OSCIOFNC_SEL == OSCIOFNC_ON
# pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#else
# error "Unknown OSCIOFNC selection."
#endif


// **************************************
// Settings for specific chips begin here
// **************************************
// Add new chips to the end of this file.
#if defined(__PIC24HJ12GP202__) || \
  defined(__PIC24HJ12GP201__) || \
  defined(__PIC24HJ32GP202__) || \
  defined(__PIC24HJ16GP304__)


// FBS
# pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
# pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
# pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
# pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
# pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)

// FOSC
# pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
# pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
# pragma config WDTPOST = PS512          // Watchdog Timer Postscaler (1:512)
# pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
# pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
# pragma config FPWRT = PWR16            // POR Timer Value (16ms)
# pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

// FICD
# pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif // #ifdef (lots of PIC24H devices)


#if HARDWARE_PLATFORM == EXPLORER16_100P && defined(__PIC24HJ256GP610__)

// FBS
# pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
# pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
# pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
# pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
# pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
# pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
# pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
# pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
# pragma config IESO = OFF               // Two-speed Oscillator Start-Up Enable (Start up with user-selected oscillator)

// FOSC
# pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
# pragma config WDTPOST = PS512          // Watchdog Timer Postscaler (1:512)
# pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
# pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
# pragma config FPWRT = PWR16            // POR Timer Value (16ms)

// FICD
# pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif


#if defined(__PIC24FJ64GA002__)

// CONFIG2
# pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
# pragma config IOL1WAY = OFF            // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
# pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
# pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
# pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
# pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
# pragma config WDTPS = PS512            // Watchdog Timer Postscaler (1:512)
# pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
# pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
# pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
# pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
# pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif // #ifdef PIC24F processors

#if HARDWARE_PLATFORM == EXPLORER16_100P && defined(__PIC24FJ128GA010__)

// CONFIG2
# pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
# pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
# pragma config WDTPS = PS512            // Watchdog Timer Postscaler (1:512)
# pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
# pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
# pragma config ICS = PGx1               // Comm Channel Select (Emulator/debugger uses EMUC1/EMUD1)
# pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
# pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif

#if defined(__PIC24FJ64GB002__) || (__PIC24FJ64GB004__)

// CONFIG4
# pragma config DSWDTPS = DSWDTPSF       // DSWDT Postscale Select (1:2,147,483,648 (25.7 days))
# pragma config DSWDTOSC = LPRC          // Deep Sleep Watchdog Timer Oscillator Select (DSWDT uses Low Power RC Oscillator (LPRC))
# pragma config RTCOSC = SOSC            // RTCC Reference Oscillator  Select (RTCC uses Secondary Oscillator (SOSC))
# pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (BOR disabled in Deep Sleep)
# pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer (DSWDT disabled)

// CONFIG3
# pragma config WPFP = WPFP63            // Write Protection Flash Page Segment Boundary (Highest Page (same as page 42))
# pragma config SOSCSEL = SOSC           // Secondary Oscillator Pin Mode Select (SOSC pins in Default (high drive-strength) Oscillator Mode)
# pragma config WUTSEL = LEG             // Voltage Regulator Wake-up Time Select (Default regulator start-up time used)
# pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Segmented code protection disabled)
# pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Last page and Flash Configuration words are unprotected)
# pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
# pragma config I2C1SEL = PRI            // I2C1 Pin Select bit (Use default SCL1/SDA1 pins for I2C1 )
# pragma config IOL1WAY = OFF            // IOLOCK One-Way Set Enable (The IOLOCK bit can be set and cleared using the unlock sequence)
# pragma config FCKSM = CSECMD           // Clock Switching and Fail-Safe Clock Monitor (Sw Enabled, Mon Disabled)
# pragma config PLL96MHZ = OFF           // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled by user in software( controlled with the PLLEN bit))
# pragma config PLLDIV = DIV2            // USB 96 MHz PLL Prescaler Select (Oscillator input divided by 2 (8 MHz input))
# pragma config IESO = OFF               // Internal External Switchover (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
# pragma config WDTPS = PS512            // Watchdog Timer Postscaler (1:512)
# pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
# pragma config WINDIS = OFF             // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
# pragma config FWDTEN = OFF             // Watchdog Timer (Watchdog Timer is disabled)
# pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
# pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
# pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif

/***********************************************************************************
*** The dsPIC33ExxGP5xx and dsPIC33ExxGP8xx devices we use have slightly different
*** config bits defined.  So we will look for our device and setup config bits
*** accordingly.  As other devices are added, hopefully they won't differ from these
*** two cases....
*** .. until Microchip makes another small, subtle change in the datasheets (UGH!)
***********************************************************************************/
#if defined(__dsPIC33EP128GP502__) || (__dsPIC33EP128GP504__)

// FICD
# pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
# pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
# pragma config ALTI2C1 = ON             // Alternate I2C1 pins (I2C1 mapped to ASDA1/ASCL1 pins)
# pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
# pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
# pragma config WDTPOST = PS512          // Watchdog Timer Postscaler bits (1:512)
# pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
# pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
# pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FOSC
# pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow multiple reconfigurations)
# pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
// FOSCSEL
# pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)
// FGS
# pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
# pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)
///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif   // #ifdefined  (__dsPIC33EP128GP502__) || (__dsPIC33EP128GP504__)

#if defined(__dsPIC33EP512GP806__)
// DSPIC33EP512GP806 Configuration Bit Settings
// FICD
# pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
# pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
# pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
# pragma config BOREN = ON               // BROWN-OUT RESET DETECTION MUST BE ENABLED (per datasheet DS70616G p.479)
# pragma config FPWRT = PWR1             // POWER ON RESET TIMER DISABLED?

// FWDT
# pragma config WDTPOST = PS512          // Watchdog Timer Postscaler bits (1:512)
# pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
# pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
# pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FOSC
# pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow multiple reconfigurations)
# pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FOSCSEL
# pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FGS
# pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
# pragma config GSS = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)
# pragma config GSSK = OFF               // General Segment KEY bit (General Segment protect is Disabled)

# define CONFIG_BITS_DEFINED
///\endcond
#endif  // #ifdefined  (__dsPIC33EP512GP806__)


#if defined(__PIC24HJ128GP502__)

// FBS
# pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
# pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
# pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
# pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
# pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
# pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
# pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
# pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
# pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)

// FOSC
# pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
# pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
# pragma config WDTPOST = PS512          // Watchdog Timer Postscaler (1:512)
# pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
# pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
# pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
# pragma config FPWRT = PWR128           // POR Timer Value (128ms)
# pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

// FICD
# pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
# pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

///\cond doxygen_ignore
# define CONFIG_BITS_DEFINED
///\endcond
#endif


// *********
// New chips
// *********
// Add new chips here.
//
//  If the chip currently in use has not be detected, the config bits
//  may not have been setup properly, so issue a warning.
//  Other chips can be added to this file as needed.
#ifndef CONFIG_BITS_DEFINED
# warning "Edit common/pic24_configbits.c to add config bits for your processor!"
#endif
