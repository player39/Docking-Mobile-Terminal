set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/LinkBackground/*.h)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/LinkBackground/*.cpp)

add_library(LinkBackground STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(LinkBackground Qt5::Network Qt5::Core)