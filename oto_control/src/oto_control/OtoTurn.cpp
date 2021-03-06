#include <oto_control/OtoController.h>

#include <string>
#include <math.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

using namespace std;

OtoController::TurnState::TurnState()
{

    ROS_INFO("Moving to Turn State");
}

bool OtoController::TurnState::initialize(OtoController* controller){
    parent_controller = controller;
    init_yaw = parent_controller->yaw;
    final_yaw = parent_controller->yaw - (M_PI / 2);

    bool success = true;
    ROS_INFO("Initialized Turn State");
    return success;
}

void OtoController::TurnState::turn(){
	 init_yaw = parent_controller->turn_init_yaw;
     final_yaw = parent_controller->turn_init_yaw - deg_to_rad(80);	//this parameter is the rough angle to track the imu through
	 sensor_interpret();
}

void OtoController::TurnState::sensor_interpret(){
	if (parent_controller->distance_plant_front > (parent_controller->cfg.min_turn_distance)){
		motor_command.joint_name = "drive";
		//motor_command.position = MAX_SPEED_PW_F * 0.5 * parent_controller->speed;
    	motor_command.position = 0.0;
    	parent_controller->publish_motor_command(motor_command);

		motor_command.joint_name = "steering";
    	motor_command.position = deg_to_rad(-45.0);
    	parent_controller->publish_motor_command(motor_command);
	}
	else{
		//set state back to cruise
		parent_controller->state = CRUISE;
	}
	/*
	//check imu for a rough estimate of our progress through turn
	if (parent_controller->yaw <= final_yaw){

		//start checking ir sensor for fine angle measurement
		if ((parent_controller->distance_plant_left <= infinity_threshold) && (parent_controller->distance_plant_right <= infinity_threshold)){
			if (abs(parent_controller->distance_plant_left - parent_controller->distance_plant_right) < parallel_threshold){
				//we are parallel(ish) to a wall
				parent_controller->state = CRUISE;
				ROS_INFO("ir trigger");
			}
		}
	}

	//turning control, could modify to use pid if needed
	if (parent_controller->distance_plant_right > infinity_threshold){
		//TURN SLOWER not really sure what to modify here

		motor_command.joint_name = "steering";
		motor_command.position = deg_to_rad(-10);//slower when needed
		parent_controller->publish_motor_command(motor_command);

	}
	else if(parent_controller->distance_plant_left < parent_controller->distance_plant_right){
		motor_command.joint_name = "steering";
		motor_command.position = deg_to_rad(12);//overshoot, turn back
		parent_controller->publish_motor_command(motor_command);
	}
	else{
		motor_command.joint_name = "steering";
		motor_command.position = deg_to_rad(-14);//default case is "perfect turn"
		parent_controller->publish_motor_command(motor_command);
	}
	*/

}

OtoController::TurnState::~TurnState()
{
    ROS_INFO("Leaving Turn State");
}
