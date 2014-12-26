#include "precompiled.hpp"

#include "scene.hpp"
#include "graphics/renderer.hpp"
#include "graphics/camera.hpp"
#include "graphics/shader.hpp"
#include "input/input.hpp"

int main()
{
	const int FRAME_RATE = 60;
	const float FRAME_TIME = 1.0f / FRAME_RATE;

	if (!glfwInit())
	{
		printf("Failed to initialize GLFW.\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "drill", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW.\n");
		return 1;
	}

	Input::Initialize(window);
	Shader::Initialize();

	Scene scene;
	Renderer renderer = Renderer(&scene.GetCamera());

	double time_last = glfwGetTime();
	double time_current = time_last;
	double frame_time_counter = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		//
		// Update
		//

		glfwPollEvents();

		time_last = time_current;
		time_current = glfwGetTime();
		double dt = time_current - time_last;

		frame_time_counter += dt;

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		scene.Update(dt);

		//
		// Render
		//

		if (frame_time_counter >= FRAME_TIME)
		{
			// Reset the frame time counter.
			frame_time_counter = 0;

			renderer.Prepare();
			scene.Draw(renderer.GetSpriteBatch(), renderer.CalculateViewportBounds());
			renderer.Cleanup();

			glfwSwapBuffers(window);
		}
	}

	glfwTerminate();

	return 0;
}
