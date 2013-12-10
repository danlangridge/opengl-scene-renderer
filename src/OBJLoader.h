#include <Loader.h>

#include <Vector.h>
#include <string.h>

class OBJLoader : public Loader {

public:
  Vector* loadModelFromFile(std::string filename); 

};
