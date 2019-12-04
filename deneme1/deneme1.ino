/* This sketch send data to Blynk server and back to mobile phone.
   The DHT11 data is not working. Some issues with the data aquisition.
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>

char auth[]= "YourAuthToken"; // Your Auth token
char ssid[]= "YourNetworkSSID";
char pass[]= "Yourpassword";

const int pinDHT11 = 2; // GPIO2 on your ESP8266 Wifi Module
SimpleDHT11 dht11;
BlynkTimer timer;

void sendSensor()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  // for debug purposes.
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  // DHT11 sampling rate is 1HZ.
  delay(1000);
  Blynk.virtualWrite(V5, temperature);

}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Sending authentication token to blynk. Getting access to your WiFi with SSID and password
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
