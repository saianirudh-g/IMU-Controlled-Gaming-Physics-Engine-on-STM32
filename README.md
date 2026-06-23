# 🧠 STM32 Physics Engine & Game Development

### Embedded Real-Time Physics Simulation using MPU6050 IMU and SWV ASCII Renderer

![STM32F407](https://img.shields.io/badge/MCU-STM32F407VG-blue)
![Language](https://img.shields.io/badge/Language-C-brightgreen)
![Interface](https://img.shields.io/badge/Interface-I2C%20%7C%20PWM%20%7C%20SWV-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)

---

## 🎯 Overview

This project implements a **real-time physics-based game engine** on the **STM32F407VG** microcontroller.

The player tilts the board to move a ball, avoids obstacles, and aims for the highest score.

All game visuals are rendered as ASCII frames in the **SWV ITM Data Console**.

---

## 🧩 Features

* **IMU Tilt Control** – Reads MPU6050 accelerometer data via I2C for motion input.
* **Physics Engine** – Calculates velocity, acceleration, and collision boundaries in real time.
* **Particle System** – Generates dynamic effects for movement and collisions.
* **Audio Feedback** – Uses TIM3 PWM output for sound effects.
* **Flash Persistence** – Saves the high score to Flash Sector 11.
* **SWV ASCII Renderer** – Displays game frames and menus in the ITM Data Console.

---

## 🛠️ Hardware Setup

| Component     | Connection                  | Description                  |
| ------------- | --------------------------- | ---------------------------- |
| STM32F407VGTx | Main MCU                    | Runs the physics engine      |
| MPU6050       | I2C1 (SCL = PB6, SDA = PB7) | Provides tilt data           |
| USER Button   | PA0                         | Starts or restarts the game  |
| SWO Pin       | PB3                         | Outputs ASCII frames via SWV |
| TIM3          | PWM Output                  | Generates sound effects      |

---

## ⚙️ Software Configuration

* **Debug Interface:** Serial Wire (SWD)
* **SWV Clock:** 2 MHz
* **Core Clock:** 84 MHz
* **ITM Port:** Port 0 Enabled
* **STM32CubeMX:** SYS → Debug = Serial Wire

---

## 📂 Project Structure

```text
├── Core/
│   ├── Src/
│   │   ├── main.c
│   │   ├── physics.c
│   │   ├── game.c
│   │   ├── renderer.c
│   │   ├── audio.c
│   │   ├── mpu6050.c
│   │   └── flash.c
│   └── Inc/
│       ├── physics.h
│       ├── game.h
│       ├── renderer.h
│       ├── audio.h
│       ├── mpu6050.h
│       └── flash.h
├── Drivers/
│   └── STM32F4xx_HAL_Driver/
├── SWV_Output/
│   └── game_log.txt
└── README.md
```

---

## 📖 File Descriptions

### Core/Src

* **main.c** – Application entry point and peripheral initialization.
* **physics.c** – Ball movement, acceleration, gravity, and collision calculations.
* **game.c** – Game state management, scoring, and gameplay logic.
* **renderer.c** – ASCII rendering engine for SWV output.
* **audio.c** – Buzzer and sound effect generation using PWM.
* **mpu6050.c** – MPU6050 sensor driver and data acquisition.
* **flash.c** – Flash memory read/write operations for high-score storage.

### Core/Inc

Contains header files corresponding to each source module.

### Drivers

Contains STM32 HAL drivers and CMSIS libraries.

### SWV_Output

Stores SWV debug logs and runtime diagnostics.

### README.md

Project documentation and setup instructions.

---

## 🚀 How to Run

1. Open the project in **STM32CubeIDE**.
2. Connect the STM32F407VG board using ST-Link.
3. Open the **SWV ITM Data Console**.
4. Enable **Port 0** and click **Start Trace**.
5. Build and flash the firmware.
6. Run the application.
7. Tilt the board to move the ball.
8. Press the **USER Button (PA0)** to start or restart the game.

---

## 🧮 Core Physics Logic

```c
void Physics_Update(GameObject *ball, float dt)
{
    ball->velocity.x += ball->acceleration.x * dt;
    ball->velocity.y += ball->acceleration.y * dt;

    ball->position.x += ball->velocity.x * dt;
    ball->position.y += ball->velocity.y * dt;

    CheckCollision(ball);
}
```

---

## 🎮 Sample Game Output

```text
========================
       GAME OVER
========================

NEW HIGH SCORE!
Final Score: 454

Press USER button to restart
```

---

## 🪙 Credits

* **Developed By:** Sai Anirudh Godavarthi
* **Guided By:** Microsoft Copilot – AI Learning Companion
* **Date:** June 2025

---

## 📜 License

This project is intended for educational and embedded systems learning purposes.
Feel free to modify and extend the code for your own projects.
