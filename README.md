# 🤖 4-DOF Robotic Arm

This project implements a 4-degree-of-freedom robotic arm controlled by a NodeMCU (ESP8266). It provides a web interface and keyboard controls to individually move each servo motor over Wi-Fi.

---

## Hardware

- NodeMCU (ESP8266)  
- 4x Servo motors  
- External 5V power supply for servos  
- Breadboard + jumper wires  

| Servo     | Function        | NodeMCU Pin |
|-----------|------------------|-------------|
| Servo 1   | Base rotation    | D1 (GPIO5)  |
| Servo 2   | Shoulder         | D2 (GPIO4)  |
| Servo 3   | Elbow            | D3 (GPIO0)  |
| Servo 4   | Wrist/Gripper    | D4 (GPIO2)  |

---

## Setup

1. Flash the NodeMCU with the Arduino sketch provided in this repository.  
2. Update the Wi-Fi credentials in the code (`SSID` and `PASSWORD`).  
3. Open the Serial Monitor to find the IP address assigned to the NodeMCU.  
4. Access the web interface in a browser using that IP address.

---

## Controls

You can control the robotic arm using the web buttons or keyboard keys:

- **Base**: `Q` / `A`  
- **Shoulder**: `W` / `S`  
- **Elbow**: `E` / `D`  
- **Wrist**: `R` / `F`  
