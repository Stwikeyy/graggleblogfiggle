// Define motor pins
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

// Define joystick pins
#define VRx A0
#define VRy A1

// Define dead zone threshold
#define DEAD_ZONE 100

void setup() {
  // Initialize motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the joystick values
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);

  // Print the joystick values (for debugging)
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" Y: ");
  Serial.println(yValue);

  // Calculate the deviation from the center position (512 for a 10-bit ADC)
  int xDeviation = xValue - 512;
  int yDeviation = yValue - 512;

  // Control the motors based on joystick position if outside dead zone
  if (abs(xDeviation) > DEAD_ZONE || abs(yDeviation) > DEAD_ZONE) {
    // Forward
    if (yDeviation > DEAD_ZONE) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    // Backward
    else if (yDeviation < -DEAD_ZONE) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    // Left
    else if (xDeviation < -DEAD_ZONE) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    // Right
    else if (xDeviation > DEAD_ZONE) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
  } else {
    // Stop if within the dead zone
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  delay(100); // Add a small delay to make the movement smoother
}
