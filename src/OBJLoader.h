#include <Loader.h>

#include <Vector.h>
#include <string>

/* OBJLoader 
 * Wavefront .obj file format Loader
 * loads vertices into a Vector buffer.
 */
class OBJLoader : public Loader {

public:
  Vector* loadModelFromFile(std::string filename); 

};
