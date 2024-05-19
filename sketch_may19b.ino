#include <Servo.h>

Servo servo1; // Continuous rotation servo
int x_axis;

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(A0, INPUT); // Joystick x-axis

  servo1.attach(10); // Attach servo to pin 10

  // Initialize servo to stopped position
  servo1.write(90); // Stop continuous rotation servo
}

void loop() {
  x_axis = analogRead(A0); // Read the joystick x-axis value

  // Debugging output to see the analog value
  Serial.print("x_axis: ");
  Serial.println(x_axis);

  // Check if the joystick is pushed forward (value > 512)
  if (x_axis > 512) {
    // Debugging output
    Serial.println("Joystick pushed forward");

    // Move servo1 to full speed in the opposite direction
    servo1.write(180); // Full speed in the opposite direction for continuous rotation servo

    // Delay to approximate one rotation (adjust this value as needed)
    delay(1000); // Adjust this value based on your servo's speed

    // Stop the servo after one rotation
    servo1.write(90);

    // Debugging output
    Serial.println("Servo completed one rotation and stopped");
  } else {
    // If joystick is not pushed forward, keep servo at its starting position
    servo1.write(90); // Stop continuous rotation servo

    // Debugging output
    Serial.println("Joystick not pushed, servo in starting position");
  }

  delay(100); // Small delay to prevent rapid looping
}
