#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];
GLFWwindow* window;

void drawBox(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawcircle(double x0, double y0, double radius);

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawBox(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue) {
	for (int i = i0; i <= i1; i++) {
		drawPixel(i, j0, red, green, blue);
		drawPixel(i, j1, red, green, blue);
	}
	for (int j = j0; j <= j1; j++) {
		drawPixel(i0, j, red, green, blue);
		drawPixel(i1, j, red, green, blue);
	}
}

void drawcircle(double x0, double y0, double radius) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		drawPixel(x0 + x, y0 + y, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 + y, y0 + x, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 - y, y0 + x, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 - x, y0 + y, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 - x, y0 - y, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 - y, y0 - x, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 + y, y0 - x, 0.0f, 0.0f, 0.0f);
		drawPixel(x0 + x, y0 - y, 0.0f, 0.0f, 0.0f);

		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}

/*mother class*/
class GeometricObjectInterface {
public:
	virtual void draw() = 0;
};

class Box {
public:
	void draw() {
		drawBox(120, 100, 180, 170, 1.0f, 1.0f, 0.0f);
	}
};

class Circle {
public:
	void draw() {
		drawcircle(260, 100, 50);
	}
};

template <class T_HOW_TO_DRAW>
class GeometricObject : public GeometricObjectInterface {
public:
	void draw() {
		T_HOW_TO_DRAW draw;
		draw.draw();
	}
};

int main() {
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//white backboard
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
			{
				pixels[(i + width*j) * 3 + 0] = 1.0f;
				pixels[(i + width*j) * 3 + 1] = 1.0f;
				pixels[(i + width*j) * 3 + 2] = 1.0f;
			}

		std::vector<GeometricObjectInterface*> obj_list;

		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);
		for (auto itr : obj_list)
			itr->draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/*std::this_thread::sleep_for(std::chrono::milliseconds(100));*/
	}

	glfwTerminate();
	delete[] pixels; // or you may reuse pixels array 

	return 0;
}