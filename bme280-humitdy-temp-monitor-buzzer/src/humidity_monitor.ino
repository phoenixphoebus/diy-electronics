#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <time.h> 
#include <math.h>

/*#include <SPI.h>
#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15*/

#define RELAY_PIN D7
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

LiquidCrystal_I2C lcd(0x27, 20, 4);

unsigned long delayTime;

const char *ssid     = "<Your SSID>";
const char *password = "<Your Password>";

#define MY_NTP_SERVER "pool.ntp.org"           
#define MY_TZ "EST5EDT"  

char daysOfTheWeek[7][10] = {"Sunday   ", "Monday   ", "Tuesday  ", "Wednesday", "Thursday ", "Friday   ", "Saturday "};
char month[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

time_t now;
tm tm; 

void setup() {

  bool status;

  Serial.begin(115200);

  Serial.println("lcd init");

  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(2, 0);
  lcd.print("Aditya's  BME280");
  lcd.setCursor(2, 1);
  lcd.print("LCD init success");

  





  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    lcd.setCursor(2, 2);
    lcd.print("BME280 not found");
    lcd.setCursor(4, 3);
    lcd.print("Check wiring");
    while (1);
  }

  Serial.println("BME280 found");

  lcd.setCursor(4, 2);
  lcd.print("BME280 found");

  lcd.setCursor(2, 3);
  lcd.print("Waiting for WiFi");

  delayTime = 1000;

  Serial.println();

  

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // turn off buzzer
  

  configTime(MY_TZ, MY_NTP_SERVER);

  lcd.clear();
  lcd.setCursor(17, 0);
  lcd.print("'");
  lcd.setCursor(2, 1);
  lcd.print(":");
  lcd.setCursor(5, 1);
  lcd.print(":");
  lcd.setCursor(0, 2);
  lcd.print("T: ");
  lcd.setCursor(0, 3);
  lcd.print("H:");
  lcd.setCursor(11, 3);
  lcd.print("P:");

  BuzzForOneSecond();
  
}

void loop() { 
  float humidityPercentage = bme.readHumidity();
  float temperatureInCelcius = bme.readTemperature();
  float temperatureInFarenheit = 1.8 * temperatureInCelcius + 32;
  float pressureInHPA = bme.readPressure() / 100.0F;
  printDateTime();
  printSensorValues(humidityPercentage, temperatureInCelcius, temperatureInFarenheit, pressureInHPA);
  processSensorValues(humidityPercentage);
  delay(delayTime);
}

void processSensorValues(float humidityPercentage){
  if(humidityPercentage < 40.0F){
    lcd.setCursor(9, 1);  
    lcd.print("Lo Humidity");
    BuzzForOneSecond();
  }
  else if(humidityPercentage > 60.0F){
    lcd.setCursor(9, 1);  
    lcd.print("Hi Humidity");
    BuzzForOneSecond();
  }
  else{
    lcd.setCursor(9, 1);  
    lcd.print("*No alerts*");
  }
}

void BuzzForOneSecond(){
  digitalWrite(RELAY_PIN, LOW);  // turn on buzzer 1 seconds
  delay(1000);
  digitalWrite(RELAY_PIN, HIGH);  // turn off buzzer
}

void printSensorValues(float humidityPercentage, float temperatureInCelcius, float temperatureInFarenheit, float pressureInHPA) {
  lcd.setCursor(3, 2);  
  lcd.print(temperatureInCelcius);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(12, 2);  
  lcd.print(temperatureInFarenheit);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(3, 3);
  lcd.print(humidityPercentage);
  lcd.print("%");
  lcd.setCursor(13, 3);  
  lcd.print((int) round(pressureInHPA));
  lcd.print("hPA");
}

void printDateTime() {
  time(&now);
  localtime_r(&now, &tm);
  
  lcd.setCursor(0, 0);
  lcd.print(daysOfTheWeek[tm.tm_wday]);

  lcd.setCursor(10, 0);
  lcd.print(month[tm.tm_mon]);

  lcd.setCursor(14, 0);
  lcd.print(convertToTwoDigitString(tm.tm_mday));

  lcd.setCursor(18, 0);
  int current_year = tm.tm_year + 1900;
  lcd.print(String(current_year).substring(2,4));

  lcd.setCursor(0, 1);
  lcd.print(convertToTwoDigitString(tm.tm_hour));

  lcd.setCursor(3, 1);
  lcd.print(convertToTwoDigitString(tm.tm_min));

  lcd.setCursor(6, 1);
  lcd.print(convertToTwoDigitString(tm.tm_sec));
}

String convertToTwoDigitString(int integer){
  return integer>9 ? String(integer) : "0"+String(integer);
}