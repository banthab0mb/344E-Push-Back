#include "EZ-Template/api.hpp"
#include "api.h"
#include "stormlib/api.hpp"

// Drivetrain
extern ez::Drive chassis;
extern ez::tracking_wheel horiz_tracker;
extern ez::tracking_wheel vert_tracker;

// Clock
extern stormlib::clock driverClock;

// LEDs

extern pros::adi::Led led;

extern stormlib::aRGB strand1;
extern stormlib::aRGB strand2;
extern stormlib::aRGB_manager LED_manager;

// Motors
inline pros::Motor conveyor(12);
inline pros::MotorGroup intake({-14, 13});

void move_intake();
