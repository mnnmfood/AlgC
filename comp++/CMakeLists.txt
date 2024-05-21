# CMakeList.txt : CMake project for comp++, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (comp++ "main.cpp" "sort/sort.h")

FILE(GLOB_RECURSE SRC_LIST "${PROJECT_SOURCE_DIR}" "*.h")
include(CMakePrintHelpers)
cmake_print_variables(SRC_LIST)
foreach(src "${SRC_LIST}")
    cmake_print_variables(subdir)
	target_sources(comp++ PUBLIC "${src}")
endforeach()

target_include_directories(comp++ PUBLIC
	"${PROJECT_SOURCE_DIR}/comp++/"
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET comp++ PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
