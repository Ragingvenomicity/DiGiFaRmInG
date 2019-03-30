#include <SoftwareSerial.h>
int ph=A0,mstr1=A1,mstr2=A2,pump=3;
float valph,valm1,valm2;
String value;
int TxD = 11;
int RxD = 10;
SoftwareSerial bluetooth(TxD, RxD);
void setup(){
  Serial.begin(9600);
  pinMode(ph,INPUT);
  pinMode(mstr1,INPUT);
  pinMode(mstr2,INPUT);
  pinMode(pump,OUTPUT);
  bluetooth.begin(9600);
}
void loop(){
 valph=0;
 for(int i=0;i<10;i++){
 valph+=analogRead(ph);delay(200);}
 valph=valph*3.5*(5.0/10240)-5;
 valm1=map(analogRead(mstr1),0,1023,100,0);
 valm2=map(analogRead(mstr2),0,1023,100,0);
 Serial.print(valph);
 Serial.print("\t");
 Serial.print(valm1);
 Serial.print("\t\t");
 Serial.println(valm2);
 bluetooth.print('#');
 bluetooth.print("Rice");
 bluetooth.print('+');
 bluetooth.print(valm1);
 bluetooth.print('+');
 bluetooth.print(valm2);
 bluetooth.print('+');
 bluetooth.print(valph);
 bluetooth.print('+');
 bluetooth.print('~');
 if(bluetooth.available()){
 value=bluetooth.readString();
 if(value=="1"){
 digitalWrite(pump,HIGH);
 Serial.println("pump on");
 }
 else if(value=="0"){
 digitalWrite(pump,LOW);
 Serial.println("pump off");
 }
 }
 delay(2000);
}
