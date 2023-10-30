// Incluimos las librerias necesarias de ROS
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
        // Definimos variables para los puertos del Arduino
#define PIN_VRx A0
#define PIN_VRy A1
#define PIN_SW 2

// State variables
unsigned int xJoystick = 0;
unsigned int yJoystick = 0;
// ROS node handle
ros::NodeHandle nh;
// ROS message and publisher
geometry_msgs::Twist cmd_msg;
ros::Publisher arduino_cmd("cmd_vel", &cmd_msg);
//Publicador para el boton switch
std_msgs::Bool button_pressed;
ros::Publisher boton("button1", &button_pressed);
// Function pre-definition
float linearTransform(float, float, float, float, float);
float linearTransformWithDeadZone(float, float, float, float, float, float,float);

void setup() {
  pinMode(PIN_SW,INPUT_PULLUP);
  nh.initNode();
  nh.advertise(arduino_cmd);
  nh.advertise(boton);
  while(!nh.connected()) {
    nh.spinOnce();
  }
  nh.loginfo("Startup complete!");
}

void loop() {
  // Read data from joystick
  xJoystick = analogRead(PIN_VRx);
  yJoystick = analogRead(PIN_VRy);

  // Scale x value
  float cmd_vel_x = linearTransformWithDeadZone(yJoystick, 0, -1, 500, 520, 1023, 1);


  // Scale y value
  float cmd_vel_rot = linearTransformWithDeadZone(xJoystick, 0, 3, 500, 520, 1023, -3);

  // Send cmd_vel msg
  cmd_msg.linear.x = cmd_vel_x;
  // Send cmd_rot msg
  cmd_msg.angular.z = cmd_vel_rot;
          
  arduino_cmd.publish(&cmd_msg);
  nh.spinOnce();
  // Publicamos el estado del boton
  if (digitalRead(PIN_SW) == 0){
    button_pressed.data = true;
    boton.publish(&button_pressed);
  }else{
    button_pressed.data = false;
    boton.publish(&button_pressed);   
  }
  
  delay(100);  
}

float linearTransform(float x, float x1, float y1, float x2, float y2) {
  float m = (y2 - y1) / (x2 - x1);
  return m * (x - x1) + y1;  
}

float linearTransformWithDeadZone(float x, float x1, float y1, float deadx1, float deadx2, float x2, float y2) {
  if ( x < deadx1 ) {
    return linearTransform(x, x1, y1, deadx1, 0);
  }
  else if ( x > deadx2 ) {
    return linearTransform(x, deadx2, 0, x2, y2);
  }
  else { //(x > deadx1 && x < deadx2)
    return 0;
  }
}