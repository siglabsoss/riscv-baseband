

cmake_minimum_required(VERSION 3.5)
project(CModem VERSION 0.1 LANGUAGES CXX)
# project(CModem)
#set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
#set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
#set(CMAKE_ASM_COMPILER arm-linux-gnueabihf-as)
#find_program(CMAKE_AR NAMES "arm-linux-gnueabihf-ar")
#find_program(CMAKE_RANLIB NAMES "arm-linux-gnueabihf-ranlib")

#################
# 
#  CMake Tradition is that users make a folder called "build", cd into there, and do cmake ..
#  this line simply enfoces that
#
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "\n\nIn-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
#end bad things


# # utils related to cmake, should come first so we can use them later
# include(utils.cmake)


# #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# # capture this somewhere better but we need to install
# #  sudo apt-get install g++-5-multilib-arm-linux-gnueabihf
# #set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
# set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++-5)

# set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc-5)

# # https://gcc.gnu.org/onlinedocs/gcc-4.8.3/gcc/ARM-Options.html
# # https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
# # https://gcc.gnu.org/onlinedocs/gcc-4.9.3/gcc/AArch64-Options.html
set(CMAKE_CXX_FLAGS  "-g -std=c++14")
# #set(CMAKE_CXX_FLAGS  "-march=armv8-a -mtune=cortex-a53 -mcpu=cortex-a53")
# #set( CMAKE_CXX_FLAGS  "-march=armv8-a -mfpu=neon-vfpv4  -mfloat-abi=hard -mcpu=cortex-a -std=c++11")

# #set( CMAKE_C_FLAGS  "-march=armv7ve -marm -mfpu=neon-vfpv4  -mfloat-abi=hard -mcpu=cortex-a")


# find_library(NE10_LIB_PATH libNE10.a HINTS ../Ne10/build/modules)


# #LINK_DIRECTORIES('/root/Ne10/build/modules')

# # threadding
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)



set(MODEL_SOURCES
    src/models/slice.cpp
    src/models/slice.hpp
)

set(CONTAINER_SOURCES
	src/models/slice_container.hpp
	src/models/slice_container.cpp
)


add_library(model_base OBJECT ${MODEL_SOURCES})
add_library(model_base_static STATIC $<TARGET_OBJECTS:model_base>)
target_link_libraries(model_base_static model_container_static)


add_library(model_container OBJECT ${CONTAINER_SOURCES})
add_library(model_container_static STATIC $<TARGET_OBJECTS:model_container>)
target_link_libraries(model_container_static model_base_static)


include_directories(
    ${PROJECT_SOURCE_DIR}/src/models
    /usr/local/include/
)


add_executable(test_slice src/main/test_slice.cpp )
target_link_libraries(test_slice m model_base_static)

add_executable(test_container src/main/test_slice_container.cpp)
target_link_libraries(test_container m model_base_static model_container_static)

