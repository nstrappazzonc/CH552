#include <ch552.h>
#include <utils.h>

#define LED P30
#define BUTTON P32

void main(void) {
  init();

  P3_MOD_OC &= ~(1 << LED);
  P3_DIR_PU |= (1 << LED);

  // Set input in pullup mode:
  P3_MOD_OC |= (1 << BUTTON);
  P3_DIR_PU |= (1 << BUTTON);

  while (1) {
    if (BUTTON) {
      LED = 1;
    } else {
      LED = 0;
    }
  }
}
