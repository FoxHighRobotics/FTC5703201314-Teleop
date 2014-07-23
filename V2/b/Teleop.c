#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     sensorUltrasonic, sensorSONAR)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     motorRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     motorLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    servoGripper,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// The Doppler Effect 2013
// Teleop 2

#include "JoystickDriver.c"
#include "Teleop.h"

volatile float driveSpeedLeft;
volatile float driveSpeedRight;

volatile float driveMaxSpeed;

// Initializations
void initialize() {
}

// Main task
task main() {
	initialize();

	// Wait for the field control system
	waitForStart();

	// Start subroutines
	StartTask(controller);
	StartTask(screen);

	// Update physical states
	while (true) {
		motor[motorLeft]        = (int) driveSpeedLeft;
		motor[motorRight]       = (int) driveSpeedRight;

		servo[servoArmPitch]    = servoArmPitchValue;
		servo[servoArmSegment]  = servoArmSegmentValue;

		// Allow other tasks to run
		EndTimeSlice();
	}
}

// Controller task
// Responsible for sampling data from the controllers, making decisions, and sending commands to the main task
task controller() {
	while (true) {
		// Poll joystick data
		getJoystickSettings(joystick);

		// Handle joystick state
		driveSpeedLeft  = ((float) joystick.joy1_y1/128.0)*driveMaxSpeed;
		driveSpeedRight = ((float) joystick.joy1_y2/128.0)*driveMaxSpeed;

		// Handle button state
		driveMaxSpeed = (joy1Btn(BUTTON_R1) == 0) ? MOTOR_DRIVE_HIGH_SPEED : MOTOR_DRIVE_LOW_SPEED;

		// Gripper buttons on controller 2
		// Continue if one is pressed, but not the other
		if ((joy2Btn(BUTTON_A) || joy2Btn(BUTTON_B)) && (joy2Btn(BUTTON_A) != joy2Btn(BUTTON_B))) {
			if (joy2Btn(BUTTON_A)) {
				// Open the gripper
				gripperState = 1;
			}

			if (joy2Btn(BUTTON_B)) {
				// Close the gripper
				gripperState = 0;
			}
		}

		// Get arm base pitch from joystick 1 on controller 2
		if (joystick.joy2_y1 >= 5) {
			servoArmPitchValue = 0;
		} else if (joystick.joy1_y2 <= -5) {
			servoArmPitchValue = 255;
		} else {
			servoArmPitchValue = 0;
		}

		// Get arm segment pitch from joystick 2 on controller 2
		if (joystick.joy2_y2 >= 5) {
			servoArmSegmentValue = 0;
		} else if (joystick.joy2_y2 <= -5) {
			servoArmSegmentValue = 255;
		} else {
			servoArmSegmentValue = 0;
		}

		// Allow other tasks to run
		EndTimeSlice();
	}
}

task screen() {
	while (true) {
		eraseDisplay();

		nxtDisplayTextLine(0, "Runtime: %i", averageRuntime);
		nxtDisplayTextLine(1, "Max: %i", driveMaxSpeed);
		nxtDisplayTextLine(2, "Left: %i", driveSpeedLeft);
		nxtDisplayTextLine(3, "Right: %i", driveSpeedRight);
		nxtDisplayTextLine(4, "Arm pitch: %i", servoArmPitchValue);

		wait1Msec(50);

		EndTimeSlice();
	}
}