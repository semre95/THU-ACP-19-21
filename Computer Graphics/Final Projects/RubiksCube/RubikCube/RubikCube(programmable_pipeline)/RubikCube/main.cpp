/// Anything in it
#include "RubikCube.h"

RubikCube rubikCube;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mode);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// the variables associated with mouse
bool leftmouse = false;
bool rightmouse = false;
bool firstmouse = true; // the first position the mouse in
GLfloat lastX = 400, lastY = 400;

// Window dimensions
GLfloat WIDTH = 800, HEIGHT = 800;
// viewport
GLfloat wid_view = std::fminf(WIDTH, HEIGHT);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
glm::mat4 view(1);
glm::mat4 projection(1);
bool keys[1024];

void myDisplay(GLFWwindow* window, Shader ourShader){
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	
	// Clear the colorbuffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport( (WIDTH-wid_view)/2, (HEIGHT-wid_view)/2, wid_view, wid_view ); // set the viewport; used to change the size
	// Camera/View transformation
	view = camera.GetViewMatrix();
	// Projection
	// projection = glm::ortho( -3.0f*cubeSize, 3.0f*cubeSize, -3.0f*cubeSize, 3.0f*cubeSize, 0.1f, 100.0f ); // use the ortho projection in order to change the size easily
	projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	// Get the uniform locations
	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// rendering the faces
	rubikCube.Render(ourShader);

	// Swap the screen buffers
	glfwSwapBuffers(window);
}

// The MAIN function, from here we start the application and run the game loop
int main(){
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "RubikCube", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // Initialize GLAD to setup the OpenGL Function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

	// Build and compile our shader program
	Shader ourShader("main.vert.glsl", "main.frag.glsl");
	
	ourShader.Use(); // before setting VAO!   
	rubikCube.set_BA_obj(); // set VAO,VBO,EBO

    // Game loop
	while(!glfwWindowShouldClose(window)){
		myDisplay(window, ourShader);
	}

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, width, height);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if(key == GLFW_KEY_Z && action == GLFW_PRESS){
		rubikCube.Track_back();
	}
	if(key >= 0 && key < 1024){
		if(action == GLFW_PRESS)
			keys[key] = true;
		else if(action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mode){
	if(button == GLFW_MOUSE_BUTTON_LEFT){
		if(!rightmouse) {
			switch(action){
			case GLFW_PRESS:
				leftmouse = true;
				rubikCube.Note_state(button);
				break;
			case GLFW_RELEASE:
				leftmouse = false;
				break;
			}
		}
	}else if(button ==  GLFW_MOUSE_BUTTON_RIGHT){
		if(!leftmouse){
			switch(action){
			case GLFW_PRESS:
				rightmouse = true;
				rubikCube.Note_state(button);
				rubikCube.Select_Cube(lastX, lastY, view, projection, camera.Zoom, wid_view, WIDTH, HEIGHT);
				break;
			case GLFW_RELEASE:
				rightmouse = false;
				//rubikCube.RotateFinish(); // finish the rotatation(choose a state)
				rubikCube.Release_Cube(); // release the selected cube
				break;
			}
		}
	}
	
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos){
	if(firstmouse){
		firstmouse = false;
	}else if(leftmouse){
		rubikCube.Mouse_LeftMove(xpos, lastX, ypos, lastY, WIDTH, HEIGHT, view);
	}else if(rightmouse){
		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos; // Reversed	
		rubikCube.Mouse_RightMove(xoffset, yoffset, view, projection, camera.Zoom, wid_view);
	}
	// must note down the mouse position
	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	GLfloat wid_old = wid_view;
	wid_view += yoffset * 20;
	rubikCube.MouseSensitivity *= wid_old / wid_view; 
}