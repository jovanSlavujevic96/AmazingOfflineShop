project(lib LANGUAGES CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(AmazingAPI STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/IObjects.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Items.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Items.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Discounts.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Discounts.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Orders.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/Orders.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/ProcessedOrders.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects/ProcessedOrders.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/IFileReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/IFileReader.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/CsvReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/CsvReader.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/TextReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_reader/TextReader.cc"
)
