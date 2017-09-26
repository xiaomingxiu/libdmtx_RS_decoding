project(baredmtx)
cmake_minimum_required( VERSION 3.9 )

find_package(OpenCV)

#link_directories(/usr/local/lib)#this sentence can not be put below.

add_executable(bare main.cpp)

target_link_libraries(bare dmtx ${OpenCV_LIBS}  )


