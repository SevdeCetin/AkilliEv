const int sensorPin= 0;
const int pinSpeaker= 10;
int smoke_level;

 
void setup() {
Serial.begin(115200); //sets the baud rate for data transfer in bits/second
pinMode(sensorPin, INPUT);//the smoke sensor will be an input to the arduino
pinMode(pinSpeaker, OUTPUT);//the buzzer serves an output in the circuit
}
 
void loop() {
smoke_level= analogRead(sensorPin); //arduino reads the value from the smoke sensor
Serial.println(smoke_level);//prints just for debugging purposes, to see what values the sensor is picking up
if(smoke_level < 500){ //if smoke level is greater than 500, the buzzer will go off
playTone(300, 160); delay(150); } } void playTone(long duration, int freq) { duration *= 1000; 
int period = (1.0 / freq) * 1000000;
long elapsed_time = 0; while (elapsed_time < duration) { digitalWrite(pinSpeaker,HIGH); delayMicroseconds(period / 2);
digitalWrite(pinSpeaker, LOW); delayMicroseconds(period / 2); elapsed_time += (period); } }
