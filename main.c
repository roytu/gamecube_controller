/*
 * Demonstration on how to redirect stdio to UART. 
 *
 * http://appelsiini.net/2011/simple-usart-with-avr-libc
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-*
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 */
 
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "main.h"
#include "uart.h"

#define shift_left_eight(buf, bit) \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit)

#define shift_left_32(buf, bit) \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit); \
            shift_left(buf, bit)

#define shift_left(buf, bit) buf <<= 1; buf |= bit
#define read_pin() ((PIND >> 3) & 0b1)

//uint8_t read_pin(void) {
//    /* Return if D3 is high (0) or low (1) */
//    return (PIND >> 3) & 0b1;
//}

uint8_t __attribute__ ((noinline)) read_bit(void) {
    /* Block until 0001 or 0111 is seen on D3, and then return
     * 0 or 1 respectively.
     */
    while (read_pin() != 0b0) {}
    PORTD |=  (1 << 5);
    PORTD &= ~(1 << 5);
    asm volatile("nop");

    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    if (read_pin() != 0b0)
        return 1;
    PORTD |=  (1 << 5);
    PORTD &= ~(1 << 5);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    if (read_pin() != 0b0)
        return 0;  // Ambiguous
    PORTD |=  (1 << 5);
    PORTD &= ~(1 << 5);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    return 0;
}

uint8_t __attribute__ ((noinline)) write_bit(uint8_t bit) {
    /* Block until 0001 or 0111 is seen on D3, and then return
     * 0 or 1 respectively.
     */
    DDRD |= 0b000001000; // Set D3 as output
    if (bit == 0) {
        PORTD &= ~(1 << 3);
        asm volatile("nop");

        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD &= ~(1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD &= ~(1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD |=  (1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing return
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
    } else {
        PORTD &= ~(1 << 3);
        asm volatile("nop");

        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD |=  (1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD |=  (1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing port read
        asm volatile("nop");
        asm volatile("nop");

        PORTD |=  (1 << 3);
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");

        // Replacing return
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
    }
    DDRD &= ~0b000001000; // Set D3 as input
}

uint8_t __attribute__ ((noinline)) write_controller_stop_bit() {
    /* Two up cycles and two down cycles
     * Controller sends this bit to console after initial packet
     */
    DDRD |= 0b000001000; // Set D3 as output
    PORTD &= ~(1 << 3);
    asm volatile("nop");

    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    // Replacing port read
    asm volatile("nop");
    asm volatile("nop");

    PORTD &= ~(1 << 3);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    // Replacing port read
    asm volatile("nop");
    asm volatile("nop");

    PORTD |= (1 << 3);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    // Replacing port read
    asm volatile("nop");
    asm volatile("nop");

    PORTD |=  (1 << 3);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    // Replacing return
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    DDRD &= ~0b000001000; // Set D3 as input
}

//const uint32_t console_req = 0x400302;
const uint32_t console_req = 0x400310;

//00 fd fd fd fc 00 00 00
inline void send_init() {
    // Tell the console we exist
    // 0000 0000 1000 0100 1000 0000 0010 0001 + (stop bit) + (2up 2down controller stop bit)

    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(1);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(0);
    write_bit(1);
    write_bit(0);
    write_bit(0);

    write_bit(1);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(0);
    write_bit(0);
    write_bit(1);
    write_bit(0);

    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(1);

    write_bit(1); // Stop bit

    write_controller_stop_bit();
}

inline void send_state() {
    // Reserved
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0); // Start
    write_bit(0); // Y
    write_bit(0); // X
    write_bit(0); // B
    write_bit(1); // A

    write_bit(1);
    write_bit(0); // L
    write_bit(0); // R
    write_bit(0); // Z
    write_bit(0); // D-Up
    write_bit(0); // D-Down
    write_bit(0); // D-Right
    write_bit(0); // D-Left

    // Joystick X value
    write_bit(0);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);

    // Joystick Y value
    write_bit(0);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);

    // C-stick X value
    write_bit(0);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);

    // C-stick Y value
    write_bit(0);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);
    write_bit(1);

    // Left Button
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    // Right Button
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);
    write_bit(0);

    write_bit(1);  // Stop bit
}

int main(void) {    
    cli();
    // Initialize serial
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

    // Set pins
    DDRD &= ~0b000001000; // Set D3 as input
    DDRD |=  0b000100000; // Set D5 as output

    // Tell console we exist
    send_init();
                
    while(1) {
        // Read for all zeros
        //uint32_t buffer = 0;
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //read_bit();  // Stop bit

        // Wait for controller ask
        uint32_t buffer = 0;
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        shift_left(buffer, read_bit());
        read_bit();  // Stop bit
        printf("%02x %02x %02x\r\n", ((uint8_t*)&buffer)[2],
                                     ((uint8_t*)&buffer)[1],
                                     ((uint8_t*)&buffer)[0]);

        if (buffer == console_req) {
            // Read controller response
            uint32_t controller_resp_h = 0;
            uint32_t controller_resp_l = 0;

            shift_left_32(controller_resp_h, read_bit());
            shift_left_32(controller_resp_l, read_bit());
            read_bit();  // Check

            //printf("%02x %02x %02x %02x %02x %02x %02x %02x\r\n",
            //       ((uint8_t*)&controller_resp_h)[3],
            //       ((uint8_t*)&controller_resp_h)[2],
            //       ((uint8_t*)&controller_resp_h)[1],
            //       ((uint8_t*)&controller_resp_h)[0],
            //       ((uint8_t*)&controller_resp_l)[3],
            //       ((uint8_t*)&controller_resp_l)[2],
            //       ((uint8_t*)&controller_resp_l)[1],
            //       ((uint8_t*)&controller_resp_l)[0]);
            //
            // Write things!
            send_state();
            printf("Sent A button");
        }

        // Handshake code
        //uint32_t buffer = 0;
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //shift_left(buffer, read_bit());
        //if (buffer == 1) {
        //    // Print handshake
        //    uint32_t controller_resp_h = 0;
        //    uint32_t controller_resp_l = 0;

        //    shift_left_32(controller_resp_h, read_bit());
        //    shift_left_32(controller_resp_l, read_bit());
        //    read_bit();  // Check

        //    printf("%02x %02x %02x %02x %02x %02x %02x %02x\r\n",
        //           ((uint8_t*)&controller_resp_h)[3],
        //           ((uint8_t*)&controller_resp_h)[2],
        //           ((uint8_t*)&controller_resp_h)[1],
        //           ((uint8_t*)&controller_resp_h)[0],
        //           ((uint8_t*)&controller_resp_l)[3],
        //           ((uint8_t*)&controller_resp_l)[2],
        //           ((uint8_t*)&controller_resp_l)[1],
        //           ((uint8_t*)&controller_resp_l)[0]);
        //}
    }
        
    return 0;
}
