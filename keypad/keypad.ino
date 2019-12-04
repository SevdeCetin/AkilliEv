#include <Keypad.h>

const byte ROWS = 4; // 4 satır
const byte COLS = 3; // 3 sütun
// Key Haritası tanıtılıyor
char keys[ROWS][COLS] = {
{‘1′,’2′,’3’},
{‘4′,’5′,’6’},
{‘7′,’8′,’9’},
{‘*’,’0′,’#’}
};
//satırların bağlantı pinleri
byte rowPins[ROWS] = { 9, 8, 7, 6 };
// sıraların/sütunların bağlantı pinleri.
byte colPins[COLS] = { 12, 11, 10 };

// tustakımı oluşturuldu
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//led 5.pine takıldı.
#define ledpin 5

int buzzerPin = 4;      //buzzer 4. pine bağlandı.
String enterPassword = “”;  //keypad den girilen değer enterPassword değişkeninde tutulacak.
String password = “1234”; // Belirlenen parola password değişkenine atandı.
int control = 0; // ‘#’ tuşuna basılmış olma durumu control değişkenine atandı.

void setup()
{
pinMode(ledpin, OUTPUT);
Serial.begin(9600);
}

void loop()
{
keyControl(); //bütün kontroller bu method da yapılıyor.
}

void keyControl()
{
char keypressed = kpd.getKey();
if(keypressed != NO_KEY)
{
Serial.print(keypressed);
if(keypressed == ‘#’)
{
Serial.println(“Lütfen parolayı giriniz: “);
control = 1;
enterPassword = “1234”;
}
if (control == 1)
{
enterPassword = enterPassword + keypressed;
counter++;
if(keypressed == ‘*’)
{
enterPassword = enterPassword.substring(1,enterPassword.length() – 1);
if(enterPassword == password){
Serial.println(“Girilen şifre:” + enterPassword);
Serial.println(“Şifre doğru. Alarm pasif”);
digitalWrite(ledpin, LOW);
noTone(buzzerPin);
enterPassword = “”;
control = 0;
counter = 0;
}
else if(enterPassword != password)
{
Serial.println(“Girilen şifre:” + enterPassword);
Serial.println(“Şifre yanlış. Alarm aktif”);
digitalWrite(ledpin, HIGH);
tone(buzzerPin,1);
enterPassword = “1234”;
control = 0;
counter = 0;
}
}

}

}
}
