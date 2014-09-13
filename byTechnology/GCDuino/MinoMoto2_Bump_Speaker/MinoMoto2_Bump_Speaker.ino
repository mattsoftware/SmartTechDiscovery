/*
	Control GCTS Minimoto robot cars
	28 Aug 2014 - 21:15 EST
*/

const int MR_SpeedPin = 6;
const int MR_DirPin = 7;
const int ML_SpeedPin = 5;
const int ML_DirPin = 4;

const int BumpSensor = 11;  // Bump sensor on front
const int GCDuinoLED = 9;   // GCDuino Built-in LED, set to flash to let you know the code is running
const int BumpedLED = 13;
#define Piezo 10
const int BumpPiezoSpeed = 100;

const int Max_DriveSpeed = 250;   // 0 = Stopped, 250 = Fast
const int MotorBias = 20;          // Correct any bias in motor power
const boolean pullsLeft = true;   // False if it pulls right
const int driveMillis = 350;     // How long to move forward before checking for a bump
const int driveFlashMillis = 150; // How long the GCDuinoLED flashes on when driving forward
// Set between 0 (always off) and driveMillis (always on) 


// Todo: apply a randomiser with a motor speed factor to effect a turn between min and max degrees
const int minTurn = 50;    // Degrees
const int maxTurn = 150;   // Degrees
const int turnDelay = 800; // The time the robot takes turning, to be computed from teh degrees above.

void setup() {
  pinMode(MR_SpeedPin, OUTPUT);
  pinMode(MR_DirPin, OUTPUT);
  pinMode(ML_SpeedPin, OUTPUT);
  pinMode(ML_DirPin, OUTPUT);
  pinMode(GCDuinoLED, OUTPUT);
  pinMode(BumpedLED, OUTPUT);
  pinMode(Piezo, OUTPUT);
 
  pinMode(BumpSensor, INPUT);

  digitalWrite(GCDuinoLED, HIGH);
  digitalWrite(BumpedLED, LOW);
}

// M1 Control (Right Motor)
void MR_Rev() {
  analogWrite(MR_SpeedPin, 0);
  digitalWrite(MR_DirPin, HIGH);
}
void ML_Rev() {
  analogWrite(ML_SpeedPin, 0);
  digitalWrite(ML_DirPin, HIGH);
}


void MR_Fwd() {
  if (pullsLeft) {
    analogWrite(MR_SpeedPin, Max_DriveSpeed - MotorBias);
  }
  else {
    analogWrite(MR_SpeedPin, Max_DriveSpeed);
  }
  digitalWrite(MR_DirPin, LOW);
}
void ML_Fwd() {
  if (pullsLeft) {
    analogWrite(ML_SpeedPin, Max_DriveSpeed);
  }
  else {
    analogWrite(ML_SpeedPin, Max_DriveSpeed - MotorBias);
  }
  digitalWrite(ML_DirPin, LOW);
}

void MR_Stop() {
  digitalWrite(MR_SpeedPin, LOW);
  digitalWrite(MR_DirPin, LOW);
}
void ML_Stop() {
  digitalWrite(ML_SpeedPin, LOW);
  digitalWrite(ML_DirPin, LOW);
}

//Control Both Motors
void M_Rev() {
  MR_Rev();
  ML_Rev();
}

void M_Fwd() {
  MR_Fwd();
  ML_Fwd();
}

void M_Stop() {
  MR_Stop();
  ML_Stop();
}

void loop() {
  if (digitalRead(BumpSensor) == LOW) { // I got bumped
    M_Stop();
    digitalWrite(BumpedLED, HIGH);
    digitalWrite(GCDuinoLED, HIGH);

    analogWrite(Piezo, 30);      // Almost any value can be used except 0 and 255
    delay(BumpPiezoSpeed);
    analogWrite(Piezo, 80);
    delay(BumpPiezoSpeed);
    analogWrite(Piezo, 250);
    delay(BumpPiezoSpeed);
    analogWrite(Piezo, 80);
    delay(BumpPiezoSpeed);
    analogWrite(Piezo, 30);
    delay(BumpPiezoSpeed);
    analogWrite(Piezo, 0);       // 0 turns it off
    delay(BumpPiezoSpeed);

    digitalWrite(GCDuinoLED, LOW);

    MR_Rev();  // reverse one wheel to turn robot
    delay(turnDelay);

    MR_Stop(); // stop all motors
    delay(100);
    digitalWrite(BumpedLED, LOW);
  }
  M_Fwd();  // Robot goes straight forward
  digitalWrite(GCDuinoLED, HIGH); // blink the onboard GCDuinoLED to show program activity
  delay(driveFlashMillis);
  digitalWrite(GCDuinoLED, LOW);
  delay(driveMillis - driveFlashMillis);
}

