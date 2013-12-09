find_package ( Boost COMPONENTS unit_test_framework REQUIRED )

add_executable ( LoaderTests LoaderTests.cpp )

add_dependencies ( LoaderTests Loaders Gravel )

target_link_libraries ( LoaderTests
                        Loaders
                        Gravel
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                      )

enable_testing ()

add_test ( LDTests LoaderTests )
