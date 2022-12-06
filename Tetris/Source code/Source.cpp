#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "TetrisGame.h"
#include "Inputs.h"
#include <stb_image.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

GLFWimage load_image(const char *path) {
	GLFWimage images[1]; 
	images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);
	//rgba channels glfwSetWindowIcon(window, 1, images); 
	//stbi_image_free(images[0].pixels);
	return images[0];
}

int main(void)
{

	srand(time(NULL));

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(900, 900, "Tetris Ultimate C++ Edition", NULL, NULL);
	GLFWimage image =  load_image("Textures/tetris_logo.png");
	glfwSetWindowIcon(window, 1, &image);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowAspectRatio(window, 1, 1);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Nieznaju" << std::endl;
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	{

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		Shader shader("Shaders/Shaders.shader");
		Renderer renderer;

		TetrisGame game(shader, renderer);

		int Inputs[1000];
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			game.GameLoop(Inputs, window);
			InputChecker(Inputs, window);

			/* Swap front and back buffers */

			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}