#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SOIL.h>
#include <algorithm>
#include <ctime>
#include "asort.h"

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 800;


static void renderMesh()
{
	glLoadIdentity();
	
	glBegin(GL_LINES); 
	glColor4ub(255, 0, 0, 255);
	for (int i = 0; i < counter; i++)
	glVertex3d(result[i].x * 2 - 1, result[i].y * 2 - 1, 0);

	glEnd();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	int n = N;
	Point point[N];
	srand(time(0));
	generatePoints(point, n);

	for (int i = 0; i < n; i++)
		cout << i << " : " << point[i].x << ", " << point[i].y << " " << point[i].colour << "\n";

	findSegment(point, 0, n);

	GLFWwindow* window;

	if (!glfwInit()) {
		fprintf(stderr, "Failed to start glfw\n");
		return -1;
	}

	//Set OpenGL Revision
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//Create Window
	window = glfwCreateWindow(1000, 1000, "OpenGL with GLFW", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to make window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSwapInterval(1);

	static GLfloat vCompColor[4];
	vCompColor[0] = (float) 59 / 255.0f;
	vCompColor[1] = (float) 127 / 255.0f;
	vCompColor[2] = (float) 255 / 255.0f;
	vCompColor[3] = 1.0f;

	while (!glfwWindowShouldClose(window)) {
		double mx, my;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float ratio;

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		ratio = (float)fbWidth / (float)winWidth;
		glViewport(0, 0, fbWidth, fbHeight);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderMesh();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
