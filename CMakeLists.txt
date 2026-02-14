cmake_minimum_required(VERSION 3.16)

project(spreadsheet)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCE_FILES
	src/main.cpp
	src/Cell.cpp
	src/Cell.h
	src/FunctionFactory.cpp
	src/FunctionFactory.h
	src/Function.h
	src/Max.cpp
	src/Max.h
	src/Mean.cpp
	src/Mean.h
	src/Min.cpp
	src/Min.h
	src/Observer.h
	src/Spreadsheet.cpp
	src/Spreadsheet.h
	src/SpreadsheetWindow.cpp
	src/SpreadsheetWindow.h
	src/Subject.h
	src/Sum.cpp
	src/Sum.h
)

add_executable(spreadsheet ${SOURCE_FILES})

target_link_libraries(spreadsheet Qt6::Widgets)
