# Develop Real-World Embedded Software Skills with STM32 Using CMSIS, FreeRTOS & Modbus  
### Air Quality Sensor Project (STM32F446RE, CMSIS Only)

## 📌 Project Overview

This project demonstrates **production-grade embedded software development** using the **STM32F446RE** microcontroller with **CMSIS and direct register-level programming** (no STM32 HAL).

An **Air Quality Monitoring System** is implemented using:
- **SGP40** VOC sensor
- **SHT30** temperature & humidity sensor
- **MB85RS64 FRAM** for non-volatile data storage
- **FreeRTOS** for real-time task scheduling
- **Modbus RTU** for industrial communication

The project focuses on **clean architecture, real-time behavior, and reliable communication**, closely resembling real industrial firmware.

---

## 🎯 Project Objectives

- Write embedded firmware **without HAL**
- Use **CMSIS & register-level drivers**
- Implement **FreeRTOS** in a real system
- Interface I²C and SPI sensors
- Store calibration & historical data in FRAM
- Implement **Modbus RTU slave**
- Apply modular, scalable firmware design

---

## 🧰 Hardware & Software Stack

### Hardware
- **STM32F446RE** (ARM Cortex-M4F @ 180 MHz)
- **SGP40** – VOC air quality sensor (I²C)
- **SHT30** – Temperature & Humidity sensor (I²C)
- **MB85RS64** – 64-Kbit FRAM (SPI)
- RS-485 transceiver (MAX485 / SN75176)
- ST-Link debugger

### Software
- **CMSIS**
- **FreeRTOS**
- **Modbus RTU**
- GCC ARM toolchain
- STM32CubeIDE (IDE & debugger only)

---

