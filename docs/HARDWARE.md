# Hardware — IoTSmartAttendanceSystem

## Parts and electrical limits
ESP32 DevKit and MFRC522 3.3 V RFID reader and 13.56 MHz tags. Power low-voltage modules from a suitable regulated supply, tie grounds together, and verify signal levels before connection. GPIO34 is input-only and ADC1 is used because ADC2 conflicts with Wi-Fi. Never apply more than 3.3 V to an ESP32 GPIO.

| ESP32 pin | Connection | Requirement |
|---|---|---|
| ESP32 3V3 | sensor VCC | Verify module supply rating |
| ESP32 GND | sensor GND | Common low-voltage ground |
| GPIO18 | MFRC522 SCK | SPI |
| GPIO19 | MFRC522 MISO | SPI |
| GPIO23 | MFRC522 MOSI | SPI |
| GPIO5 | MFRC522 SS | SPI |
| GPIO22 | MFRC522 RST | 3.3 V logic |

Use a pull-down on GPIO14's driver input so the load remains off during boot. Low-voltage relays must not be connected directly to GPIO, and inductive loads need flyback protection.

## Sensor specification and calibration
The firmware accepts card detected from 0 to 1 boolean. Secondary value is UID hash (32-bit integer). Publishes a noncryptographic UID hash only; tags are clonable and no identity roster is included. Use a multimeter and the sensor data sheet for the exact module revision.
