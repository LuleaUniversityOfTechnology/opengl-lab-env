#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>

namespace Triangulation3d {

    Reader::Reader() {
        //empty
    }
    
    Reader::~Reader() {
        //empty
    }

    /**
     *  Reads points from file.
     *  file_path: is the path to the file.
     *  Note: Delete return value when done to avoid memory leaks.
     */
    GLfloat* Reader::readPoints(std::string file_path) {
        std::ifstream infile(file_path);
        int length;
        infile >> length;
        std::cout << length;
        std::cout << "\n";

        GLfloat* points = new GLfloat[length * 2];

        for (int i = 0; i < length; i++) {
            GLfloat x, y;
            infile >> x >> y;
            std::cout << x;
            std::cout << " ";
            std::cout << y;
            std::cout << "\n";
            points[0 + i * 2] = x;
            points[1 + i * 2] = y;
        }
        return NULL;
    }
}
