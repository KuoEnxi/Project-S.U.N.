int piezoPin = 9;
const int buttonPin = 2;
int buttonState = 0;

unsigned long echo = 0; //pulse input for ultrasonic sensors
unsigned long pingValue[]={
  0,0};
unsigned long defValue[]={
  50,50};
unsigned long thresh=20;
int ultraSoundSignal[]={
  6,7};
boolean beep=false;

void setup() //turns on all input and output
{
  Serial.begin(9600); 
  pinMode(piezoPin, OUTPUT);
  pinMode(buttonPin, INPUT); 
  for(int i=0; i<2; i++) 
  {
    pinMode(ultraSoundSignal[i],OUTPUT);
  }
  ping();
  setDefault();

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
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) { 
    setDefault();
  }
  for(int i=0; i<2; i++) 
  {
    Serial.print(pingValue[i]);
    Serial.print("cm"); 
    Serial.print(i);
    Serial.println();
    Serial.print(defValue[i]);
    Serial.print("cm"); 
    Serial.print(i);
    Serial.println();
  }
  delay(100);

  calculate();

  if(beep){
    tone(9, 2100, 100);
  }

}

void calculate(){
  for(int i=0; i<2; i++) 
  {
    if(abs(defValue[i]-pingValue[i])<=thresh)
    {
      beep=false;
    }
    else
    {
      beep=true;
    }
  }

}

void setDefault(){
  for(int i=0; i<2; i++) 
  {
    defValue[i]=pingValue[i];
  }
}


