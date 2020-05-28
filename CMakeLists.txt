cmake_minimum_required(VERSION 3.16)
project(L_System_Visualizer_Importer_Tests)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:\\Qt\\Qt5.9.9\\5.9.9\\mingw53_32)

    set(GLM_FOLDER C:/glm-0.9.9.8/glm)
endif(WIN32)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${GLM_FOLDER})
include_directories(${Qt5Widgets_INCLUDES})

add_executable(L_System_Visualizer_Importer_Tests main.cpp Importer/Model.h Importer/Model.cpp Importer/ReadResult.h Importer/ReadResult.cpp
                Tests/TestImporter.cpp Tests/TestImporter.h)

target_link_libraries(L_System_Visualizer_Importer_Tests ${Qt5Widgets_LIBRARIES} ${Qt5Test_LIBRARIES})