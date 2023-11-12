cmake_minimum_required(VERSION 3.5)

project(email_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/rooot/Qt/6.5.2/gcc_64")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql )



find_package(vmime)

#find_package(Poco REQUIRED COMPONENTS Net )




set(PROJECT_SOURCES

        main.cpp
        maillHandler.h
        model.h
        ENV.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        loadingWidget/waitingspinnerwidget.h
        loadingWidget/waitingspinnerwidget.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(email_app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        login_image.qrc
        customwidget.h customwidget.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET email_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(email_app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(email_app
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(email_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
#target_link_libraries(email_app PUBLIC  Poco::Net Poco::Foundation )
target_link_libraries(email_app PUBLIC  curl )
target_link_libraries(email_app PUBLIC  vmime )


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.email_app)
endif()
set_target_properties(email_app PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS email_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(email_app)
endif()
