#pragma once
#include <GLFW/glfw3.h>

#define Key_Exit Inputs[0]
#define Key_FullScreen Inputs[1]
#define Key_Enter Inputs[2]
#define Key_Left Inputs[3]
#define Key_Right Inputs[4]
#define Key_A Inputs[5]
#define Key_D Inputs[6]
#define Key_Up Inputs[7]
#define Key_Down Inputs[8]
#define Key_W Inputs[9]
#define Key_S Inputs[10]
#define Key_Sound Inputs[11]
#define Key_Space Inputs[12]

void InputChecker(int Inputs[], GLFWwindow* window);