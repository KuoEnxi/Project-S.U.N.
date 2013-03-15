int piezoPin = 9; //pin location for piezo element
unsigned long echo = 0; //pulse input for ultrasonic sensors
unsigned long pingValue[] = {//distance in cm
 0,0};
int ultraSoundSignal[] = {//pin locations for ultrasonic sensors (two)
 6,7};
 int vibrator[] = {//pin locations for vibration motors (two)
 4,5};

 
void setup() //turns on all input and output
{
 Serial.begin(9600); 
 pinMode(piezoPin, OUTPUT);
 for(int i=0; i<2; i++) 
 {
   pinMode(ultraSoundSignal[i],OUTPUT);
   pinMode(vibrator[i],OUTPUT);
 }


}
void ping(){
 for(int i=0; i<2; i++) 
 {
   pinMode(ultraSoundSignal[i], OUTPUT); // Switch signalpin to output
   digitalWrite(ultraSoundSignal[i], LOW); // Send low pulse
   delayMicroseconds(2); // Wait for 2 microseconds
   digitalWrite(ultraSoundSignal[i], HIGH); // Send high pulse
   delayMicroseconds(5); // Wait for 5 microseconds
   digitalWrite(ultraSoundSignal[i], LOW); // Holdoff
   pinMode(ultraSoundSignal[i], INPUT); // Switch signalpin to input
   digitalWrite(ultraSoundSignal[i], HIGH); // Turn on pullup resistor
   echo = pulseIn(ultraSoundSignal[i], HIGH, 38000);
   pingValue[i] = (echo / 58.138) ; //convert to CM, add *.39 for inches
 }

}
void loop()
{
 ping();//calibrates the ultrasonic sensors
//prints length information to serial monitor
 Serial.print(pingValue[0]);
 Serial.print("cm");
 Serial.println();
 vibrate(pingValue[0],0);
 
 Serial.print(pingValue[1]);
 Serial.print("cm2");
 Serial.println();
 vibrate(pingValue[1],1);
}

void vibrate(long cm, int index){
if (cm<55){
 if(cm>50){

   tone(9, 400, 100); //(pin, tone, duration)
    digitalWrite(vibrator[index], HIGH);
   delay(250);
   digitalWrite(vibrator[index], LOW);
 } 

else if(cm>25){
      tone(9, 600, 100); //(pin, tone, duration)
      digitalWrite(vibrator[index], HIGH);
   delay(150);
   digitalWrite(vibrator[index], LOW);
   }
else if(cm>15){
      tone(9, 2100, 100);
       digitalWrite(vibrator[index], HIGH);
   delay(150);
   digitalWrite(vibrator[index], LOW);
   }
else if(cm>5){
     tone(9,1700, 100);
      digitalWrite(vibrator[index], HIGH);
   delay(100);
   digitalWrite(vibrator[index], LOW);
   }
   else{
    tone(9,1700, 100); 
     digitalWrite(vibrator[index], HIGH);
   delay(80);
   digitalWrite(vibrator[index], LOW);
   }
   
  
//   vibrationWait=100;
//   thresh[index]=false;

}
}

