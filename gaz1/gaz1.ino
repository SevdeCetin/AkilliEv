float sensor=A0;
float gasValue;
int ledPin = 11; 
void setup()
{
pinMode(ledPin, OUTPUT);
pinMode(sensor,INPUT);
Serial.begin(9600);

}

void loop()
{

gasValue=analogRead(sensor);
Serial.println(gasValue);

if( gasValue > 600kö ){ 
digitalWrite(ledPin, HIGH); 
delay(500); 

} else{
digitalWrite(ledPin, LOW);
delay(500); 
}
}
