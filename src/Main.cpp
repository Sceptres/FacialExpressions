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

DebugFilter debug; // The debug filter that renders shapes as lines
PPMCapture capturer; // Captures the contents of the window as a PPM

int main() {
	try {
		glfwInit();

		// Create and startup window
		Window window(512, 512, false, "Facial Expressions");
		window.Launch();

		// Input handler that processes clicks of registered keys
		InputHandler inputHandler(window.getGLWindow());
		window.ApplyCloseWindowToInputHandler(inputHandler);
		debug.ApplyToInputHandler(inputHandler);
		capturer.ApplyToInputHandler(inputHandler);

		// Load shader program from the disk
		ShaderProgram shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

		// The face blend mesh
		FaceMesh faceBlendMesh;
		faceBlendMesh.GLInit();

		Face face(
			&faceBlendMesh,
			glm::vec3(0, 0, 0),
			1.0f,
			0.0f,
			glm::vec3(0, 0, 0)
		);

		// Setup the camera
		Camera camera(glm::vec3(20, 100, 200), 30.0f, 1.0f, 0.1f, 1000.0f);
		camera.LookAt(glm::vec3(0, 110, 0));

		// Background color of the window
		Color backgroundColor(0.3, 0.4, 0.5, 1.0f);

		// A counter for the blend mesh id [0. 11]
		int counter = -1;

		// Register incrementing counter on up key click
		inputHandler.AddKeyCallback(GLFW_KEY_UP, false, [&counter, &faceBlendMesh] (GLFWwindow* window) {
			counter = (counter + 1) % 12;
			faceBlendMesh.BlendMesh(counter);
			std::cout << "Current Blend ID: " << counter << std::endl;
		});

		// Register decrementing counter on down key click
		inputHandler.AddKeyCallback(GLFW_KEY_DOWN, false, [&counter, &faceBlendMesh] (GLFWwindow* window) {
			if(counter > 0) { // Is the blend mesh id one of the blend meshes and not the base mesh?
				counter -= 1;
				faceBlendMesh.BlendMesh(counter % 12);
				
				std::cout << "Current Blend ID: " << counter << std::endl;
			} else if(counter == 0) { // Is the user going back to the face mesh?
				counter = -1;
				faceBlendMesh.Reset();
				std::cout << "Current Blend is Base Mesh" << std::endl;
			}
		});

		while(!window.ShouldClose()) {
			// Process user input into the window
			inputHandler.ProcessInput();

			// Set background color of the window
			window.ClearColor(backgroundColor);

			// Activate shader program
			shaderProgram.Activate();
			
			// Send info to shader
			debug.HandleDebugShader(shaderProgram);
			camera.Apply(shaderProgram);

			// Render the face
			face.Render(shaderProgram);

			// Swap back and front buffers
			window.SwapBuffers();

			// Poll keyboard input
			glfwPollEvents();
		}

		// Delete face mesh VAO and VBO
		faceBlendMesh.Delete();

		// Delete shader program
		shaderProgram.Delete();
		glfwTerminate();

		return 0;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}
}