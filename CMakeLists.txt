cmake_minimum_required(VERSION 3.14)

set(PROJET_NAME poc-QJSEngine_use)

project(${PROJET_NAME} LANGUAGES CXX)

set(QT_COM_MODULES 
	Core
	Qml
	Quick
	Concurrent
)

set(PROJECT_HEADERS
	src/be_window.h
	src/interpreter.h
	src/js_api.h
	src/qml_register_classes.h
)
set(PROJECT_SOURCES
	src/be_window.cpp
	src/interpreter.cpp
	src/js_api.cpp
	src/main.cpp
)
set(PROJECT_UI
	ui/qml.qrc
)



set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS ${QT_COM_MODULES} REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_COM_MODULES} REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(${PROJET_NAME}
		${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI}
	)
else()
	if(ANDROID)
		add_library(${PROJET_NAME} SHARED
			${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI}
		)
	else()
		add_executable(${PROJET_NAME}
		  ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI}
		)
	endif()
endif()

target_compile_definitions(${PROJET_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJET_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
