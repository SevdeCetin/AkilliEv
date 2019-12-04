#include <Keypad.h>

char* guvenlik_kodu="1234"; // kendi güvenlik kodumuzu burada olusturuyoruz
int position="0";   // hangi tuşa basıldığını bilmek için gerekli

const byte satir=4;
const byte sutun=3;

//tuş takımı rakamları ve sembollerini tanımlıyoruz
char tus[satir][sutun]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  //tus takımlarının bağlı olduğu pinler
  byte satir_pinleri[satir]={2,7,6,4};
  byte sutun_pinleri[sutun]={12,11,10};
  Keypad keypad=Keypad (makeKeymap (tus), satir_pinleri,sutun_pinleri,satir,sutun);
  int sari_led=8;
  int yesil_led=9;
  
void setup() {
  pinMode(sari_led, OUTPUT);
  pinMode(yesil_led, OUTPUT);
  setLocked (true);
//setLocked fonksiyonu tanımlanmıştır değer olarak true veya  false döndürür true değeri locked'dir ki bu tuş takımının kilitli olduğunu false değeri tuş takımının açık olduğunu belirtir
}

void loop() {
 //getKey() özelliği ile hangii tuşa basıldığına bakıyoruz
  char hangi_tus=keypad.getKey();
 //eğer * ve # tuşlarına basılırsa sistem kilitli
  if(hangi_tus == '*' || hangi_tus == '#')
  {
  position = 0;
  setLocked (true);  
  } 
  //eğer basılan tuşlargüvenlik kodu ile aynıysa
  //4 hane girilmesine izin ver
  //4 sayı bizim tanıttığımız kod rakamlarıdır
  if(hangi_tus == guvenlik_kodu[position])
  {
   position ++; 
  }
  if(position == 4)
  {
  setLocked(false);  
  }
  delay(100); //tuş sıçramasından dolayı güvenlik geçikmesi standarttır

}
//setLoked fonksiyonu tanımlanıyor

void setLocked (int  locked){
  if(locked)
  {
  digitalWrite(sari_led, HIGH);
  digitalWrite(yesil_led, LOW);  
  }
  else
  {
  digitalWrite(sari_led, LOW);
  digitalWrite(yesil_led, HIGH);      
  }
  
  }
