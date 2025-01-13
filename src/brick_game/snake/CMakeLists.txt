cmake_minimum_required(VERSION 3.16)

project(consolelibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set( CMAKE_INCLUDE_PATH "/usr/include")
# set( CMAKE_LIBRARY_PATH "/usr/lib64/libncurses.dylib")
# target_link_libraries(consolelibrary ncurses)

add_library(consolelibrary SHARED
    controller.cpp controller.h model.cpp model.h structure.h
    )

include(GNUInstallDirs)

install(TARGETS consolelibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

