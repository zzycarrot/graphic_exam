cmake_minimum_required(VERSION 3.21)
project(graphic_exam)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/Users/ez_zz/Desktop/Lessons/graphic_exam/include)
link_directories(C:/Users/ez_zz/Desktop/Lessons/graphic_exam/lib/x64)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY )		# 指定编译后exe放入文件夹中
add_executable(graphic_exam main.cpp test1.cpp geomodeling.cpp)
target_link_libraries(graphic_exam libopengl32.a  libfreeglut.a  glu32.dll) #链接对应的库文件
