/*
    OS47 is a tiny kernel OS for your Arduino sketches.
    It can help you to improve your productivity to develop parallels tasks on your microcontroller.
    See http://www.rtos47.com/tuto/getting_started/
    David Tangye <DavidTangye@gmail.com> - 08/09/2014
*/

#include "os47.h"
const int kernelInt = 100;  // Initialize the kernel interruption: occurs every 1/(kernelInt) seconds (eg 100 = 10ms).

const float cycleSecs_1 = 0.5;
const long onMillis_1 = 200;
const int ledPin_1 = 9;

const float cycleSecs_2 = 5.0;
const long onMillis_2 = 2500;
const int ledPin_2 = 2;

int ledState_1 = LOW;
int ledState_2 = LOW;
long previousMillis_1 = 0;
long previousMillis_2 = 0;

const long offMillis_1 = (1000 * cycleSecs_1) - onMillis_1;
const long offMillis_2 = (1000 * cycleSecs_2) - onMillis_2;
long timerMillis_1 = onMillis_1;
long timerMillis_2 = onMillis_2;

void setup() {
  pinMode(ledPin_1, OUTPUT);
  digitalWrite(ledPin_1,ledState_1);

  pinMode(ledPin_2, OUTPUT);
  digitalWrite(ledPin_2,ledState_2);

  os47_setup(kernelInt); // Initialize the kernel interruption

/*
  Create tasks.
    Parameter 1: the memory size in bytes that will be available in the stack.
    Parameter 2: the priority of the task. A relative value compared with the value of the other tasks.
    Parameter 3: the address of the function representing the code of your task.
*/
  os47_new_task(10, 1, &task1);
  os47_new_task(10, 1, &task2);

  os47_start(); // Notify the kernel to start the scheduler. Code after here will never be executed except if the function fails.
}

void loop() {} // Does not execute

void task1() {
  for(;;) {
    OS47_ATOMIC_BCK ( // A macro to tell to the kernel to not interrupt the execution of this code section.
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis_1 > timerMillis_1) {
        if (ledState_1 == LOW) {
          ledState_1 = HIGH;
          timerMillis_1 = onMillis_1;
        }
        else {
          ledState_1 = LOW;
          timerMillis_1 = offMillis_1;
        }
        digitalWrite(ledPin_1, ledState_1);
        previousMillis_1 = currentMillis;
        }
      )
    }
}

void task2() {
  for(;;)    {  
    OS47_ATOMIC_BCK
      (
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis_2 > timerMillis_2) {
        if (ledState_2 == LOW) {
          ledState_2 = HIGH;
          timerMillis_2 = onMillis_2;
        }
        else {
          ledState_2 = LOW;
          timerMillis_2 = offMillis_2;
        }
        digitalWrite(ledPin_2, ledState_2);
        previousMillis_2 = currentMillis;
        }
    )
  }
}

