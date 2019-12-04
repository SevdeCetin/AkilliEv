// Karanlıkta yanan ışık projesi, arduonik.blogspot.com
int ldr = A1;             // ldr mizi analog pine bağlıyoruz 
int ldr_deger ;        //ldr değerinin tutulacağı değişkeni tanımlıyoruz değişkenimiz tam sayı olacağı için int(integer) olarak belirliyoruz
int led = 4;           // led bağladığımız pini tanımlıyoruz
void setup()
{
 pinMode(led, OUTPUT);  //led pinimizi çıkış olarak kuruyoruz
  pinMode(ldr, INPUT);  //ldr pinimizi veri giriş pini olarak kuruyoru
  Serial.begin(9600);
}

void loop()
{
  ldr_deger = analogRead(ldr);          // ldr değerimizi analog pinden okuyoruz
  Serial.println(ldr_deger); // Serial ekranımıza ( Arduino ide açıkken ctrl+shit+m tuş kombinasyonu ile yada üst taraftaki simgesi yada üsteki menüden açabilirsiniz) ldr değrini yazdırıyoruz
  if (ldr_deger < 600){ // eğer ldr değerimiz 600 den fazla olursa
     digitalWrite(led, HIGH);  // led yanacak
  }
  else{   // 600 den küçük değilse
    digitalWrite(led, LOW); // led yanmauacak 
    }
  delay(100); // 0.1 saniye sonra ldr değeri okunarak yukarıda istenilen şartlar kontrol edecek ve güç kesilene kadar bu işlemler devam edecek 
}
