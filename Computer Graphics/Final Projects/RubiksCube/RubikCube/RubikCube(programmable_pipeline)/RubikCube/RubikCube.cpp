#include "RubikCube.h"
#include <iomanip>

double rotateSpeed = 1.0f;

/************************************************************************/
/* Constructor of RubikCube class
 Read this function carefully to understand the structure of the Rubik's cube*/
/************************************************************************/

RubikCube::RubikCube(): attr(3), model(glm::mat4(1)), MouseSensitivity(0.5f){
	// set the axis
	axis[0] = glm::vec4(1.0, 0.0, 0.0, 1.0);
	axis[1] = glm::vec4(0.0, 1.0, 0.0, 1.0);
	axis[2] = glm::vec4(0.0, 0.0, 1.0, 1.0);

	cube_array(); // cubes, vertices, and indices

	Layers_set();
}

RubikCube::~RubikCube(){
	// Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

 // set cubes, vertices & indices
void RubikCube::cube_array(){
	// vertices
	GLfloat a,b,c;
	int n = 0;
	for(a = 0.0f; a < 4.0f; a++){
		for(b = 0.0f; b < 4.0f; b++){
			for(c=0.0f; c < 4.0f; c++){
				vertices[n] = (a - 1.5) * cubeSize;
				n++;
				vertices[n] = (b - 1.5) * cubeSize;
				n++;
				vertices[n] = (c - 1.5) * cubeSize;
				n++;
			}
		}
	}

	int i,j,k;
	int n1 = 0, n2 = 0;
	GLuint begin = 0;  // the beginning vertex_index
	GLuint relative[cube_fnum * 3] = { 0,1,5, 0,4,5, 0,1,17, 0,16,17, 0,4,20, 0,16,20, 
					4,5,21, 4,20,21, 1,5,21, 1,17,21, 16,17,21, 16,20,21 }; // the relative difference with the beginning vertex of a single sub_cube
	GLuint rel_lines[cube_lnum * 2] = { 0,1, 4,5, 20,21, 16,17, 0,4, 1,5, 17,21, 16,20, 0,16, 1,17, 5,21, 4,20 };	
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			for (k = 0; k < 3; k++, n1 += cube_fnum*3, n2 += cube_lnum*2){
				magicCube[i][j][k].begin_index = n1; // the beginning index in indices
				magicCube[i][j][k].begin_lines = n2; // the beginning index in ind_lines

				begin = ( i * 4 + j ) * 4 + k;
				for( int m=0; m<cube_fnum*3; m++)
					indices[n1+m] = begin + relative[m];
				for( int m=0; m<cube_lnum*2; m++)
					ind_lines[n2+m] = begin + rel_lines[m];

				magicCube[i][j][k].if_select = 0;
				magicCube[i][j][k].m_cube = glm::mat4(1); // model matrix
				magicCube[i][j][k].center = glm::vec4( GLfloat(i-1)*cubeSize, GLfloat(j-1)*cubeSize, GLfloat(k-1)*cubeSize, 1.0f );
				magicCube[i][j][k].layer[0] = i;
				magicCube[i][j][k].layer[1] = j;
				magicCube[i][j][k].layer[2] = k;

				// face_show array				
				show_face_construct(i, j, k);
				// colors of faces
				face_color_construct(i, j, k);				
			}
		}
	}
}

 // construct the face_show array
void RubikCube::show_face_construct(int i, int j, int k){
	memset(magicCube[i][j][k].face_show, false, cube_fnum * sizeof(bool));
	if(i == 0){
		magicCube[i][j][k].face_show[0] = magicCube[i][j][k].face_show[1] = true;
	} else if(i == 2){
		magicCube[i][j][k].face_show[10] = magicCube[i][j][k].face_show[11] = true;
	}

	if(j == 0){
		magicCube[i][j][k].face_show[2] = magicCube[i][j][k].face_show[3] = true;
	}else if(j == 2){
		magicCube[i][j][k].face_show[6] = magicCube[i][j][k].face_show[7] = true;
	}

	if(k == 0){
		magicCube[i][j][k].face_show[4] = magicCube[i][j][k].face_show[5] = true;
	} else if(k == 2){
		magicCube[i][j][k].face_show[8] = magicCube[i][j][k].face_show[9] = true;
	}

}

 // construct the facecolor array
