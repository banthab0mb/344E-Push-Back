#include "main.h"

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {1, 2, 3},     // Left Chassis Ports (negative port will reverse it!)
    {-4, -5, -6},  // Right Chassis Ports (negative port will reverse it!)

    7,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Uncomment the trackers you're using here!
// - `8` and `9` are smart ports (making these negative will reverse the sensor)
//  - you should get positive values on the encoders going FORWARD and RIGHT
// - `2.75` is the wheel diameter
// - `4.0` is the distance from the center of the wheel to the center of the robot
ez::tracking_wheel horiz_tracker(8, 2.75, 4.0);  // This tracking wheel is perpendicular to the drive wheels
ez::tracking_wheel vert_tracker(9, 2.75, 4.0);   // This tracking wheel is parallel to the drive wheels

///
// Motors and other devices below:
///

// LEDs 
stormlib::aRGB strand1(4, 41); // D
stormlib::aRGB strand2(5, 41); // E

// LED Manager
stormlib::aRGB_manager LED_manager(&strand1, &strand2, nullptr, nullptr,
                                  nullptr, nullptr, nullptr, nullptr);

// Control functions
void move_intake() {
	// <motor name>.move(a number between -127 and 127);
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		intake.move(-127); 
	} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		intake.move(127);
	} else {
		intake.move(0);
	}
}

