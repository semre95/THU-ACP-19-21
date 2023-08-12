#ifndef _RUBIKCUBE_H_
#define _RUBIKCUBE_H_

#include <iostream>
#include <cmath>
using namespace std;

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
#include "camera.h"

#include <stack>
#include <vector>
#include <list>
#include "Vector3D.h"
// #include "trackball.h"
#include <ctime>

//sub-cube size
const GLfloat cubeSize = 1.0f;

// number of faces or lines needed to paint in a cube
const GLuint cube_fnum = 12;
const GLuint cube_lnum = 12;

struct TriInt{
	int x, y, z;
public:
	TriInt(): x(-1),y(-1),z(-1) {}
	TriInt(int x, int y, int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	bool isEqual(TriInt t){
		return (x==t.x) && (y==t.y) && (z==t.z);
	}
};

struct TriFloat{
	GLfloat x, y, z;
};

//Sub-cube structure
struct Cube{
	//the beginning vertex index of the sub-cube
	GLuint begin_index;
	GLuint begin_lines;
	// whether to show the face
	bool face_show[cube_fnum]; 
	//colors of faces
	TriFloat faceColor[cube_fnum];

	bool if_select; // if being selected
	glm::mat4 m_cube; // model matrix
	glm::vec4 center; // the center position
	int layer[3]; // the layers it belongs to
	int lay_ind[3]; // the index in the layers
};

//Layer structure
struct Layer{
	//sub-cubes.
	//see the constructor of RubikCube for details
	Cube* cubes[9];
};

struct Rotation{
	bool first; // 
	int ax_ind; // the index of axis
	int layerY; // the index of layer in the axis
	bool anti_clock; // clockwise
	GLfloat offset; // offset of rotating
	GLfloat ang_roted; // angle of rotating

	Rotation(): first(true), ax_ind(0), layerY(0), anti_clock(true), offset(0.0f), ang_roted(0.0f) {}
	void change( int ax_ind, int layerY, bool anti_clock, GLfloat offset ){
		this->ax_ind = ax_ind;
		this->layerY = layerY;
		this->anti_clock = anti_clock;
		this->offset = offset;
	}
};

//Structure of Rubik's cube
class RubikCube{
	//27 sub-cubes, organized as a 3 by 3 by 3 structure.
	Cube magicCube[3][3][3];

	//9 layers, organized as a 3 by 3 as the rotating axis and position.
	Layer layers[3][3];

	TriInt cube_selected; // the selected cube

	// the stacks to note down the past states(in order to track back)
	stack<glm::mat4*> cubes;
	stack<glm::mat4> states;

public:
	GLuint VAO,VBO;
	GLfloat vertices[64 * 3];
	GLuint indices[27 * cube_fnum * 3];
	GLuint ind_lines[27 * cube_lnum * 2]; // 线段索引数组
	int attr; //attributes of vertices

	glm::mat4 model; // rotate as a whole
	GLfloat MouseSensitivity;
	Rotation rotation; // the data used to rotate
	glm::vec4 axis[3]; // three rotate axis

public:
	RubikCube();
	~RubikCube();

	void cube_array(); // set cubes, vertices & indices

	void show_face_construct(int i, int j, int k); // construct the face_show array

	void face_color_construct(int i, int j, int k); // construct the facecolor array

	void Layers_set(); // set up the layers

	void set_BA_obj(); //set VBO,VAO,EBO

	glm::vec3 get_trackball_vec(GLfloat x, GLfloat y, GLfloat WIDTH, GLfloat HEIGHT);

	void Mouse_LeftMove(GLfloat current_x, GLfloat last_x, GLfloat current_y, GLfloat last_y, GLfloat WIDTH, GLfloat HEIGHT, glm::mat4 view);

	void Select_Cube(GLfloat xpos, GLfloat ypos, glm::mat4 view, glm::mat4 projection, GLfloat zoom, GLfloat wid_view, GLfloat WIDTH, GLfloat HEIGHT); // right mouse select a sub_cube

	void Mouse_RightMove(GLfloat xoffset, GLfloat yoffset, glm::mat4 view, glm::mat4 projection, GLfloat zoom, GLfloat wid_view);

	void RotateStep();

	void Release_Cube(); // when right mouse released

	void RotateFinish();

	void Render(Shader ourShader); 	// Render

	void Note_state(int button); // to note down the past state

	void Track_back(); // back to the last state

private:
	void RenderSingleCube(Shader ourShader, int x, int y, int z);

	void ReplaceColors(Cube *cube1, Cube *cube2, int order[], int relativeTop[]);
};
#endif