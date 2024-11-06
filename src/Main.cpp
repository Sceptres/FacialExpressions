#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif

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
#include "mesh/Mesh.hpp"
#include "mesh/face/FaceMesh.hpp"
#include "entity/face/Face.hpp"
#include "weights/MeshWeight.hpp"

DebugFilter debug;
PPMCapture capturer;

int main() {
	try {
		glfwInit();

		Window window(512, 512, false, "Facial Expressions");
		window.Launch();

		InputHandler inputHandler(window.getGLWindow());
		window.ApplyCloseWindowToInputHandler(inputHandler);
		debug.ApplyToInputHandler(inputHandler);
		capturer.ApplyToInputHandler(inputHandler);

		ShaderProgram shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

		FaceMesh faceBlendMesh;
		faceBlendMesh.GLInit();

		Face face(
			&faceBlendMesh,
			glm::vec3(0, 0, 0),
			1.0f,
			0.0f,
			glm::vec3(0, 0, 0)
		);

		Camera camera(glm::vec3(20, 100, 200), 30.0f, 1.0f, 0.1f, 1000.0f);
		camera.LookAt(glm::vec3(0, 110, 0));

		Color backgroundColor(0.3, 0.4, 0.5, 1.0f);

		int counter = -1;

		inputHandler.AddKeyCallback(GLFW_KEY_UP, false, [&counter, &faceBlendMesh] (GLFWwindow* window) {
			counter = (counter + 1) % 12;
			faceBlendMesh.BlendMesh(counter);
			std::cout << "Current Blend ID: " << counter << std::endl;
		});

		inputHandler.AddKeyCallback(GLFW_KEY_DOWN, false, [&counter, &faceBlendMesh] (GLFWwindow* window) {
			if(counter > 0) {
				counter -= 1;
				faceBlendMesh.BlendMesh(counter % 12);
				
				std::cout << "Current Blend ID: " << counter << std::endl;
			} else if(counter == 0) {
				counter = -1;
				faceBlendMesh.Reset();
				std::cout << "Current Blend is Base Mesh" << std::endl;
			}
		});

		while(!window.ShouldClose()) {
			inputHandler.ProcessInput();

			window.ClearColor(backgroundColor);

			shaderProgram.Activate();
			debug.HandleDebugShader(shaderProgram);
			camera.Apply(shaderProgram);

			face.Render(shaderProgram);

			window.SwapBuffers();

			glfwPollEvents();
		}

		faceBlendMesh.Delete();
		shaderProgram.Delete();
		glfwTerminate();

		return 0;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}
}