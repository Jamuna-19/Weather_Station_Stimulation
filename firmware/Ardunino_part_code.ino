
#include <LiquidCrystal_I2C.h>
#define LIGHT_SENSOR_PIN A0
#define MQ135_PIN A0
#define WIND_SPEED_PIN 2
#define WIND_DIRECTION_PIN A1
LiquidCrystal_I2C lcd(0x20,16,2);  
volatile unsigned long pulseCount = 0;
void countPulse() {
  pulseCount++;
}
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Hardware Team");
  pinMode(WIND_SPEED_PIN, INPUT);
  attachInterrupt(
    digitalPinToInterrupt(WIND_SPEED_PIN),
    countPulse,
    RISING
  );
}


void loop()
{
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  int gasValue = analogRead(MQ135_PIN);
 
  noInterrupts();
  unsigned long pulses = pulseCount;
  interrupts();
  float frequency = pulses / 2.0;
  float windSpeed = frequency;

  int analogValue = analogRead(WIND_DIRECTION_PIN);
  int angle = map(analogValue, 0, 1023, 0, 360);
 String direction;

  if (angle >= 337 || angle < 23) {
    direction = "NORTH";
  }

  else if (angle < 68) {
    direction = "NORTH-EAST";
  }

  else if (angle < 113) {
    direction = "EAST";
  }

  else if (angle < 158) {
    direction = "SOUTH-EAST";
  }

  else if (angle < 203) {
    direction = "SOUTH";
  }

  else if (angle < 248) {
    direction = "SOUTH-WEST";
  }

  else if (angle < 293) {
    direction = "WEST";
  }

  else {
    direction = "NORTH-WEST";
  }

  Serial.println("APDS9600");
  Serial.print("Light Intensity: ");
  Serial.println(lightValue);
  Serial.print("Day Time: ");

  if (lightValue > 1000) {
    Serial.println("Night Time");
  }
  else if (lightValue > 900 && lightValue < 1000) {
    Serial.println("Evening Time");
  }
  else {
    Serial.println("Morning Time");
  }


  Serial.println("Magnetic Hall");
  Serial.print("Wind Speed: ");
  Serial.print(windSpeed, 2);
  Serial.println(" km/h");
  Serial.print("Wind Angle: ");
  Serial.print(angle);
  Serial.println(" degrees");
  Serial.print("Wind Direction: ");
  Serial.println(direction);
  

  Serial.println("MQ135");
  Serial.print("Air quality value: ");
  Serial.println(gasValue);
  Serial.print("Air quality Data: ");
  if(gasValue <= 150)
  {
    Serial.println("GOOD");
    
  }
  else if(gasValue <= 350)
  {
    Serial.println("MODERATE");
    
  }
  else if(gasValue <= 600)
  {
    Serial.println("UNHEALTHY");
    
  }
  else if(gasValue <= 850)
  {
    Serial.println("VERY BAD");
    
  }
  else
  {
    Serial.println("HAZARDOUS");
    
  }
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println();
  
  delay(5000);

 }




