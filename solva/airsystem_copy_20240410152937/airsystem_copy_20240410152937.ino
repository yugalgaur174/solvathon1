#define BLYNK_TEMPLATE_ID "TMPL33iWhnlmr"
#define BLYNK_TEMPLATE_NAME "airsystem"
#define BLYNK_AUTH_TOKEN "n39HrLfApoKLIBt0Wv6UxvWFSE664lIu"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


char auth[] = "n39HrLfApoKLIBt0Wv6UxvWFSE664lIu";
char ssid[] = "Infinix";  // Enter your WIFI SSID
char pass[] = "sakshamp";
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int mq135Pin = 4; 
int gasThreshold = 300;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(100L, DHT11sensor);
}

void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (t > 37.5) {
    Blynk.logEvent("temperature", "Very High Temperature! BE CALM !!");
  } else {
    Blynk.logEvent("temperature", "Nothing to Worry");
  }

  if (h > 90) {
    Blynk.logEvent("humidity", "Warning,Sweating very much ! Don't panic !! ");
  } else {
    Blynk.logEvent("humidity", "Warning, Nothing to worry");
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

void mq135Reading(){
  int gasValue = analogRead(mq135Pin);
  if (gasValue > gasThreshold){
    Blynk.logEvent("gas_sensor","WARNNG! Not Good Air");
  }else{
    Blynk.logEvent("gas_sensor","NO WORRIES");
  }

  Blynk.virtualWrite(V2, gasValue);
}

void loop(){
int gasValue = analogRead(mq135Pin);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    Serial.println("Gas emissions detected. Shift to other place for health caution.");
  } else {
    Serial.println("No gas emission detected");
  }

   //Blynk.virtualWrite(V2, gasValue);

  Blynk.run();
  timer.run();
}