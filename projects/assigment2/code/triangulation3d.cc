#include "triangulation3d.h"
#include "reader.h"
#include <iostream>

namespace Triangulation3d {

    Triangulation3d::Triangulation3d() {

    }
    
    Triangulation3d::~Triangulation3d() {
        
    }

    bool Triangulation3d::Open() {
        Reader r;
        r.readPoints("/home/niklas/Desktop/D7045E/assigments/opengl-lab-env/projects/assigment2/code/test.txt");
        return false;
    }

    void Triangulation3d::Run() {
       
    }
}
