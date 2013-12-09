#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Loader_test

#include <boost/test/unit_test.hpp>

#include <OBJLoader.h>
#include <Vector.h>


BOOST_AUTO_TEST_SUITE( LoadersTest )

BOOST_AUTO_TEST_CASE ( OBJLoader_test )
{
  OBJLoader objLoader;
  Vector* vector = objLoader.loadModelFromFile("OBJSimpleInput.OBJ");
}


BOOST_AUTO_TEST_SUITE_END()
