
// The Doppler Effect 2013-2014
// Teleop V3 Header
// Designed for FTC Block Party 2013-2014

/* -------------------------------------------------- */

// Drive speeds
#define DRIVE_POWER_MAXIMUM 100
#define DRIVE_POWER_PRECISE 60

// Arm pitch speeds
#define ARM_PITCH_POWER_MAXIMUM 75
#define ARM_PITCH_POWER_PRECISE 50

// Elevator speeds
#define ELEVATOR_POWER_MAXIMUM 100
#define ELEVATOR_POWER_PRECISE 75

// Gripper servo states
#define SERVO_ARM_GRIPPER_STATE_IDLE    127
#define SERVO_ARM_GRIPPER_STATE_OPENING 256
#define SERVO_ARM_GRIPPER_STATE_CLOSING 0

// Buttons
#define BUTTON_PRECISION_MODE_1 6
#define BUTTON_PRECISION_MODE_2 6
#define BUTTON_ELEVATOR_UP 1
#define BUTTON_ELEVATOR_DOWN 4
#define BUTTON_GRIPPER_OPEN 3
#define BUTTON_GRIPPER_CLOSE 2

// A threshold to correct the infamous joystick deadband issue
// Any absolute joystick value less than or equal to this value is ignored
#define JOYSTICK_DEADBAND_THRESHOLD 10

// Function prototypes
void initialize();
task main();
task controller();
task gripperMaintain();
