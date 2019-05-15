cmake_minimum_required(VERSION 3.13)
project(SSSQsim)

set(CMAKE_CXX_STANDARD 14)

add_executable(SSSQsim main.cpp Distribution.h Distribution.cpp Entity.h Entity.cpp SimObj.h SimObj.cpp Sink.h Sink.cpp Source.cpp Source.h SSSQ.h SSSQ.cpp)