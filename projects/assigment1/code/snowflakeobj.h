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

            float getSize();

            void setSize(float s);

            float getAngle();

            void setAngle(float a);

            int getDepth();

            void setDepth(int d);

            int getNumPoints();

            GLfloat* getSnowFlake();

            GLfloat* getTriangleSnowFlake();

		private:
        // Var
            float size;
            float angle;

			int depth;
			int numPoints;

            GLfloat* snowFlake;
            GLfloat* triangleSnowFlake;
            int pos;

        // Funcs
            GLfloat* createTriangle(GLfloat a);

			GLfloat* calcTriangle(GLfloat ps[4]);

			GLfloat* calcSnowflake(GLfloat* triangle, int num_points, int depth);

	};
} // namespace Snowflake