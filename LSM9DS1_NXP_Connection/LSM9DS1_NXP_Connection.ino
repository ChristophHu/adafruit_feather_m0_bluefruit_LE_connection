#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c conection
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5

/* 
//software SPI connection
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
*/
/*
//hardware SPI connection (In this case, only CS pins are passed in)
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);
*/
void setupSensor()
{
    //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);                                // Set the accelerometer range 2G, 4G, 8G, 16G
    //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);                                 // Set the magnetometer sensitivity 4GAUSS, 8GAUSS, 12GAUSS, 16GAUSS
    lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);                                // Setup the gyroscope 245DPS, 500DPS, 2000DPS
}

void setup() {
    Serial.begin(115200);                                                       // Bauderate in serial

    while (!Serial) {
        delay(1);                                                               // will pause Zero, Leonardo, etc until serial console opens
    }
    
    Serial.println("LSM9DS1 data read demo");
    
    if (!lsm.begin()) {                                                         // Try to initialise and warn if we couldn't detect the chip
        Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
        while (1);
    }
    Serial.println("Found LSM9DS1 9DOF");

    setupSensor();                                                              // helper to just set the default scaling we want, see above!
}

void loop() {
    lsm.read();                                                                 // ask it to read in the data
    sensors_event_t a, m, g, temp;                                              // Get a new sensor event
    lsm.getEvent(&a, &m, &g, &temp);                                            // handing over to lsm

    /* Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
    Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
    Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

    Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" gauss");
    Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" gauss");
    Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" gauss");
    */
    Serial.print("Gyro X: "); Serial.print(g.gyro.x); Serial.print(" dps");     // Gyro X-Wert
    Serial.print("\tY: "); Serial.print(g.gyro.y); Serial.print(" dps");        // Gyro Y-Wert
    Serial.print("\tZ: "); Serial.print(g.gyro.z); Serial.println(" dps");      // Gyro Z-Wert

    Serial.println();                                                           // new line
    delay(200);                                                                 // Timeout
}