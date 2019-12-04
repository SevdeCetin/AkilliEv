/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - Arduino Uno board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "618100c9cab64f67b455f0f2d355fa7b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AndroidAP";
char pass[] = "nzss6578";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);
/*Alev sensörü*/
int sensorPin = A0; // select the input pin for the LDR
        int sensorValue = 0; // variable to store the value coming from the sensor
        //int led_alev_sensoru = 2; // Output pin for LED
        int buzzer = 12; // Output pin for Buzzer
/*Alev sensörü bitiş*/

/*Gaz sensörü*/
float sensor=A1;
float gasValue;
int ledPin = 11; 
/*Gaz sensörü bitiş*/

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

  /*alev sensörü*/
 // pinMode(led_alev_sensoru, OUTPUT);
        pinMode(buzzer,OUTPUT);Serial.begin(115200); //sets the baud rate for data transfer in bits/second
pinMode(sensorPin, INPUT);//the smoke sensor will be an input to the arduino
//pinMode(pinSpeaker, OUTPUT);//the buzzer serves an output in the circuit
/*alev sensörü bitişi*/

/*Gaz sensörü*/
pinMode(ledPin, OUTPUT);
pinMode(sensor,INPUT);
Serial.begin(9600);
/*Gaz sensörü bitişi*/
}


void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  /*alev sensörü baslangıç*/
 Serial.println("Welcome to TechPonder Flame Sensor Tutorial");
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if (sensorValue < 100)
        {
          Blynk.virtualWrite(V0, "Ateş algılandı.");
        //digitalWrite(led_alev_sensoru,HIGH);
        digitalWrite(buzzer,HIGH);
        }
        else if(sensorValue >= 100){
          Blynk.virtualWrite(V0, "Ateş yok.");
         // digitalWrite(led_alev_sensoru,LOW);
        digitalWrite(buzzer,LOW);
          }
   Serial.println("alev yok");
  /*alev sensörü bitisi*/
  
  /*Gaz sensörü*/
   gasValue=analogRead(sensor);
   Serial.println(gasValue);

   if( gasValue > 550){ 
   digitalWrite(ledPin, HIGH); 
    Blynk.virtualWrite(V1, "Gaz algılandı.");
  
   }
   else{
   digitalWrite(ledPin, LOW);
   delay(500); 
   Blynk.virtualWrite(V1, "Gaz yok.");
   }
    Serial.println("gaz yok");
  /*Gaz sensörü bitişi*/
  
}
