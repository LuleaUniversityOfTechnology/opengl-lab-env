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
	class Slider : public Core::App {
		public:
			/// constructor
			Slider(Display::Window* window, int min, int max, float posx, float posy, float size);
			/// destructor
			~Slider();

            bool getNewValue();

            int getValue();

            GLfloat* getSliderVertex();

		private:
            Display::Window* window;

            int min;
            int max;

            float posx;
            float posy;

            float size;

            bool wasPressed;
			bool newValue;
			int value;

            GLfloat* slider;
        
            void start();

            void calcVertex();
	};
} // namespace Snowflake