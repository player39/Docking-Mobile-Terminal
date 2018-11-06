project(OSGShip)
cmake_minimum_required(VERSION 3.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(3RDPARTY_DIR "C:/3rdpart")
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Network)
find_package(OpenSceneGraph 3.0.0 REQUIRED osgDB osgGA osgUtil osgText osgViewer osgWidget)
find_package(osgqt)
find_package(Qt5OpenGL)
find_package(Boost)
include_directories(
${PROJECT_SOURCE_DIR}/include
${OPENSCENEGRAPH_INCLUDE_DIRS}
${Qt5Widgets_INCLUDE_DIRS}
${OSGQT_INCLUDE_DIR}
${Qt5OpenGL_INCLUDE_DIRS}
${Boost_INCLUDE_DIR}
${CMAKE_BINARY_DIR}/src/QtWindow
)
add_subdirectory(src)