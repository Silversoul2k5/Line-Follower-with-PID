// ----------------------------------------------------------------------
// IR SENSOR ANALOG PINS
// ----------------------------------------------------------------------
int S1 = A0;    // Very Left
int S2 = A1;    // Slight Left
int S3 = A2;    // Middle
int S4 = A3;    // Slight Right
int S5 = A4;    // Very Right

// ----------------------------------------------------------------------
// IR THRESHOLDS
// ----------------------------------------------------------------------
int thresholdBlack = 600;    // below = BLACK
int thresholdWhite = 800;    // above = WHITE

// ----------------------------------------------------------------------
// MOTOR PINS
// ----------------------------------------------------------------------
int LF = 7;      // Left Forward
int LB = 8;      // Left Backward
int LS = 6;      // Left PWM Speed
int RF = 9;      // Right Forward
int RB = 10;     // Right Backward
int RS = 5;      // Right PWM Speed

// ----------------------------------------------------------------------
// PID CONSTANTS (you can tune these)
// ----------------------------------------------------------------------
float Kp = 25;
float Ki = 0;       // Start with 0, increase later only if needed
float Kd = 15;

// PID control variables
float error = 0;
float lastError = 0;
float integral = 0;
float derivative = 0;
float correction = 0;

// ----------------------------------------------------------------------
// SPEED SETTINGS
// ----------------------------------------------------------------------
//max speed 250...
int baseSpeed = 60;      // Base speed for both motors
int maxPWM = 80;

// ----------------------------------------------------------------------
// SETUP
// ----------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LS, OUTPUT);

  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(RS, OUTPUT);

  Serial.println("PID Line Follower Ready...");
}

// ----------------------------------------------------------------------
// BLACK/WHITE DETECTION
// ----------------------------------------------------------------------
int isBlack(int v) {
  return (v < thresholdBlack) ? 1 : 0;
}

// ----------------------------------------------------------------------
// MOTOR CONTROL HELPERS
// ----------------------------------------------------------------------
void runMotors(int leftPWM, int rightPWM) {

  // Left motor always forward
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);

  // Right motor always forward
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);

  // Limit PWM range
  leftPWM = constrain(leftPWM, 0, maxPWM);
  rightPWM = constrain(rightPWM, 0, maxPWM);

  analogWrite(LS, leftPWM);
  analogWrite(RS, rightPWM);
}

// ----------------------------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------------------------
void loop() {

  // Read IR analog values
  int v1 = analogRead(S1);
  int v2 = analogRead(S2);
  int v3 = analogRead(S3);
  int v4 = analogRead(S4);
  int v5 = analogRead(S5);

  // Convert to binary BLACK/WHITE
  int b1 = isBlack(v1);
  int b2 = isBlack(v2);
  int b3 = isBlack(v3);
  int b4 = isBlack(v4);
  int b5 = isBlack(v5);

  // Print states
  Serial.print("S1: "); Serial.print(b1 ? "BLACK" : "WHITE"); Serial.print(" | ");
  Serial.print("S2: "); Serial.print(b2 ? "BLACK" : "WHITE"); Serial.print(" | ");
  Serial.print("S3: "); Serial.print(b3 ? "BLACK" : "WHITE"); Serial.print(" | ");
  Serial.print("S4: "); Serial.print(b4 ? "BLACK" : "WHITE"); Serial.print(" | ");
  Serial.print("S5: "); Serial.println(b5 ? "BLACK" : "WHITE");

  // ------------------------------------------------------------------
  // PID INPUT (weighted average)
  // BLACK = 1, WHITE = 0
  // More weight → stronger correction
  // ------------------------------------------------------------------
  error = (-2 * b1) + (-1 * b2) + (0 * b3) + (1 * b4) + (2 * b5);

  // PID CALCULATION
  integral += error;
  derivative = error - lastError;
  correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
  lastError = error;

  // APPLY MOTOR SPEEDS
  int leftPWM = baseSpeed - correction;
  int rightPWM = baseSpeed + correction;

  runMotors(leftPWM, rightPWM);

  delay(30);
}
