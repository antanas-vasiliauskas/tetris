#include "Inputs.h"

void InputChecker(int Inputs[], GLFWwindow* window)
{
	Key_Exit = glfwGetKey(window, GLFW_KEY_ESCAPE);
	Key_FullScreen = glfwGetKey(window, GLFW_KEY_F11);
	Key_Enter = glfwGetKey(window, GLFW_KEY_ENTER);
	Key_Left = glfwGetKey(window, GLFW_KEY_LEFT);
	Key_Right = glfwGetKey(window, GLFW_KEY_RIGHT);
	Key_A = glfwGetKey(window, GLFW_KEY_A);
	Key_D = glfwGetKey(window, GLFW_KEY_D);
	Key_Up = glfwGetKey(window, GLFW_KEY_UP);
	Key_Down = glfwGetKey(window, GLFW_KEY_DOWN);
	Key_W = glfwGetKey(window, GLFW_KEY_W);
	Key_S = glfwGetKey(window, GLFW_KEY_S);
	Key_Sound = glfwGetKey(window, GLFW_KEY_C);
	Key_Space = glfwGetKey(window, GLFW_KEY_SPACE);
	//=========================================================================================
	if (Key_FullScreen == GLFW_PRESS)
		if (glfwGetPrimaryMonitor() == glfwGetWindowMonitor(window))
		{
			int winwidth, winheight;
			glfwGetWindowSize(window, &winwidth, &winheight);
			glfwSetWindowMonitor(window, NULL, (winwidth - 900) / 2, (winheight - 900) / 2, 900, 900, NULL);
			glViewport(0, 0, 900, 900);
		}
		else
		{
			int count;
			const GLFWvidmode *mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode[count - 1].height, mode[count - 1].width, mode[count - 1].refreshRate);
			int winwidth, winheight;
			glfwGetWindowSize(window, &winwidth, &winheight);
			glViewport((winwidth - winheight) / 2, 0, winheight, winheight);
		}
}
