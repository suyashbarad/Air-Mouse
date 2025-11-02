# #Air-Mouse
Developed a wireless air mouse using an ESP32 microcontroller and MPU6050 motion sensor to control computer cursor movements through hand gestures. Implemented sensor data processing and Bluetooth communication for seamless motion-based control.

#  #Air Mouse using ESP32 and MPU6050

##  #Project Overview
The **Air Mouse** is an innovative project that transforms hand gestures into mouse movements using an **ESP32 microcontroller** and an **MPU6050 motion sensor**. The system captures real-time accelerometer and gyroscope data to control the cursor wirelessly via Bluetooth, offering a hands-free and intuitive user experience.

---

##  #Features
- Motion-controlled wireless mouse  
- Bluetooth connectivity with computers  
- Real-time accelerometer and gyroscope data processing  
- Compact and low-power design  
- Cross-platform compatibility (Windows, macOS, Linux)

---

##  #Working Principle
1. The **MPU6050** sensor detects the orientation and movement of the hand.  
2. The **ESP32** processes the sensor data using motion algorithms.  
3. The ESP32 transmits cursor control signals via **Bluetooth HID (Human Interface Device)**.  
4. The connected computer interprets these signals as normal mouse movements.

---

##  #Hardware Components
| Component | Description |
|------------|-------------|
| ESP32 | Wi-Fi and Bluetooth-enabled microcontroller |
| MPU6050 | 3-axis accelerometer and 3-axis gyroscope |
| Power Supply | 5V battery or USB connection |
| Jumper Wires | For connections between components |

---

##  #Circuit Connections
| ESP32 Pin | MPU6050 Pin |
|------------|--------------|
| 3.3V | VCC |
| GND | GND |
| GPIO 21 | SDA |
| GPIO 22 | SCL |

---

##  #Software & Libraries
- **Arduino IDE**
- **ESP32 Board Package**
- **Wire.h** for I2C communication  
- **BluetoothSerial.h** or **BleMouse.h** for Bluetooth HID functionality  
- **MPU6050.h** for sensor data handling  

---

##  #Setup Instructions
1. Install **Arduino IDE** and add the **ESP32 board** via Board Manager.  
2. Install required libraries (`MPU6050`, `Wire`, `BleMouse`).  
3. Upload the program to your ESP32.  
4. Pair the ESP32 with your computer via Bluetooth.  
5. Move your hand — the cursor should move accordingly!

---

##  #Applications
- Gesture-controlled computer interface  
- Smart presentation controller  
- Gaming or VR input device  
- Accessibility tool for physically challenged users  

---

##  #Author
**Suyash Sachin Barad**  
📍 Pune, Maharashtra, India  
🔗 [GitHub](https://github.com/suyashbarad) | [LinkedIn](https://www.linkedin.com/in/suyash-sachin-barad-796b6534b)

---

##  #License
This project is open-source and available under the **MIT License**.

---

⭐ *If you like this project, don’t forget to star the repository!*
