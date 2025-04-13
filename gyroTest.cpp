#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>

#define I2C_SDA 5
#define I2C_SCL 4


// Object for the LSM6DSOX accelerometer
Adafruit_LSM6DSOX lsm6ds;

void setup() {
  Serial.begin(115200);
  
  // Initialize the LSM6DSOX sensor
  if (!lsm6ds.begin_I2C()) {
    Serial.println("Failed to find LSM6DSOX chip");
    while (1) delay(10);
  }
  
  // Set up accelerometer range (2, 4, 8, or 16 G)
  lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  
  // Set data rate (default is 104 Hz)
  lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
  
  Serial.println("LSM6DSOX Ready!");
}

void loop() {
  // Get new sensor events with the readings
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds.getEvent(&accel, &gyro, &temp);

  // Format data as CSV for easy parsing on the PC side
  Serial.print(accel.acceleration.x);
  Serial.print(",");
  Serial.print(accel.acceleration.y);
  Serial.print(",");
  Serial.println(accel.acceleration.z);
  
  // Small delay to not overwhelm the serial connection
  delay(50);  // 50Hz update rate
}