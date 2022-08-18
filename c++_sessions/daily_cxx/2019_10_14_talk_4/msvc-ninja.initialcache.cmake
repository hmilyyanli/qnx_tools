set(CMAKE_GENERATOR Ninja CACHE STRING "Build system")
set(CMAKE_CXX_COMPILER cl.exe CACHE STRING "C++ Compiler")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build mode")
set(CMAKE_CXX_FLAGS_INIT "/W4" CACHE STRING "C++ Flags")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL
    "Generate 'compile_commands.json'")
