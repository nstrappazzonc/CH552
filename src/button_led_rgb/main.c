#include <ch552.h>
#include <utils.h>

#define RED    P34
#define GREEN  P33
#define BLUE   P11
#define BUTTON P32

void main(void) {
    init();

    uint8_t color;

    RED   = 0;
    GREEN = 0;
    BLUE  = 0;

    //Set input in pullup mode:
    P3_MOD_OC |= (1<<BUTTON);
    P3_DIR_PU |= (1<<BUTTON);

    while(1) {
        if(BUTTON) {
            delay(50);

            if(BUTTON) {
                color++;
                if (color > 3) {
                    color = 0;
                }

                RED   = 0;
                GREEN = 0;
                BLUE  = 0;

                switch(color) {
                    case 1:
                        RED = 1;
                        break;
                    case 2:
                        GREEN = 1;
                        break;
                    case 3:
                        BLUE = 1;
                        break;
                    default:
                        break;
                }

                while(BUTTON);
            }
        }
    }
}
