//------------------------------------------------------------------------------
// snowflakeapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
// #include "config.h"
#include "snowflakeobj.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <math.h>
#include <iostream>


// using namespace Display;
namespace Snowflake {

	//------------------------------------------------------------------------------
	/**
	*/
	SnowflakeObj::SnowflakeObj() {
		this->size = 1.3f;
		this->posx = 0.0f;
        this->posy = 0.0f;
        this->angle = 0.0f;
        this->depth = 0;
        this->numPoints = 3 * pow(4, this->depth);

		this->pos = 0;
		this->triangleSnowFlake = new GLfloat(3 * pow(4, this->depth) * 3);

        this->create();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	SnowflakeObj::~SnowflakeObj() {
		delete[] this->snowFlake;
	}

	//------------------------------------------------------------------------------
	/**
	*/

	GLfloat* SnowflakeObj::createTriangle(GLfloat a, GLfloat cx, GLfloat cy) {
		float r = (a * sqrt(3))/6;
		float h = (a * sqrt(3))/2;

		GLfloat* triangle = new GLfloat[9];

		triangle[0] = cx - a/2;	triangle[1] = cy - r;	triangle[2] = -1; // pos 0

		triangle[3] = cx;	triangle[4] = cy + (h - r);	triangle[5] = -1; // pos 1

		triangle[6] = cx + a/2;	triangle[7] = cy - r;	triangle[8] = -1; // pos 2

		return triangle;
	}

	GLfloat* SnowflakeObj::calcTriangle(GLfloat ps[4]) {
		float dx = ps[2] - ps[0];
		float dy = ps[3] - ps[1];
		float hyp = sqrt(dx * dx + dy*dy);
		float a = hyp/3;

		float r = (a * sqrt(3))/6;
		float h = (a * sqrt(3))/2;
		
		GLfloat* triangle = new GLfloat[9];

		triangle[0] = ps[0] + dx/3;	triangle[1] = ps[1] + dy/3;	triangle[2] = -1; // pos 0

		triangle[3] = ps[0] + dx/2 + (((-dy/3) * sqrt(3))/2);	triangle[4] = ps[1] + dy/2 + (((dx/3) * sqrt(3))/2) ;	triangle[5] = -1; // pos 1

		triangle[6] = ps[0] + dx/3 * 2;	triangle[7] = ps[1] + dy/3 * 2;	triangle[8] = -1; // pos 2

		for (int i = 0; i < 9; i++) {
			this->triangleSnowFlake[this->pos + i] = triangle[i];
		}
		this->pos += 9;

		return triangle;
	}

	GLfloat* SnowflakeObj::calcSnowflake(GLfloat* points, int num_points, int depth) {
		GLfloat* result = new GLfloat[num_points * 4 * 3];

		if (depth > 0) {

			GLfloat edge[4] = {0,0,0,0};
			GLfloat* newTriangle;

			for (int i = 0; i < num_points ; i++) {
				edge[0] = points[0 + 3 * i]; edge[1] = points[1 + 3 * i]; edge[2] = points[3 + 3 * i]; edge[3] = points[4 + 3 * i]; 
				if (i == num_points - 1) {
					edge[0] = points[0 + 3 * i]; edge[1] = points[1 + 3 * i]; edge[2] = points[0]; edge[3] = points[1]; 
				}
				newTriangle  = calcTriangle(edge);

				for (int j = 0; j < 3; j++) {
					result[j + 12 * i] = points[j + 3 * i]; 
				}
				for (int j = 0; j < 9; j++) {
					result[j + 12 * i + 3 ] = newTriangle[j]; 
				}

				delete[] newTriangle;
			}

			GLfloat* r = calcSnowflake(result, num_points * 4, depth -1);
			delete[] result;

			return r;
		} else {
			for (int i = 0; i < num_points * 3; i++) { 
				result[i] = points[i];
			}
			return result;
		}
	}

    void SnowflakeObj::translatePoint(GLfloat* px, GLfloat* py, GLfloat tx, GLfloat ty) {
		// *px += tx;
		// *py += ty;
	}

	void SnowflakeObj::rotatePoint(GLfloat* px, GLfloat* py, float angle) {
		// GLfloat x = *px;
		// GLfloat y = *py;
		// *px = x * cos(angle * M_PI) - y * sin(angle * M_PI);
		// *py = x * sin(angle * M_PI) + y * cos(angle * M_PI);
	}

    void SnowflakeObj::translateSnowflake(float x, float y) {
		// for (int i = 0; i < this->numPoints; i++) {
		// 	translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], x, y);
		// }
	}

	void SnowflakeObj::rotateSnowflake(float angle) {
		// for (int i = 0; i < this->numPoints; i++) {
		// 	translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], -this->posx, -this->posy);
		// 	rotatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], angle);
		// 	translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], this->posx, this->posy);

		// 	translatePoint(&this->triangleSnowFlake[i * 3], &this->triangleSnowFlake[i * 3 + 1], -this->posx, -this->posy);
		// 	rotatePoint(&this->triangleSnowFlake[i * 3], &this->triangleSnowFlake[i * 3 + 1], angle);
		// 	translatePoint(&this->triangleSnowFlake[i * 3], &this->triangleSnowFlake[i * 3 + 1], this->posx, this->posy);
		// }
	}

	void SnowflakeObj::create(){
		delete[] this->triangleSnowFlake;
		int numFloats = 3 * pow(4, depth) * 3;
		
		this->triangleSnowFlake = new GLfloat[numFloats];
		this->pos = 0;
		GLfloat* triangle = createTriangle(this->size, this->posx, this->posy);
		GLfloat* points = calcSnowflake(triangle, 3, this->depth);

		for (int i = 0; i < 9; i++) {
			this->triangleSnowFlake[this->pos + i] = triangle[i];
		}
		this->pos += 9;

		delete[] triangle;

        this->snowFlake = points;

		rotateSnowflake(this->angle);

		// std::cout << this->numPoints * 3;
		// std::cout << "\n";
		// std::cout << this->pos;
		// std::cout << "\n";

		// for (int i = 0; i < this->numPoints; i++) {
		// 	std::cout << this->snowFlake[i * 3 + 0];
		// 	std::cout << " : ";
		// 	std::cout << this->snowFlake[i * 3 + 1];
		// 	std::cout << " : ";
		// 	std::cout << this->snowFlake[i * 3 + 2];
		// 	std::cout << "\n";
		// }
		// std::cout << "\n";
	}

	GLfloat* SnowflakeObj::calcTriangleSnowflake(GLfloat* points, int depth) {
		int numFloats = 3 * pow(4, depth) * 3;
		GLfloat* triangleSnowflake = new GLfloat[numFloats];
		for (int i = 0; i < numFloats; i++) {
			triangleSnowflake[i] = 0;
		}

		if (depth > 0) {
			int prevNumPoints = 3 * pow(4, depth - 1);

			for (int i = 0; i < prevNumPoints; i++) {
				triangleSnowflake[0 + i * 9] = points[0 + i * 9 + (i+1) * 3];
				triangleSnowflake[1 + i * 9] = points[1 + i * 9 + (i+1) * 3];
				triangleSnowflake[2 + i * 9] = points[2 + i * 9 + (i+1) * 3];

				triangleSnowflake[3 + i * 9] = points[3 + i * 9 + (i+1) * 3];
				triangleSnowflake[4 + i * 9] = points[4 + i * 9 + (i+1) * 3];
				triangleSnowflake[5 + i * 9] = points[5 + i * 9 + (i+1) * 3];

				triangleSnowflake[6 + i * 9] = points[6 + i * 9 + (i+1) * 3];
				triangleSnowflake[7 + i * 9] = points[7 + i * 9 + (i+1) * 3];
				triangleSnowflake[8 + i * 9] = points[8 + i * 9 + (i+1) * 3];
			}

			GLfloat temp[prevNumPoints * 3];
			for (int i = 0; i < prevNumPoints; i++) {
				temp[0 + i * 3] = points[0 + i * 12];
				temp[1 + i * 3] = points[1 + i * 12];
				temp[2 + i * 3] = points[2 + i * 12];
			}
			GLfloat* newTriangleSnowflake = calcTriangleSnowflake(temp, depth - 1);

			for (int i = 0; i < prevNumPoints * 3; i++) {
				triangleSnowflake[i + prevNumPoints * 9] = newTriangleSnowflake[i];
			}

			delete[] newTriangleSnowflake;

			return triangleSnowflake;
		} else {
			for (int i = 0; i < numFloats; i++) {
				triangleSnowflake[i] = points[i];
			}
			return triangleSnowflake;
		}
	}


	float SnowflakeObj::getSize() {
		return this->size;
	}

	void SnowflakeObj::setSize(float s) {
		if (this->size != s) {
			this->size = s;
			create();
		}
	}

    float SnowflakeObj::getPosX() {
        return this->posx;
    }

    float SnowflakeObj::getPosY() {
        return this->posy;
    }
    float SnowflakeObj::getAngle() {
        return this->angle;
    }

    void SnowflakeObj::setPos(float x, float y) {
		if (this->posx  != x || this->posy != y) {
			translateSnowflake(this->posx, this->posy);
			this->posx = x;
			this->posy = y;
			translateSnowflake(this->posx, this->posy);
		}
    }

    void SnowflakeObj::setAngle(float a) {
		if (this->angle != a) {
			rotateSnowflake(-this->angle);
			this->angle = a;
			rotateSnowflake(this->angle);
		}
    }

    int SnowflakeObj::getDepth() {
        return this->depth;
    }

    void SnowflakeObj::setDepth(int d) {
		if (this->depth != d) {
			this->depth = d;
			this->numPoints = 3 * pow(4, this->depth);

			create();
		}
    }

    int SnowflakeObj::getNumPoints() {
        return this->numPoints;
    }

    GLfloat* SnowflakeObj::getSnowFlake() {
        return this->snowFlake;
    }

	GLfloat* SnowflakeObj::getTriangleSnowFlake() {
        return this->triangleSnowFlake;
    }

} // namespace Snowflake