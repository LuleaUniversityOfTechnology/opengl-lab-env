#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for Snowflake application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
namespace Snowflake {
	class SnowflakeObj : public Core::App {
		public:
			/// constructor
			SnowflakeObj();
			/// destructor
			~SnowflakeObj();

        // funcs
            void create();

            float getPosX();
            float getPosY();
            float getAngle();

            void setPos(float x, float y);
            void setAngle(float a);

            int getDepth();

            void setDepth(int d);

            int getNumPoints();

            GLfloat* getSnowFlake();

		private:
        // Var
            float posx;
            float posy;
            float angle;

			int depth;
			int numPoints;

            GLfloat* snowFlake;

        // Funcs
            GLfloat* createTriangle(GLfloat a, GLfloat cx, GLfloat cy);

			GLfloat* calcTriangle(GLfloat ps[4]);

			GLfloat* calcSnowflake(GLfloat* triangle, int num_points, int depth);

            void translatePoint(GLfloat* px, GLfloat* py, GLfloat tx, GLfloat ty);

			void rotatePoint(GLfloat* px, GLfloat* py, float angle);

            void translateSnowflake(float x, float y);

            void rotateSnowflake(float angle);

	};
} // namespace Snowflake