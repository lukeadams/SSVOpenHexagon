cmake_minimum_required(VERSION 3.0)

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
#foreach(dep ${SSVDeps})
CPM_AddModule("SSVCMake"
	GIT_REPOSITORY "${SSVDepsRoot}SSVCMake"
	USE_EXISTING_VER false
	GIT_TAG "cpm")
SET(CMAKE_MODULE_PATH ${CPM_KV_SOURCEDIR_MAP_SSVCMake}/cmake/modules ${CMAKE_MODULE_PATH})
include(SSVCMake)
#endforeach(dep)
CPM_Finish()
