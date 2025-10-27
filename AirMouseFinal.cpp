#include "BleMouse.h"    // Include the Bluetooth Mouse library
#include <Wire.h>
#include <MPU6050.h>

// Create a BluetoothMouse object
BleMouse bleMouse;

// MPU6050 object
MPU6050 gyro;

// Sensitivity for cursor movement
float sensitivity = 1.5;  // Adjust this to control cursor speed

// Variables for accelerometer readings and angles
float axx = 0, ayy = 0, azz = 0;
float roll = 0, pitch = 0;  // Angles around axes

// Kalman filter variables
float roll_est = 0, roll_err = 1;
float pitch_est = 0, pitch_err = 1;
float process_noise = 0.01;
float measurement_noise = 0.1;

// Offset for calibration
float ay_offset = 0.0;

// Button pin setup
const int buttonPin = 15; // GPIO for left click
bool lastButtonState = HIGH;

// Threshold to prevent jitter
const float movementThreshold = 1.0;

void setup() {
  Serial.begin(115200);

  // Initialize I2C and MPU6050
  Wire.begin();
  gyro.initialize();

  // Calibration routine
  int numSamples = 100;
  int16_t ax, ay, az;
  for (int i = 0; i < numSamples; i++) {
    gyro.getAcceleration(&ax, &ay, &az);
    ay_offset += ay / 16384.0;
    delay(10);
  }
  ay_offset /= numSamples;

  // Begin Bluetooth Mouse
  bleMouse.begin();
  Serial.println("✅ Bluetooth Mouse is ready to pair");

  pinMode(buttonPin, INPUT_PULLUP);
}

// Kalman filter function
float kalmanFilter(float measurement, float &estimate, float &error) {
  error += process_noise;
  float kalman_gain = error / (error + measurement_noise);
  estimate += kalman_gain * (measurement - estimate);
  error *= (1 - kalman_gain);
  return estimate;
}

void loop() {
  if (bleMouse.isConnected()) {
    int16_t ax, ay, az;
    gyro.getAcceleration(&ax, &ay, &az);

    // Normalize readings
    axx = ax / 16384.0;
    ayy = (ay / 16384.0) - ay_offset;
    azz = az / 16384.0;

    // Calculate tilt angles
    float roll_meas = atan2(ayy, sqrt(axx * axx + azz * azz)) * 180 / PI;
    float pitch_meas = atan2(-axx, sqrt(ayy * ayy + azz * azz)) * 180 / PI;

    // Apply Kalman filter
    roll = kalmanFilter(roll_meas, roll_est, roll_err);
    pitch = kalmanFilter(pitch_meas, pitch_est, pitch_err);

    // Convert tilt to cursor movement
    int deltaY = (abs(roll) > movementThreshold) ? roll * sensitivity : 0;
    int deltaX = (abs(pitch) > movementThreshold) ? pitch * sensitivity : 0;

    // Scroll control using Z-axis tilt (azz)
    int scroll = 0;
    if (azz > 0.25) {          // Tilt forward → scroll up
      scroll = -3;
    } else if (azz < -0.25) {  // Tilt backward → scroll down
      scroll = 3;
    }

    // Move cursor and scroll
    bleMouse.move(deltaX, -deltaY, scroll);

    Serial.print("Roll: "); Serial.print(roll);
    Serial.print(" | Pitch: "); Serial.print(pitch);
    Serial.print(" | DeltaX: "); Serial.print(deltaX);
    Serial.print(" | DeltaY: "); Serial.print(deltaY);
    Serial.print(" | Scroll: "); Serial.println(scroll);

    // Left click on button press
    bool currentButtonState = digitalRead(buttonPin);
    if (lastButtonState == HIGH && currentButtonState == LOW) {
      bleMouse.click(MOUSE_LEFT);
      Serial.println("🖱️ Mouse Click!");
    }
    lastButtonState = currentButtonState;

    delay(20);

  } else {
    Serial.println("❌ Mouse not connected");
    delay(1000);
  }
}
