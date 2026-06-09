cmake_minimum_required(VERSION 3.22.1)

project("MyLibName")

# Header directories
include_directories(
        .
        Includes/
        Dobby/
)

# Prebuilt Keystone library
add_library(Keystone STATIC IMPORTED)
set_target_properties(Keystone PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/Deps/Keystone/libs-android/${ANDROID_ABI}/libkeystone.a)

# Prebuilt Dobby library
add_library(Dobby STATIC IMPORTED)
set_target_properties(Dobby PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/Dobby/${ANDROID_ABI}/libdobby.a)

# Main library
add_library(MyLibName SHARED
        Main.cpp
        Menu/Jni.cpp
        Menu/Menu.cpp
        Menu/Setup.cpp
        Includes/Utils.cpp
        KittyMemory/KittyAsm.cpp
        KittyMemory/KittyIOFile.cpp
        KittyMemory/KittyMemory.cpp
        KittyMemory/KittyPtrValidator.cpp
        KittyMemory/KittyScanner.cpp
        KittyMemory/KittyUtils.cpp
        KittyMemory/MemoryBackup.cpp
        KittyMemory/MemoryPatch.cpp
        xDL/xdl.c
        xDL/xdl_iterate.c
        xDL/xdl_linker.c
        xDL/xdl_lzma.c
        xDL/xdl_util.c
)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17 -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions")

# Linker flags
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections,--strip-all")

# Link libraries
target_link_libraries(MyLibName
        Keystone
        Dobby
        log
        android
        EGL
        GLESv2
)
