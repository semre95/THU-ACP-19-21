#include <iostream>
#include <string>
// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "shader.h"

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void DrawPic(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Shader ourShader, GLuint vao, GLuint ebo, GLuint vbo);
void do_movement();
void do_rotate();
void choose_model(GLboolean &flag);

// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat yaw = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat fov = 45.0f;

// Deltatime
GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;      // Time of last frame

bool keys[1024];
glm::mat4 model(1);

int main() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Homework1", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// Initialize GLAD to setup the OpenGL Function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Build and compile our shader program
	Shader ourShader1("hw1.vert1.glsl", "hw1.frag1.glsl");
	Shader ourShader2("hw1.vert1.glsl", "hw1.frag2.glsl");
    Shader ourShader3("hw1.vert1.glsl", "hw1.frag3.glsl");


	// Loading data
	std::string s;
	std::string head;
	GLfloat vertex[3030];
	GLushort face1[6066];
	int i = 3, j = 0;

	std::ifstream ifs("eight.uniform.obj");

	while (std::getline(ifs, s))
	{
		if (s[0] == 'v') //vertex
		{
			std::istringstream sin(s);
			sin >> head >> vertex[i] >> vertex[i + 1] >> vertex[i + 2];
			i += 3;
		}
		else if (s[0] == 'f') //face
		{
			std::istringstream sin(s);
			sin >> head >> face1[j] >> face1[j + 1] >> face1[j + 2];
			j += 3;
		}
	}

	GLuint vao1, ebo1, vbo1;
	glGenVertexArrays(1, &vao1);
	glGenBuffers(1, &ebo1);
	glGenBuffers(1, &vbo1);

	glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face1), face1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLboolean flag = false;			//Used in function choose_model
	while (!glfwWindowShouldClose(window))
	{

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();
		do_rotate();
		choose_model(flag);
		

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Camera/View transformation
		glm::mat4 view(1);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		// Projection
		glm::mat4 projection(1);
		projection = glm::perspective(glm::radians(fov), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		if (keys[GLFW_KEY_4])
			flag = true;

		if (flag)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			DrawPic(model, view, projection, ourShader2, vao1, ebo1, vbo1);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			DrawPic(model, view, projection, ourShader1, vao1, ebo1, vbo1);

		}
		else

        if (keys[GLFW_KEY_C]){
            DrawPic(model, view, projection, ourShader3, vao1, ebo1, vbo1);
        }
			DrawPic(model, view, projection, ourShader1, vao1, ebo1, vbo1);

		glfwSwapBuffers(window);
	}	

	glDeleteVertexArrays(1, &vao1);
	glDeleteBuffers(1, &vbo1);
	glDeleteBuffers(1, &ebo1);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, width, height);
}

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 2.0f * deltaTime;
	if (keys[GLFW_KEY_EQUAL])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_MINUS])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraUp;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraUp;
}

void do_rotate()
{
	if (keys[GLFW_KEY_UP])
		model = glm::rotate(model, glm::radians(55.0f * deltaTime), glm::vec3(1.0f, 0.0f, 0.0f));
	if (keys[GLFW_KEY_DOWN])
		model = glm::rotate(model, glm::radians(-55.0f * deltaTime), glm::vec3(1.0f, 0.0f, 0.0f));
	if (keys[GLFW_KEY_RIGHT])
		model = glm::rotate(model, glm::radians(55.0f * deltaTime), glm::vec3(0.0f, 0.0f, 1.0f));
	if (keys[GLFW_KEY_LEFT])
		model = glm::rotate(model, glm::radians(-55.0f * deltaTime), glm::vec3(0.0f, 0.0f, 1.0f));
	if (keys[GLFW_KEY_Z] )
		model = glm::rotate(model, glm::radians(-55.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
	if (keys[GLFW_KEY_X])
		model = glm::rotate(model, glm::radians(55.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));

}

void choose_model(GLboolean &flag)
{

	if (keys[GLFW_KEY_1])
	{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		flag = false;

	}

	if (keys[GLFW_KEY_2])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		flag = false;

	}

	if (keys[GLFW_KEY_3])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		flag = false;

	}
}

void DrawPic(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Shader ourShader, GLuint vao, GLuint ebo, GLuint vbo)
{
	ourShader.Use();

	// Get the uniform locations
	GLint modelLoc1 = glGetUniformLocation(ourShader.Program, "model");
	GLint viewLoc1 = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc1 = glGetUniformLocation(ourShader.Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc1, 1, GL_FALSE, glm::value_ptr(projection));


	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6066, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


