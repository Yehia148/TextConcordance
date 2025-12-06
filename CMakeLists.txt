cmake_minimum_required(VERSION 3.16)
project(TextConcordance)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(TextConcordanceLib STATIC
        ConcordanceTree.cpp
        TrieConcordance.cpp
)

target_include_directories(TextConcordanceLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(TextConcordanceCLI
        main.cpp
        WordNetSynonyms.cpp
        WordNetSynonyms.h
        map.cpp
        UIForTextProject/GhostTextEdit.h
        UIForTextProject/GhostTextEdit.cpp
)


target_link_libraries(TextConcordanceCLI PRIVATE TextConcordanceLib)


set_target_properties(TextConcordanceCLI PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

