#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>

#define I2C_SDA 5
#define I2C_SCL 4


LSM6DSOXSensor lsm6dsoxSensor = LSM6DSOXSensor(&Wire, LSM6DSOX_I2C_ADD_L);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Default clock is 100kHz. LSM6DSOX also supports 400kHz, let's use it
  Wire.setClock(400000);

  // Init the sensor
  lsm6dsoxSensor.begin();

  // Enable accelerometer and gyroscope, and check success
  if (lsm6dsoxSensor.Enable_X() == LSM6DSOX_OK && lsm6dsoxSensor.Enable_G() == LSM6DSOX_OK) {
    Serial.println("Success enabling accelero and gyro");
  } else {
    Serial.println("Error enabling accelero and gyro");
  }

  // Read ID of device and check that it is correct
  uint8_t id;
  lsm6dsoxSensor.ReadID(&id);
  if (id != LSM6DSOX_ID) {
    Serial.println("Wrong ID for LSM6DSOX sensor. Check that device is plugged");
  } else {
    Serial.println("Receviced correct ID for LSM6DSOX sensor");
  }

  // Set accelerometer scale at +- 2G. Available values are +- 2, 4, 8, 16 G
  lsm6dsoxSensor.Set_X_FS(2);

  // Set gyroscope scale at +- 125 degres per second. Available values are +- 125, 250, 500, 1000, 2000 dps
  lsm6dsoxSensor.Set_G_FS(125);


  // Set Accelerometer sample rate to 208 Hz. Available values are +- 12.0, 26.0, 52.0, 104.0, 208.0, 416.0, 833.0, 1667.0, 3333.0, 6667.0 Hz
  lsm6dsoxSensor.Set_X_ODR(208.0f);


  // Set Gyroscope sample rate to 208 Hz. Available values are +- 12.0, 26.0, 52.0, 104.0, 208.0, 416.0, 833.0, 1667.0, 3333.0, 6667.0 Hz
  lsm6dsoxSensor.Set_G_ODR(208.0f);


}

void loop() {

  // Read accelerometer
  uint8_t acceleroStatus;
  lsm6dsoxSensor.Get_X_DRDY_Status(&acceleroStatus);
  if (acceleroStatus == 1) { // Status == 1 means a new data is available
    int32_t acceleration[3];
    lsm6dsoxSensor.Get_X_Axes(acceleration);
    // Plot data for each axis in mg
    Serial.print("AccelerationX="); Serial.print(acceleration[0]); Serial.print("mg, AccelerationY="); Serial.print(acceleration[1]); Serial.print("mg, AccelerationZ="); Serial.print(acceleration[2]); Serial.println("mg");
  }

  // Read gyroscope
  uint8_t gyroStatus;
  lsm6dsoxSensor.Get_G_DRDY_Status(&gyroStatus);
  if (gyroStatus == 1) { // Status == 1 means a new data is available
    int32_t rotation[3];
    lsm6dsoxSensor.Get_G_Axes(rotation);
    // Plot data for each axis in milli degrees per second
    Serial.print("RotationX="); Serial.print(rotation[0]); Serial.print("mdps, RotationY="); Serial.print(rotation[1]); Serial.print("mdps, RotationZ="); Serial.print(rotation[2]); Serial.println("mdps");
  }

  delay(10);

}