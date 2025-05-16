#include "controls.h"
#include "robotConfig.h"

void setIntake() {
	// <motor name>.move(a number between -127 and 127);
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		intake.move(-127); 
	} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		intake.move(127);
	} else {
		intake.move(0);
	}
}