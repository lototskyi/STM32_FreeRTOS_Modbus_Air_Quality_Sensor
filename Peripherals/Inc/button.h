/*
 * button.h
 *
 * Interface for initializing and managing the Nucleo Board USER button for IWDG acknowledgment.
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>

/**
 * Time interval in milliseconds for LED blinking while waiting for button acknowledgment.
 */
#define BUTTON_ACK_BLINK_INTERVAL       ((uint32_t) 500)

/**
 * Sets up semaphore and configures external interrupts for the Nucleo Board USER button.
 */
void button_init(void);

/**
 * Handles an Independent Watchdog (IWDG) reset event.
 * It checks for the event, requires user acknowledgment through button press, and clears the IWDG flags.
 */
void button_check_and_acknowledge_iwdg_event();

#endif /* INC_BUTTON_H_ */
