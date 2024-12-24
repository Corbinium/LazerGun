#include <Arduino.h>
#include <string>
#include <sstream>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  pinMode(35, INPUT);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
}

void loop() {
  // digitalWrite(2, HIGH);
  // // Serial.println("LED is on");
  // delay(1000);

  // digitalWrite(2, LOW);
  // // Serial.println("LED is off");
  // delay(1000);

  int state = analogRead(32);
  std::ostringstream message;
  message << "  " << state;
  Serial.println(message.str().c_str());
}
