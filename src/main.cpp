#include "main.h"
#include "okapi/api.hpp"
#include "math.h"
#define MOTOR_LEFT_BACK 2
#define MOTOR_LEFT_FRONT 1
#define MOTOR_RIGHT_FRONT 3
#define MOTOR_RIGHT_BACK 4
#define MOTOR_TRAY 5
#define MOTOR_LIFT 6
#define INTAKE_LEFT 20
#define INTAKE_RIGHT 19



/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	//If center button is pressed
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::Motor tray_initializer (MOTOR_TRAY, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);


	pros::lcd::set_text(1, "Test Bot: Verson 1.3");


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
 void moveLeft(pros::Motor l, int velocity) {
	l.move(velocity);
	pros::lcd::set_text(2, "LD: " + std::to_string(velocity));
 }
 void moveRight(pros::Motor r, int velocity) {
	r.move(-velocity);
	pros::lcd::set_text(3, "RD: " + std::to_string(velocity));
 }
using namespace okapi;
auto chassis = ChassisControllerFactory::create({MOTOR_LEFT_FRONT, MOTOR_LEFT_BACK}, {MOTOR_RIGHT_FRONT, MOTOR_RIGHT_BACK});
void autonomous() {
	//pros::Motor left_back (MOTOR_LEFT_BACK);
	//pros::Motor left_front (MOTOR_LEFT_FRONT);
	//pros::Motor right_back (MOTOR_RIGHT_BACK);
	//pros::Motor right_front (MOTOR_RIGHT_FRONT);
	pros::Motor tray (MOTOR_TRAY);
	chassis.moveDistance(5.0); //positive is FORWARDS
	chassis.waitUntilSettled();
	chassis.turnAngle(90.0);
	chassis.waitUntilSettled();
	chassis.moveDistance(1.0);
	chassis.waitUntilSettled();
	chassis.turnAngle(90.0);
	chassis.waitUntilSettled();
	chassis.moveDistance(-2.0);
	chassis.waitUntilSettled();
	chassis.turnAngle(90.0);
	chassis.waitUntilSettled();
	chassis.moveDistance(1.0);
	chassis.waitUntilSettled();
	chassis.turnAngle(90.0);
	chassis.waitUntilSettled();
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
	pros::Motor left (MOTOR_LEFT_BACK, MOTOR_LEFT_FRONT);
	pros::Motor right (MOTOR_RIGHT_BACK, MOTOR_RIGHT_FRONT);
	pros::Motor tray (MOTOR_TRAY); //Uses initialization above; 100 RPM
	pros::Motor lift (MOTOR_LIFT);
	pros::Motor intakeL (INTAKE_LEFT);
	pros::Motor intakeR (INTAKE_RIGHT);
	//pros::Motor intake0 (INTAKE_LEFT, INTAKE_RIGHT); Example of what not to do

	pros::Controller controller(pros::E_CONTROLLER_MASTER);


	enum driveType { tank, right_only, left_only };
	driveType drive = right_only;
	double mag = 0.0; //magnitude, 0.0 to 1.0
	double dir = 0.0; //direction, 0 to 2pi
	double liftMovement = 120.0;
	double liftDiff = 0.0;
	bool liftEnabled = false;
	while (true) {
		//DRIVE
		switch (drive) {
			case tank:
				moveLeft(left, controller.get_analog(ANALOG_LEFT_Y));
				moveRight(right, controller.get_analog(ANALOG_RIGHT_Y));
				break;
			case left_only:
				mag = hypot(controller.get_analog(ANALOG_LEFT_X), controller.get_analog(ANALOG_LEFT_Y)) * 5/3;
				dir = atan2((double)controller.get_analog(ANALOG_LEFT_Y), (double)controller.get_analog(ANALOG_LEFT_X));
				moveLeft(left, round(mag * cos(dir - 0.785))); //1.75 = pi/2
				moveRight(right, round(mag * sin(dir - 0.785)));
				break;
			case right_only:
				mag = hypot(controller.get_analog(ANALOG_RIGHT_X), controller.get_analog(ANALOG_RIGHT_Y)) * 5/3;
				dir = atan2((double)controller.get_analog(ANALOG_RIGHT_Y), (double)controller.get_analog(ANALOG_RIGHT_X));
				moveLeft(left, round(mag * cos(dir - 0.785))); //1.75 = pi/2
				moveRight(right, round(mag * sin(dir - 0.785)));

				break;
		}
		if (controller.get_digital(DIGITAL_A)) {
			//drive = tank;
		}
		if (controller.get_digital(DIGITAL_B)) {
			drive = right_only;
		}
		//TRAY
		if (controller.get_digital(DIGITAL_R1)) {
			if (true/*tray.get_position()<1000.0*/) {
				tray.move(64);
			}; //50% power...?
		} else if (controller.get_digital(DIGITAL_R2)) {
			tray.move(-64);
		} else {
			tray.move(0);
		}

		//switch (drive) {
		//	case tank:
				//Use use left/right :OR: buttons
		//		break;
		//	default:

				pros::lcd::set_text(4, std::to_string(tray.get_position()));
				pros::lcd::set_text(5, std::to_string(lift.get_voltage()));
				pros::lcd::set_text(6, std::to_string(liftMovement));

				if (liftEnabled) {
					liftMovement = liftMovement + controller.get_analog(ANALOG_LEFT_Y);
					if (controller.get_analog(ANALOG_LEFT_Y)>20 && tray.get_position()<500.0) {
						tray.move(controller.get_analog(ANALOG_LEFT_Y)*1.8);}
						if (liftMovement > 1800.0) { //maxLiftMovement
							liftMovement = 1800.0;
						} else if (liftMovement < 100.0) { //minLiftMovement
							liftMovement = 100.0;
							liftEnabled = false;
							lift.move(0);
					}
				} else {
					if (controller.get_analog(ANALOG_LEFT_Y) > 32) {
						liftEnabled = true;
						liftMovement = 110.0;
					}
				}
				//pros::lcd::set_text(5, "LIFT: " + std::to_string(liftMovement));
				if (abs(liftMovement - liftDiff)> 100.0) {
				lift.move_absolute(liftMovement, 64); //max set at 50% power
				liftDiff = liftMovement;

			}

			if (controller.get_digital((DIGITAL_UP))) {
				//lift.move_absolute(1800, 64);
				if (tray.get_position()<1000.0) {
					tray.move(64);
				}
			}
		//		break;
		//}
		//Move to position from left joystick at max speed 127

		//INTAKE
		if (controller.get_digital(DIGITAL_L1)) {
			intakeL.move(128); //FULL POWER
			intakeR.move(-128);
		} else if (controller.get_digital(DIGITAL_L2)) {
			intakeL.move(-128);
			intakeR.move(128);
		} else {
			intakeL.move(0);
			intakeR.move(0);
		}
		if (controller.get_analog(ANALOG_LEFT_X) > 16) {
			intakeL.move(controller.get_analog(ANALOG_LEFT_X)/4);
			intakeR.move(-controller.get_analog(ANALOG_LEFT_X)/4);
		} else if (controller.get_analog(ANALOG_LEFT_X) < -16) {
			intakeL.move(controller.get_analog(ANALOG_LEFT_X)/4);
			intakeR.move(-controller.get_analog(ANALOG_LEFT_X)/4);
		}



		pros::delay(40);
	}



}
