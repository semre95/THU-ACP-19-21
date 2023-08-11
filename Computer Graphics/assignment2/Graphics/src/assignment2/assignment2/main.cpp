// Std. Includes
#include <string>
#include <map>

// GLAD
#include <glad/glad.h>

// OpenGL
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

//GLUT
#include <GLUT/glut.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "shader.h"
#include "camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// Properties
GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint loadTexture(const char* path, GLboolean alpha = false);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];



class star
{
public:
    GLfloat angle, a, b, x, y;
    glm::vec4 color;
};


// put stars in the array
const int num = 100;
const float pi = 3.1415;
star stars[num];

// distance to the stars
GLfloat zoom = -25.0f;
// initial angle
GLfloat def_a, def_b = 0.5;
GLint iter = 0;
GLfloat max_distance = 5.0;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Star Rotation", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);
    
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    
    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Initialize GLAD to setup the OpenGL Function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);


    
    // Setup and compile our shaders
    Shader shader("main.vert.glsl", "main.frag.glsl");
    
    // Set the object data (buffers, vertex attributes)
    GLfloat starVertices[] = {
        // Positions          // Texture Coords
        0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  0.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  0.0f,
    };


    glm::vec4 random_colors[] = {
        glm::vec4(160.0 / 255, 0, 200.0 / 255, 1.0f),
        glm::vec4(110.0 / 255, 0, 220.0 / 255, 1.0f),
        glm::vec4(30.0 / 255, 60.0 / 255, 1.0f, 1.0f),
        glm::vec4(0, 160.0 / 255, 1.0f, 1.0f),
        glm::vec4(0, 200.0 / 255, 200.0 / 255, 1.0f),
        glm::vec4(0, 210.0 / 255, 140.0 / 255, 1.0f),
        glm::vec4(0, 220.0 / 255, 0, 1.0f),
        glm::vec4(160.0 / 255, 230.0 / 255, 50.0 / 255, 1.0f),
    };

    

    // Setup star VAO
    GLuint starVAO, starVBO;
    glGenVertexArrays(1, &starVAO);
    glGenBuffers(1, &starVBO);
    glBindVertexArray(starVAO);
    glBindBuffer(GL_ARRAY_BUFFER, starVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), &starVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);
    
    // Load textures
    GLuint starTexture = loadTexture("Star.bmp", true);
    

    for (int j = 0; j < num; j++) {
        stars[j].color = random_colors[j % 10];
        stars[j].angle = pi / 10 * j;
        stars[j].a = def_a * (1 + pi / 10) / (1 + pi / 10 * (j));
        stars[j].b = def_b * (1 + pi / 10) / (1 + pi / 10 * (j));
        stars[j].x = (def_a + def_b * stars[j].angle) * cos(stars[j].angle);
        stars[j].y = (def_a + def_b * stars[j].angle) * sin(stars[j].angle);

    }
    max_distance = glm::sqrt(stars[num - 1].x * stars[num - 1].x + stars[num - 1].y * stars[num - 1].y);
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        
        // Check and call events
        glfwPollEvents();
        
        // Clear the colorbuffer
        glClearColor(0, 0, 0, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // Draw objects
        shader.Use();
        glm::mat4 model(1);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        for (int i = 0; i < num; i++) {
            glBindVertexArray(starVAO);
            glBindTexture(GL_TEXTURE_2D, starTexture);
            model = glm::mat4(1);
            GLfloat distance = glm::sqrt(stars[i].x * stars[i].x + stars[i].y * stars[i].y);

            stars[i].x *= 1 + pi / 1000 / distance;
            stars[i].y *= 1 + pi / 1000 / distance;

            model = glm::translate(model, glm::vec3(stars[i].x, stars[i].y, zoom + i * 0.001));
            if (distance >= max_distance) {
                iter = (iter + 1) % num;
                stars[i].a = def_a * (1 + pi / 10) / (1 + pi / 10 * (iter));
                stars[i].b = def_b * (1 + pi / 10) / (1 + pi / 10 * (iter));
                stars[i].angle = pi / 10 * iter;
                stars[i].x = (stars[i].a + stars[i].b * stars[i].angle) * cos(stars[i].angle);
                stars[i].y = (stars[i].a + stars[i].b * stars[i].angle) * sin(stars[i].angle);
            }
            stars[i].color.w = 1 - distance / max_distance;
            GLint color_location = glGetUniformLocation(shader.Program, "my_color");
            glUniform4f(color_location, stars[i].color.x, stars[i].color.y, stars[i].color.z, stars[i].color.w);
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 12);
        }
        glBindVertexArray(0);
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

// This function loads a texture from file. Note: texture loading functions like these are usually
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio).
// For learning purposes we'll just define it as a utility function.

GLuint loadTexture(const char* path, GLboolean alpha)
{
    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);    // Use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes value from next repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);
    return textureID;
}

// Moves/alters the camera positions based on user input


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, width, height);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        keys[key] = true;§
        else if (action == GLFW_RELEASE)
        keys[key] = false;
    }
}


