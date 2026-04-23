cmake_minimum_required(VERSION 3.22)

project(Aetherflow VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch JUCE
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.4
)
FetchContent_MakeAvailable(JUCE)

# Set up the Aetherflow executable
juce_add_gui_app(Aetherflow
    PRODUCT_NAME "Aetherflow"
    COMPANY_NAME "Aetherflow"
    BUNDLE_ID "com.aetherflow.daw"
    IS_CONTENT_PREVIEW_HOST TRUE
)

# Source files
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")
target_sources(Aetherflow PRIVATE ${SOURCES})

# Include directories
target_include_directories(Aetherflow PRIVATE Source)

# Link JUCE modules
target_link_libraries(Aetherflow
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
)

# Set up App Config
juce_generate_juce_header(Aetherflow)
