#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char *SSID = "HSU_Students";
const char *PASSWORD = "dhhs12cnvch";
//sử dụng webapi cua bài backend tuần trước
const char *URL = "http://10.106.23.200:5555/insertSensor";
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
HTTPClient http;
void setup() {
Serial.begin(115200);
// Serial.setDebugOutput(true);
Serial.println();
Serial.println();
Serial.println();
for (uint8_t t = 4; t > 0; t--) {
Serial.printf("[SETUP] WAIT %d...\n", t);
Serial.flush();
delay(1000);
}
WiFi.mode(WIFI_STA);
WiFiMulti.addAP(SSID, PASSWORD);
// wait for WiFi connection
while (WiFiMulti.run() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void postJsonData() {
Serial.print("connecting to ");
if ((WiFiMulti.run() == WL_CONNECTED)) {
Serial.print("[HTTP] begin...\n");
if (http.begin(client, URL)) { // HTTP
Serial.print("[HTTP] POST...\n");
// format JSON
StaticJsonDocument<200> doc;  // Adjust the capacity as needed

// Gửi thông tin json
// {"id":"1","temperature":"25","humid":"43", time: ":"2021-5-25 10:00:12" }

doc["id"] = 1;  // Assuming 'id' is a numeric value
doc["temp"] = 25;  // Assuming 'temperature' is a numeric value
doc["humid"] = 43;  // Assuming 'humid' is a numeric value
doc["time"] = "2021-5-25 10:00:12";
doc["farmid"] = "1";
char output[128];
serializeJson(doc, Serial);  // Output to Serial for testing


http.addHeader("Content-Type", "application/json");
int httpCode = http.POST(output);
Serial.println(httpCode); //Print HTTP return code
// file found at server
if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
{
String payload = http.getString();
Serial.println(payload);
char input[128];
payload.toCharArray(input, 128);
//parseJson
Serial.println("Begin parse json data ...");
DynamicJsonDocument docResponse(2048);
DeserializationError err = deserializeJson(docResponse, payload);
if (err) {
Serial.print(F("deserializeJson() failed with code "));
Serial.println(err.c_str());
}
auto name = docResponse["name"].as<char*>();
Serial.println(name);
} else {
Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
}
http.end(); //Close connection Serial.println();
Serial.println("closing connection");
}
}
}
void loop() {
postJsonData();
delay(10000);
}