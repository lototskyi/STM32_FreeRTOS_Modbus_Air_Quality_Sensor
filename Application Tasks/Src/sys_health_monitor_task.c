/*
 * sys_health_monitor_task.c
 *
 *  Implements the System Health Monitor Task, responsible for:
 *  1. Monitoring the MCU's internal temperature and notifying the Error Handler if thresholds are exceeded.
 *  2. Regularly checking the status of critical tasks and resetting the watchdog timer if they are operational.
 */

#include "sys_health_monitor_task.h"
#include "error_handler_task.h"
#include "gpio.h"
// Todo: include adc.h, iwdg.h, tim.h

// Global health flags
volatile bool g_sensors_task_ok = false;
// ... Add more flags for other critical tasks if needed

// MCU temperature health flag
static volatile bool mcu_temp_ok = true;

// Optional: flag & variable used for demonstrating obtaining the updated MCU temperature
static volatile uint8_t ADC1_CONVERSION_COMPLETE = 0;
static volatile uint16_t adc_temp_val            = 0;

// Todo: define temperature_to_adc() conversion function

// Todo: define get_temperature() function

/**
 * System Health Monitor Task which monitors the MCU temperature and,
 * if critical tasks are operational, periodically kicks the Independent Watchdog.
 * @param param Parameters passed to the task (unused).
 */
static void sys_health_monitor_task(void *param)
{
    float internal_temp;

    // Todo: Convert the temperature high/low thresholds to ADC values using temperature_to_adc()

    // Todo: Initialize the analog watchdog based on the thresholds using adc_awd_init()

    // Initialize the IWDG here if not in Debug Mode
    if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 0)
    {
        // Debugger not connected, safe to enable IWDG
        // Todo: call iwdg_init()
    }

    // Variable used to check the system health
    bool system_healthy;

    // Specify the frequency of task execution and,
    // Initialize the xLastWakeTime variable with the current time
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        // Wait for the next cycle
        xTaskDelayUntil(&xLastWakeTime, xFrequency);

        // Todo: remove later
        gpio_toggle_pin(USER_LED_PORT, USER_LED_PIN);

        // Optional: Get the temperature for demonstration purposes
        if (ADC1_CONVERSION_COMPLETE)
        {
            // Todo: update `internal_temp` using `get_temperature(adc_temp_val)`
            ADC1_CONVERSION_COMPLETE = 0;
        }

        // Check if all critical tasks are running correctly
        system_healthy = g_sensors_task_ok && mcu_temp_ok;

        if (system_healthy)
        {
            // Todo: call iwdg_reset()

            g_sensors_task_ok = false;
            // ... reset any other task flags as well
        }
        else
        {
            // Handle the system health issue (e.g., log error to FRAM, take corrective action)
        }

        // Get rid of unused variable warning
        (void)internal_temp;
    }
}

void sys_health_monitor_task_start(void)
{
    // Setup for getting MCU temperature (TIM2 and ADC)
    // Todo: call tim2_init()
    // Todo: call adc_init()

    configASSERT(xTaskCreate(sys_health_monitor_task,
                             "System Health Monitor Task",
                             SYS_HEALTH_MONITOR_TASK_STACK_SIZE,
                             NULL,
                             SYS_HEALTH_MONITOR_TASK_PRIORITY,
                             NULL) == pdPASS);
}

// Todo: Define ADC_IRQHandler()
