/*
 * modbus_data_mgr_task.c
 *
 * Contains the Modbus Data Manager task implementation.
 */

#include "modbus_data_mgr_task.h"
#include "modbus_slave_task.h"
#include "modbus_sync.h"
#include "error_handler_task.h"
#include "sensors_task.h"

#include "queue.h"

/**
 * Queue handle for the Modbus Data Manager task.
 */
static QueueHandle_t modbus_data_mgr_queue_handle;

// Todo: process_modified_coils(), process_modified_holding_registers()
// Todo: process_input_registers_update() and related helper functions

/**
 * Handles incoming messages to update various Modbus data types,
 * including coils, holding registers, and input registers.
 * 1. Waits for data update messages in the queue.
 * 2. Processes updates based on the data type and takes appropriate actions.
 * 3. Sends feedback if required and handles errors during processing.
 * 4. Maintains synchronization with Mutex to ensure data consistency.
 */
static void modbus_data_mgr_task(void *param)
{
    modbus_data_mgr_processing_msg_t data_update_msg;
    modbus_data_mgr_feedback_msg_t feedback_msg;

    while (1)
    {
        if (xQueueReceive(modbus_data_mgr_queue_handle, &data_update_msg, portMAX_DELAY))
        {
            error_t lock_status = modbus_sync_lock();

            if (lock_status == ERR_OK)
            {
                feedback_msg.status = ERR_OK;

                switch (data_update_msg.msg_type)
                {
                    case COIL_COMMAND:
//                        feedback_msg.status = process_modified_coils(data_update_msg);
                        if (feedback_msg.status != ERR_OK)
                        {
                            error_handler_send_msg(EVT_MODBUS_DATA_UPDATE_COILS_FAIL);
                        }
                        break;
                    case HOLDING_REGS_UPDATE:
//                        feedback_msg.status = process_modified_holding_registers(data_update_msg);
                        if (feedback_msg.status != ERR_OK)
                        {
                            error_handler_send_msg(EVT_MODBUS_DATA_UPDATE_HOLDING_REGS_FAIL);
                        }
                        break;
                    case INPUT_REGS_UPDATE:
//                        feedback_msg.status = process_input_registers_update(data_update_msg);
                        if (feedback_msg.status != ERR_OK)
                        {
                            error_handler_send_msg(EVT_MODBUS_DATA_UPDATE_INPUT_REGS_FAIL);
                        }
                        break;
                    default:
                        feedback_msg.status = ERR_FAIL;
                        break;
                }

                if (data_update_msg.requires_feedback)
                {
                    modbus_data_mgr_send_feedback_msg(feedback_msg.status);
                }

                modbus_sync_unlock();
            }
            else
            {
                error_handler_send_msg(EVT_MODBUS_MUTEX_TIMEOUT);
            }
        }

    }
}

error_t modbus_data_mgr_send_processing_msg(modbus_data_mgr_msg_e msg_type,
                                            void *data,
                                            uint16_t addr,
                                            uint16_t qty,
                                            bool req_feedback)
{
    error_t status = ERR_OK;

    modbus_data_mgr_processing_msg_t data_update_msg;
    data_update_msg.msg_type = msg_type;
    data_update_msg.data = data;
    data_update_msg.address = addr;
    data_update_msg.quantity = qty;
    data_update_msg.requires_feedback = req_feedback;

    if (xQueueSend(modbus_data_mgr_queue_handle, &data_update_msg, portMAX_DELAY) != pdTRUE)
    {
        status = ERR_FAIL;
    }

    return status;
}

error_t modbus_data_mgr_send_feedback_msg(error_t feedback_status)
{
    error_t status = ERR_OK;

    modbus_data_mgr_feedback_msg_t feedback_message;
    feedback_message.status = feedback_status;

    if (xQueueSend(modbus_feedback_queue_handle, &feedback_message, portMAX_DELAY) != pdTRUE)
    {
        status = ERR_FAIL;
    }

    return status;
}

void modbus_data_mgr_start(void)
{
    modbus_data_mgr_queue_handle = xQueueCreate((UBaseType_t) 10, sizeof(modbus_data_mgr_processing_msg_t));

    configASSERT(modbus_data_mgr_queue_handle != NULL);

    configASSERT(xTaskCreate(modbus_data_mgr_task,
                             "Modbus Data Manager Task",
                             MODBUS_DATA_MGR_TASK_STACK_SIZE,
                             NULL,
                             MODBUS_DATA_MGR_TASK_PRIORITY,
                             NULL) == pdPASS);
}
