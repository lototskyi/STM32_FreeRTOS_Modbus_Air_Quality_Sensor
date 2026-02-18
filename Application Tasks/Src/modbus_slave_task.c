/*
 * modbus_slave_task.c
 *
 * Contains the Modbus Slave application task implementation.
 */

#include "modbus_slave_task.h"
#include "error_handler_task.h"
// Todo: include the below once integrated/implemented
//#include "modbus_data_mgr_task.h"
#include "modbus_slave.h"
//#include "modbus_sync.h"
//#include "system_events.h"
//#include "uart.h"

// Initialize Modbus Slave buffers
modbus_buffers_t modbus_buffers = {0};

// Queue handle for the feedback queue, shared with the Modbus Data Manager Task
QueueHandle_t modbus_feedback_queue_handle = NULL;

// GLobal task handle for the Modbus Slave task
static TaskHandle_t modbus_slave_task_handle;

/**
 * Modbus FreeRTOS task.
 * Handles Modbus RTU requests by processing commands from the master device.
 * This task initializes required components, waits for notifications to process incoming data,
 * validates requests, and executes appropriate actions based on function codes.
 * `Todo` comments mark sections for further development as the task is implemented step-by-step.
 */
static void modbus_slave_task(void * params)
{
    // Modbus operations return status
    error_t modbus_slave_task_status;

    // Todo: Initialize UART2 for the Modbus Slave


    // Todo: Initialize the Holding Registers


    // Todo: Initialize the Input Registers


    // Todo: Enable RXNE interrupt


    // Todo: Set Modbus initialized bit for synchronization with the Sensor Task

    // Address and quantity to pass to the Modbus Data Manager Task
    uint16_t changed_address, number_of_regs_changed;

    while (1)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
        {

        }

    }
}

void modbus_slave_task_send_notification_from_isr(BaseType_t *xHigherPriorityTaskWoken)
{
    vTaskNotifyGiveFromISR(modbus_slave_task_handle, xHigherPriorityTaskWoken);
}

void modbus_slave_tasks_start(void)
{
    // Todo: Create the synchronization mutex


    // Todo: Create the feedback queue


    // Todo: Start the Modbus Data Manager Task


    // Create Modbus Slave Task
    configASSERT(xTaskCreate(modbus_slave_task,
                             "Modbus Slave Task",
                             MODBUS_SLAVE_TASK_STACK_SIZE,
                             NULL,
                             MODBUS_SLAVE_TASK_PRIORITY,
                             &modbus_slave_task_handle) == pdPASS);
}
