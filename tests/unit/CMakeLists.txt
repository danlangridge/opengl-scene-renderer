find_package ( Boost COMPONENTS unit_test_framework REQUIRED )

add_executable ( LoaderTests LoaderTests.cpp )

add_dependencies ( LoaderTests Loaders Gravel )

target_link_libraries ( LoaderTests
                        Loaders
                        Gravel
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                      )

add_executable ( ObjectTests ObjectTests.cpp )

add_dependencies ( ObjectTests Graphics Gravel )

target_link_libraries ( ObjectTests
                        Graphics
                        Gravel
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                      )

enable_testing ()

add_test ( LDTests LoaderTests )
add_test ( OBTests ObjectTests )
