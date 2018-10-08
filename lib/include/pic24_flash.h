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
 *  FLASH memory read/write support functions
 */

#pragma once

#include <stdint.h>
#include "pic24_unions.h"

#if (defined(__dsPIC33E__) || defined(__PIC24E__))
//this family will use double word programming.
//assume a page size of 1024 instructions as this is true for most of these family members
# define FLASH_ROWSIZE    2       //in number of instructions
# define FLASH_ROWS_PER_PAGE (1024/FLASH_ROWSIZE)
#else
# define FLASH_ROWSIZE    64       //in number of instructions
# define FLASH_ROWS_PER_PAGE 8
#endif

#define FLASH_PAGEINSTR (FLASH_ROWSIZE * FLASH_ROWS_PER_PAGE)  //8 rows of 64 instructions
#define FLASH_PAGESIZE (FLASH_PAGEINSTR*2)     //each instruction appears to occupy 2 program memory addresses
#define FLASH_PAGEBYTES (FLASH_PAGEINSTR*3)  //total bytes is FLASH_PAGEINSTR *3 = 1536
#define FLASH_ROWBYTES  (FLASH_ROWSIZE*3)    //bytes in one row

void doWriteLatchFlash(uint16_t u16_addrhi, uint16_t u16_addrlo, uint16_t u16_wordhi, uint16_t u16_wordlo);
uint32_t doReadLatchFlash(uint16_t u16_addrhi, uint16_t u16_addrlo);
void doEraseFlash (uint16_t u16_addrhi, uint16_t u16_addrlo);
void doWriteFlash();
void doWritePageFlash(union32 u32_pmemAddress, uint8_t* pu8_data, uint16_t u16_len);
void doReadPageFlash(union32 u32_pmemAddress, uint8_t* pu8_data, uint16_t u16_len);
