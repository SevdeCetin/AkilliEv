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
char auth[] = "efcb1a28f1f7462cb14cd9eedfc3b0fd";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Sevde iPhone’u";
char pass[] = "sevdesare";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

/*mesafe sensörü basi*/
#define echoPin 9
#define trigPin 7
#define buzzerPin 8
int maximumRange = 50;
int minimumRange = 0;
/*mesafe sensörü sonu*/

/*rfid başı*/
#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>                      //MFRC522 kütüphanemizi tanımlıyoruz.
#include <Servo.h>                        //Servo kütüphanemizi tanımlıyoruz.

int RST_PIN = 9;                          //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 10;                          //RC522 modülü chip select pinini tanımlıyoruz.
int servoPin = 8;                         //Servo motor pinini tanımlıyoruz.

Servo motor;                              //Servo motor için değişken oluşturuyoruz.
MFRC522 rfid(SS_PIN, RST_PIN);            //RC522 modülü ayarlarını yapıyoruz.
byte ID[4] = {50, 180, 19, 211};          //Yetkili kart ID'sini tanımlıyoruz. 
byte ID1[4] = {46, 246, 218, 43}; 
/*rfid sonu*/

BLYNK_WRITE(V0){
  
  int pinValue = param.asInt();
  
  }
  
BLYNK_WRITE(V1){
  
  int pinValue = param.asInt();
  
  }
void setup()
{
  // Debug console
  //Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
  /*mesafe sensörü basi*/
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  /*mesafe sensörü sonu*/

  /*rfid başı*/
  motor.attach(servoPin);                 //Servo motor pinini motor değişkeni ile ilişkilendiriyoruz.
  Serial.begin(9600);                     //Seri haberleşmeyi başlatıyoruz.
  SPI.begin();                            //SPI iletişimini başlatıyoruz.
  rfid.PCD_Init();                        //RC522 modülünü başlatıyoruz.

  /*rfid sonu*/
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  
  /*mesafe başı*/
  int olcum = mesafe(maximumRange, minimumRange);
  melodi(olcum * 10);
  /*mesafe sonu*/
  

  /*rfid bası*/

  if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
    return;

  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] &&
    rfid.uid.uidByte[3] == ID[3] ) {
        Serial.println("Kapi acildi");
        Blynk.virtualWrite(V1, "acildi");
       // ekranaYazdir();
        motor.write(180);                 //Servo motoru 180 dereceye getiriyoruz.
        delay(1000);
    }
  
    if (rfid.uid.uidByte[0] == ID1[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID1[1] && 
    rfid.uid.uidByte[2] == ID1[2] && 
    rfid.uid.uidByte[3] == ID1[3] ) {
        Serial.println("Kapi kapandi");
        Blynk.virtualWrite(V1, "kapandi");
        //ekranaYazdir();
        motor.write(0);                   //Servo motoru 0 dereceye getiriyoruz.
        delay(1000);
    }
    
   else{                                 //Yetkisiz girişte içerideki komutlar çalıştırılır.
      Serial.println("");
      //ekranaYazdir();
    }
  rfid.PICC_HaltA();
  
  /*rfid sonu*/
  
}

/*mesafe başı*/
int mesafe(int maxrange, int minrange)
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(50);
  Blynk.virtualWrite(V0, distance);
  if (distance >= maxrange || distance <= minrange)
    return 0;
  return distance;
  
}

int melodi(int dly)
{
  tone(buzzerPin, 440);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}
/*mesafe sonu*/
