cmake_minimum_required(VERSION 3.0)
project(SSVOpenHexagon)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#set(CMAKE_CXX_FLAGS "-std=c++14 -w -fmax-errors=1")
#set(CMAKE_CXX_FLAGS "-std=c++14 -fmax-errors=1") #GCC
#set(CMAKE_CXX_FLAGS "-std=c++14 -ferror-limit=1")#Clang

include(cmake/modules/CPM-init.cmake)

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

file(GLOB_RECURSE LIST "src/*.cpp") #Generate list of source files
include_directories("./include")	#Include headers

find_package(LUA REQUIRED)
find_package(ZLIB REQUIRED)
find_package(SFML 2 REQUIRED graphics window network audio system)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${LIST})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES} ${ZLIB_LIBRARIES} ${SFML_LIBRARIES} ${CPM_LIBRARIES})

##Convenience targets

#Downloads assets for SSVOH
add_custom_target("fetch-assets"
	#Probably should use GH releases as zip..? Anyways, nc skips if already 'dled
	COMMAND wget --quiet --directory-prefix="${CMAKE_SOURCE_DIR}/cache/_RELEASE-dl" -r -nH -nc --cut-dirs=4 --no-parent -e robots="off" --reject="*index.html*" "http://vittorioromeo.info/Misc/Linked/OHResources/Testing/"
)

#Copies assets to build dir
#Copy assets to 
add_custom_target("copy-assets"
	DEPENDS "fetch-assets"
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/_RELEASE $<TARGET_FILE_DIR:${PROJECT_NAME}> #Vanilla assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/cache/_RELEASE-dl $<TARGET_FILE_DIR:${PROJECT_NAME}> #Downloaded assets
)



