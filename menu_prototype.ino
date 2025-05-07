#include <openGLCD.h>
// Analog input pins
#define CAPACITY_PIN 25
#define HEALTH_PIN 15
#define VOLTAGE_PIN 4

int currentScreen = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  GLCD.Init();       // Initialize the GLCD
  GLCD.ClearScreen();

  // Optional: Display loading or startup screen
  GLCD.SelectFont(System5x7);
  GLCD.print("Starting...");
  delay(1000);
  GLCD.ClearScreen();
}

void loop() {
  // Handle button press with debounce
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > debounceDelay) {
    currentScreen = (currentScreen + 1) % 4;
    lastDebounceTime = millis();
    updateDisplay();
  }

  lastButtonState = buttonState;
}

// Function to update the screen based on current menu
void updateDisplay() {
  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7);

  switch (currentScreen) {
    case 0:
      displaySpeed();
      break;
    case 1:
      displayCapacity();
      break;
    case 2:
      displayHealth();
      break;
    case 3:
      displayVoltage();
      break;
  }
}

// Simulated analog read conversion functions
void displaySpeed() {
  int val = analogRead(ANALOG_PIN);       // Read analog value
  float speed = map(val, 0, 4095, 0, 100); // Simulate speed in km/h
  GLCD.print("Speed:");
  GLCD.CursorTo(0, 2);
  GLCD.print(speed, 1);
  GLCD.print(" km/h");
}

void displayCapacity() {
  int val = analogRead(CAPACITY_PIN);
  float percent = map(val, 0, 4095, 0, 100);
  GLCD.print("Battery Capacity:");
  GLCD.CursorTo(0, 2);
  GLCD.print(percent, 1);
  GLCD.print(" %");
}

void displayHealth() {
  int val = analogRead(HEALTH_PIN);
  float health = map(val, 0, 4095, 80, 100); // Assume health is 80-100%
  GLCD.print("State of Health:");
  GLCD.CursorTo(0, 2);
  GLCD.print(health, 1);
  GLCD.print(" %");
}

void displayVoltage() {
  int val = analogRead(VOLTAGE_PIN);
  float voltage = (val / 4095.0) * 3.3 * 2.0;  // Assuming voltage divider by 2
  GLCD.print("Battery Voltage:");
  GLCD.CursorTo(0, 2);
  GLCD.print(voltage, 2);
  GLCD.print(" V");
}
