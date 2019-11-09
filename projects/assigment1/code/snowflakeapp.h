#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for Snowflake application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "snowflakeobj.h"
namespace SnowflakeApp {
	class SnowflakeApp : public Core::App {
		public:
			/// constructor
			SnowflakeApp();
			/// destructor
			~SnowflakeApp();

			/// open app
			bool Open();
			/// run app
			void Run();
		private:

			GLuint program;
			GLuint vertexShader;
			GLuint pixelShader;
			GLuint vertex;
			Display::Window* window;

			void updateBuffer();

			Snowflake::SnowflakeObj snowFlake;
	};
} // namespace SnowflakeApp