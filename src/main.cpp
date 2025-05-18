#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Create lvgl object for the brain banner image
lv_obj_t* brain_banner;
LV_IMG_DECLARE(brain_banner_344E);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
	// Print our branding over your terminal :D
	ez::ez_template_print();

	pros::delay(500);  // Stop the user from doing anything while legacy ports configure

	// Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
	//  - change `back` to `front` if the tracking wheel is in front of the midline
	//  - ignore this if you aren't using a horizontal tracker
	// chassis.odom_tracker_back_set(&horiz_tracker);
	// Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
	//  - change `left` to `right` if the tracking wheel is to the right of the centerline
	//  - ignore this if you aren't using a vertical tracker
	// chassis.odom_tracker_left_set(&vert_tracker);

	// Configure your chassis controls
	chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
	chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
	chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

	// Set the drive to your own constants from autons.cpp!
	default_constants();

	// These are already defaulted to these buttons, but you can change the left/right curve buttons here!
	// chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
	// chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	LED_manager.rainbow();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	/// . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	auton();
}

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {

  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void op_control() {
	
    // Print brain banner image to the screen when driver control starts
    brain_banner = lv_img_create(lv_scr_act());
    lv_img_set_src(brain_banner, &brain_banner_344E);
    lv_obj_set_size(brain_banner, 480, 240);
    lv_obj_align(brain_banner, LV_ALIGN_CENTER, 0, 0);

    // This is preference to what you like to drive on
	chassis.drive_brake_set(MOTOR_BRAKE_COAST);

	while(true) {
		// Gives you some extras to make EZ-Template easier
		ez_template_extras(); 

								   // chassis.opcontrol_tank();  // Tank control
		chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
								   // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
								   // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
								   // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

		// . . .
		// Put more user control code here!
		// . . .

        // functions etc.
		move_intake();

		pros::delay(ez::util::DELAY_TIME);	// This is used for timer calculations! Keep this ez::util::DELAY_TIME
	}
}