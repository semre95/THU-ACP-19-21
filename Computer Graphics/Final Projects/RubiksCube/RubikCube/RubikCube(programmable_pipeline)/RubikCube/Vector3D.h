#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <cmath>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Vector2D
{
public:
	double x, y;

public:
	Vector2D(){x = 0; y = 0;}
	Vector2D(double x, double y){this->x = x; this->y = y;}
};

class Vector3D
{
public:
	GLfloat x, y, z;

public:
	Vector3D(){x = 0; y = 0; z = 0;}
	Vector3D(GLfloat x, GLfloat y, GLfloat z){this->x = x; this->y = y; this->z = z;}
	Vector3D(glm::vec3 input){this->x = input.x; this->y = input.y; this->z = input.z;}

	glm::vec3 vec2glm() // Vector3D -> glm::vec3
	{
		glm::vec3 ans;
		ans.x = x;
		ans.y = y;
		ans.z = z;
		return ans;
	}

	GLfloat length()
	{
		return sqrt(x*x+y*y+z*z);
	}

	void norm()
	{
		GLfloat len = length();
		if( len != 0 )
		{
			x /= len; 
			y /= len; 
			z /= len;
		}
	}

	Vector3D operator+ (const Vector3D& v)
	{
		return Vector3D(x+v.x, y+v.y, z+v.z);
	}

	Vector3D operator- (const Vector3D& v)
	{
		return Vector3D(x-v.x, y-v.y, z-v.z);
	}

	GLfloat operator* (const Vector3D& v)
	{
		return x*v.x+y*v.y+z*v.z;
	}

	GLfloat operator| (const Vector3D& v) // 两矢量间的夹角
	{
		GLfloat len = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
		return acos( (*this)*v / ( this->length() * len ) );
	}

	Vector3D operator* (GLfloat v)
	{
		return Vector3D(x*v, y*v, z*v);
	}

	Vector3D operator^ (const Vector3D& v)
	{
		return Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	}

	Vector3D operator/(GLfloat v)
	{
		return Vector3D(x/v, y/v, z/v);
	}

	Vector3D& operator+=(const Vector3D& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector3D& operator=(const Vector3D& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	GLfloat& operator[](unsigned int i)
	{
		switch(i)
		{
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}
};

#endif