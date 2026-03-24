#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Initialize I2C LCD (Address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11 Setup
#define DHTPIN 4     // Digital pin connected to the DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int greenLed = 7;
const int redLed = 6;
const int buzzer = 10;

// Temperature Thresholds (Celsius)
float lowThreshold = 35.0;  // Normal range below this
float highThreshold = 55.0; // Critical above this

unsigned long lastSerialTime = 0; 
const unsigned long serialInterval = 3000; 

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  Serial.println("--- Temp Monitoring System Online ---");
}

void loop() {
  
  float temp = dht.readTemperature(); 
  unsigned long currentTime = millis();

  // Safety check for sensor disconnection
  if (isnan(temp)) {
    lcd.setCursor(0,0);
    lcd.print("Sensor Error!  ");
    return;
  }

  // --- SERIAL MONITOR LOGIC (Every 3 Seconds) ---
  if (currentTime - lastSerialTime >= serialInterval) {
    Serial.print("Current Temp: ");
    Serial.print(temp);
    Serial.print("C");
    
    if (temp < lowThreshold) Serial.println(" [SAFE]");
    else if (temp < highThreshold) Serial.println(" [WARNING]");
    else Serial.println(" [CRITICAL ALERT]");
    
    lastSerialTime = currentTime; 
  }

  // --- ALARM & LCD LOGIC ---
  if (temp < lowThreshold) {
    // --- STAGE: SAFE ---
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    noTone(buzzer);
    
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print("C      "); // Spaces clear old characters
    lcd.setCursor(0, 1);
    lcd.print("Status: SAFE    ");
  } 
  else if (temp >= lowThreshold && temp < highThreshold) {
    // --- STAGE: WARNING (Blinking Red) ---
    digitalWrite(greenLed, LOW);
    
    // Red LED blinking
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    
    tone(buzzer, 1000); 
    delay(100); 
    noTone(buzzer);
    
    lcd.setCursor(0, 0);
    lcd.print("CAUTION: HEAT   ");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print("C      ");
  } 
  else {
    // --- STAGE: CRITICAL (Constant Alarm) ---
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    tone(buzzer, 1500); 
    
    lcd.setCursor(0, 0);
    lcd.print("!! FIRE ALERT !!");
    lcd.setCursor(0, 1);
    lcd.print("EVACUATE NOW!   ");
  }

  delay(100); 
}