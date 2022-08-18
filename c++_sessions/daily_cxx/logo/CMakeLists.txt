cmake_minimum_required(VERSION 3.18)

project(logo CXX)

find_package(unofficial-cairo CONFIG REQUIRED)
find_package(unofficial-glib CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

find_library(Pango pango-1.0
    D:/repos/vcpkg/installed/x64-windows/lib)
find_library(PangoCairo pangocairo-1.0
    D:/repos/vcpkg/installed/x64-windows/lib)

add_executable(gen_logo gen_logo.m.cpp)

target_link_libraries(gen_logo PRIVATE
    unofficial::cairo::cairo
    unofficial::cairo::cairo-gobject
    unofficial::glib::gio
    unofficial::glib::glib
    unofficial::glib::gmodule
    unofficial::glib::gobject
    Microsoft.GSL::GSL
    Eigen3::Eigen
    ${Pango}
    ${PangoCairo}
)