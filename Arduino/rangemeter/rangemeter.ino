const int trigPin=4;
const int echoPin=5;
const int redLed=10;
const int yellowLed=9;
const int greenLed=8;
const int buttonPin=2; // Only 2 and 3 work on the UNO board

long duration;
int distance;
volatile bool active= true;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonPin, INPUT);
  setupIsr();
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  updateLeds(distance);
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
}

void updateLeds(int distance) {
  if(!active) {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    return;
  }
  if(distance < 15) {
    //Serial.println("Red ON");
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
  }
  else if( distance < 30) {
    //Serial.println("Yellow ON");
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);    
  }
  else
  {
    //Serial.println("Green ON");
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
}
int calucateDistance(long value) {
  distance = value*0.034/2;
  return distance;
}

void setupIsr(void) {
  attachInterrupt(digitalPinToInterrupt(buttonPin), myIsr, RISING); // Can be LOW, CHANGE, FALLING, RISING (and on some boards HIGH)
}

void myIsr(void) {
  // Do stuff using volatile global variables
//  if(digitalRead(buttonPin) == HIGH) {
    Serial.println("Button pressed");
    active = !active;
    Serial.print("New mode:");
    Serial.println(active);
//  }
//  else {
//    Serial.println("Button released");
//  }
}
