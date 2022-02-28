cmake_minimum_required(VERSION 3.0)

project(mask_r_cnn_c++)

IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native")

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   add_definitions(-DCOMPILEDWITHC0X)
   message(STATUS "Using flag -std=c++0x.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

message("PROJECT_SOURCE_DIR: " ${OpenCV_DIR})
find_package(OpenCV 2.4.11 QUIET)
if(NOT OpenCV_FOUND)
    message("OpenCV > 2.4.11 not found.")
    find_package(OpenCV 3.4 QUIET)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV > 3.0 not found.")
    else()
        message("OpenCV libs were found! ")
        message("OpenCV libs directory : " ${OpenCV_INCLUDE_DIRS})
    endif()
endif()

find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

#set (PythonLibs_DIR /home/george/anaconda3/envs/tensorflow1.5/)
#find_package(PythonLibs REQUIRED)
#if (NOT PythonLibs_FOUND)
#  message(FATAL_ERROR "PYTHON LIBS not found. ")
#else()
#  message("PYTHON LIBS were found!")
#  message("PYTHON LIBS DIRECTORY: " ${PYTHON_LIBRARY}) 
#endif()


set(PYTHON_LIBRARY /home/george/anaconda3/envs/tensorflow_gpu/lib/libpython3.6m.so)

find_package(Boost REQUIRED COMPONENTS thread)
if(Boost_FOUND)
    message("Boost was found!")
    message("Boost Headers DIRECTORY: " ${Boost_INCLUDE_DIRS})
    message("Boost LIBS DIRECTORY: " ${Boost_LIBRARY_DIRS})
    message("Found Libraries: " ${Boost_LIBRARIES})
endif()

set(PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS} /home/george/anaconda3/envs/tensorflow_gpu/lib/python3.6/site-packages/numpy/core/include/numpy)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
/home/george/anaconda3/envs/tensorflow_gpu/include/python3.6m/
/home/george/anaconda3/envs/tensorflow_gpu/lib/python3.6/site-packages/numpy/core/include/numpy
${Boost_INCLUDE_DIRS}
${EIGEN3_INCLUDE_DIR}
${Pangolin_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS}
)


set(own_lib
${PYTHON_LIBRARY}
${Boost_LIBRARIES}
${OpenCV_LIBS}
${EIGEN3_LIBS}
${Pangolin_LIBRARIES}
)

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#add_executable(lab1 src/lab1.cpp)
#target_link_libraries(lab1 ${own_lib})

#add_executable(lab_class src/lab_class.cpp)
#target_link_libraries(lab_class ${own_lib})

add_executable(mask_cnn_use src/mask_cnn_use.cpp)
target_link_libraries(mask_cnn_use ${own_lib})

add_executable(get_mask src/get_mask.cpp)
target_link_libraries(get_mask ${own_lib})

add_executable(use_mask_with_pic src/use_mask_with_pic.cpp)
target_link_libraries(use_mask_with_pic ${own_lib})

add_executable(for_use_mask src/for_use_mask.cpp)
target_link_libraries(for_use_mask ${own_lib})

#add_executable(learn1 src/learn1.cpp)
#target_link_libraries(learn1 ${own_lib})