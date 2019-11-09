//------------------------------------------------------------------------------
// snowflakeapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "slider.h"
#include <math.h>

using namespace Display;
namespace Snowflake {

	//------------------------------------------------------------------------------
	/**
	*/
	Slider::Slider(Display::Window* window, int min, int max, float posx, float posy, float size) {
		this->window = window;
        this->min = min;
        this->max = max;
        this->posx = posx;
        this->posy = posy;
        this->size = size;

        this->wasPressed = false;
		this->newValue = false;
        this->value = min;
        start();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Slider::~Slider() {
		delete[] this->slider;
	}

	//------------------------------------------------------------------------------
	/**
	*/


	void Slider::start(){
        calcVertex();
		window->SetMousePressFunction([this](int32 button, int32 pressed, int32 c) {
			if (pressed && button == GLFW_MOUSE_BUTTON_LEFT) {
				this->wasPressed = true;
			}

			if (pressed == 0 && button == GLFW_MOUSE_BUTTON_LEFT) {
				if (this->wasPressed) {
					this->newValue = true;
					this->wasPressed = false;
                    calcVertex();
				}
			}
		});

		window->SetMouseMoveFunction([this](float64 x, float64 y) {
            float dx = this->size * (this->max + 1 - this->min);
            float dy = this->size;
            float rx = (x)/500 - 1;
            float ry = (y)/500 - 1;

            
            if (rx > this->posx - dx/2 && rx < this->posx + dx/2) {
                if (ry > -this->posy && ry < -this->posy + dy) {
                    int v = ((int)round(( (rx - (this->posx - dx/2))/this->size))) + min;
                    if (v >= this->max) {
                        v = this->max;
                    }
                    this->value = v;
                }
            }
		});
	}

    void Slider::calcVertex() {
        delete[] this->slider;

        GLfloat* sliderVertexs = new GLfloat[24];

        float dx = this->size * (this->max + 1 - this->min);
        float dy = this->size;
        float size = this->size;
        int value = this->value - this->min;

        sliderVertexs[0] = this->posx - dx/2;
        sliderVertexs[1] = this->posy - dy/2;
        sliderVertexs[2] = -1;

        sliderVertexs[3] = this->posx - dx/2;
        sliderVertexs[4] = this->posy + dy/2;
        sliderVertexs[5] = -1;

        sliderVertexs[6] = this->posx + dx/2;
        sliderVertexs[7] = this->posy + dy/2;
        sliderVertexs[8] = -1;

        sliderVertexs[9] = this->posx + dx/2;
        sliderVertexs[10] = this->posy - dy/2;
        sliderVertexs[11] = -1;

        sliderVertexs[12] = this->posx - dx/2 + value * size;
        sliderVertexs[13] = this->posy - size/2;
        sliderVertexs[14] = -1;

        sliderVertexs[15] = this->posx - dx/2 + value * size;
        sliderVertexs[16] = this->posy + size/2;
        sliderVertexs[17] = -1;

        sliderVertexs[18] = this->posx - dx/2 + value * size + size;
        sliderVertexs[19] = this->posy + size/2;
        sliderVertexs[20] = -1;

        sliderVertexs[21] = this->posx - dx/2 + value * size + size;
        sliderVertexs[22] = this->posy - size/2;
        sliderVertexs[23] = -1;
        
        this->slider = sliderVertexs;
    }

    bool Slider::getNewValue() {
         return this->newValue;
     }

    int Slider::getValue() {
        this->newValue = false;
        return this->value + min;
    }

    GLfloat* Slider::getSliderVertex() {
        return this->slider;
    }


} // namespace Snowflake