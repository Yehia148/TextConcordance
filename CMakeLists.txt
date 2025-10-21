cmake_minimum_required(VERSION 4.0)
project(TextConcordance)

set(CMAKE_CXX_STANDARD 20)

add_executable(TextConcordance main.cpp
        ConcordanceTree.h
        ConcordanceTree.cpp)
