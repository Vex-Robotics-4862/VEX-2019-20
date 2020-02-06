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


	pros::lcd::set_text(1, "Test Bot: Verson 1.5");


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
 void forward_relative(pros::Motor all, double distance) {

 }
//using namespace okapi;
//auto chassis = ChassisControllerFactory::create(Motor(MOTOR_LEFT_FRONT), Motor(MOTOR_RIGHT_FRONT), Motor(MOTOR_LEFT_BACK), Motor(MOTOR_RIGHT_BACK));
void autonomous() {
	//Turning is moving, moving is turning.
	pros::Motor leftB (MOTOR_LEFT_BACK, true);
	pros::Motor rightB (MOTOR_RIGHT_BACK);
	pros::Motor leftF (MOTOR_LEFT_FRONT, true);
	pros::Motor rightF (MOTOR_RIGHT_FRONT);

	pros::Motor tray (MOTOR_TRAY);
	pros::Motor intakeL (INTAKE_LEFT);
	pros::Motor intakeR (INTAKE_RIGHT);
	enum autoType { close_cube, old_auto, five_cube };
	autoType whatAuto = five_cube;

	switch (whatAuto) {
	// leftB.move_relative(350, 96);
	// leftF.move_relative(350, 96);
	// rightB.move_relative(350, 90);
	// rightF.move_relative(350, 90);
	// pros::delay(2000);
	// leftB.move_relative(-90, 96);
	// leftF.move_relative(-90, 96);
	// rightB.move_relative(90, 90);
	// rightF.move_relative(90, 90);
	// pros::delay(2000);
	case close_cube:
	intakeL.move(64); //INTAKE
	intakeR.move(-64);
	pros::delay(200);
	leftB.move_relative(750, 96);
	leftF.move_relative(750, 96);
	rightB.move_relative(750, 96);
	rightF.move_relative(750, 96);
	pros::delay(800);
	intakeL.move(0);
	intakeR.move(0);
	pros::delay(1000);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);


	//chassis.turn_Angle(-850); //negative is forwards; -910 is barely too far
	//260 is 1 tile at low battery
	intakeL.move(-128); //OUTTAKE
	intakeR.move(128);
	pros::delay(1000);
	intakeL.move(0);
	intakeR.move(0);
	pros::delay(1000);
	leftB.move(-48);
	leftF.move(-48);
	rightF.move(-48);
	rightB.move(-48);
	pros::delay(1000);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);
	break;
	// *******
	case five_cube:
	// leftB.move(70);
	// leftF.move(70);
	// rightB.move(70);
	// rightF.move(70);
	leftB.move_relative(3500, 55);
	leftF.move_relative(3500, 55);
	rightB.move_relative(3500, 55);
	rightF.move_relative(3500, 55);
	intakeL.move(128);
	intakeR.move(-128);
	pros::delay(1450);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);
	pros::delay(800);
	intakeL.move(0);
	intakeR.move(0);
	leftB.move_relative(-940, 64);
	leftF.move_relative(-940, 64);
	rightB.move_relative(940, 64);
	rightF.move_relative(940, 64);
	pros::delay(2000);
	leftB.move(70);
	leftF.move(70);
	rightB.move(70);
	rightF.move(70);
	pros::delay(1300);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);
	tray.move_relative(500, 96);
	leftB.move_relative(-450, 96);
	leftF.move_relative(-450, 96);
	rightB.move_relative(-450, 96);
	rightF.move_relative(-450, 96);

	break;
	default:
	leftB.move_relative(750, 96);
	leftF.move_relative(750, 96);
	rightB.move_relative(750, 96);
	rightF.move_relative(750, 96);
	pros::delay(2000);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);

	pros::delay(200);

	//chassis.turn_Angle(-850); //negative is forwards; -910 is barely too far
	//260 is 1 tile at low battery
	intakeL.move(-128); //FULL POWER
	intakeR.move(128);
	pros::delay(1000);
	intakeL.move(0);
	intakeR.move(0);
	pros::delay(2000);
	leftB.move(-48);
	leftF.move(-48);
	rightF.move(-48);
	rightB.move(-48);
	pros::delay(1000);
	leftB.move(0);
	leftF.move(0);
	rightB.move(0);
	rightF.move(0);

	break;
	}
	//chassis.turnAngle(250);
	//chassis.moveDistance(180); //rotate 180 degrees

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
	pros::Motor leftB (MOTOR_LEFT_BACK);
	pros::Motor rightB (MOTOR_RIGHT_BACK);
	pros::Motor leftF (MOTOR_LEFT_FRONT, true);
	pros::Motor rightF (MOTOR_RIGHT_FRONT, true);

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
	int liftDoubleClick = 0;
	int liftTimer = 0;

	while (true) {
		//DRIVE
		switch (drive) {
			case tank:
				moveLeft(left, controller.get_analog(ANALOG_LEFT_Y));
				moveRight(right, controller.get_analog(ANALOG_RIGHT_Y));
				break;
			case left_only:
				/*mag = hypot(controller.get_analog(ANALOG_LEFT_X), controller.get_analog(ANALOG_LEFT_Y)) * 5/3;
				dir = atan2((double)controller.get_analog(ANALOG_LEFT_Y), (double)controller.get_analog(ANALOG_LEFT_X));
				moveLeft(left, round(mag * cos(dir - 0.785))); //1.75 = pi/2
				moveRight(right, round(mag * sin(dir - 0.785)));*/
				break;
			case right_only:
				mag = hypot(controller.get_analog(ANALOG_RIGHT_X), controller.get_analog(ANALOG_RIGHT_Y)) * 1.42; //mult by sqrt(2)
				dir = atan2((double)controller.get_analog(ANALOG_RIGHT_Y), (double)controller.get_analog(ANALOG_RIGHT_X));
				//dir =
				moveLeft(leftB, round(mag * cos(dir - 0.7854))); //0.785 = pi/4; intersect of sin and cos
				moveRight(rightB, round(mag * sin(dir - 0.7854)));
				moveLeft(leftF, round(mag * cos(dir - 0.7854)));
				moveRight(rightF, round(mag * sin(dir - 0.7854)));
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
			if ((tray.get_position()<816.0 || liftDoubleClick > 1) && tray.get_position()<1000.0) {
				if (tray.get_position() > 830.0) {
					liftTimer += 1;
					tray.move(0);
					if (liftTimer > 25) { //50 * 40ms delay = 2 seconds
						tray.move(32);
					}
				} else if (tray.get_position() > 500.0) {
					liftDoubleClick = 3;
					tray.move(71);

				} else {
					liftDoubleClick = 0;
					liftTimer = 0; //RESET lift timer at this point
					tray.move(96);
					if (lift.get_position() < 120.0) {
						lift.move(64);
					}
				}
			} else { //50% power...?
				liftDoubleClick = 1;
				tray.move(0);
			}
		} else if (controller.get_digital(DIGITAL_R2) && tray.get_position()>220.0) {

				tray.move(-64);

		} else {
			tray.move(0);
			if (liftDoubleClick == 1) {
				liftDoubleClick = 2;
			} else if (liftDoubleClick == 3) {
				liftDoubleClick = 0;
			}
		}

		//switch (drive) {
		//	case tank:
				//Use use left/right :OR: buttons
		//		break;
		//	default:

				pros::lcd::set_text(4, std::to_string(tray.get_position()));
				pros::lcd::set_text(5, std::to_string(lift.get_voltage()));
				pros::lcd::set_text(6, std::to_string(lift.get_position()));
				pros::lcd::set_text(7, std::to_string(leftB.get_position()));
				/*if (liftEnabled) {
					//lift.move(controller.get_analog(ANALOG_LEFT_Y)*(4/3));
					if (controller.get_analog(ANALOG_LEFT_Y)>20 && tray.get_position()<615.0) {
						tray.move(controller.get_analog(ANALOG_LEFT_Y)*1.5);}
						liftMovement = liftMovement + controller.get_analog(ANALOG_LEFT_Y);
						if (liftMovement > 3400.0) { //maxLiftMovement
							liftMovement = 3400.0;
						} else if (liftMovement < 100.0) { //minLiftMovement
							liftMovement = 90.0;
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
				if (abs(liftMovement - lift.get_position())> 100.0 && liftMovement != 0.0) { //add && liftEnabled to not force lift down
				lift.move_absolute(liftMovement, 127); //max set at 50% power
				//liftDiff = liftMovement;
				//TODO
			}*/
			if (lift.get_position() < 200.0 && controller.get_analog(ANALOG_LEFT_Y) < 2) {
				//lift.move(-4);
			} else if (abs(controller.get_analog(ANALOG_LEFT_Y)) > 48 && !controller.get_digital(DIGITAL_R1)) {
				lift.set_brake_mode(MOTOR_BRAKE_HOLD);
				lift.move(controller.get_analog(ANALOG_LEFT_Y));
				if (tray.get_position()<570.0) {
					tray.move(controller.get_analog(ANALOG_LEFT_Y) * 1.5);
				}
			} else if (abs(controller.get_analog(ANALOG_LEFT_Y)) < 49) {
				lift.move(0);
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
		if (controller.get_analog(ANALOG_LEFT_X) > 16) {
			intakeL.move(controller.get_analog(ANALOG_LEFT_X)/4);
			intakeR.move(-controller.get_analog(ANALOG_LEFT_X)/4);
		} else if (controller.get_analog(ANALOG_LEFT_X) < -16) {
			intakeL.move(controller.get_analog(ANALOG_LEFT_X)/4);
			intakeR.move(-controller.get_analog(ANALOG_LEFT_X)/4);
		}
		if (controller.get_digital(DIGITAL_L1) && controller.get_digital(DIGITAL_L2)) {
			intakeL.move(-128);
			intakeR.move(128);
		} else if (controller.get_digital(DIGITAL_L1)) {
			intakeL.move(128); //FULL POWER
			intakeR.move(-128);
		} else if (controller.get_digital(DIGITAL_L2)) {
			intakeL.move(-48);
			intakeR.move(48);
		} else if (abs(controller.get_analog(ANALOG_LEFT_X)) < 16) {
			intakeL.move(0);
			intakeR.move(0);
		}




		pros::delay(40);

	}



}
