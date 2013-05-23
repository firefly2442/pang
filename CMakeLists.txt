#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.8)

# define a macro that helps defining an option
macro(pang_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()


project(pang)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "pang")

SET(SOURCES
	src/pang.cpp
	src/Game.h
	src/Game.cpp
	src/SplashScreen.h
	src/SplashScreen.cpp
	src/MainMenu.h
	src/MainMenu.cpp
	src/VisibleGameObject.h
	src/VisibleGameObject.cpp
	src/PlayerPaddle.h
	src/PlayerPaddle.cpp
	src/GameObjectManager.h
	src/GameObjectManager.cpp
	src/GameBall.h
	src/GameBall.cpp
	src/SFMLSoundProvider.h
	src/SFMLSoundProvider.cpp
	src/SoundFileCache.h
	src/SoundFileCache.cpp
	src/AIPaddle.h
	src/AIPaddle.cpp
	src/ServiceLocator.h
	src/ServiceLocator.cpp
	src/PreferencesMenu.h
	src/PreferencesMenu.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  message(STATUS "SFML found.")
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# add an option for building the documentation
pang_set_option(PANG_BUILD_DOC FALSE BOOL "TRUE to generate the documentation, FALSE to ignore it")


# Detect and add SFGUI
find_package(SFGUI REQUIRED)
if(SFGUI_FOUND)
  message(STATUS "SFGUI found.")
  include_directories(${SFGUI_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFGUI_LIBRARY})
endif()

if(PANG_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Look for C++11 support
include(FindCXX11)
if(CXX11_FOUND)
	message(STATUS "Adding C++11 support to compiler flags: " ${CXX11_FLAGS})
	#list(APPEND CMAKE_CXX_FLAGS "${CXX11_FLAGS}")
	SET (CMAKE_CXX_FLAGS "${CXX11_FLAGS}" CACHE STRING "" FORCE)
else()
	message(FATAL_ERROR "Compiler does not support C++11")
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

#Copy over resources (images and such)
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
