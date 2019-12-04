#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "efcb1a28f1f7462cb14cd9eedfc3b0fd";
char ssid[] = "hande";
char pass[] = "12345678";
#define EspSerial Serial
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}
//ısı-nem sensörü baş/
        #include "dht.h"
        #define dht_apin A2 // Analog Pin sensor is connected to
        dht DHT;
//ısı-nem sensörü son/
void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  //ısı-nem sensörü baş/
        DHT.read11(dht_apin);
        int nem=DHT.humidity;
        int isi=DHT.temperature;
        Blynk.virtualWrite(V3, nem);
        Blynk.virtualWrite(V4, isi);
        delay(2000);
//ısı-nem sensörü son/
}
