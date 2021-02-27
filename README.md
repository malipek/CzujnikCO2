# CzujnikCO2
Temperature and CO<sub>2</sub> level digital indicator.

![Photo of the prototype](https://raw.githubusercontent.com/malipek/CzujnikCO2/main/media/CzujnikCO2.jpg)

## Key components
* Arduino compatible board (at least 15kB Flash, 520B RAM); Arduino Pro Micro is used in project.
* CSS811 sensor with I<sup>2</sup>C bus interface; [SS-CCS811](https://itbrainpower.net/sensors/CCS811-CO2-TVOC-I2C-sensor-breakout) is used in the project
* 1-Wire DS18x20 temperature sensor
* 2x16 LCD display with HD44780 driver

## Project concept
Due to COVID-19 and home-office activities the quality of indoor air becomes an issue. Too high level of CO<sub>2</sub> [may cause cognitive-impairment](https://www.news-medical.net/news/20200421/Atmospheric-CO2-levels-can-cause-cognitive-impairment.aspx). 

The device measures temperature with 1-Wire DS1820 sensor, and feeds the data to CCS811 sensor which measures the level of volatile organic compunds in the air. Based on the assumption, that main source of coal in the air indoors is human breath the CO<sub>2</sub> level is calculated.

Measured temperature (in <sup>o</sup>C) and calculated CO<sub>2</sub> level (in particles per million) are shown on the LCD display.

Green LED lights up for the time of sensors' reading. Red LED lights up in case the declared level of CO<sub>2</sub> is exceeded.