#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ppm/PPMCapture.hpp"
#include "buffer/VBO/VBO.hpp"
#include "buffer/EBO/EBO.hpp"
#include "array/VAO.hpp"
#include "shader/ShaderProgram.hpp"
#include "camera/Camera.hpp"
#include "input/InputHandler.hpp"
#include "debug/DebugFilter.hpp"
#include "window/Window.hpp"
#include "color/Color.hpp"

DebugFilter debug;
PPMCapture capturer;

int main() {
	try {
		glfwInit();

		Window window(1024, 576, false, "Solar Simulation");
		window.Launch();

		InputHandler inputHandler(window.getGLWindow());
		window.ApplyCloseWindowToInputHandler(inputHandler);
		debug.ApplyToInputHandler(inputHandler);
		capturer.ApplyToInputHandler(inputHandler);

		ShaderProgram shaderProgram("shaders/default.vert", "shaders/default.frag");

		VAO vao;
		vao.Bind();

		vao.Unbind();

		Camera camera(glm::vec3(30, 20, 90), 45.0f, 16.0/9.0, 0.1f, 1000.0f);

		Color backgroundColor(0.3, 0.4, 0.5, 1.0f);

		while(!window.ShouldClose()) {
			inputHandler.ProcessInput();

			window.ClearColor(backgroundColor);

			shaderProgram.Activate();
			debug.HandleDebugShader(shaderProgram);
			camera.Apply(shaderProgram);

			vao.Bind();

			vao.Unbind();

			window.SwapBuffers();

			glfwPollEvents();
		}

		vao.Delete();
		shaderProgram.Delete();
		glfwTerminate();

		return 0;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}
}