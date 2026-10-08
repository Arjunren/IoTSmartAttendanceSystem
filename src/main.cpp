#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <math.h>
#include <SPI.h>
#include <MFRC522.h>
#if __has_include("device_config.h")
#include "device_config.h"
#else
#include "device_config.example.h"
#endif
#include "logic.h"

WiFiClientSecure tls;
PubSubClient mqtt(tls);
unsigned long nextConnect=0, nextSample=0;
unsigned long backoff=1000;
MFRC522 reader(5,22);

Sample readSample() { Sample s{0,0,false}; if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) { uint32_t h=2166136261u; for(byte i=0;i<reader.uid.size;i++) h=(h^reader.uid.uidByte[i])*16777619u; s.value=1; s.aux=(float)(h & 0x00ffffffu); s.valid=true; reader.PICC_HaltA(); } return s; }

void connectNetwork() {
  if (WiFi.status()!=WL_CONNECTED) { WiFi.begin(WIFI_SSID,WIFI_PASSWORD); return; }
  if (time(nullptr)<1704067200) return; // Wait for SNTP before TLS validation.
  if (mqtt.connected()) return;
  String clientId=String("IoTSmartAttendanceSystem-")+DEVICE_ID;
  if (mqtt.connect(clientId.c_str(),MQTT_USERNAME,MQTT_PASSWORD)) { backoff=1000; }
}

void setup() {
  Serial.begin(115200);
  SPI.begin(18,19,23,5); reader.PCD_Init();
  WiFi.mode(WIFI_STA);
  configTime(0,0,"pool.ntp.org");
  tls.setCACert(MQTT_CA_CERT);
  mqtt.setServer(MQTT_HOST,8883);
  mqtt.setBufferSize(512);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
}

void loop() {
  unsigned long now=millis();
  if (WiFi.status()!=WL_CONNECTED || !mqtt.connected()) {

    if ((long)(now-nextConnect)>=0) {
      connectNetwork();
      nextConnect=now+backoff;
      backoff=backoff<30000 ? backoff*2 : 60000;
    }
  } else mqtt.loop();
  if ((long)(now-nextSample)<0) return;
  nextSample=now+200;
  Sample s=readSample();
  bool alarm=isAlert(s);

  if (!mqtt.connected()) return;
  char topic[128], payload[256];
  snprintf(topic,sizeof(topic),"devices/%s/telemetry",DEVICE_ID);
  snprintf(payload,sizeof(payload),"{\"device_id\":\"%s\",\"measurement\":%.3f,\"secondary\":%.3f,\"valid\":%s,\"alert\":%s,\"uptime_ms\":%lu}",DEVICE_ID,s.value,s.aux,s.valid?"true":"false",alarm?"true":"false",now);
  mqtt.publish(topic,payload,false);
}
