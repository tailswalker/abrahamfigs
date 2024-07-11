cmake_minimum_required(VERSION 2.8)
project( lgca )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(
	lgca
	main.cpp
	wire/aux_func.h
	wire/node.h
	wire/lgca.h
)
target_link_libraries( lgca ${OpenCV_LIBS} )