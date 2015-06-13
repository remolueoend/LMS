cmake_minimum_required(VERSION 3.2)
project(LMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    headers/Action.h
    headers/Book.h
    headers/Borrow.h
    headers/EscapeException.h
    headers/IO.h
    headers/List.h
    headers/LMS.h
    headers/Menu.h
    headers/App.h
    headers/Selectable.h
    headers/Student.h
    src/Book.cpp
    src/Borrow.cpp
    src/IO.cpp
    src/LMS.cpp
    src/main.cpp
    src/Menu.cpp
    src/App.cpp
    src/Selectable.cpp
    src/Student.cpp
    headers/Dictionary.h
    headers/GroupableList.h
    src/Record.cpp
    headers/Record.h
    src/Actions.cpp
    headers/Actions.h)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(LMS ${SOURCE_FILES})