void RubikCube::face_color_construct(int i, int j, int k){
	// cubes and faces	
	GLfloat colors[6][3] = {
		{1.0f, 0.0f, 0.0f},		 
		{0.0f, 1.0f, 0.0f}, 
		{0.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{1.0f, 0.0f, 1.0f}, 
		{0.0f, 1.0f, 1.0f} };

	for (int f = 0; f < 6; ++f){
		if( magicCube[i][j][k].face_show[2*f] ){
			magicCube[i][j][k].faceColor[2*f].x = colors[f][0];
			magicCube[i][j][k].faceColor[2*f].y = colors[f][1];
			magicCube[i][j][k].faceColor[2*f].z = colors[f][2];

			magicCube[i][j][k].faceColor[2*f+1].x = colors[f][0];
			magicCube[i][j][k].faceColor[2*f+1].y = colors[f][1];
			magicCube[i][j][k].faceColor[2*f+1].z = colors[f][2];
		}else{
			magicCube[i][j][k].faceColor[2*f].x = 0.5f;
			magicCube[i][j][k].faceColor[2*f].y = 0.5f;
			magicCube[i][j][k].faceColor[2*f].z = 0.5f;

			magicCube[i][j][k].faceColor[2*f+1].x = 0.5f;
			magicCube[i][j][k].faceColor[2*f+1].y = 0.5f;
			magicCube[i][j][k].faceColor[2*f+1].z = 0.5f;
		}
	}
}

 // set up the layers
void RubikCube::Layers_set(){
	//Construct layers rotate around x-axis
	for(int i = 0; i < 3; ++i){
		layers[0][i].cubes[0] = &magicCube[i][0][0]; magicCube[i][0][0].lay_ind[0] = 0;
		layers[0][i].cubes[1] = &magicCube[i][1][0]; magicCube[i][1][0].lay_ind[0] = 1;
		layers[0][i].cubes[2] = &magicCube[i][2][0]; magicCube[i][2][0].lay_ind[0] = 2;
		layers[0][i].cubes[3] = &magicCube[i][2][1]; magicCube[i][2][1].lay_ind[0] = 3;
		layers[0][i].cubes[4] = &magicCube[i][2][2]; magicCube[i][2][2].lay_ind[0] = 4;
		layers[0][i].cubes[5] = &magicCube[i][1][2]; magicCube[i][1][2].lay_ind[0] = 5;
		layers[0][i].cubes[6] = &magicCube[i][0][2]; magicCube[i][0][2].lay_ind[0] = 6;
		layers[0][i].cubes[7] = &magicCube[i][0][1]; magicCube[i][0][1].lay_ind[0] = 7;
		layers[0][i].cubes[8] = &magicCube[i][1][1]; magicCube[i][1][1].lay_ind[0] = 8;
	}
	//Construct layers rotate around y-axis
	for(int i = 0; i < 3; ++i){
		layers[1][i].cubes[0] = &magicCube[0][i][0]; magicCube[0][i][0].lay_ind[1] = 0;
		layers[1][i].cubes[1] = &magicCube[0][i][1]; magicCube[0][i][1].lay_ind[1] = 1;
		layers[1][i].cubes[2] = &magicCube[0][i][2]; magicCube[0][i][2].lay_ind[1] = 2;
		layers[1][i].cubes[3] = &magicCube[1][i][2]; magicCube[1][i][2].lay_ind[1] = 3;
		layers[1][i].cubes[4] = &magicCube[2][i][2]; magicCube[2][i][2].lay_ind[1] = 4;
		layers[1][i].cubes[5] = &magicCube[2][i][1]; magicCube[2][i][1].lay_ind[1] = 5;
		layers[1][i].cubes[6] = &magicCube[2][i][0]; magicCube[2][i][0].lay_ind[1] = 6;
		layers[1][i].cubes[7] = &magicCube[1][i][0]; magicCube[1][i][0].lay_ind[1] = 7;
		layers[1][i].cubes[8] = &magicCube[1][i][1]; magicCube[1][i][1].lay_ind[1] = 8;
	}
	//Construct layers rotate around z-axis
	for(int i = 0; i < 3; ++i){
		layers[2][i].cubes[0] = &magicCube[0][0][i]; magicCube[0][0][i].lay_ind[2] = 0;
		layers[2][i].cubes[1] = &magicCube[1][0][i]; magicCube[1][0][i].lay_ind[2] = 1;
		layers[2][i].cubes[2] = &magicCube[2][0][i]; magicCube[2][0][i].lay_ind[2] = 2;
		layers[2][i].cubes[3] = &magicCube[2][1][i]; magicCube[2][1][i].lay_ind[2] = 3;
		layers[2][i].cubes[4] = &magicCube[2][2][i]; magicCube[2][2][i].lay_ind[2] = 4;
		layers[2][i].cubes[5] = &magicCube[1][2][i]; magicCube[1][2][i].lay_ind[2] = 5;
		layers[2][i].cubes[6] = &magicCube[0][2][i]; magicCube[0][2][i].lay_ind[2] = 6;
		layers[2][i].cubes[7] = &magicCube[0][1][i]; magicCube[0][1][i].lay_ind[2] = 7;
		layers[2][i].cubes[8] = &magicCube[1][1][i]; magicCube[1][1][i].lay_ind[2] = 8;
	}
}

 //set VBO,VAO
void RubikCube::set_BA_obj(){
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*v_num*attr, vertices, GL_STATIC_DRAW);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attr * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO
}

