
int dummyValue;
int measuredValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  measuredValue = analogRead(A3);

  if(measuredValue < 300) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  Serial.print("Result:");
  Serial.println(measuredValue);
}
