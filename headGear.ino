unsigned long echo = 0; //pulse input for ultrasonic sensors
unsigned long pingValue[] = {//distance in cm
  0,0,0};
int ultraSoundSignal[] = {//pin locations for ultrasonic sensors (two)
  5,6,7};
int vibrator[] = {//pin locations for vibration motors (two)
  8,9,10};
int least=0;

void setup() //turns on all input and output
{
  Serial.begin(9600); 
  for(int i=0; i<3; i++) 
  {
    pinMode(ultraSoundSignal[i],OUTPUT);
    pinMode(vibrator[i],OUTPUT);
  }


}
void ping(){
  for(int i=0; i<3; i++) 
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

  Serial.print(pingValue[1]);
  Serial.print("cm2");
  Serial.println();

  Serial.print(pingValue[2]);
  Serial.print("cm3");
  Serial.println();


  calc();
}


void calc(){
  int i=0;
  int index=0;
  int greatest=0;
  while(i<3){

    if(pingValue[i]>greatest)
    {
      greatest=pingValue[i];
      index=i;
    }
    i++;
  }
  
  Serial.print(greatest);
  Serial.print("greatest");
  Serial.println();
  

  Serial.print(index);
  Serial.print("index");
  Serial.println();
  digitalWrite(vibrator[index], HIGH);
  delay(200);
  digitalWrite(vibrator[index], LOW);


}




