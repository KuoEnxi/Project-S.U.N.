unsigned long echo = 0; //pulse input for ultrasonic sensors
unsigned long pingValue[] = {//distance in cm
  0,0,0,0};
int ultraSoundSignal[] = {//pin locations for ultrasonic sensors (two)
  1,2,3,4};
int vibrator[] = {//pin locations for vibration motors (two)
  8,9};
void setup() //turns on all input and output
{
  Serial.begin(9600); 
  for(int i=0; i<3; i++) 
  {
    pinMode(ultraSoundSignal[i],OUTPUT);
  }
  for(int i=0; i<2; i++) 
  {
    pinMode(vibrator[i],OUTPUT);
  }
}

void ping(){
  for(int i=0; i<4; i++) 
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
  for(int i=0; i<4; i++) 
  {
    Serial.print(pingValue[i]);
    Serial.print(" cm");
    Serial.print(i+1);
    Serial.println();
  }

  vibrate();
}

void vibrate()
{
  if(pingValue[0]+pingValue[1]<150){
    if(pingValue[0]+pingValue[1]<75){
      digitalWrite(vibrator[0], HIGH);
      delay(250);
      digitalWrite(vibrator[0], LOW);
    }
    else{
    digitalWrite(vibrator[0], HIGH);
    delay(100);
    digitalWrite(vibrator[0], LOW);
    }
  }
  
 if(pingValue[2]+pingValue[3]<150){
    if(pingValue[2]+pingValue[3]<75){
      digitalWrite(vibrator[1], HIGH);
      delay(250);
      digitalWrite(vibrator[1], LOW);
    }
    else{
    digitalWrite(vibrator[1], HIGH);
    delay(100);
    digitalWrite(vibrator[1], LOW);
    }
  }


}