// *******Created my own trackball ************
// get a point on the unit sphere from screen coordinates
glm::vec3 RubikCube::get_trackball_vec(GLfloat x, GLfloat y, GLfloat WIDTH, GLfloat HEIGHT){
	// get x and y in a range between -1 and 1
	glm::vec3 p(1.f * x / WIDTH * 2 - 1.f, 1.f * y / HEIGHT * 2 - 1.f, 0);
	p.y *= -1;
	// compute z variable on sphere if (x,y) is in unit circle, otherwise put (x,y) on circle border 
	float p_squared = p.x * p.x + p.y * p.y;
	if(p_squared <= 1.f){
		p.z = sqrt(1 - p_squared);
	}else{
		p = glm::normalize(p);
	}
	return p;
}

/*
	TODO: You should implement the function for rotating the whole rubicube. 
	You could implement it using track ball. The variable "model" is the matrix of track ball.
	*/
// rotate the whole cube based on the current and last cursor position using a trackball model
void RubikCube::Mouse_LeftMove(GLfloat current_x, GLfloat last_x, GLfloat current_y, GLfloat last_y,
	// get the vectors on the trackball anc compute the rotation axis and angle
	GLfloat WIDTH, GLfloat HEIGHT, glm::mat4 view){
	glm::vec3 a = get_trackball_vec(last_x, last_y, WIDTH, HEIGHT);
	glm::vec3 b = get_trackball_vec(current_x, current_y, WIDTH, HEIGHT);
	float angle = acos(fmin(1.f, glm::dot(a, b)));
	glm::vec3 axis_in_camera_coords = glm::cross(a, b);
	// transform the rotation axis to object coordinates
	glm::mat3 cam_to_object_trafo = glm::inverse(view * model);
	glm::vec3 axis_in_object_coords = cam_to_object_trafo * axis_in_camera_coords;
	// rotate the model matrix. The factor of 2 makes the rotating experience more satisfying
	model = glm::rotate(model, angle * 2.f, axis_in_object_coords);
}

// world coordinate -> window coordinate (for vertices)
glm::vec3 wor2win(glm::vec3 v, GLfloat zoom, GLfloat wid_view, GLfloat WIDTH, GLfloat HEIGHT){
	glm::vec3 res;
	GLfloat wor_wid = -2 * v.z * tan( glm::radians(zoom/2) );
	res.x = v.x * wid_view / wor_wid + WIDTH / 2;
	res.y = -v.y * wid_view / wor_wid + HEIGHT / 2; //reversed
	res.z = 0.0f;
	return res;
}

 // to judge if a vertex v is in a triangle abc
