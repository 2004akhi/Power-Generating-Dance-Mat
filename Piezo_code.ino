#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SENSOR_PIN A0                // Analog pin connected to DC Voltage Sensor
#define VOLTAGE_THRESHOLD 0.01       // Set a voltage level to count presses
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address
int pressCount = 0;                  // Counter for threshold crossings
float voltage = 0.0;                 // Measured voltage
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Voltage Monitor");
  delay(2000);
  lcd.clear();
}
void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  voltage = sensorValue * (5.0 / 1023.0) * 11;  // Scaling factor for 50V sensor
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print("V");
  // Check if voltage crosses the threshold
  if (voltage >= VOLTAGE_THRESHOLD) {
    pressCount++;
    lcd.setCursor(0, 1);
    lcd.print("Press Count: ");
    lcd.print(pressCount);
    delay(500);  // Debounce delay
  }
}