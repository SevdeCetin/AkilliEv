const int prob = A0; // sensörümüzden gelen veri ucuna A0 pini atandı
 
int olcum_sonucu; // toprağa giren probdan gelen verilerin kayıt edildiği
 // değişkenimiz
 
void setup()
{
 // analog pinler Arduino'da otomatik olarak giriş pin modunda olduğu için 
 // burada pinmodunu ayarlamaya gerek kalmıyor
 
Serial.begin(9600); // probtan gelen verileri okumak için seri monitörü başlattık
}
 
void loop()
{
 
olcum_sonucu = analogRead(prob); // prob pininden okunan veriyi ölçüm sonucuna kayıt ediyoruz
 
 Serial.print(" Toprak İslakligi = ");
 Serial.print(olcum_sonucu); // Ölçülen değeri seri monitöre yazdırıyoruz
 Serial.print("\n");
 delay(500); // seri monitördeki verileri rahat görebilmek veri için akışı yavaşlatıyoruz
}