bool if_here(Vector3D v, Vector3D a, Vector3D b, Vector3D c){
	bool con1 = ( ( (c-a)|(v-a) ) < ( (c-a)|(b-a) ) ) || ( ( (c-a)|(v-a) ) == ( (c-a)|(b-a) ) );
	bool con2 = ( ( (b-a)|(v-a) ) < ( (c-a)|(b-a) ) ) || ( ( (b-a)|(v-a) ) == ( (c-a)|(b-a) ) );
	bool con3 = ( ( (c-b)|(v-b) ) < ( (c-b)|(a-b) ) ) || ( ( (c-b)|(v-b) ) == ( (c-b)|(a-b) ) );
	bool con4 = ( ( (a-b)|(v-b) ) < ( (c-b)|(a-b) ) ) || ( ( (a-b)|(v-b) ) == ( (c-b)|(a-b) ) );
	return con1 && con2 && con3 && con4;
}

 //
void RubikCube::Select_Cube(GLfloat xpos, GLfloat ypos, glm::mat4 view, glm::mat4 projection, GLfloat zoom, GLfloat wid_view, GLfloat WIDTH, GLfloat HEIGHT){
	glm::vec4 v1, v2, v3;
	int begin, first, second, third;
	GLfloat z_max, z_tmp;
	z_max = -DBL_MAX;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				// 
				for(int f=0; f<cube_fnum; f++){
					begin = magicCube[i][j][k].begin_index + f*3;
					first = indices[begin];
					second = indices[begin+1];
					third = indices[begin+2];
					v1 = glm::vec4( vertices[3*first], vertices[3*first+1], vertices[3*first+2], 1.0f );
					v2 = glm::vec4( vertices[3*second], vertices[3*second+1], vertices[3*second+2], 1.0f );
					v3 = glm::vec4( vertices[3*third], vertices[3*third+1], vertices[3*third+2], 1.0f );
					glm::vec3 vp1 = glm::vec3(view * model * magicCube[i][j][k].m_cube * v1);
					glm::vec3 vp2 = glm::vec3(view * model * magicCube[i][j][k].m_cube * v2);
					glm::vec3 vp3 = glm::vec3(view * model * magicCube[i][j][k].m_cube * v3);
					vp1 = wor2win(vp1, zoom, wid_view, WIDTH, HEIGHT);
					vp2 = wor2win(vp2, zoom, wid_view, WIDTH, HEIGHT);
					vp3 = wor2win(vp3, zoom, wid_view, WIDTH, HEIGHT);
					Vector3D v(xpos,ypos,0.0f), a(vp1), b(vp2), c(vp3);
					
					if(if_here(v,a,b,c)){ // if the mouse position is in the triangle
						glm::vec4 center = model * magicCube[i][j][k].m_cube * magicCube[i][j][k].center;
						z_tmp = center.z;
						if( z_tmp > z_max ){
							z_max = z_tmp;
							cube_selected = TriInt(i,j,k); // mark the nearest cube
						}
						break;
					}
				}
			}
		}
	}
	if(!cube_selected.isEqual(TriInt(-1, -1, -1))){
		magicCube[cube_selected.x][cube_selected.y][cube_selected.z].if_select = 1;
	}
}

 // world coordinate -> window coordinate (for direction)
glm::vec3 wor2win(glm::vec3 v, GLfloat zoom, GLfloat wid_view){
	glm::vec3 res;
	GLfloat wor_wid = -2 * v.z * tan( glm::radians(zoom/2) );
	res.x = v.x * wid_view / wor_wid;
	res.y = v.y * wid_view / wor_wid; // don't need to reversed again! because we have reversed the y-coordinate in the main file !
	res.z = 0.0f;
	return res;
}

