/*
 * Main.c
 *
 * Created on: Sep 3, 2024
 * Author: Ahmed Nageeb
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

// Define segment bits for the first 7-segment display (lower nibble)
#define SEG_A1  0
#define SEG_B1  1
#define SEG_C1  2
#define SEG_D1  3

// Define segment bits for the second 7-segment display (upper nibble)
#define SEG_A2  7
#define SEG_D2  4
#define SEG_E2  5
#define SEG_F2  6

//Running Speed
#define Speed 500 //mSec

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
 * Function to handle rotation checks and activate corresponding cycles
 */
void CheckRotation(void) {
    RightCycle(); // Handle right rotation cycle
    LeftCycle();  // Handle left rotation cycle
    StopCycle();  // Handle stop cycle
}

/*
 * Function to cycle through segments in a rightward direction
 */
void RightCycle(void) {
    u8 RightCounter = 0; // Counter for segment position
    PORTA = 0xFF; // Set PORTA to high initially

    while ((0b11111110 == PINB) && (0b11111101 != PINB) && (0b11111100 != PINB)) {
        PORTA ^= (1 << SegmentArray[RightCounter]); // Toggle the current segment
        staues = PINA; // Store the current state of PORTA
        _delay_ms(Speed); // Delay for 500ms

        if (RightCounter == 7) { // Reset counter when it exceeds array bounds
            RightCounter = 0; // Start again from the beginning
        } else {
            RightCounter++; // Increment the counter
        }
    }
}

/*
 * Function to cycle through segments in a leftward direction
 */
void LeftCycle(void) {
    u8 LeftCounter = 7; // Counter for segment position
    PORTA = 0xFF; // Set PORTA to high initially

    while ((0b11111110 != PINB) && (0b11111101 == PINB) && (0b11111100 != PINB)) {
        PORTA ^= (1 << SegmentArray[LeftCounter]); // Toggle the current segment
        staues = PINA; // Store the current state of PORTA
        _delay_ms(Speed); // Delay for 500ms

        if (LeftCounter == 0) { // Reset counter when it goes below array bounds
            LeftCounter = 7; // Start again from the end
        } else {
            LeftCounter--; // Decrement the counter
        }
    }
}

/*
 * Function to stop the segment cycle and retain the last state
 */
void StopCycle(void) {
    while ((0b11111110 != PINB) && (0b11111101 != PINB) && (0b11111100 == PINB)) {
        PORTA = staues; // Retain the last state of PORTA
    }
}
