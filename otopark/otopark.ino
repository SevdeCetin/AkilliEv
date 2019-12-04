
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
   - Arduino Mega 2560 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */

/*  Dolu digital portlar: 0 1 3 4 22 23 24 26 32 33 36 38 39 42 43 44 */
/*  Dolu analog portlar: a15 a14 a13 a12  */
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
//SoftwareSerial EspSerial(0, 1); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);






                BLYNK_WRITE(V0)   //bu sanal pin bu bylnk da görünür lcd de gösterebilirsin
                {
                  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
                
                  // process received value
                }BLYNK_WRITE(V1)
                {
                  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
                
                  // process received value
                }
                /*RFID sensör baş*/
                      #include <SPI.h>
                      /* Include the RFID library */
                      #include <RFID.h>
                        
                      /* Define the DIO used for the SDA (SS) and RST (reset) pins. */
                      #define SDA_DIO 10
                      #define RESET_DIO 9
                      #define ledPin 8
                     /* Create an instance of the RFID library */
                      RFID RC522(SDA_DIO, RESET_DIO); 
                      String kart1="501801921170";
                      String kart2="462462184341";
                      String kart="";
                
                /*RFID sensör son*/

                
  /*mesafe sensörü basi*/
  #define echoPin 6
  #define trigPin 7
  #define buzzerPin 5
  int maximumRange = 15;
  int minimumRange = 0;
  /*mesafe sensörü sonu*/
      
      
                BLYNK_WRITE(V2)
                {
                  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
                
                  // process received value
                }
                /*servo-motor baş*/
                        #include <Servo.h>  
                        Servo servo1kapi;
                       // #define servointKapi 6
                /*servo-motor son*/
                


/*fan-röle başı*/
//röle ve lm35 in pinleri belirlendi
int role=3;       
int lm35=A2;
/*fan-röle sonu*/ 

          
void setup()
{
  // Debug console
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

        /*RFID sensör baş*/
        /* Initialise the RFID reader */
        RC522.init();
        pinMode(ledPin, OUTPUT);
        /*RFID sensör son*/
                
                /*servo-motor baş*/
                        //Kahverengi=GND Ortadaki=VCC Diğeri=OUT
                        servo1kapi.attach(A1);  //anakapı
                /*servo-motor son*/
 /*mesafe sensörü basi*/
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  /*mesafe sensörü sonu*/
  


  /*fan-röle başı*/
  analogReference(INTERNAL);    //arduino 1,1V referansa ayarlandı
  pinMode(role,OUTPUT);       //röle çıkış olarak tanımlandı
 /*fan-röle sonu*/ 
  
            
}


void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

            /*RFID sensör baş*/
                    kart=""; // bu boş kart ben tanımladım okutulan kar bu kart değerine eşitleniyor sonra işlem yapıldıktan sonra değer sıfırlanıyor boş oluyor
                    
                    /* Has a card been detected? */
                    if (RC522.isCard())
                    {
                      /* If so then get its serial number */
                      RC522.readCardSerial();
                      //Serial.println("Card detected:");
                      for(int i=0;i<5;i++)
                      {
                      //Serial.print(RC522.serNum[i],DEC);
                      kart=kart+RC522.serNum[i];
                      //Serial.print(RC522.serNum[i]); //to print card detail in Hexa Decimal format
                      }
                      //Serial.println();
                      //Serial.println();
                      //Serial.println(kart);
                      Blynk.virtualWrite(V0, kart); // burada okutulan kartın kodunu gösteriyor blynk da lcd ye v7 seçersen değeri görürsün
                    }
                    
                    if (kart == kart1) {                //kart kart1 e eşitse kapıyı açıyor ve v8 e kapı açıldı yazıyor
                          servo1kapi.write(100);
                          digitalWrite(ledPin, HIGH);
                          Blynk.virtualWrite(V1, "KAPI AÇILDI.");  
                          } 
                       if (kart == kart2) {     // okutulan kart kart2 ye eşitse kapıyı kapatıp kapandı yazıyor 
                            servo1kapi.write(10);
                            digitalWrite(ledPin, LOW);
                          Blynk.virtualWrite(V1, "KAPI KAPANDI.");
                            }
            /*RFID sensör son*/ 
  /*mesafe başı*/
  int olcum = mesafe(maximumRange, minimumRange);
  melodi(olcum * 10);
  /*mesafe sonu*/  




    /*fan-röle başı*/
  int okunanDeger = analogRead(A2);          //analog deger okundu ve okunanDeger değişkenine atandı
  float derece = okunanDeger / 9.31;         //derece hesaplandı
  Serial.println(derece);                    //derece ekrana yazdırıldı
  delay(100);

  Blynk.virtualWrite(V4, derece);
  if(derece >35){
    digitalWrite(role,LOW);                 //röleye güç verildi
    Blynk.virtualWrite(V3, "FAN AÇILDI."); 
  }
    else{
    digitalWrite(role,HIGH);                  //röle kapatıldı
    Blynk.virtualWrite(V3, "FAN KAPANDI."); 
    }
  /*fan-röle sonu*/ 
        
            
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
  Blynk.virtualWrite(V2, distance);
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
