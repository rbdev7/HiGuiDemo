# CMakeList.txt : CMake project for HiGuiDemo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HiGuiDemo")

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
else()
	message(STATUS "OpenCV NOT found !")
endif(OpenCV_FOUND)

set(VCPKG_INSTALL_OPTIONS "--clean-after-build")

include_directories(include)

# Add source to this project's executable.
add_executable (higui_demo "src/HiGuiDemo.cpp" "include/HiGuiDemo.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET higui_demo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(higui_demo ${OpenCV_LIBRARIES})