// 
void RubikCube::Mouse_RightMove(GLfloat xoffset, GLfloat yoffset, glm::mat4 view, glm::mat4 projection, GLfloat zoom, GLfloat wid_view){
	if(cube_selected.isEqual(TriInt(-1, -1, -1))){ // 
		return;
	}

	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;
	Vector3D movement(xoffset, yoffset, 0.0f);
	if(movement.length() == 0){ // 
		return;
	}
	int i=cube_selected.x, j=cube_selected.y, k=cube_selected.z;
	glm::vec4 v_sel4 = glm::vec4( magicCube[i][j][k].center.x, magicCube[i][j][k].center.y, magicCube[i][j][k].center.z, 1.0f ); // the selected vertex
	glm::vec3 v_sel3 = glm::vec3(model * magicCube[i][j][k].m_cube * v_sel4);
	Vector3D radius(v_sel3); // calculate the initial rotation radius
	Vector3D ax_ini = radius^movement; // calculate the initial rotation axis that looks like

	int ind, ax_tru; // the truly rotation axis index
	glm::vec3 ax;
	GLfloat dot, dot_max = 0; //
	Vector3D ax_tmp;
	for( ind=0; ind<3; ind++ ){
		ax = glm::vec3(view * model * this->axis[ind]);
		ax = wor2win(ax, zoom, wid_view);
		ax_tmp = Vector3D(ax);
		if(ax_tmp.length() == 0){ // 
			continue;
		}
		ax_tmp.norm(); // normalize
		dot = ax_ini * ax_tmp;
		if( abs(dot) >= abs(dot_max) ){
			dot_max = dot;
			ax_tru = ind;
		}
	}

	int layerY = magicCube[i][j][k].layer[ax_tru];
	if(rotation.first){ // 
		rotation.change( ax_tru, layerY, bool(dot_max>0), movement.length() );
		rotation.first = false;
		RotateStep(); // rotate!
	}
	else if( ax_tru == rotation.ax_ind ){ //
		rotation.change( ax_tru, layerY, bool(dot_max>0), movement.length() );
		RotateStep(); // rotate!
	}
	// 
}

/************************************************************************/
/* Rotate a single angle (rotateSpeed) for the sub-cubes in the given layer and store the result model-view matrix for each 
rotated sub-cube in its matrix variable
using struct rotation
/************************************************************************/
void RubikCube::RotateStep(){ // use the rotation structure to rotate
	glm::vec3 axis_true;
	if(rotation.anti_clock){
		axis_true = glm::vec3(this->axis[rotation.ax_ind]);
		rotation.ang_roted += rotation.offset; // note down the rotated angle
	}
	else{
		axis_true = - glm::vec3(this->axis[rotation.ax_ind]);
		rotation.ang_roted -= rotation.offset; // note down the rotated angle
	}
	/*
	TODO: rotate the subcubes
	You should compute a rotation matrix and apply it to the layer
	*/
	// update all subcube model matrices
	for(int i = 0; i < 9; i++){
		Cube* sub_cube = layers[rotation.ax_ind][rotation.layerY].cubes[i];
		glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(rotation.offset), axis_true);
		sub_cube->m_cube = rot * sub_cube->m_cube;
	}
}

//
void RubikCube::Release_Cube() // when the rotation of sub_cubes done
{
	if( !cube_selected.isEqual(TriInt(-1,-1,-1)) ) // 
	{
		magicCube[cube_selected.x][cube_selected.y][cube_selected.z].if_select = 0;
		cube_selected = TriInt(-1,-1,-1);
	}

	Track_back(); // 

	if( abs(rotation.ang_roted) > 45.0f ) // 
	{
		glm::vec3 axis_true;
		if( rotation.ang_roted > 0 ) //
			axis_true = glm::vec3(this->axis[rotation.ax_ind]);
		else //
			axis_true = - glm::vec3(this->axis[rotation.ax_ind]);
		glm::mat4 rot = glm::rotate( glm::mat4(1), glm::radians(90.0f), axis_true ); //rotation matrix

		Note_state(GLFW_MOUSE_BUTTON_RIGHT); // note down the state again
		// then rotate the sub_cubes
		int i;
		for(i=0; i<9; i++)
		{
			Cube* sub_cube = layers[rotation.ax_ind][rotation.layerY].cubes[i];
			sub_cube->m_cube = rot * sub_cube->m_cube;
		}

		RotateFinish(); // then reset the layers!
	}
	rotation.ang_roted = 0.0f; // 
	rotation.first = true;
}

/************************************************************************/
/* 
The positions of cubes have been updated. But the connection bettween cubes and layers have not. It leads something wrong.

For the sub-cubes of rotated layers, update which cubes belong to a layer.  

This function includes two cases: clockwise and anti-clockwise

You should focus on the variable "layers" and update it.

*/

