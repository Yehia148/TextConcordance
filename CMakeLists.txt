cmake_minimum_required(VERSION 4.0)
project(TextConcordance)

set(CMAKE_CXX_STANDARD 20)

add_executable(TextConcordance
        main.cpp
        ConcordanceTree.h
        ConcordanceTree.cpp
        TrieConcordance.h
        TrieConcordance.cpp
)
set_target_properties(TextConcordance PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)