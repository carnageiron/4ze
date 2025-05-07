# 🧾 Battery Monitor Interface on KS0108 GLCD using Arduino Nano

This project displays a boot-up logo followed by a navigable menu showing real-time battery statistics like speed, voltage, capacity, and state of health on a 128x64 GLCD (KS0108-based) using an Arduino Nano.

---

## 📦 Features

- ✅ Displays a **custom logo** on startup  
- ✅ Simple **menu interface** with selectable items  
- ✅ Shows mock battery values for:
  - Speed (km/h)
  - Capacity (%)
  - Voltage (V)
  - State of Health (%)

---

## 🧰 Hardware Requirements

| Component             | Specs                                  |
|-----------------------|----------------------------------------|
| Microcontroller       | Arduino Nano (ATmega328P)              |
| Display               | 128x64 GLCD (KS0108 controller)        |
| Library Requirement   | `glcd-arduino` (GLCD library by Michael Margolis) |
| Power Supply          | 5V USB or external                     |
| Interface             | Parallel (as per KS0108 standard pinout) |
| Optional              | Push buttons (if interactive navigation is desired) |

---

## 📚 Software Requirements

- **Arduino IDE**
- **GLCD Library**  
  Install via:  
  `Sketch > Include Library > Manage Libraries...` → search for **GLCD** by Michael Margolis

---

## 🛠 Wiring (KS0108 to Arduino Nano)

| GLCD Pin | Function        | Nano Pin        |
|----------|------------------|-----------------|
| D0–D7    | Data Bus         | D8–D13, A0, A1   |
| RS       | Register Select  | D7              |
| RW       | Read/Write       | GND             |
| EN       | Enable           | D6              |
| CS1/CS2  | Chip Select      | D4 / D5         |
| VEE      | Contrast Adjust  | Potentiometer   |
| VCC/GND  | Power            | 5V / GND        |

**Note**: Wiring depends on the GLCD library's configuration. Adjust as needed in `glcd_Config.h`.

---

## 🚀 Upload Instructions

1. Connect your Arduino Nano via USB
2. In Arduino IDE:
   - **Board**: Select `Arduino Nano`
   - **Processor**: Try `ATmega328P (Old Bootloader)` if upload fails
   - **Port**: Select the correct COM port
3. Upload the sketch

If upload fails with `stk500_getsync()` error, see the troubleshooting section.

---

## 🔧 Troubleshooting

If upload fails:
- Select **"ATmega328P (Old Bootloader)"** under Tools > Processor
- Use a **data-capable USB cable**
- Install **CH340 driver** (commonly used in Nano clones)
- Press the Nano’s **reset button** just before upload begins

---

## 🖼 Tips

FLASH glcd_v2.ino as it the more improved and worked on version also it is the most up-to-date version

## PIN LIST

KS0108_GLCD display: D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, A2, A3, A4
BUTTON_PIN: A0
SPEED POTENTIOMETER: A1
BATTERY_CAP: A5
VOLTAGE: A6
SOH: A7
