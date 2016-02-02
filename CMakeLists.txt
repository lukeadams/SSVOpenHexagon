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
SET(SSVDeps "SSVCMake;SSVEntitySystem;SSVLuaWrapper;SSVMenuSystem;SSVStart;SSVUtils;vrm_pp")
SET(SSVDepsRoot "https://github.com/SuperV1234/")
foreach(dep ${SSVDeps})
	CPM_AddModule("SSVCMake"
		GIT_REPOSITORY "${SSVDepsRoot}${dep}"
		GIT_TAG "master")
endforeach(dep)
CPM_Finish()

#[[
# Include SSVCmake.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../SSVCMake/cmake/modules/"
    "${CMAKE_SOURCE_DIR}/extlibs/SSVCMake/cmake/modules/")

include(SSVCMake)

vrm_cmake_init_project(SSVOpenHexagon)

SSVCMake_setDefaults()
vrm_cmake_add_common_compiler_flags()

SSVCMake_findSFML()
find_package(LUA REQUIRED)
find_package(ZLIB REQUIRED)
SSVCMake_findExtlib(vrm_pp)
SSVCMake_findExtlib(SSVUtils)
SSVCMake_findExtlib(SSVMenuSystem)
SSVCMake_findExtlib(SSVLuaWrapper)
SSVCMake_findExtlib(SSVEntitySystem)
SSVCMake_findExtlib(SSVStart)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--stack,4194304 -fpermissive")
endif()

include_directories(${LUA_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SRC_LIST})
SSVCMake_linkSFML()
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARY})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/_RELEASE/)
]]
