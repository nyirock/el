// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN1 2     // what digital pin we're connected to
#define DHTPIN2 3
#define DHTPIN3 4
// Uncomment whatever type you're using!
#define DHTTYPE11 DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht11(DHTPIN3,DHTTYPE11);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  dht2.begin();
  dht11.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();
  float f2 = dht2.readTemperature(true);
  
  float t11 = dht11.readTemperature();
  float h11 = dht11.readHumidity();
  float f11 = dht11.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT1 sensor!");
    return;
  }
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT2 sensor!");
    return;
  }
  if (isnan(h11) || isnan(t11) || isnan(f11)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }*/
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Compute heat index in Fahrenheit (the default)
  float hif2 = dht2.computeHeatIndex(f2, h2);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = dht2.computeHeatIndex(t2, h2, false);


  float hif11 = dht11.computeHeatIndex(f11, h11);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic11 = dht11.computeHeatIndex(t11, h11, false);
  
  Serial.print("Humidity1: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature1: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index1: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  Serial.print("Humidity2: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature2: ");
  Serial.print(t2);
  Serial.print(" *C ");
  Serial.print(f2);
  Serial.print(" *F\t");
  Serial.print("Heat index2: ");
  Serial.print(hic2);
  Serial.print(" *C ");
  Serial.print(hif2);
  Serial.println(" *F");

  Serial.print("Humidity11: ");
  Serial.print(h11);
  Serial.print(" %\t");
  Serial.print("Temperature11: ");
  Serial.print(t11);
  Serial.print(" *C ");
  Serial.print(f11);
  Serial.print(" *F\t");
  Serial.print("Heat index11: ");
  Serial.print(hic2);
  Serial.print(" *C ");
  Serial.print(hif2);
  Serial.println(" *F");

}
