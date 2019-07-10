#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
const int trigPin = 8;
const int echoPin = 7;
// defines variables
long duration;
int distance;
int demo;
int game_work = 0;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);
pinMode(LED_BUILTIN,OUTPUT);
// Sets the echoPin as an Input
Serial.begin(9600);
mySerial.begin(9600);
Serial.println("GSM SIM900A BEGIN");
 // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(LED_BUILTIN,LOW);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.println(distance);
if(distance<=15){
  //digitalWrite(LED_BUILTIN,HIGH);
  game_work++;
  if(game_work>=1000){
    digitalWrite(LED_BUILTIN,HIGH);
    SendMessage();
    ReceiveMessage(); 
    delay(5000);
    game_work=0;
  }
}
else{
  game_work=0;
}
//game_work = 0;
//Serial.println(distance);
}
void SendMessage()
{
  mySerial.println("Messaging");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918200011676\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Vehicle detected in no parking area at 22.989900, 72.00000");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available()>0)
  {
    msg=mySerial.read();
    Serial.print(msg);
  }
}
