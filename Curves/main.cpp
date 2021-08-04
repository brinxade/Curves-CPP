#include<glad/glad.h>
#include<glfw/glfw3.h>
#include"CatmullRom.h"

/*
A struct to hold a key state, to enable one-time-press behaviour 
instead of continuous polling in each render loop iteration
*/
struct Key
{
	bool pressed = false;
	bool ready = true;
};

int main()
{
	// Initialize GLFW Window
	glfwInit();
	GLFWwindow* win = glfwCreateWindow(500, 500, "Curves", nullptr, nullptr);
	glfwMakeContextCurrent(win);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Set Projection Matrix or (define a coordinate system)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	// Toggling keyboard keys being used
	struct Key key_x, key_z;
	float speed = 0.2f;
	bool isLooped = true;

	// Control points for curve
	int selected_point = 0;
	std::vector<Point2d> points = {
		{50, 250}, {100, 250}, {150, 250}, {200, 250}, {250, 250}, {300, 250}, {350, 250}, {400, 250}, {450, 250}
	};

	// Render Loop
	while (!glfwWindowShouldClose(win))
	{
		// Set background color and clear the color buffer
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		// Define point size and color for each point on the curve
		glPointSize(2);
		glColor3f(1, 1, 1);

		// Draw points on the curve
		glBegin(GL_POINTS);
		for (float t = 0.0f; t < (float)points.size() - (isLooped?0:3); t += 0.05f)
		{
			Point2d pt = CatmullRom::getPointOnCurve(points, t, isLooped);
			glVertex2f(pt.x, pt.y);
		}
		glEnd();

		// Draw control points with bigger point size
		glPointSize(10);
		glBegin(GL_POINTS);
			for (int i = 0; i < points.size(); i++)
			{
				Point2d pt = points[i];
				glVertex2f(pt.x, pt.y);
			}

			// Draw currently selected point with a different color
			glColor3f(1, 0, 0);
			Point2d pt = points[selected_point];
			glVertex2f(pt.x, pt.y);
		glEnd();


		// Key Handling to switch between selected points - one-time-press key state
		if ((glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS))
		{
			if (key_x.ready)
			{
				++selected_point;
				if (selected_point > points.size() - 1)
					selected_point = 0;

				key_x.ready = false;
				key_x.pressed = true;
			}
		}
		else
		{
			key_x.ready = true;
		}

		if ((glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS))
		{
			if (key_z.ready)
			{
				--selected_point;
				if (selected_point < 0)
					selected_point = points.size() - 1;

				key_z.ready = false;
				key_z.pressed = true;
			}
		}
		else
		{
			key_z.ready = true;
		}
		
		// Key Handling to move the control points and switch between looping modes - continuous key state polling
		if ((glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS))
			isLooped = false;
		if ((glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS))
			isLooped = true;
		if ((glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS))
			points[selected_point].y += speed;
		if ((glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS))
			points[selected_point].y -= speed;
		if ((glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS))
			points[selected_point].x += speed;
		if ((glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS))
			points[selected_point].x -= speed;

		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	return 0;
}