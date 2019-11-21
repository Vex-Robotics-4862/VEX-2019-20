#include "main.h"
#define MOTOR_LEFT_BACK 2
#define MOTOR_LEFT_FRONT 1
#define MOTOR_RIGHT_FRONT 3
#define MOTOR_RIGHT_BACK 4
#define MOTOR_TRAY 5
#define MOTOR_LIFT 6

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Middle button toggled");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Test Bot: Verson 0.1");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
 void moveLeft(pros::Motor lb, pros::Motor lf, int velocity) {
	lb.move(-velocity);
	lf.move(-velocity);
 }
 void moveRight(pros::Motor rb, pros::Motor rf, int velocity) {
	rb.move(velocity);
	rf.move(velocity);
 }
void autonomous() {
	pros::Motor left_back (MOTOR_LEFT_BACK);
	pros::Motor left_front (MOTOR_LEFT_FRONT);
	pros::Motor right_back (MOTOR_RIGHT_BACK);
	pros::Motor right_front (MOTOR_RIGHT_FRONT);
	pros::Motor tray (MOTOR_TRAY);





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

void opcontrol() {
	pros::Motor left_back (MOTOR_LEFT_BACK);
  pros::Motor left_front (MOTOR_LEFT_FRONT);
	pros::Motor right_back (MOTOR_RIGHT_BACK);
  pros::Motor right_front (MOTOR_RIGHT_FRONT);
	pros::Motor tray (MOTOR_TRAY);

	pros::Controller controller(pros::E_CONTROLLER_MASTER);


	enum driveType { tank, right_only, left_only };
	driveType drive = left_only;
	double mag = 0.0; //magnitude, 0.0 to 1.0
	double dir = 0.0; //direction, 0 to 2pi
	while (true) {
		switch (drive) {
			case tank:
				moveLeft(left_back, left_front, controller.get_analog(ANALOG_LEFT_Y));
				moveRight(right_back, right_front, controller.get_analog(ANALOG_RIGHT_Y));
				break;
			case left_only:
				mag = hypot(controller.get_analog(ANALOG_LEFT_X), controller.get_analog(ANALOG_LEFT_Y));
				dir = atan(controller.get_analog(ANALOG_LEFT_Y)/controller.get_analog(ANALOG_LEFT_X));
				moveLeft(left_back, left_front, mag * cos(dir));
				moveRight(right_back, right_front, mag * sin(dir));
				//Using trigonometric ratios gives us at most -sqrt(2) against +sqrt(2)
				//So, turning could be made more powerful than this
				break;
			case right_only:
				mag = hypot(controller.get_analog(ANALOG_RIGHT_X), controller.get_analog(ANALOG_RIGHT_Y));
				dir = atan(controller.get_analog(ANALOG_RIGHT_Y)/controller.get_analog(ANALOG_RIGHT_X));
				moveLeft(left_back, left_front, mag * cos(dir));
				moveRight(right_back, right_front, mag * sin(dir));
				break;
		}

		if (controller.get_digital(DIGITAL_A)) {
			drive = tank;
		}
		if (controller.get_digital(DIGITAL_R1)) {
			tray.move(96); //At 32/128 = 25% power...?
		} else if (controller.get_digital(DIGITAL_R2)) {
			tray.move(-96);
		} else {
			tray.move(0);
		}


		pros::delay(20);
	}



}
