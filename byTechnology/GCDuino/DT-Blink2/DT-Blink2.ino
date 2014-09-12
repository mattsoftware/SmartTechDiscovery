/*
    Blink 2 LEDs, based on the timer, not delays
    The blink cycle of the second (slow) LED is based on the cycle of the first (fast) LED.
    David Tangye <DavidTangye@gmail.com> - 08/09/2014
 */

 
//const float fastCycleSecs = 0.5;
const float fastCycleSecs = 1.0;
const long onMillis = 200;
const int fastLedPin = 9;

const int slowLedCycle = 5; // Number of fast cycles per slow cycle
const int slowLedPin = 2;
int fastLedCycleCount = 0;

int fastLedState = LOW;
int slowLedState = LOW;
long previousMillis = 0;

const long offMillis = (1000 * fastCycleSecs) - onMillis;
long timerMillis = onMillis;


void setup() {                
  pinMode(fastLedPin, OUTPUT);     
  pinMode(slowLedPin, OUTPUT);     
  digitalWrite(slowLedPin,slowLedState);
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > timerMillis) {
    if (fastLedState == LOW) {
      fastLedState = HIGH;
      timerMillis = onMillis;
//      SlowLed;
      fastLedCycleCount = fastLedCycleCount + 1;
      if(fastLedCycleCount == slowLedCycle) {
        if (slowLedState == LOW) {
          slowLedState = HIGH;
        }
        else {
          slowLedState = LOW;
        }
        digitalWrite(slowLedPin,slowLedState);
        fastLedCycleCount = 0;
      }
   }
    else {
      fastLedState = LOW;
      timerMillis = offMillis;
    }
    digitalWrite(fastLedPin, fastLedState);
    previousMillis = currentMillis;
  }
}
