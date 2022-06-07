project(test LANGUAGES CXX)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(AmazingShopTest
	"${CMAKE_CURRENT_SOURCE_DIR}/test.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/CsvReaderTest.cc"
)
target_link_libraries(AmazingShopTest PUBLIC
	GTest::gtest
	GTest::gtest_main
#	GTest::gmock
	AmazingAPI
)
target_include_directories(AmazingShopTest PUBLIC
	"${CMAKE_SOURCE_DIR}/lib"
)

enable_testing()

add_test(CMakeAmazingShopTest AmazingShopTest)
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS AmazingShopTest)
