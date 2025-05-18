#include "main.h"

using namespace pros;

// Team colors
// red = "FF0000"
// blue = "0000FF"

// Auton selector constructor
rd::Selector selector = rd::Selector({
    {"Move Forward", move_forward},
    {"Drive and Turn", drive_and_turn},
    {"Red Left", red_left},
});

// Sets some ez stuff
// Starts the auton selector.
// Shouldn't need anything else in here as the selector takes care of calls.
void auton() {
    chassis.pid_targets_reset();				// Resets PID targets to 0
	chassis.drive_imu_reset();					// Reset gyro position to 0
	chassis.drive_sensor_reset();				// Reset drive sensors to 0
	chassis.odom_xyt_set(0_in, 0_in, 0_deg);	// Set the current position, you can start at a specific position with this
	chassis.drive_brake_set(E_MOTOR_BRAKE_COAST);	// Set motors to hold.  This helps autonomous consistency
    
    // Starts auton selector
    selector.run_auton();
}

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

///
// Auton functions
///

void move_forward() { 
    // Drives forward 24 inches
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();
}

void drive_and_turn() {
    // Drive and turn test
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_turn_set(-45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_turn_set(0_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();
}

void red_left() {
    LED_manager.setColor(0xFF0000);
}

void blue_left() {
    LED_manager.setColor(0x0000FF);
}

// Feel free to remove these examples. thought they were good to have for reference

// See other examples in the EZ-Template example project https://github.com/EZ-Robotics/EZ-Template/blob/main/EZ-Template-Example-Project/src/autons.cpp

 
///
// Interference example
///
void tug(int attempts) {
	for(int i = 0; i < attempts - 1; i++) {
		// Attempt to drive backward
		printf("i - %i", i);
		chassis.pid_drive_set(-12_in, 127);
		chassis.pid_wait();

		// If failsafed...
		if(chassis.interfered) {
			chassis.drive_sensor_reset();
			chassis.pid_drive_set(-2_in, 20);
			pros::delay(1000);
		}
		// If the robot successfully drove back, return
		else {
			return;
		}
	}
}

// If there is no interference, the robot will drive forward and turn 90
// degrees. If interfered, the robot will drive forward and then attempt to
// drive backward.
void interfered_example() {
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	if(chassis.interfered) {
		tug(3);
		return;
	}

	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
}