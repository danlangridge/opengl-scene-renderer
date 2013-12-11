#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Object_test

#include <boost/test/unit_test.hpp>

#include <Object.h>


BOOST_AUTO_TEST_SUITE( ObjectTest )

BOOST_AUTO_TEST_CASE ( Position_test )
{
  Object object;

  object.setPosition(2,2,2);

  Vector position;
  position = object.getPosition();

  BOOST_CHECK( position.x == 2  );
}

BOOST_AUTO_TEST_CASE ( Orientation_test )
{

}

BOOST_AUTO_TEST_SUITE_END()
