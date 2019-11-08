#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for Snowflake application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
namespace Snowflake {
	class SnowflakeApp : public Core::App {
		public:
			/// constructor
			SnowflakeApp();
			/// destructor
			~SnowflakeApp();

			GLfloat* createTriangle(GLfloat a, GLfloat cx, GLfloat cy);

			void translatePoint(GLfloat* px, GLfloat* py, GLfloat tx, GLfloat ty);

			void rotatePoint(GLfloat* px, GLfloat* py, float angle);

			GLfloat* calcTriangle(GLfloat ps[4]);

			GLfloat* calcSnowflake(GLfloat* triangle, int num_points, int depth);

			/// open app
			bool Open();
			/// run app
			void Run();
		private:

			GLuint program;
			GLuint vertexShader;
			GLuint pixelShader;
			GLuint triangle;
			Display::Window* window;
			int depth;
			int num_points;
	};
} // namespace Snowflake