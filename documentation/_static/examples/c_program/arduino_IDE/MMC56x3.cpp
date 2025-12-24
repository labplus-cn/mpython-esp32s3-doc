#include <MMC56x3.h>
#include <Wire.h>

/* Assign a unique ID to this sensor at the same time */
MMC5603 mmc = MMC5603();

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("MMC5603 Magnetometer Test");
  Serial.println("");

  Wire.begin(44,43,400000);
  /* Initialise the sensor */
  if (!mmc.begin(MMC56X3_DEFAULT_ADDRESS, Wire)) {  // I2C mode
    /* There was a problem detecting the MMC5603 ... check your connections */
    Serial.println("Ooops, no MMC5603 detected ... Check your wiring!");
    while (1) delay(10);
  }
}

MMC5603_Data_t data;

void loop(void) {
  // Get a new sensor event 
  mmc.getData(&data);

  // Display the results (magnetic vector values are in micro-Tesla (uT))
  Serial.print("X: ");
  Serial.print(data.magX);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(data.magY);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(data.magZ);
  Serial.print("  ");
  Serial.println("uT");

  // Read and display temperature
  float temp_c = mmc.readTemperature();
  Serial.print("Temp: "); Serial.print(temp_c); Serial.println(" *C");
  // Delay before the next sample
  delay(100);
}