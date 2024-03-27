# CMakeList.txt : CMake project for comp++, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (comp++ "main.cpp"  "linked_list.h" "skip_list.h" "queue.h" "binary_tree.h")

target_include_directories(comp++ PUBLIC
	"${PROJECT_SOURCE_DIR}/comp++/"
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET comp++ PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
