# Troubleshooting — IoTSmartAttendanceSystem

| Symptom | Check |
|---|---|
| No card detected | Verify sensor power, grounds, pin table, voltage limits, and module orientation. |
| Invalid sample | Check 0–1 boolean range and sensor calibration. |
| Wi-Fi disconnected | Check SSID, 2.4 GHz coverage, and local network policy. |
| MQTT disconnected | Check broker DNS, port 8883, CA PEM, device credentials, and publish ACL. |
| Unexpected alert | Inspect raw card detected and UID hash; calibrate the threshold in `logic.h`. |
| Build failure | Confirm PlatformIO is installed and dependency downloads are permitted. |

Publishes a noncryptographic UID hash only; tags are clonable and no identity roster is included.
