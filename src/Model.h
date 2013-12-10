#include <Vector.h>

/**
 * Model contains all of the information needed to rendure an object's model
 */ 
class Model : public Object {

public:
 
 Model();
 
 int loadVertices(char* filename);

 int loadTexture(char* filename);

 Vector* getVertices(char* filename);

private:
 Vector* _vertices;


};
