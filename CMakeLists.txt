cmake_minimum_required(VERSION 3.20)

project(MyTFMDescent CXX C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Config types" FORCE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Files for dependencies and platform specific config
include(cmake/deps_files.cmake)
include(cmake/platform.cmake)
include(cmake/compiler.cmake)

#****************************************************
# Engine Library
#****************************************************
#Engine Source Files

set(ENGINE_SRC_FILES
    #####################
    # old classes removed
    # empty at moment 
    #####################

    #####################
    # TFM From scratchs #
    #####################


   
    # MartianHelmet Application (main program) #
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/mhpch.cpp


    # log classes
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/log/log.cpp

    

    # ImGUI 
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_impl_glfw.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui.cpp
    
    # window context on window S.O platform
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/windows/windowWin.cpp

    # Core OpenGL
    
    

    # Projectes dependency
    )

set(ENGINE_HEADER_FILES

    #####################
    # old classes removed
    # empty at moment 
    #####################  

    ########################
    # TFM From scratchs
    ########################  

    # MartianHelmet Application (main program) #
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/engine.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/mainPoint.hpp      


    # log classes
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/log/log.hpp 


    # events 



    # window interface and SO Layers
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/baseWindow.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/platform/windows/windowWin.hpp

    # Core OpenGL

    
    # ECS 


    # Projectes dependency
    )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ PREFIX "Source Files" FILES ${ENGINE_SRC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/engine PREFIX "Header Files" FILES ${ENGINE_HEADER_FILES})

add_library(EngineLib STATIC ${ENGINE_SRC_FILES} ${ENGINE_HEADER_FILES} ${DEPS_SRC_FILES_COMMON})

target_include_directories(EngineLib PRIVATE ${INCLUDE_PATHS})

if (UNIX)  # assimp files in linus   #
    target_link_libraries(EngineLib PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/lib/linux/libassimp.so)
endif()

if (WIN32) # assimp files in windows #
    target_link_libraries(EngineLib PRIVATE
    debug ${CMAKE_CURRENT_LIST_DIR}/lib/Debug/assimp-vc142-mt.lib
    optimized ${CMAKE_CURRENT_LIST_DIR}/lib/Release/assimp-vc142-mt.lib)
endif()   

target_compile_definitions(EngineLib PRIVATE -D_GLFW_USE_OPENGL=1)
target_compile_features(EngineLib PRIVATE cxx_std_14)

configure_platform(EngineLib)
configure_compiler(EngineLib)

if (WIN32) # assimp files in windows macro #
    add_custom_command(TARGET EngineLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_LIST_DIR}/lib/$<CONFIGURATION>/assimp-vc142-mt.dll" 
    $<TARGET_FILE_DIR:EngineLib>)
endif()


# List of projects
set(PROJECT_LIST Tests MyTFMDescent MH_Editor)


#Root path of the projects
set(PROJECTS_PATH ${CMAKE_CURRENT_LIST_DIR}/projects)
#Configure All Projects
foreach(PROJECT ${PROJECT_LIST})
    message("Generating Project " ${PROJECT})

    #Create Directory and main.cpp
    file(MAKE_DIRECTORY ${PROJECTS_PATH}/${PROJECT})
    file(TOUCH ${PROJECTS_PATH}/${PROJECT}/${PROJECT}.cpp)

    #Create Project and configure
    add_executable(${PROJECT} ${PROJECTS_PATH}/${PROJECT}/${PROJECT}.cpp ${DEPS_SRC_FILES})
    target_include_directories(${PROJECT} PRIVATE ${INCLUDE_PATHS})
    target_compile_definitions(${PROJECT} PRIVATE -D_GLFW_USE_OPENGL=1)
    target_link_libraries(${PROJECT} PRIVATE EngineLib)
    target_compile_features(${PROJECT} PRIVATE cxx_std_14)
    configure_platform(${PROJECT})
    configure_compiler(${PROJECT})
endforeach()