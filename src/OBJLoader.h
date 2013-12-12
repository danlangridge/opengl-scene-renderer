#include <Loader.h>

#include <Vector.h>
#include <string>

class OBJLoader : public Loader {

public:
  Vector* loadModelFromFile(std::string filename); 

};
