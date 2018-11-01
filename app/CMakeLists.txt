cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION -std=c++14)
set (CMAKE_CXX_STANDARD 14)

# Set the path to the Oboe directory.
set (OBOE_DIR ../../oboe)

# Add the Oboe library as a subdirectory in your project.
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories (${OBOE_DIR}/include)

add_library( native-lib SHARED
        src/main/cpp/native-lib.cpp
        src/main/cpp/Oscillator.cpp
        src/main/cpp/SoundRecording.cpp
        )

target_link_libraries(
        native-lib
        oboe
        log
        android
)

target_compile_options(native-lib
PRIVATE -std=c++14)