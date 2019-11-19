#include "core/app.h"
#include <string>

namespace Triangulation3d {
	class Reader : public Core::App {
		public:
			// constructor
			Reader();
			
            // destructor
			~Reader();
        
            // Var


            // funcs
            GLfloat* readPoints(std::string file_path);


		private:
            // Var


            // Funcs
            

	};
} // namespace Triangulation3d