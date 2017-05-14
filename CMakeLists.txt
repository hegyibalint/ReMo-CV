cmake_minimum_required(VERSION 3.6)
project(ReMoCV)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package (ZBar)
include_directories( ${ZBAR_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES cv.hpp cv.cpp)

add_executable(ReMoCalib calib.cpp ${SOURCE_FILES})
target_link_libraries( ReMoCalib ${OpenCV_LIBS} ${ZBAR_LIBRARIES} ${PUGIXML_LIBRARY})

add_executable(ReMoCorrect ${SOURCE_FILES} correct.cpp)
target_link_libraries( ReMoCorrect ${OpenCV_LIBS} ${ZBAR_LIBRARIES} ${PUGIXML_LIBRARY})