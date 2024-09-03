/*
 * Main.c
 *
 * Created on: Sep 3, 2024
 * Author: Ahmed Nageeb
 *
 * Description: This program controls a 7-segment display based on the input from PORTB.
 * It cycles through the segments of the display in both rightward and leftward directions
 * depending on the input conditions. It also retains the last state of the display when
 * a specific condition is met.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "STD_Types.h"

#define F_CPU 8000000UL  // Define CPU frequency for delay functions

// Function prototypes
void CheckRotation(void);
void RightCycle(void);
void LeftCycle(void);
void StopCycle(void);

// Define segment bit positions for the first 7-segment display (lower nibble)
#define SEG_A1  0
#define SEG_B1  1
#define SEG_C1  2
#define SEG_D1  3

// Define segment bit positions for the second 7-segment display (upper nibble)
#define SEG_A2  7
#define SEG_D2  4
#define SEG_E2  5
#define SEG_F2  6

// Define the delay speed in milliseconds
#define Speed 500

u8 Counter = 0;  // Counter for segment position

// Array to hold segment bit positions for sequential activation
u8 SegmentArray[8] = {SEG_A1, SEG_B1, SEG_C1, SEG_D1, SEG_D2, SEG_E2, SEG_F2, SEG_A2};

u8 staues = 0;  // Variable to hold the current state of PORTA

int main(int argc, char **argv) {
    DDRB = 0x00; // Set PORTB as input
    DDRA = 0xFF; // Set PORTA as output
    DDRC = 0xFF; // Set PORTC as output (though it's not used in the code)
    PORTB = 0xFF; // Initialize PORTB to high

    while (1) {
        CheckRotation(); // Continuously check rotation
    }

    return 0;
}

/*
 * Function to check rotation conditions and activate corresponding cycles.
 */
void CheckRotation(void) {
    RightCycle(); // Handle right rotation cycle
    LeftCycle();  // Handle left rotation cycle
    StopCycle();  // Handle stop cycle
}

/*
 * Function to cycle through segments in a rightward direction.
 */
void RightCycle(void) {
    // Check for specific conditions on PINB
    while ((0b11111110 == PINB) && (0b11111101 != PINB) && (0b11111100 != PINB)) {
        // Reset counter when it exceeds array bounds
        if (Counter == 7) {
            Counter = 0; // Start again from the beginning
        } else {
            Counter++; // Increment the counter
        }
        PORTA = ~(1 << SegmentArray[Counter]); // Toggle the current segment
        staues = PINA; // Store the current state of PORTA
        _delay_ms(Speed); // Delay for defined speed
    }
}

/*
 * Function to cycle through segments in a leftward direction.
 */
void LeftCycle(void) {
    // Check for specific conditions on PINB
    while ((0b11111110 != PINB) && (0b11111101 == PINB) && (0b11111100 != PINB)) {
        PORTA = ~(1 << SegmentArray[Counter]); // Toggle the current segment
        staues = PINA; // Store the current state of PORTA
        _delay_ms(Speed); // Delay for defined speed

        // Reset counter when it goes below array bounds
        if (Counter == 0) {
            Counter = 7; // Start again from the end
        } else {
            Counter--; // Decrement the counter
        }
    }
}

/*
 * Function to stop the segment cycle and retain the last state.
 */
void StopCycle(void) {
    // Check for specific conditions on PINB
    while ((0b11111110 != PINB) && (0b11111101 != PINB) && (0b11111100 == PINB)) {
        PORTA = staues; // Retain the last state of PORTA
    }
}
