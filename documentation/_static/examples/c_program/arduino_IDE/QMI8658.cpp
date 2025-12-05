/*
  QMI8658 Basic Example - Enhanced with Flexible Units & Precision
  
  This example demonstrates the enhanced QMI8658 library with flexible
  unit selection and precision control.
  
  New Features:
  - Choose between mg or m/s² for accelerometer
  - Choose between dps or rad/s for gyroscope  
  - Set decimal precision (2, 4, 6 digits)
  - Alternative reading functions for specific units
  
  Connections for RP2040:
  - VCC to 3.3V
  - GND to GND  
  - SDA to pin 44
  - SCL to pin 43
  
  Author: [Your Name]
  Date: [Date]
*/

#include <QMI8658.h>

// Create QMI8658 instance
QMI8658 imu;

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for serial to stabilize
    
    Serial.println("🚀 QMI8658 Enhanced Library - Flexible Units & Precision");
    Serial.println("========================================================");
    
    // Initialize the sensor with pins 6,7 (uses Wire1 automatically on RP2040)
    Serial.println("📍 Initializing sensor...");
    bool success = imu.begin(44, 43);
    
    if (!success) {
        Serial.println("❌ Failed to initialize QMI8658!");
        Serial.println("Please check:");
        Serial.println("- Wiring connections (SDA=6, SCL=7)");
        Serial.println("- Power supply (3.3V)");
        Serial.println("- I2C address");
        while (1) {
            Serial.println("⏳ Retrying in 5 seconds...");
            delay(5000);
        }
    }
    
    Serial.println("✅ QMI8658 initialized successfully!");
    Serial.print("WHO_AM_I: 0x");
    Serial.println(imu.getWhoAmI(), HEX);
    
    // Configure sensor settings
    Serial.println("\n⚙️ Configuring sensor...");
    
    // Set accelerometer range (±8g)
    imu.setAccelRange(QMI8658_ACCEL_RANGE_8G);
    
    // Set accelerometer output data rate (1000Hz)
    imu.setAccelODR(QMI8658_ACCEL_ODR_1000HZ);
    
    // Set gyroscope range (±512dps)
    imu.setGyroRange(QMI8658_GYRO_RANGE_512DPS);
    
    // Set gyroscope output data rate (1000Hz)
    imu.setGyroODR(QMI8658_GYRO_ODR_1000HZ);
    
    // ⭐ NEW: Configure units and precision
    Serial.println("\n🎯 Setting units and precision...");
    
    // Set units (DEFAULT: mg for accel, dps for gyro - matches most IMU displays)
    imu.setAccelUnit_mg(true);      // Use mg (like your screen: ACC_X = -965.82)
    imu.setGyroUnit_dps(true);      // Use dps (degrees per second)
    imu.setDisplayPrecision(6);     // 6 decimal places (like your screen)
    
    // Alternative ways to set units:
    // imu.setAccelUnit_mps2(true);  // Would use m/s² instead of mg
    // imu.setGyroUnit_rads(true);   // Would use rad/s instead of dps
    // imu.setDisplayPrecision(QMI8658_PRECISION_4); // 4 decimal places
    
    // Enable sensors
    imu.enableSensors(QMI8658_ENABLE_ACCEL | QMI8658_ENABLE_GYRO);
    
    Serial.println("✅ Configuration complete!");
    
    // Show current settings
    Serial.println("\n📋 Current Settings:");
    Serial.print("   Accelerometer unit: ");
    Serial.println(imu.isAccelUnit_mg() ? "mg" : "m/s²");
    Serial.print("   Gyroscope unit: ");
    Serial.println(imu.isGyroUnit_dps() ? "dps" : "rad/s");
    Serial.print("   Display precision: ");
    Serial.print(imu.getDisplayPrecision());
    Serial.println(" decimal places");
    
    Serial.println("\n📊 Starting sensor readings...");
    Serial.println("Time(ms)\tAcc_X(mg)\tAcc_Y(mg)\tAcc_Z(mg)\tGyro_X(dps)\tGyro_Y(dps)\tGyro_Z(dps)\tTemp(°C)");
    Serial.println("-----------------------------------------------------------------------------------------");
    
    delay(100); // Allow sensor to stabilize
}

void loop() {
    // Method 1: Read all sensor data at once (recommended)
    QMI8658_Data sensorData;
    
    if (imu.readSensorData(sensorData)) {
        Serial.print(millis());
        Serial.print("\t");
        Serial.print(sensorData.accelX, 6);
        Serial.print("\t");
        Serial.print(sensorData.accelY, 6);
        Serial.print("\t");
        Serial.print(sensorData.accelZ, 6);
        Serial.print("\t");
        Serial.print(sensorData.gyroX, 6);
        Serial.print("\t");
        Serial.print(sensorData.gyroY, 6);
        Serial.print("\t");
        Serial.print(sensorData.gyroZ, 6);
        Serial.print("\t");
        Serial.println(sensorData.temperature, 1);
    } else {
        Serial.println("❌ Failed to read sensor data!");
    }
    
    /* 
    // Method 2: Read sensors individually with specific units
    float ax, ay, az;
    float gx, gy, gz;
    float temp;
    
    // Read with default configured units
    if (imu.readAccel(ax, ay, az) && imu.readGyro(gx, gy, gz) && imu.readTemp(temp)) {
        Serial.print("📈 Accel (mg): ");
        Serial.print(ax, 6); Serial.print(", ");
        Serial.print(ay, 6); Serial.print(", ");
        Serial.print(az, 6);
        
        Serial.print(" | Gyro (dps): ");
        Serial.print(gx, 6); Serial.print(", ");
        Serial.print(gy, 6); Serial.print(", ");
        Serial.print(gz, 6);
        
        Serial.print(" | 🌡️ Temp: ");
        Serial.print(temp, 1);
        Serial.println("°C");
    }
    
    // Method 3: Read with specific units (if supported by your library)
    // Example: Force read in m/s² even if default is mg
    // if (imu.readAccel_mps2(ax, ay, az)) {
    //     Serial.print("Accel in m/s²: ");
    //     Serial.print(ax, 6); Serial.print(", ");
    //     Serial.print(ay, 6); Serial.print(", ");
    //     Serial.println(az, 6);
    // }
    */
    
    delay(100); // Read at 10Hz
}
