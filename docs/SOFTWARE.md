# Software — IoTSmartAttendanceSystem

Firmware is C++ with Arduino on ESP32. `src/main.cpp` implements rfid acquisition, bounded JSON telemetry, Wi-Fi reconnection, TLS broker connection, and alert publication. `include/logic.h` defines value validation and the `card detected > 0.5f` rule. PlatformIO pins `platformio/espressif32@6.10.0` and `knolleary/PubSubClient@2.8.0` plus `miguelbalboa/MFRC522@1.4.12`.

No backend, frontend, or database is part of this firmware-only architecture. An operator-supplied MQTT broker enforces the device's publish ACL and TLS identity. No watchdog API is configured; a hardware watchdog and persistent configuration are future work.
