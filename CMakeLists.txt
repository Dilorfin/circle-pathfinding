cmake_minimum_required(VERSION 3.20)

set(PROJECT_TITLE CirclePathfinding)

project(${PROJECT_TITLE} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TESTS "Building tests require doctest library")
option(BUILD_BENCHMARKS "Building benhmarks require nanobench library")

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)	
endif(CMAKE_CONFIGURATION_TYPES)

find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED) # graphics audio network system window

set(GENERAL_DEPENDENCIES SFML::System SFML::Window SFML::Graphics)

file(
	GLOB_RECURSE SOURCE_LIST
	"*.[hc]pp"
	"*.[hc]"
)

list(FILTER SOURCE_LIST EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}\/[.].*\/")

add_executable(${PROJECT_TITLE} ${SOURCE_LIST})

target_link_libraries(${PROJECT_TITLE} ${GENERAL_DEPENDENCIES}) # SFML::<component>

if(BUILD_TESTS OR BUILD_BENCHMARKS)
	set(SOURCE_LIST_WO_MAIN ${SOURCE_LIST})
	list(FILTER SOURCE_LIST_WO_MAIN EXCLUDE REGEX ".*main\.cpp")
endif(BUILD_TESTS OR BUILD_BENCHMARKS)

if(BUILD_TESTS)
	find_package(doctest REQUIRED)
	message("-- Found doctest in ${doctest_DIR}")

	enable_testing()

	add_subdirectory(.tests)
endif(BUILD_TESTS)

if(BUILD_BENCHMARKS)
	find_package(nanobench REQUIRED)
	message("-- Found nanobench in ${nanobench_DIR}")

	add_subdirectory(.benchmarks)
endif(BUILD_BENCHMARKS)

# Prettify IDEs Projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Visual Studio Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_TITLE})
# sourse file grouping for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
