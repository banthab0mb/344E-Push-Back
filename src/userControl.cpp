#include "userControl.h"
#include "robotConfig.h"
#include "ezTemplateExtras.h"
#include "EZ-Template/drive/drive.hpp"
#include "controls.h"

// Create lvgl object for the brain banner image
lv_obj_t* brainBanner;
LV_IMG_DECLARE(brainBanner344E);

void userControl() {

    // Print brain banner image to the screen when driver control starts
    brainBanner = lv_img_create(lv_scr_act());
    lv_img_set_src(brainBanner, &brainBanner344E);
    lv_obj_set_size(brainBanner, 480, 240);
    lv_obj_align(brainBanner, LV_ALIGN_CENTER, 0, 0);

    // This is preference to what you like to drive on
	chassis.drive_brake_set(MOTOR_BRAKE_COAST);

	while(true) {
		// Gives you some extras to make EZ-Template easier
		ezExtras();

								   // chassis.opcontrol_tank();  // Tank control
		chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
								   // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
								   // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
								   // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

		// . . .
		// Put more user control code here!
		// . . .

        // functions etc.
		setIntake();

		pros::delay(ez::util::DELAY_TIME);	// This is used for timer calculations! Keep this ez::util::DELAY_TIME
	}
}