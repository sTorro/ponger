cmake_minimum_required(VERSION 2.6)

project(Ponger)

if (WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH $ENV{OGRE_HOME}/Samples/include)
endif (WIN32)

if (UNIX)
	if (EXISTS "/usr/local/lib/OGRE/cmake")
	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
	elseif (EXISTS "/usr/lib/OGRE/cmake")
	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one
	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif (EXISTS "/usr/local/lib/OGRE")
endif (UNIX)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/Debug")

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

if (NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif ()


#################
# SOURCES
#################
file(GLOB HDRS src/*.h src/*.hpp)
file(GLOB SRCS src/*.cpp)

include_directories(
	${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Overlay_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} WIN32 ${HDRS} ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES})

if (MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif (MINGW OR UNIX)

# Just for Visual Studio, set the Working Directory to $(SolutionDir)$(Configuration)\
if (WIN32)
	# This works with VS 2015 Community Edition !
	file(COPY in/project.vcxproj.user.in DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/project.vcxproj.user.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user)
endif (WIN32)

#################
# INSTALL
#################
if(WIN32)
	# DEBUG
	set(VS_DEBUG_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/Debug)

	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION ${VS_DEBUG_FOLDER}
		CONFIGURATIONS Debug)
	
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION ${VS_DEBUG_FOLDER}
		CONFIGURATIONS Debug
	)

	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D11_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/OgreOverlay_d.dll
		${OGRE_PLUGIN_DIR_DBG}/OIS_d.dll
		DESTINATION ${VS_DEBUG_FOLDER}
		CONFIGURATIONS Debug
	)

	# RELEASE
	set(VS_RELEASE_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/Release)

	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION ${VS_RELEASE_FOLDER}
		CONFIGURATIONS Release)

	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION ${VS_RELEASE_FOLDER}
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D11.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/OgreOverlay.dll
		${OGRE_PLUGIN_DIR_REL}/OIS.dll
		DESTINATION ${VS_RELEASE_FOLDER}
		CONFIGURATIONS Release RelWithDebInfo
	)
endif(WIN32)

if(UNIX)
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)

	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
endif(UNIX)
