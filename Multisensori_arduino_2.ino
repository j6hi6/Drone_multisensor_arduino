/*
SCD41 SCL SDA portteihin
BME28 SCL(KELT)= A5 SDA(VALK) = A4
*/


//Grove - Barometer Sensor BME280 - Seeed Studio
#include "Seeed_BME280.h"

//SparkFun SCD4x Arduion Library
#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
SCD4x mySensor;

#include <Wire.h>

// ArdionoJson by Benoit
#include <ArduinoJson.h>



BME280 bme280;



void setup()

{
  Serial.begin(9600);
 // Serial.println("TESTI"); 
  Wire.begin();

// SCD41 error message

  if (mySensor.begin() == false)
  {
    Serial.println(F("CO2 Sensor not detected."));
    while (1)
      ;
  }
 
  
}


void loop()
{

//Muuttujat SCD41

  long Time = millis();
  int Temperature = mySensor.getTemperature();
  int Humidity = mySensor.getHumidity();
  int CO2 = mySensor.getCO2();

//Muuttujat BME280

  float pressure = (bme280.getPressure() );
  int Altitude = (bme280.calcAltitude(pressure));


// JSON Muotoilu


  StaticJsonDocument<200> doc;

  doc["Time"] = Time;
  doc["Temperature"] = Temperature;
  doc["Humidity"] = Humidity;
  doc["CO2"] = CO2;
  doc["Pressure"] = (pressure = bme280.getPressure());
  doc["Altitude"] = Altitude;

  // Send the JSON document over the "link" serial port
  serializeJson(doc, Serial);
  Serial.println();


  // Wait
  delay(5000);

}





/*
void loop()
{
  if (mySensor.readMeasurement()) // readMeasurement will return true when fresh data is available
  {
    Serial.println();

    Serial.print(F("CO2(ppm):"));
    Serial.print(mySensor.getCO2());

    Serial.print(F("\tTemperature(C):"));
    Serial.print(mySensor.getTemperature(), 1);

    Serial.print(F("\tHumidity(%RH):"));
    Serial.print(mySensor.getHumidity(), 1);

    Serial.println();
  }
  else
  
  Serial.println("No CO2 Data");

  delay(5000);
}
*/

