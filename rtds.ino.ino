#include <SPI.h>
#include <CAN.h>

#define BUZZER_PIN     4
#define LIGHT_PIN      7
#define SHUTDOWN_PIN   8
#define SHUTDOWN_SENSE 9
#define BRAKE_PIN      A0   // Changed to analog pin

const int CAN_ID_MC_ACTIVATE = 0x101;
const byte ACTIVATE_MSG[1]   = { 0x01 };

const unsigned long BUZZER_DURATION = 2000;

bool driveMode = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(SHUTDOWN_PIN, OUTPUT);
  pinMode(SHUTDOWN_SENSE, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(SHUTDOWN_PIN, LOW);

  Serial.begin(9600);
  while (!Serial);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  Serial.println("CAN started successfully");
}

void loop() {
  int brakeValue = analogRead(BRAKE_PIN);
  bool brakePressed = (brakeValue > 500);  // Threshold — adjust based on sensor
  bool shutdownClosed = (digitalRead(SHUTDOWN_SENSE) == HIGH);

  if (!driveMode && brakePressed && shutdownClosed) {
    digitalWrite(LIGHT_PIN, HIGH);
  } else if (!driveMode) {
    digitalWrite(LIGHT_PIN, LOW);
  }

  if (!driveMode) {
    if (brakePressed && shutdownClosed) {
      Serial.println("RTDS Conditions Met");

      digitalWrite(BUZZER_PIN, HIGH);
      delay(BUZZER_DURATION);
      digitalWrite(BUZZER_PIN, LOW);

      CAN.beginPacket(CAN_ID_MC_ACTIVATE);
      CAN.write(ACTIVATE_MSG[0]);
      CAN.endPacket();
      Serial.println("Motor Controller Activation Message Sent");

      digitalWrite(SHUTDOWN_PIN, HIGH);
      Serial.println("Shutdown signal: relay closed");

      driveMode = true;
      digitalWrite(LIGHT_PIN, HIGH);
      delay(500);
    }
  } 
  else {
    if (!shutdownClosed) {
      digitalWrite(SHUTDOWN_PIN, LOW);
      Serial.println("Shutdown signal: relay open");
      driveMode = false;
      digitalWrite(LIGHT_PIN, LOW);
    } 
    else {
      // PLACE APPS CODE HERE
    }
  }
}
