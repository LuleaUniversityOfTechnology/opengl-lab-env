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
		this->size = 1.6f;
		this->posx = 0.0f;
        this->posy = 0.0f;
        this->angle = 0.0f;
        this->depth = 0;
        this->numPoints = 3 * pow(4, this->depth);

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

		triangle[3] = ps[0] + dx/2 -dy/3;	triangle[4] = ps[1] + dy/2 + dx/3 ;	triangle[5] = -1; // pos 1

		triangle[6] = ps[0] + dx/3 * 2;	triangle[7] = ps[1] + dy/3 * 2;	triangle[8] = -1; // pos 2

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
		*px += tx;
		*py += ty;
	}

	void SnowflakeObj::rotatePoint(GLfloat* px, GLfloat* py, float angle) {
		GLfloat x = *px;
		GLfloat y = *py;
		*px = x * cos(angle * M_PI) - y * sin(angle * M_PI);
		*py = x * sin(angle * M_PI) + y * cos(angle * M_PI);
	}

    void SnowflakeObj::translateSnowflake(float x, float y) {
		for (int i = 0; i < this->numPoints; i++) {
			translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], x, y);
		}
	}

	void SnowflakeObj::rotateSnowflake(float angle) {
		for (int i = 0; i < this->numPoints; i++) {
			translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], -this->posx, -this->posy);
			rotatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], angle);
			translatePoint(&this->snowFlake[i * 3], &this->snowFlake[i * 3 + 1], this->posx, this->posy);
		}
	}

	void SnowflakeObj::create(){
		GLfloat* triangle = createTriangle(this->size, this->posx, this->posy);
		GLfloat* points = calcSnowflake(triangle, 3, this->depth);
		delete[] triangle;

        this->snowFlake = points;

		rotateSnowflake(this->angle);

		// for (int i = 0; i < this->numPoints; i++) {
		// 	std::cout << this->snowFlake[i * 3 + 0];
		// 	std::cout << " : ";
		// 	std::cout << this->snowFlake[i * 3 + 1];
		// 	std::cout << " : ";
		// 	std::cout << this->snowFlake[i * 3 + 2];
		// 	std::cout << "\n";
		// }
	}

	float SnowflakeObj::getSize() {
		return this->size;
	}

	void SnowflakeObj::setSize(float s) {
		this->size = s;
		create();
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
		translateSnowflake(this->posx, this->posy);
        this->posx = x;
        this->posy = y;
		translateSnowflake(this->posx, this->posy);
    }

    void SnowflakeObj::setAngle(float a) {
		rotateSnowflake(-this->angle);
        this->angle = a;
		rotateSnowflake(this->angle);
    }

    int SnowflakeObj::getDepth() {
        return this->depth;
    }

    void SnowflakeObj::setDepth(int d) {
        this->depth = d;
        this->numPoints = 3 * pow(4, this->depth);

		create();
    }

    int SnowflakeObj::getNumPoints() {
        return this->numPoints;
    }

    GLfloat* SnowflakeObj::getSnowFlake() {
        return this->snowFlake;
    }

} // namespace Snowflake