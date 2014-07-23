
// The Doppler Effect 2013
// Teleop 2 - Header

#define MAX_AVG_RUNTIME_CNT 3

// Motor constants
#define MOTOR_DRIVE_HIGH_SPEED 100
#define MOTOR_DRIVE_LOW_SPEED 50

// Servo constants
#define SERVO_GRIPPER_OPEN_POS 90
#define SERVO_GRIPPER_CLOSED_POS 0
#define SERVO_ARM_SEGMENT_SPEED 0.5
#define SERVO_ROTATE_SPEED 75

// Button constants
#define BUTTON_R1 6
#define BUTTON_A 2
#define BUTTON_B 3

// Task prototypes
task controller();
task screen();
