cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pcl-tcp)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Set PCL_INCLUDE_DIRS to the include directory of the PCL library
set(PCL_INCLUDE_DIRS /usr/local/include/pcl-1.12)

# Set PCL_LIBRARY_DIRS to the directory containing the PCL library
set(PCL_LIBRARY_DIRS /usr/local/lib)

# Set PCL_DEFINITIONS to any additional compiler flags required by the PCL library
set(PCL_DEFINITIONS -DPCL_NO_PRECOMPILE)
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(ply_to_pcd src/ply_to_pcd.cpp)
target_link_libraries(ply_to_pcd ${PCL_LIBRARIES})

add_executable(pcd_to_ply src/pcd_to_ply.cpp)
target_link_libraries(pcd_to_ply ${PCL_LIBRARIES})

add_executable(server src/server.cpp)
target_link_libraries(server ${PCL_LIBRARIES})

add_executable(client1 src/client1.cpp)
target_link_libraries(client1 ${PCL_LIBRARIES})

add_executable(client2 src/client2.cpp)
target_link_libraries(client2 ${PCL_LIBRARIES})

add_executable(client src/client3.cpp)
target_link_libraries(client ${PCL_LIBRARIES})

