// ===================================================================================
// Basic GPIO, PWM and ADC Functions for CH551, CH552 and CH554               * v1.5 *
// ===================================================================================
//
// Pins must be defined as P10, P11, P12, etc. - e.g.:
// #define PIN_LED P33      // LED on pin P3.3
//
// Functions available:
// --------------------
// PIN_input(PIN)           set PIN as INPUT (high impedance, no pullup)
// PIN_input_PU(PIN)        set PIN as INPUT with internal PULLUP
// PIN_output(PIN)          set PIN as OUTPUT (push-pull)
// PIN_output_OD(PIN)       set PIN as OUTPUT (open-drain)
//
// PIN_low(PIN)             set PIN output value to LOW
// PIN_high(PIN)            set PIN output value to HIGH
// PIN_toggle(PIN)          TOGGLE PIN output value
// PIN_read(PIN)            read PIN input value
// PIN_write(PIN, val)      write PIN output value (0 = LOW / 1 = HIGH)
//
// PIN_asm(PIN)             convert PIN for inline assembly: setb PIN_asm(PIN_LED)
// PIN_set(PIN)             convert PIN for direct manipulation: PIN_set(PIN_LED) = 1;
//
// PIN_WAKE_enable(PIN)     enable wake-up from sleep by PIN low (P13, P14, P15 only)
// PIN_WAKE_disable(PIN)    disable wake-up from sleep by PIN low
//
// PWM_start(PIN)           start PWM output on PIN, can be (P15 or P30) and (P34 or P31)
// PWM_stop(PIN)            stop PWM output on PIN
// PWM_write(PIN, val)      set PWM output active level duty cycle on PIN
//
// PWM_pol_normal(PIN)      set normal PWM polarity on PIN (default low and active high)
// PWM_pol_reverse(PIN)     set reverse PWM polarity on PIN (default high and active low)
// PWM_set_freq(FREQ)       set global PWM frequency (in Hertz)
//
// ADC_enable()             enable ADC
// ADC_disable()            disable ADC
// ADC_fast()               set ADC fast mode ( 96 clock cycles per sample, less accurate)
// ADC_slow()               set ADC slow mode (384 clock cycles per sample, more accurate)
// ADC_input(PIN)           set ADC input pin (P11, P14, P15, P32 only)
// ADC_read()               sample and read ADC value (0..255)
//
// CMP_enable()             enable comparator
// CMP_disable()            disable comparator
// CMP_positive(PIN)        set CMP non-inverting input pin (P11, P14, P15, P32 only)
// CMP_negative(PIN)        set CMP inverting input pin (P14, P32 only)
// CMP_read()               read CMP output (0: pos < neg, 1: pos > neg)
//
// Notes:
// ------
// Pins used for PWM should be set as OUTPUT beforehand.
// Pins used for ADC or CMP must have been set as INPUT (high impedance) beforehand.
//
// 2022 by Stefan Wagner:   https://github.com/wagiminator

#pragma once
#include <stdint.h>
#include "ch552.h"

// ===================================================================================
// Enumerate pin designators (use these designators to define pins)
// ===================================================================================

enum{P10, P11, P12, P13, P14, P15, P16, P17, P30, P31, P32, P33, P34, P35, P36, P37};

// ===================================================================================
// Helper Defines (these are for internal use only)
// ===================================================================================

// Define pins for direct bit manipulation
SBIT(PP10, 0x90, 0);
SBIT(PP11, 0x90, 1);
SBIT(PP12, 0x90, 2);
SBIT(PP13, 0x90, 3);
SBIT(PP14, 0x90, 4);
SBIT(PP15, 0x90, 5);
SBIT(PP16, 0x90, 6);
SBIT(PP17, 0x90, 7);
SBIT(PP30, 0xB0, 0);
SBIT(PP31, 0xB0, 1);
SBIT(PP32, 0xB0, 2);
SBIT(PP33, 0xB0, 3);
SBIT(PP34, 0xB0, 4);
SBIT(PP35, 0xB0, 5);
SBIT(PP36, 0xB0, 6);
SBIT(PP37, 0xB0, 7);

// 2nd-stage glue defines
#define PIN_h_a(PIN) _P##PIN
#define PIN_h_s(PIN) P##PIN

// ===================================================================================
// Set pin as OPEN-DRAIN OUTPUT (also high-impedance input, no pullup)
// ===================================================================================
#define PIN_output_OD(PIN) \
  ((PIN>=P10)&&(PIN<=P17) ? (P1_MOD_OC |= (1<<(PIN&7)), P1_DIR_PU &= ~(1<<(PIN&7))) : \
  ((PIN>=P30)&&(PIN<=P37) ? (P3_MOD_OC |= (1<<(PIN&7)), P3_DIR_PU &= ~(1<<(PIN&7))) : \
(0)))

// ===================================================================================
// Pin manipulation macros
// ===================================================================================
#define PIN_low(PIN)          PIN_h_s(PIN) = 0              // set pin to LOW
#define PIN_high(PIN)         PIN_h_s(PIN) = 1              // set pin to HIGH
#define PIN_read(PIN)         (PIN_h_s(PIN))                // READ pin
#define PIN_write(PIN, val)   PIN_h_s(PIN) = val            // WRITE pin value
