# Configuration — IoTSmartAttendanceSystem

Create ignored `include/device_config.h` from the example. `WIFI_SSID` and `WIFI_PASSWORD` select the network; `MQTT_HOST` is the broker DNS name on port 8883; `MQTT_USERNAME`/`MQTT_PASSWORD` are unique per device; `MQTT_CA_CERT` is the PEM CA chain; `DEVICE_ID` is a short broker-approved identifier. Do not put secrets in `platformio.ini`, command-line build flags, or GitHub Actions.

The sampling interval is 200 milliseconds. The alert rule is `card detected > 0.5f` and the accepted primary range is 0–1 boolean. Change thresholds in `include/logic.h` after calibration. During Wi-Fi or broker loss, no output is driven.  SNTP access is needed before TLS broker connection. Rotate credentials at the broker, update the local ignored header, rebuild, and reflash securely.
