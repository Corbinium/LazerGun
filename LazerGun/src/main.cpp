#include <Arduino.h>
#include <string>
#include <sstream>

#define FIRE_PIN 5
#define HIT_PIN 18
#define TRIGGER_PIN 4

int team = 0; // blue = 0, red = 1, green = 2, white = 3
int damage = 1;

// fireSignals
uint64_t b1 = 0xF5524955AAD59000;
uint64_t b2 = 0xF5524955AA559800;
uint64_t b3 = 0xF5524955AA6A5000;
uint64_t r1 = 0xF5524954AAD59800;
uint64_t r2 = 0xF5524954AA54A000;
uint64_t r3 = 0xF5524954AA6A5800;
uint64_t g1 = 0xF5524954D56A5000;
uint64_t g2 = 0xF5524954D52A5800;
uint64_t g3 = 0xF5524954D5352600;
uint64_t w1 = 0xF5524956AAD4B000;
uint64_t w2 = 0xF5524956AA549800;
uint64_t w3 = 0xF5524956AA6A6800;

unsigned long long rollingCode = 0;
uint64_t trueSignal = 0xF5524955AAD59000;
signed char currentSignal = -1;

void fireSystemReceive() {
  int incoming = ~(digitalRead(HIT_PIN)) & 1;
  rollingCode = (rollingCode << 1) | incoming;
  Serial.printf("%d", incoming);
}

void fireSystemSend() {
  if (currentSignal < 0) {
    return;
  }
  else {
    char bit = (trueSignal >> currentSignal) & 1;
    currentSignal--;
    digitalWrite(FIRE_PIN, bit);
  }
}

bool pressedButton = false;

void triggerSystem() {
  int trigger = digitalRead(TRIGGER_PIN);
  if (trigger == HIGH && !pressedButton) {
    currentSignal = 63;
    Serial.print("\nTriggered\n");
    pressedButton = true;
    delay(100);
  }
  else if (trigger == LOW) {
    pressedButton = false;
  }
}

void changeSignal() {
  if (team == 0) {
    if (damage == 3) { trueSignal = b3; }
    else if (damage == 2) { trueSignal = b2; }
    else { trueSignal = b1; }
  }

  else if (team == 1) {
    if (damage == 3) { trueSignal = r3; }
    else if (damage == 2) { trueSignal = r2; }
    else { trueSignal = r1; }
  }

  else if (team == 2) {
    if (damage == 3) { trueSignal = g3; }
    else if (damage == 2) { trueSignal = g2; }
    else { trueSignal = g1; }
  }

  else {
    if (damage == 3) { trueSignal = w3; }
    else if (damage == 2) { trueSignal = w2; }
    else { trueSignal = w1; }
  }
}

/**************************************************************************************************
 * Running Code
 *************************************************************************************************/
void setup() {
  Serial.begin(2400);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  pinMode(TRIGGER_PIN, INPUT);
  pinMode(FIRE_PIN, OUTPUT);
  pinMode(HIT_PIN, INPUT);
}



void loop() {
  triggerSystem();
  fireSystemReceive();
  fireSystemSend();
}
