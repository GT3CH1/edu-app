cmake_minimum_required(VERSION 3.5)

project(FishTutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        fishvc.cpp
        fishvc.h
        fishvc.ui
        fishmodel.h
        fishmodel.cpp
        renderarea.h
        renderarea.cpp
        gameobject.h
        gameobject.cpp
        sprites.qrc
        objectrenderinformation.h
        objectrenderinformation.cpp
        callbackoptions.h
        callbackoptions.cpp
        physicsgameobject.h
        physicsgameobject.cpp
        draggable.h
        draggable.cpp
        fishtank.cpp
        fishtank.h
        quest.h
        physicgameobjectsfile.h
        animatedfish.h
        animatedfish.cpp
        questsfile.h
        questfillbowl.h
        questfillbowl.cpp
        questfilltank.cpp
        questfilltank.h
        questchoosefish.cpp
        questchoosefish.h
        questaddfish.cpp
        questaddfish.h
        questwait.cpp
        questwait.h
        questaddfood.cpp
        questaddfood.h
        physicsbowl.cpp
        physicsbowl.h
        physicsclock.cpp
        physicsclock.h
        physicsfood.cpp
        physicsfood.h
        physicsfoodcontainer.cpp
        physicsfoodcontainer.h
        physicsspigot.cpp
        physicsspigot.h
        physicsfish.cpp
        physicsfish.h
        physicstank.cpp
        physicstank.h
        physicscountertop.cpp
        physicscountertop.h
        physicswall.h
        physicswall.cpp
        questremovefishfrombag.cpp
        questremovefishfrombag.h
        scenestate.h
        queststart.h
        queststart.cpp
        questend.h
        questend.cpp
        physicsstartbutton.h
        physicsstartbutton.cpp)

add_subdirectory(box2d-src)
include_directories(./)
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FishTutorial
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET FishTutorial APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(FishTutorial SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(FishTutorial
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(FishTutorial PRIVATE Qt${QT_VERSION_MAJOR}::Widgets tobanteGaming::Box2D)

set_target_properties(FishTutorial PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FishTutorial)
endif ()
