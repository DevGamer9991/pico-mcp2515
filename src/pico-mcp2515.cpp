#include <stdio.h>
#include "pico/stdlib.h"
#include "mcp2515/mcp2515.h"

MCP2515 can0;
struct can_frame rx;

int main() {
    stdio_init_all();

    // wait for serial connection
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // turn led on
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, 1);

    printf("Serial Connected\n");

    //Initialize interface
    can0.reset();
    can0.setBitrate(CAN_1000KBPS, MCP_16MHZ);
    can0.setNormalMode();

    //Listen loop
    while(true) {
        if(can0.readMessage(&rx) == MCP2515::ERROR_OK) {
            printf("New frame from ID: %10x\n", rx.can_id);
        }
    }

    return 0;
}
