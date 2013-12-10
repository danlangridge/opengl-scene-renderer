#include <OBJLoader.h>

#include <fstream>


Vector* OBJLoader::loadModelFromFile(std::string filename) {

  std::fstream file;
  file.open(filename.c_str());

  char currentWord[256] = {0};
  
  Vector* model = new Vector[100];
  unsigned modelIndex = 0, vectorIndex = 0; 

  Vector* currentVector;
  
  while(file.good()) {
   
   file.get(currentWord, 256);    
   
   if (currentWord[0] == '#') {
     file.getline(currentWord, 256);
   }
   if (currentWord[0] == 'v') {
     model[modelIndex] = *currentVector; 
   }
   else {
     switch(vectorIndex) {
       case 0:
         currentVector->x = (float)*currentWord; 
         break;
       case 1:
         currentVector->y = (float)*currentWord; 
         break;
       case 2:
         currentVector->z = (float)*currentWord; 
         break;
       case 3:
         vectorIndex = 0;
         modelIndex++;
         currentVector = new Vector();
       break;
     }
     vectorIndex++;
   }

  }

  file.close();
  return model; 
}
