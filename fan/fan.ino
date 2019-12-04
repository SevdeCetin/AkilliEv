
//röle ve lm35 in pinleri belirlendi
int role=3;       
int lm35=A2;
 
void setup() {
 
  Serial.begin(9600);    //seri haberleşme başlatıldı
  analogReference(INTERNAL);    //arduino 1,1V referansa ayarlandı
  pinMode(role,OUTPUT);       //röle çıkış olarak tanımlandı
 
}
 
void loop() {
  int okunanDeger = analogRead(A0);          //analog deger okundu ve okunanDeger değişkenine atandı
  float derece = okunanDeger / 9.31;         //derece hesaplandı
  Serial.println(derece);                    //derece ekrana yazdırıldı
  delay(1000);
 
  if(derece >30)
    digitalWrite(role,LOW);                 //röleye güç verildi
    else
    digitalWrite(role,HIGH);                  //röle kapatıldı
  
 
}
