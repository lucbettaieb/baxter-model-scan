/*
 * merry_demo
 *
 * Copyright (c) 2015, Luc Bettaieb
 * BSD Licensed
 */

#include "model_acquisition/baxter_interface.h"

#include <ros/ros.h>
#include <std_msgs/UInt32.h>

ros::Subscriber g_cmd_sub;

BaxterInterface* baxter;

void reset()
{
  // 'left_e0', 'left_e1', 'left_s0', 'left_s1', 'left_w0', 'left_w1', 'left_w2'
  Vectorq7x1 vec_resetPose;
  vec_resetPose(2, 0) = 0.0;
  vec_resetPose(3, 0) = 0.0;
  vec_resetPose(0, 0) = 0.0;
  vec_resetPose(1, 0) = 0.0;
  vec_resetPose(4, 0) = 0.0;
  vec_resetPose(5, 0) = 0.0;
  vec_resetPose(6, 0) = 0.0;

  baxter->goToPose(vec_resetPose, 0);
}

void wave()
{
  Vectorq7x1 vec_startWavePose;
  vec_startWavePose(2, 0) = 0.0;
  vec_startWavePose(3, 0) = 0.0;
  vec_startWavePose(0, 0) = 0.0;
  vec_startWavePose(1, 0) = 0.0;
  vec_startWavePose(4, 0) = 0.0;
  vec_startWavePose(5, 0) = 0.0;
  vec_startWavePose(6, 0) = 0.0;

  Vectorq7x1 vec_leftWavePose;
  vec_leftWavePose(2, 0) = 0.0;
  vec_leftWavePose(3, 0) = 0.0;
  vec_leftWavePose(0, 0) = 0.0;
  vec_leftWavePose(1, 0) = 0.0;
  vec_leftWavePose(4, 0) = 0.0;
  vec_leftWavePose(5, 0) = 0.0;
  vec_leftWavePose(6, 0) = 0.0;

  Vectorq7x1 vec_rightWavePose;
  vec_rightWavePose(2, 0) = 0.0;
  vec_rightWavePose(3, 0) = 0.0;
  vec_rightWavePose(0, 0) = 0.0;
  vec_rightWavePose(1, 0) = 0.0;
  vec_rightWavePose(4, 0) = 0.0;
  vec_rightWavePose(5, 0) = 0.0;
  vec_rightWavePose(6, 0) = 0.0;

  baxter->goToPose(vec_startWavePose, 0);

  baxter->goToPose(vec_leftWavePose, 0);
  baxter->goToPose(vec_rightWavePose, 0);

  baxter->goToPose(vec_leftWavePose, 0);
  baxter->goToPose(vec_rightWavePose, 0);

  reset();
}

void nod()
{


}

void hug()
{
  Vectorq7x1 vec_startHugPose;
  vec_startHugPose(2, 0) = 0.0;
  vec_startHugPose(3, 0) = 0.0;
  vec_startHugPose(0, 0) = 0.0;
  vec_startHugPose(1, 0) = 0.0;
  vec_startHugPose(4, 0) = 0.0;
  vec_startHugPose(5, 0) = 0.0;
  vec_startHugPose(6, 0) = 0.0;

  Vectorq7x1 vec_closeHugPose;
  vec_closeHugPose(2, 0) = 0.0;
  vec_closeHugPose(3, 0) = 0.0;
  vec_closeHugPose(0, 0) = 0.0;
  vec_closeHugPose(1, 0) = 0.0;
  vec_closeHugPose(4, 0) = 0.0;
  vec_closeHugPose(5, 0) = 0.0;
  vec_closeHugPose(6, 0) = 0.0;


  baxter->goToPose(vec_startHugPose, 0);
  baxter->goToPose(vec_closeHugPose, 0);
  baxter->goToPose(vec_startHugPose, 0);
  
  reset();
}

void moveArm()
{
  Vectorq7x1 vec_startMoveArmPose;
  vec_startMoveArmPose(2, 0) = 0.0;
  vec_startMoveArmPose(3, 0) = 0.0;
  vec_startMoveArmPose(0, 0) = 0.0;
  vec_startMoveArmPose(1, 0) = 0.0;
  vec_startMoveArmPose(4, 0) = 0.0;
  vec_startMoveArmPose(5, 0) = 0.0;
  vec_startMoveArmPose(6, 0) = 0.0;

  Vectorq7x1 vec_altMoveArmPose;
  vec_altMoveArmPose(2, 0) = 0.0;
  vec_altMoveArmPose(3, 0) = 0.0;
  vec_altMoveArmPose(0, 0) = 0.0;
  vec_altMoveArmPose(1, 0) = 0.0;
  vec_altMoveArmPose(4, 0) = 0.0;
  vec_altMoveArmPose(5, 0) = 0.0;
  vec_altMoveArmPose(6, 0) = 0.0;

  baxter->goToPose(vec_startMoveArmPose, 0);
  baxter->goToPose(vec_altMoveArmPose, 0);
  baxter->goToPose(vec_startMoveArmPose, 0);
  baxter->goToPose(vec_altMoveArmPose, 0);
  baxter->goToPose(vec_startMoveArmPose, 0);
  baxter->goToPose(vec_altMoveArmPose, 0);
  

  reset();
}

void alexaCodeCB(const std_msgs::UInt32& cmd_msg)
{
  uint cmd = cmd_msg.data;

  switch(cmd)
  {
    case 0: reset();
    case 1: wave();
    case 2: nod();
    case 3: hug();
    case 4: moveArm();
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "merry_demo");
  ros::NodeHandle nh;

  g_cmd_sub = nh.subscribe("/Alexa_codes", 1, &alexaCodeCB);

  baxter = new BaxterInterface(nh);

  ros::spin();
}