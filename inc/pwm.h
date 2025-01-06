#pragma once

// Frequency division, default clock Fsys
#define PWMSetClk(CK_SE) (PWM_CK_SE = CK_SE)
// Set PWM output duty cycle
#define PWMSetData1(dat) (PWM_DATA1 = dat)
#define PWMSetData2(dat) (PWM_DATA2 = dat)
// PWM mapping pin P30
#define PWM1PinAlter()                                                         \
  {                                                                            \
    PIN_FUNC |= bPWM1_PIN_X;                                                   \
  }
// PWM mapping pin P31
#define PWM2PinAlter()                                                         \
  {                                                                            \
    PIN_FUNC |= bPWM2_PIN_X;                                                   \
  }
// Force clear PWM FIFO and COUNT
#define PWMForceClear()                                                        \
  {                                                                            \
    PWM_CTRL |= bPWM_CLR_ALL;                                                  \
  }
// Unclear PWM FIFO and COUNT
#define PWMCancelClear()                                                       \
  {                                                                            \
    PWM_CTRL &= ~bPWM_CLR_ALL;                                                 \
  }
// Enable PWM1 output
#define PWM1OutEnable() (PWM_CTRL |= bPWM1_OUT_EN)
// Enable PWM2 output
#define PWM2OutEnable() (PWM_CTRL |= bPWM2_OUT_EN)
// Turn off PWM1 output
#define DsiablePWM1Out() (PWM_CTRL &= ~bPWM1_OUT_EN)
// Turn off PWM2 output
#define DisablePWM2Out() (PWM_CTRL &= ~bPWM2_OUT_EN)
// PWM1 output default low, active high
#define PWM1OutPolarHighAct() (PWM_CTRL &= ~bPWM1_POLAR)
// PWM2 output default low, active high
#define PWM2OutPolarHighAct() (PWM_CTRL &= ~bPWM2_POLAR)
// PWM1 output default high, active low
#define PWM1OutPolarLowAct() (PWM_CTRL |= bPWM1_POLAR)
// PWM2 output default high, active low
#define PWM2OutPolarLowAct() (PWM_CTRL |= bPWM2_POLAR)
// PWM interrupt enable
#define PWMInterruptEnable()                                                   \
  {                                                                            \
    PWM_CTRL |= bPWM_IF_END | bPWM_IE_END;                                     \
    IE_PWMX = 1;                                                               \
  }
#define PWMInterruptDisable()                                                  \
  {                                                                            \
    IE_PWMX = 0;                                                               \
  }
