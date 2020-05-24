cmake_minimum_required(VERSION 3.14)

project(robotcontroller LANGUAGES C CXX)

# Set source files
set(MAIN_FILES
    # Header files
    Gui.h
    Input.h
    Serial.h
    # Source files
    Gui.cpp
    Input.cpp
    Serial.cpp
    # Main
    main.cpp)

source_group("\\" FILES ${MAIN_FILES})

set(PROJECT_FILES
    ${MAIN_FILES})

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
    imgui
    glfw
    docopt
    glew_s)

if(MSVC)
    #Set the working directory to the source of the project so developer dont have to
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    #Configure output paths
    foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${CONFIG_TYPE} SUFFIX)
        string(TOLOWER ${CONFIG_TYPE} CONFIG_DIR)
        set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/bin/${CONFIG_DIR}/${TARGET_ARCH})
        set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/lib/${CONFIG_DIR}/${TARGET_ARCH})
        set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/lib/${CONFIG_DIR}/${TARGET_ARCH})
    endforeach()
endif()