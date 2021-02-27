// HD44780 LCD driver library
#include <LiquidCrystal.h>

// I2C Wire library
#include <Wire.h>

// CCS811 library
#include "SparkFunCCS811.h"

/* 
https://www.pjrc.com/teensy/td_libs_OneWire.html
1-Wire bus librabry
*/
#include <OneWire.h>

/*
https://github.com/milesburton/Arduino-Temperature-Control-Library
DS1820-family temperature sensor library
*/
#include <DallasTemperature.h>

// I2C address of CCS811 sensor (hardware  based)
#define CCS811_ADDR 0x5A

// digital output for red/alarm LED
#define ALARM 18

// digital output for green computing LED
#define TEST 19

// digital i/o for 1-Wire bus (DS1820 sensor)
#define W1W 20

// digital output for RegistrySelect signal for LCD display
#define RS 4

// digital output for Enable signal for LCD display
#define E 5

// digital output for DB04 signal for LCD display
#define IN0 6

// digital output for DB05 signal for LCD display
#define IN1 7

// digital output for DB06 signal for LCD display
#define IN2 8

// digital output for DB07 signal for LCD display
#define IN3 9

// level of CO2 which triggers alarm
#define ALERTLVL 1000

// LCD init, 4-bit mode
LiquidCrystal lcd(RS,E,IN0,IN1,IN2,IN3);

// CCS811 init with I2C address
CCS811 o2(CCS811_ADDR);

// 1-Wire init with bus pin
OneWire oneWire(W1W);

// DS1820 init with 1-Wire object
DallasTemperature w1w(&oneWire);

void setup() {
  // initialize hardware
  Wire.begin();
  o2.begin();
  w1w.begin();

  // set-up pins mode for LEDs
  pinMode(ALARM, OUTPUT);
  pinMode(TEST, OUTPUT);

  // initial display on LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("CO2: ");
}

void loop() {
  int co2;
  float temp;

  // light processing LED
  digitalWrite(TEST, HIGH);
  
  // get DS1820 temp
  w1w.requestTemperatures();
  temp = w1w.getTempCByIndex(0);
  
  // clear temp display
  lcd.setCursor(6,0);
  lcd.print("         ");

  // print temp in Celsius
  lcd.setCursor(6,0);
  lcd.print(temp);
  lcd.print(" C");

  /*
  set temperature correction for CSS811,
  humidity is hardcoded to 60%
  due to lack of sensor
  */
  o2.setEnvironmentalData(60,temp);
  
  // do we have CO2 readings?
  if (o2.dataAvailable())
  {
    // get CO2 level
    o2.readAlgorithmResults();
    co2 = o2.getCO2();

    // clear CO2 display
    lcd.setCursor(5,1);
    lcd.print("          ");

    // print new CO2 value
    lcd.setCursor(5,1);
    lcd.print(co2);
    lcd.print("ppm");

    // is CO2 level to high?
    if (co2 > ALERTLVL){
      // yes, light alarm LED
      digitalWrite(ALARM, HIGH);
    }
    else{
      // no, disable alarm LED
      digitalWrite(ALARM, LOW);
    }
  }

  // processing ends, disable processing LED
  digitalWrite(TEST, LOW);

  delay(10000);
}
