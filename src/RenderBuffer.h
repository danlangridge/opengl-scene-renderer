#include <boost/unordered_map.hpp>
#include <VertexArrayObject.h>
#include <string>

class RenderBuffer {
  boost::unordered_map<std::string,VertexArrayObject> _objectsCurrentlyRendering;

};
