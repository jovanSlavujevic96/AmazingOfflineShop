cmake_minimum_required(VERSION 3.20)
project(Amazing_Offline_Shop CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(AmazingAPI STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/IObjects.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Items.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Items.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Discounts.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Discounts.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Orders.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/Orders.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/ProcessedOrders.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/objects/ProcessedOrders.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/IFileReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/IFileReader.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/CsvReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/CsvReader.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/TextReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/amazing/file_reader/TextReader.cc"
)
target_include_directories(AmazingAPI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/amazing")

add_executable(AmazingShop
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cc"
)
target_link_libraries(AmazingShop PUBLIC AmazingAPI)
