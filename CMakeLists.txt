cmake_minimum_required(VERSION 2.8)
project(StrProc)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(srt-proc
	main.cpp
	srt-editor.cpp
	srt-record.cpp
	srt-time.cpp)

