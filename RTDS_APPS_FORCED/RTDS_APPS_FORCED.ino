// rtds+apps code for testing
#include <SPI.h>
#include <CAN.h>

#define BUZZER_PIN      4
#define LIGHT_PIN       13
#define shutdown_pin_mc 8
#define sdc_relay_state 10
#define START_BUTTON    5

const int potentiometer1 = A1;
const int potentiometer2 = A2;
const int brakepotentiometer = A0;
const int Motor = 9;

// ====== SIMULATION CONTROL ======
#define SIMULATE_SHUTDOWN true // true = simulate shutdown relay state

float potentiometer_1, potentiometer_2, brakepressure;
float value1, value2, value3;
unsigned long implausibilityStart = 0;
bool implausibility = false;
bool brakeReleased = true;

const int CAN_ID_MC_ACTIVATE = 0x101;
const byte ACTIVATE_MSG[1]   = { 0x01 };

const unsigned long BUZZER_DURATION = 2000;
const int BRAKE_THRESHOLD = 100;

bool driveMode = false;
bool canAvailable = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(shutdown_pin_mc, OUTPUT);
  pinMode(sdc_relay_state, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(shutdown_pin_mc, LOW);

  pinMode(Motor, OUTPUT);
  digitalWrite(Motor, LOW); 

  Serial.begin(250000);
  Serial.println("CAN sender");

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed");
    while (1);
  }
}

void loop() {
  bool brakePressed;
  bool shutdownClosed;
  bool startPressed;

  // Real hardware reads for everything except shutdown relay
  brakePressed    = analogRead(brakepotentiometer) > BRAKE_THRESHOLD;
  startPressed    = digitalRead(START_BUTTON) == LOW;
  potentiometer_1 = analogRead(potentiometer1);
  potentiometer_2 = analogRead(potentiometer2);
  brakepressure   = analogRead(brakepotentiometer);

  // Shutdown relay state is simulated if enabled
  if (SIMULATE_SHUTDOWN) {
    shutdownClosed = true; // Always closed in simulation
  } else {
    shutdownClosed = digitalRead(sdc_relay_state) == LOW;
  }

  // Map values
  value1 = map(potentiometer_1, 0, 1023, 0, 100);
  value2 = map(potentiometer_2, 0, 1023, 0, 100);
  value3 = map(brakepressure,   0, 1023, 0, 100);

  // Enable RTDS sequence if all conditions are met
  canAvailable = !brakePressed && shutdownClosed && startPressed;

  if (!driveMode) {
    digitalWrite(LIGHT_PIN, HIGH); // Light on before driveMode
    if (canAvailable) {
        Serial.println("RTDS Conditions Met");

        tone(BUZZER_PIN, 9000);
        Serial.println("buzzer on");
        delay(BUZZER_DURATION);
        noTone(BUZZER_PIN);
        Serial.println("buzzer off");

        CAN.beginPacket(CAN_ID_MC_ACTIVATE);
        CAN.write(ACTIVATE_MSG[0]);
        CAN.endPacket();
        Serial.println("Motor Controller Activation Message Sent via CAN");

        digitalWrite(shutdown_pin_mc, HIGH);
        Serial.println("Shutdown signal: relay closed");

        driveMode = true;
        delay(500);
    }
  } else {
    if (!shutdownClosed) {
      digitalWrite(shutdown_pin_mc, LOW);
      Serial.println("Shutdown signal: relay open");
      driveMode = false;
      digitalWrite(LIGHT_PIN, LOW);
    } else {
      int average = (potentiometer_1 + potentiometer_2) / 2;
      int mapaverage = map(average, 0, 1023, 0, 32767);
      byte msb = (mapaverage >> 8) & 0xFF;
      byte lsb = mapaverage & 0xFF;
      byte send_msb = msb;
      byte send_lsb = lsb;

      Serial.print("P1="); Serial.print(value1);
      Serial.print(" | P2="); Serial.print(value2);
      Serial.print(" | Average="); Serial.print(mapaverage);
      Serial.print(" | Brake="); Serial.print(value3);
      Serial.print(" | MSB=0x"); Serial.print(msb, HEX);
      Serial.print(" | LSB=0x"); Serial.println(lsb, HEX);

      brakeReleased = (value3 <= 5);

      float percentagedifference = abs(value1 - value2);

      if (!implausibility) {
        if (percentagedifference > 10) {
          if (implausibilityStart == 0) {
            implausibilityStart = millis();
          } else if (millis() - implausibilityStart >= 100) {
            implausibility = true;
            Serial.print("Implausibility detected! Difference = ");
            Serial.println(percentagedifference);
          }
        } else {
          implausibilityStart = 0;
        }
      } else {
        if (value1 == 0 && value2 == 0 && value3 == 0) {
          implausibility = false;
          implausibilityStart = 0;
          Serial.println("Implausibility reset: Both pedals are at 0");
        }
      }

      bool motorAllowed = !implausibility && brakeReleased && (value3 < 25);
      digitalWrite(Motor, motorAllowed ? HIGH : LOW);
      Serial.println(motorAllowed ? "Motor ON" : "Motor OFF");

      if (implausibility || value3 >= 25) {
        send_msb = 0x00;
        send_lsb = 0x00;
        Serial.println("Implausibility/Brake - sending 0 as acceleration");
      }

      CAN.beginPacket(0x304);
      CAN.write(0x90);
      CAN.write(send_lsb);
      CAN.write(send_msb);
      CAN.endPacket();
      Serial.println("CAN packet sent");

      delay(100);
    }
  }
}
