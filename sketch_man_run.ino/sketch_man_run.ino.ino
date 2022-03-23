#include <Stepper.h>
#include <ros.h>
#include <std_msgs/Float32.h>


float man_angle = 0.000;

float gear_ratio = 5.000; 

float motor_step_time = 4.000;

Stepper myStepper(200, 4, 5, 6, 7);

ros::NodeHandle  nh;

//void man_angle_move(float angle){
void man_angle_move(const std_msgs::Float32& msg){
    
    
    float angle = msg.data;

    int arrival_time = 100 ;
    "1/frequency at which signal is published in ms";

    float angle_diff = angle - man_angle;

    float diff_steps = angle_diff * 100 * gear_ratio / M_PI;
    int diff_steps_count = diff_steps;
    Serial.print(" diff_steps ");
    Serial.print(diff_steps);
    

    
    

    float fract_time = arrival_time / abs(diff_steps);
    
    float wait_time = fract_time - motor_step_time;
    Serial.print(" wait_ time (ms) ");
    Serial.print(wait_time);

    if (diff_steps > 0){
          for (int i = 0; i < diff_steps; i++){
              myStepper.step(1);
              Serial.print(" step forward ");
              delay(wait_time);
              
              diff_steps_count = diff_steps_count - 1;
              man_angle = man_angle + 100 * gear_ratio / M_PI;
              "#rospublishmanangle";
          }
    } else if (diff_steps < 0) {
          for (int i = 0; i > diff_steps; i--){
              myStepper.step(-1);
              Serial.print(" step backward ");
              delay(wait_time);
              
              diff_steps_count = diff_steps_count + 1;
              man_angle = man_angle - 100 * gear_ratio / M_PI;
              "rospublishmanangle";
          }
    }

    if (diff_steps_count == 0){
          Serial.print( " here ");
          man_angle = angle;

          return;
    } else{

          return;
    }
}

ros::Subscriber<std_msgs::Float32> subMan("5678/mannequinAngle", &man_angle_move);

  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(subMan);
  "float My_angle = M_PI/25";
  
  "man_angle_move(My_angle)";
  
}

void loop() {
   nh.spinOnce();

}
