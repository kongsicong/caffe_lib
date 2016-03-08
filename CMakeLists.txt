project(CaffeTest)
cmake_minimum_required(VERSION 2.5 FATAL_ERROR)
if(COMMAND cmake_policy)
     cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


#链接opencv库
find_package(OpenCV REQUIRED)


#链接caffe_lib库
include_directories(${CMAKE_SOURCE_DIR}/caffe_lib/include/)
link_directories(${CMAKE_SOURCE_DIR}/caffe_lib/lib/)


#链接caffe_lib的依赖库
include_directories(${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include ${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include/openblas ${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include/google)
include_directories(${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include/gtest ${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include/gflags ${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/include/glog)
include_directories(${CMAKE_SOURCE_DIR}/caffe_lib/include)
link_directories(${CMAKE_SOURCE_DIR}/caffe_lib/3rdparty/lib)
set(LIBS debug gflagsd optimized gflags
         debug gflags_nothreadsd optimized gflags_nothreads
         debug libglogd optimized libglog
         debug libprotobufd optimized libprotobuf
         debug libprotocd optimized libprotoc
         debug libcaffed optimized libcaffe
         libopenblas Shlwapi)
#链接boost库
set(BOOST_DIR $ENV{BOOST_DIR})
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)




#生成执行文件的源文件及头文件
file(GLOB SRC ./*.cpp)
file(GLOB INC ./*.h ./*.hpp)


add_executable(testCaffe ${SRC} ${INC})
target_link_libraries(testCaffe ${LIBS} ${OpenCV_LIBS})