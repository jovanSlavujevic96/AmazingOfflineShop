project(app LANGUAGES CXX)

add_executable(AmazingShop
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cc"
)
target_link_libraries(AmazingShop PUBLIC AmazingAPI)
target_include_directories(AmazingShop PUBLIC "${CMAKE_SOURCE_DIR}/lib")
