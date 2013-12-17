#include <OBJLoader.h>
#include <fstream>
#include <string>

Vector* OBJLoader::loadModelFromFile(std::string filename) {

  std::fstream file;
  file.open(filename.c_str());

  char currentWord[256] = {0};
  
  Vector* model = new Vector[100];
  unsigned modelIndex = 0, vectorIndex = 0; 

  Vector* currentVector;
  
  while(file.good()) {
  
   // get next contiguous word/number
   file.getline(currentWord, 256);    
  
   std::string currentWordString(currentWord);
   
   // Comment. Ignore and move on
   if (currentWordString[0] == '#') {
     file.getline(currentWord, 256);
   }
   else if (currentWordString[0] == 'v') {
     currentVector = new Vector();
     model[modelIndex] = *currentVector;
     int i = 0;
     while ( currentWordString.find(' ') ) {
       std::string posData = currentWordString.substr(0,currentWordString.find("\\"));
       //currentVector[i] = atof(posData.c_str()); 
       i++;
       currentWordString = currentWordString.substr(' ',currentWordString.length());
     }
     modelIndex++;
   }
   else if (currentWordString[0] == 'f') {
     //TODO: handle face data 
   }
  }

  file.close();
  return model; 
}
