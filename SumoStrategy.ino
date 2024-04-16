#include <Wire.h>
#include <Zumo32U4.h>

// Initialize components of the robot
Zumo32U4OLED display; // OLED display for feedback
Zumo32U4ButtonA buttonA; // Button for starting/pausing
Zumo32U4Motors motors; // Motors for movement
Zumo32U4LineSensors lineSensors; // Line sensors for edge detection

unsigned int lineSensorValues[3]; // Stores line sensor readings

// Configuration constants
const uint16_t lineSensorThreshold = 1000; // Threshold for line detection
const uint16_t reverseSpeed = 200; // Speed while reversing
const uint16_t forwardSpeed = 200; // Speed while moving forward
const uint16_t turnSpeed = 200; // Speed while turning
const uint16_t reverseTime = 200; // Duration of reversing
const uint16_t turnTime = 400; // Duration of turning to avoid loops
const uint16_t waitTimeBeforeStart = 5000; // Initial wait time before starting

// Define the robot's possible states
enum RobotState {
  Pausing, // Robot is paused
  WaitingForStart, // Robot is waiting to start
  DrivingForward, // Robot is driving forward
  Reversing, // Robot is reversing
  Turning // Robot is turning to avoid loops
};

RobotState currentState = Pausing; // Current state of the robot
uint16_t stateEntryTime; // Time the current state was entered
bool isNewState = true; // Flag to indicate if just entered a new state

void setup() {
  randomSeed(analogRead(0)); // Seed the random number generator
  lineSensors.initThreeSensors(); // Initialize the line sensors
  enterState(Pausing); // Start in the Pausing state
}

void loop() {
  // Handle button press to toggle between Pausing and WaitingForStart
  if (buttonA.getSingleDebouncedPress()) {
    if (currentState == Pausing) {
      enterState(WaitingForStart);
    } else {
      enterState(Pausing);
    }
  }

  // State machine for the robot's behavior
  switch (currentState) {
    case Pausing: handlePausing(); break;
    case WaitingForStart: handleWaitingForStart(); break;
    case DrivingForward: handleDrivingForward(); break;
    case Reversing: handleReversing(); break;
    case Turning: handleTurning(); break;
  }
}

// Handles the Pausing state: stops the motors and displays "Paused"
void handlePausing() {
  motors.setSpeeds(0, 0);
  if (isNewState) {
    isNewState = false;
    display.print(F("Paused"));
  }
}

// Handles the WaitingForStart state: displays remaining wait time
void handleWaitingForStart() {
  motors.setSpeeds(0, 0);
  displayRemainingWaitTime();
  if (timeInCurrentState() >= waitTimeBeforeStart) {
    enterState(DrivingForward);
  }
}

// Handles the DrivingForward state: moves forward and checks for edges
void handleDrivingForward() {
  detectBorderAndReverseIfNeeded();
  motors.setSpeeds(forwardSpeed, forwardSpeed);
}

// Handles the Reversing state: reverses for a set time
void handleReversing() {
  motors.setSpeeds(-reverseSpeed, -reverseSpeed);
  if (timeInCurrentState() >= reverseTime) {
    enterState(Turning);
  }
}

// Handles the Turning state: turns in a random direction to avoid loops
void handleTurning() {
  if (isNewState) {
    isNewState = false;
    int turnDirection = random(2) * 2 - 1; // Chooses -1 (left) or 1 (right)
    motors.setSpeeds(turnDirection * turnSpeed, -turnDirection * turnSpeed);
  }
  if (timeInCurrentState() >= turnTime) {
    enterState(DrivingForward); // Return to forward movement after turning
  }
}

// Displays the remaining time before starting
void displayRemainingWaitTime() {
  uint16_t timeLeft = waitTimeBeforeStart - timeInCurrentState();
  display.gotoXY(0, 0);
  display.print(timeLeft / 1000 % 10);
  display.print('.');
  display.print(timeLeft / 100 % 10);
}

// Detects the border and reverses if necessary
void detectBorderAndReverseIfNeeded() {
  lineSensors.read(lineSensorValues);
  if (lineSensorValues[0] < lineSensorThreshold || lineSensorValues[2] < lineSensorThreshold) {
    enterState(Reversing);
  }
}

// Calculates the time spent in the current state
uint16_t timeInCurrentState() {
  return (uint16_t)(millis() - stateEntryTime);
}

// Changes the robot's state and initializes state transition
void enterState(RobotState newState) {
  currentState = newState;
  isNewState = true;
  stateEntryTime = millis();
  display.clear();
}