//TO DO
// updates the affiliation of subcubes to the layers and the layer reference in each subcube
void RubikCube::RotateFinish(){
	// make copy of subcube data (use vectors, as they automatically handle memory allocation)
	vector<vector<vector<int>>> sub_cube_data(8, vector<vector<int>>(2, vector<int>(3)));
	vector<Cube*> sub_cubes(8);
	for(int i = 0; i < 8; i++){
		sub_cubes[i] = layers[rotation.ax_ind][rotation.layerY].cubes[i];
		for(int j = 0; j < 3; j++){
			sub_cube_data[i][0][j] = sub_cubes[i]->layer[j];
			sub_cube_data[i][1][j] = sub_cubes[i]->lay_ind[j];
		}
	}

	for(int i = 0; i < 8; i++){
		// move all cubes on the outer ring x positions counterclockwise
		for(int j = 0; j < 3; j++){
			sub_cubes[i]->layer[j] = sub_cube_data[(i + (int)rotation.ang_roted / 45) % 8][0][j];
			sub_cubes[i]->lay_ind[j] = sub_cube_data[(i + (int)rotation.ang_roted / 45) % 8][1][j];
		}
		// update layers based on updated subcube data
		layers[0][sub_cubes[i]->layer[0]].cubes[sub_cubes[i]->lay_ind[0]] = sub_cubes[i];
		layers[1][sub_cubes[i]->layer[1]].cubes[sub_cubes[i]->lay_ind[1]] = sub_cubes[i];
		layers[2][sub_cubes[i]->layer[2]].cubes[sub_cubes[i]->lay_ind[2]] = sub_cubes[i];
	}
}

// painting the 27 sub-cubes
void RubikCube::Render(Shader ourShader){
	glBindVertexArray(VAO);

	// the model matrix for the object; pass it to shader before drawing
	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// paint the sub-cubes one by one
	for (int i = 0;i < 3;++i){
		for (int j = 0;j < 3;++j){
			for (int k = 0;k < 3;++k){				
				RenderSingleCube(ourShader, i, j, k);
			}
		}
	}
	glBindVertexArray(0);
}

// painting a single sub_cube(faces & lines)
void RubikCube::RenderSingleCube(Shader ourShader, int x, int y, int z){
	// Calculate the model matrix for the object and pass it to shader before drawing
	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model_cube");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(magicCube[x][y][z].m_cube));

	GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
	// Painting faces
	if(magicCube[x][y][z].if_select){ // if the sub-cube is selected right now
		for(int i=0; i<cube_fnum; i++){	
			glUniform4f(vertexColorLocation, 0.5*magicCube[x][y][z].faceColor[i].x, 0.5*magicCube[x][y][z].faceColor[i].y, 
				0.5*magicCube[x][y][z].faceColor[i].z, 1.0f); // Change color
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices + magicCube[x][y][z].begin_index + i*3 ); // drawing
		}
	}else{ // if not selected
		for(int i=0; i<cube_fnum; i++){
			glUniform4f(vertexColorLocation, magicCube[x][y][z].faceColor[i].x, magicCube[x][y][z].faceColor[i].y, 
				magicCube[x][y][z].faceColor[i].z, 1.0f); // Change color

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices + magicCube[x][y][z].begin_index + i*3 ); // drawing
		}
	}
	// Painting lines
	glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f); // Change color
	glLineWidth(4.0f); // line width
	for(int i=0; i<cube_fnum; i++){	
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, ind_lines + magicCube[x][y][z].begin_lines + i*2 ); // drawing
	}
}

// to note down the past state (when the left or right mouse clicked)
void RubikCube::Note_state(int button){
	switch(button){
	case GLFW_MOUSE_BUTTON_LEFT:
		// push the present state to the stacks
		cubes.push( &(this->model) );
		states.push(this->model);
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		// now you should note down the states of all the sub_cubes
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				for (int k = 0; k < 3; k++){
					cubes.push( &(magicCube[i][j][k].m_cube) );
					states.push(magicCube[i][j][k].m_cube);
				}
			}
		}
		break;
	}
}

// 
void RubikCube::Track_back(){
	// the first track back
	if( cubes.empty() || states.empty() ) //
		return;
	glm::mat4* model_loc = cubes.top();
	cubes.pop();
	glm::mat4 state = states.top();
	states.pop();

	*model_loc = state;

	if( model_loc != &(this->model) ){ // if not the whole rotation
		for(int i=0; i<26; i++){ // then we should track back the left 26 sub_cubes
			if(cubes.empty() || states.empty()){ //
				return;
			}
			model_loc = cubes.top();
			cubes.pop();
			state = states.top();
			states.pop();
			*model_loc = state;
		}
	}
}