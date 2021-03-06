CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(BOUNDARYMODULE)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

FIND_PACKAGE(Eigen3 REQUIRED)

SET(CORE_SOURCES		src/main.cpp
						src/ClusterManager.cpp
						src/ClusterNodes.cpp
						src/NodeCalculations.cpp
						src/BoundaryProcessor.cpp
						src/NodeProcessor.cpp
						src/InputParser.cpp)
				
SET(CORE_HEADERS		include/ClusterManager.h
						include/ClusterNodes.h
						include/NodeCalculations.h
						include/BoundaryProcessor.h
						include/NodeProcessor.h
						include/InputParser.h)

SET(BOUNDARYMODULE_SOURCES	${CORE_SOURCES})
SET(BOUNDARYMODULE_HEADERS	${CORE_HEADERS})

SOURCE_GROUP("Source Files" FILES ${CORE_SOURCES})
SOURCE_GROUP("Header Files" FILES ${CORE_HEADERS})

INCLUDE_DIRECTORIES(${CMAKE_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include
					${CMAKE_BINARY_DIR})
				
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/build.mac)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

SET(CMAKE_XCODE_ATTRIBUTE_USER_HEADER_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(CMAKE_XCODE_ATTRIBUTE_USER_HEADER_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_EXECUTABLE(BOUNDARYMODULE	${CORE_SOURCES}	${CORE_HEADERS})

# TARGET_LINK_LIBRARIES(BOUNDARYMODULE	Eigen3)