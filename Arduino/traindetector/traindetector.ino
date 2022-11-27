// IR sensor input pin
const int SENSOR_PIN = 7;
// Sense threshold
const float THR = 0.95;
// Sampling interval
const unsigned long INTERVAL = 50;  // milliseconds, 20 Hz

const int redLed = 12;
const int yellowLed = 11;
const int greenLed = 10;

// channel calibrations
unsigned int g_thr;        // sensor thresholds from calibration
// next scheduled sample time (milliseconds)
unsigned long g_next = 0;


// Calibrate sensor channels by reading and averaging
// no-sense outputs.
void calibrateSensors()
{
  // Will average ITERS samples.
  const int ITERS = 60;
  // Accumulators for averaging.
  unsigned long sums;
  // Zero accumulators.
  sums = 0;

  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(greenLed, HIGH);
  Serial.println("Start of calibration");
  // For ITERS samples...
  for (int j = 0; j < ITERS; ++j) {
    // For NUM_AIN channels...
    // Read and accumulate.
    sums += analogRead(SENSOR_PIN);
  }
  // Delay 1 msec before next iteration.
  delay(1);
  // For each channel, sense threshold is THR times
  // average of no-sense samples.
  g_thr = (unsigned int) (THR * sums / ITERS);
  Serial.print("Calibration result:");
  Serial.println(g_thr);
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}


// The read function runs at a high rate on the slave,
// but will be interrupted when an SPI transaction is
// started by the SPI Master.
void readAnalogs()
{
  // Copy analog status (atomic read).
  //byte ain = g_analogs;

  // Read all analog channels, set to 0 any bits for
  // sensors which detect object.
  int sensorValue = analogRead(SENSOR_PIN);
  if (sensorValue > g_thr) {
    // No sense, set bit to 1.
    //  ain |= (1 << i);
    //Serial.println("Train detected");
    //Serial.println(analogRead(SENSOR_PIN));
    if (sensorValue - g_thr < 50 && sensorValue - g_thr > 10) {
      //Serial.println(sensorValue);
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);
    } else {
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, HIGH);
    }
  } else {
    // Sense, set bit to 0.
    //ain &= ~(1 << i);
    Serial.print("Train detected:");
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    Serial.println(analogRead(SENSOR_PIN));
  }

  // Update analog status, masking off unwanted bits
  // (atomic write).  Bits masked out will be forced
  // to 1, i.e. no-sense.
  //g_analogs = ain | ~g_mask;
}


void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication'

  // Calibrate sensors on analog inputs.
  calibrateSensors();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Time to read the analog inputs again?
  if ((long) (millis() - g_next) >= 0) {
    // Update analogs.
    readAnalogs();
    // Pace the acquisition loop.
    g_next = millis() + INTERVAL;
  }
}
