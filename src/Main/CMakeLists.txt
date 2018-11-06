set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
file(GLOB SOURCE_FILES *.cpp)

add_executable(Main ${SOURCE_FILES})
target_link_libraries(Main QtWindow OSGRender Data BaseClass MathMethod)