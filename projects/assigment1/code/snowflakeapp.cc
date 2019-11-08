//------------------------------------------------------------------------------
// snowflakeapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "snowflakeapp.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <math.h>
#include <iostream>

const GLchar* vs =
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) in vec3 pos;\n"
	"layout(location=1) in vec4 color;\n"
	"layout(location=0) out vec4 Color;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(pos, 1);\n"
	"	Color = color;\n"
	"}\n";

const GLchar* ps =
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) in vec4 color;\n"
	"out vec4 Color;\n"
	"void main()\n"
	"{\n"
	"	Color = color;\n"
	"}\n";

using namespace Display;
namespace Snowflake {

	//------------------------------------------------------------------------------
	/**
	*/
	SnowflakeApp::SnowflakeApp() {
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	SnowflakeApp::~SnowflakeApp() {
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/

	GLfloat* SnowflakeApp::createTriangle(GLfloat a, GLfloat cx, GLfloat cy) {
		float r = (a * sqrt(3))/6;
		float h = (a * sqrt(3))/2;

		GLfloat* triangle = new GLfloat[9];

		triangle[0] = cx - a/2;	triangle[1] = cy - r;	triangle[2] = -1; // pos 0

		triangle[3] = cx;	triangle[4] = cy + (h - r);	triangle[5] = -1; // pos 1

		triangle[6] = cx + a/2;	triangle[7] = cy - r;	triangle[8] = -1; // pos 2

		return triangle;
	}

	void SnowflakeApp::translatePoint(GLfloat* px, GLfloat* py, GLfloat tx, GLfloat ty) {
		*px += tx;
		*py += ty;
	}

	void SnowflakeApp::rotatePoint(GLfloat* px, GLfloat* py, float angle) {
		GLfloat x = *px;
		GLfloat y = *py;
		*px = x * cos(angle * M_PI) - y * sin(angle * M_PI);
		*py = x * sin(angle * M_PI) + y * cos(angle * M_PI);
	}

	GLfloat* SnowflakeApp::calcTriangle(GLfloat ps[4]) {
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

	GLfloat* SnowflakeApp::calcSnowflake(GLfloat* points, int num_points, int depth) {
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

	bool SnowflakeApp::Open(){
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32, int32, int32, int32) {
			this->window->Close();
		});

		GLfloat pos[] = {0.0f, 0.2f};
		GLfloat* t1_buf = createTriangle(0.5f, pos[0], pos[1]);

		this->depth = 4;
		this->num_points = 3 * pow(4, this->depth);
		GLfloat* t2_buf = calcSnowflake(t1_buf, 3, this->depth);

		delete[] t1_buf;

		GLfloat buf[this->num_points * 7];

		for (int i = 0; i < this->num_points; i++) {
			buf[i * 7] = t2_buf[i * 3];
			buf[1 + i * 7] = t2_buf[1 + i * 3];
			buf[2 + i * 7] = t2_buf[2 + i * 3];

			buf[3 + i * 7] = 0;
			buf[4 + i * 7] = 0;
			buf[5 + i * 7] = 0;
			buf[6 + i * 7] = 1;
		}

		delete[] t2_buf;

		for (int i = 0; i < this->num_points; i++) {
			translatePoint(&buf[i * 7 + 0], &buf[i * 7 + 1], -pos[0], -pos[1]);
			rotatePoint(&buf[i * 7 + 0], &buf[i * 7 + 1], 0.0f);
			translatePoint(&buf[i * 7 + 0], &buf[i * 7 + 1], pos[0], pos[1]);
		}

		for (int i = 0; i < this->num_points; i++) {
			std::cout << buf[i * 7 + 0];
			std::cout << " : ";
			std::cout << buf[i * 7 + 1];
			std::cout << " : ";
			std::cout << buf[i * 7 + 2];
			std::cout << "\n";

			std::cout << buf[i * 7 + 3];
			std::cout << " : ";
			std::cout << buf[i * 7 + 4];
			std::cout << " : ";
			std::cout << buf[i * 7 + 5];
			std::cout << " : ";
			std::cout << buf[i * 7 + 6];
			std::cout << "\n";
		}
	

		if (this->window->Open()) {
			// set clear color to gray
			glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

			// setup vertex shader
			this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLint length = (GLint)std::strlen(vs);
			glShaderSource(this->vertexShader, 1, &vs, &length);
			glCompileShader(this->vertexShader);

			// get error log
			GLint shaderLogSize;
			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0) {
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// setup pixel shader
			this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
			length = (GLint)std::strlen(ps);
			glShaderSource(this->pixelShader, 1, &ps, &length);
			glCompileShader(this->pixelShader);

			// get error log
			shaderLogSize;
			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0) {
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// create a program object
			this->program = glCreateProgram();
			glAttachShader(this->program, this->vertexShader);
			glAttachShader(this->program, this->pixelShader);
			glLinkProgram(this->program);
			glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0) {
				GLchar* buf = new GLchar[shaderLogSize];
				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
				printf("[PROGRAM LINK ERROR]: %s", buf);
				delete[] buf;
			}

			// setup vbo
			glGenBuffers(1, &this->triangle);
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void SnowflakeApp::Run() {
		while (this->window->IsOpen()) {
			glClear(GL_COLOR_BUFFER_BIT);
			this->window->Update();

			// do stuff
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			glUseProgram(this->program);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
			glDrawArrays(GL_LINE_LOOP, 0, this->num_points);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			this->window->SwapBuffers();
		}
	}

} // namespace Snowflake