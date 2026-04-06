# RFID Door Lock — Arduino UNO

A compact access control system built with an RFID reader, servo motor, and buzzer. Swipe a valid card to unlock the door for 3 seconds. Invalid cards trigger a 3-beep alert.

---

## Wiring Diagram

![Wiring Diagram](wiring_diagram.png)

> **Warning:** The RC522 module runs on **3.3V**. Connecting it to 5V will damage the module.

---

## Components

| Component       | Model / Notes             |
|-----------------|---------------------------|
| Microcontroller | Arduino UNO               |
| RFID module     | MFRC522 (RC522)           |
| Servo motor     | SG90 or equivalent        |
| Buzzer          | Active or passive buzzer  |
| Power supply    | USB or 9V adapter         |

---

## Wiring

### RC522 → Arduino UNO

| RC522 pin | Arduino pin | Wire color |
|-----------|-------------|------------|
| SDA (SS)  | 10          | Blue       |
| SCK       | 13          | Cyan       |
| MOSI      | 11          | Amber      |
| MISO      | 12          | Pink       |
| RST       | 9           | Green      |
| GND       | GND         | Gray       |
| 3.3V      | **3.3V** ⚠️ | Orange     |

### Servo motor → Arduino UNO

| Servo  | Arduino pin |
|--------|-------------|
| Signal | 6           |
| VCC    | 5V          |
| GND    | GND         |

### Buzzer → Arduino UNO

| Buzzer | Arduino pin |
|--------|-------------|
| +      | 7           |
| −      | GND         |

---

## Libraries

Install via **Arduino IDE → Tools → Manage Libraries**:

- [MFRC522](https://github.com/miguelbalboa/rfid) by Miguel Balboa
- [Servo](https://www.arduino.cc/en/Reference/Servo) — built into Arduino IDE

---

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/rfid-lock.git
   ```

2. Open `rfid_lock/rfid_lock.ino` in Arduino IDE.

3. Install the required libraries (see above).

4. Connect all components according to the wiring diagram.

5. **Find your card's UID** — open Serial Monitor (9600 baud), hold your card near the reader, and note the UID printed to the console.

6. Update the UID in the sketch:
   ```cpp
   byte validUID[4] = {0x05, 0xA3, 0xC7, 0x01}; // ← replace with your card's UID
   ```

7. Upload the sketch to your Arduino.

---

## How It Works

```
Card presented
      │
      ▼
  Read UID
      │
 ┌────┴────┐
 │ Valid?  │
 └────┬────┘
  Yes │       No
  ▼             ▼
Buzzer (1×)   Buzzer (3×)
Servo → 90°   ──────────
Wait 3s
Servo → 0°
```

---

## Project Structure

```
rfid-lock/
├── rfid_lock/
│   └── rfid_lock.ino
├── wiring_diagram.png
├── README.md
└── LICENSE
```

---

## Possible Improvements

- [ ] Support multiple valid cards
- [ ] Add green/red LED indicators
- [ ] Add an LCD display for status messages
- [ ] Log access events to an SD card
- [ ] Add a manual override button

---

## License

This project is licensed under the [MIT License](LICENSE).
