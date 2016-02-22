cmake_minimum_required(VERSION 3.0)
project(SSVOpenHexagon)

#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
execute_process(
  COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
  RESULT_VARIABLE error_code
  OUTPUT_QUIET ERROR_QUIET)
if(error_code)
  message(FATAL_ERROR "CPM failed to get the hash for HEAD")
endif()
endif()
include(${CPM_DIR}/CPM.cmake)

#------------------------------------------------------------------------------
# CPM Modules
#------------------------------------------------------------------------------

#SET(SSVDeps "SSVCMake;SSVEntitySystem;SSVLuaWrapper;SSVMenuSystem;SSVStart;SSVUtils;vrm_pp")
SET(SSVDepsRoot "https://github.com/lukeadams/")
#SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
CPM_AddModule("SSVCMake"
	GIT_REPOSITORY "${SSVDepsRoot}SSVCMake"
	GIT_TAG "cpm")
SET(CMAKE_MODULE_PATH ${CPM_KV_SOURCEDIR_MAP_SSVCMake}/cmake/modules ${CMAKE_MODULE_PATH})
include(SSVCMake)

CPM_AddModule("SSVEntitySystem"
	GIT_REPOSITORY "${SSVDepsRoot}SSVEntitySystem"
	GIT_TAG "cpm")
CPM_AddModule("SSVLuaWrapper"
	GIT_REPOSITORY "${SSVDepsRoot}SSVLuaWrapper"
	GIT_TAG "cpm")
#SET(CMAKE_MODULE_PATH ${CPM_KV_SOURCEDIR_MAP_SSVLuaWrapper}/cmake/modules ${CMAKE_MODULE_PATH})
CPM_AddModule("SSVMenuSystem"
	GIT_REPOSITORY "${SSVDepsRoot}SSVMenuSystem"
	GIT_TAG "cpm")
CPM_AddModule("SSVStart"
	GIT_REPOSITORY "${SSVDepsRoot}SSVStart"
	GIT_TAG "cpm")
CPM_AddModule("SSVUtils" #Not workign rn
	GIT_REPOSITORY "${SSVDepsRoot}SSVUtils"
	GIT_TAG "cpm")
CPM_AddModule("vrm_pp"
	GIT_REPOSITORY "${SSVDepsRoot}vrm_pp"
	GIT_TAG "cpm")
CPM_Finish()
#------------------------------------------------------------------------------
# Build
#------------------------------------------------------------------------------

vrm_cmake_init_project(SSVOpenHexagon)

SSVCMake_setDefaults()
vrm_cmake_add_common_compiler_flags()

file(GLOB_RECURSE LIST "src/*.cpp") #Generate list of source files
include_directories("./include")	#Include headers


find_package(LUA REQUIRED)
find_package(ZLIB REQUIRED)
#find_package(SFML 2 REQUIRED graphics window network audio system)

#include_directories(${SFML_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

include_directories(${LUA_INCLUDE_DIR})

SSVCMake_findSFML()
#vrm_cmake_init_project(${PROJECT_NAME})

include_directories(${ZLIB_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${LIST})

target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
SSVCMake_linkSFML()
