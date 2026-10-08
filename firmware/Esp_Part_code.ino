
#include <LiquidCrystal.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ALTITUDE 1013.25
#define SHT21_ADDR 0x40                
#define SHT21_TEMP_CMD 0xF3
#define SHT21_HUMID_CMD 0xF5
#define ONE_WIRE_BUS 0 

Adafruit_BMP085 bmp;

LiquidCrystal lcd(10, 11, 19, 18, 17, 16);

float readSHT21Temp() {
  Wire.beginTransmission(SHT21_ADDR);
  Wire.write(SHT21_TEMP_CMD);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(SHT21_ADDR, 2);
  if (Wire.available() == 2) {
    uint16_t rawTemp = Wire.read() << 8;
    rawTemp |= Wire.read();
    rawTemp &= 0xFFFC;
    float temp = -46.85 + 175.72 * (rawTemp / 65536.0);
    return temp;
  }
  return -999;
}

float readSHT21Humidity() {
  Wire.beginTransmission(SHT21_ADDR);
  Wire.write(SHT21_HUMID_CMD);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(SHT21_ADDR, 2);
  if (Wire.available() == 2) {
    uint16_t rawHumid = Wire.read() << 8;
    rawHumid |= Wire.read();
    rawHumid &= 0xFFFC;
    float humidity = -6.0 + 125.0 * (rawHumid / 65536.0);
    return humidity;
  }
  return -999;
}

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
 
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(20, 2);

  pinMode(7, INPUT);   
  pinMode(5, INPUT);   

  lcd.setCursor(0, 0);
  lcd.print("Datacorp Engineering");
  lcd.setCursor(0, 1);
  lcd.print("Innovations Pvt Ltd.");

  if (!bmp.begin())
  {
    Serial.println("BMP180 not found!");
    while (1);
  }

}

void loop()
{
  float Temperature = readSHT21Temp();
  float Humidity = readSHT21Humidity();

  float bmpTemp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0;   

  int rain = digitalRead(7);
  int sound = digitalRead(5);
  int gasValue = analogRead(A0);    

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  Serial.println("SHT21");
  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.println(" %");
  

  Serial.println("BMP180");
  Serial.print("Temperature: ");
  Serial.print(bmpTemp);
  Serial.println(" C");
  Serial.print("Altitude: ");
  Serial.print(ALTITUDE);
  Serial.println(" meters");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  Serial.println("DS18B20");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");
  
  
  Serial.println("Rain Sensor");
  
  if (rain)
    Serial.println("Rain: Detected");
  else
    Serial.println("Rain: Not Detected");
  

  Serial.println("Sound Sensor");
  if (sound)
    Serial.println("Sound: Detected");
  else
    Serial.println("Sound: Not Detected");

  Serial.println();
  Serial.println("-----------------------");
  Serial.println();

  delay(5000);
}

