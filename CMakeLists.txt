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
    # old dependences removed # empty at moment 
    #####################
    # ....
    #####################
    # TFM From scratchs #
    #####################


   
    # MartianHelmet Application (main program) #
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/MHCore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/Engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/MHpch.cpp


    # Node System
    # layer system
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/node/nodeLayer.cpp

    # log classes
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/log/LogManager.cpp
        # Log strategies
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/log/strategies/SimpleLog.cpp

    

    # ImGUI 
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/RenderAPI/OpenGL/imgui.cpp
        # ImGUI Source for Engine
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/ImGui/ImGuiLayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/ImGui/imgui_hack_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/ImGui/imgui_hack_glfw.cpp

    
    # window context on window S.O platform
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/platform/Windows/WindowWin.cpp

    

    # Core OpenGL
    
    

    # Projectes dependency
    )

set(ENGINE_HEADER_FILES

    #####################
    # old dependences removed # empty at moment 
    #####################
    # ....
    #####################
    # TFM From scratchs #
    #####################

    # MartianHelmet Application (main program) #
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/MHCore.hpp
    
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/MHSetup.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/Engine.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/MainPoint.hpp      

    # Node system
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/node/Node.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/node/NodeLayer.hpp


    # log classes
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/log/LogManager.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/log/Log.hpp # base log class 

        # Log strategies
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/log/strategies/SimpleLog.hpp

    # ImGUI Source for Engine
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/ImGui/ImGuiLayer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/ImGui/imgui_hack_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/ImGui/imgui_hack_glfw.h



    # events & event sender     
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/Event.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/EventSender.hpp
        # KeyEvents : event
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/KeyEvents/KeyEvent.hpp
            # OnKeyEvents : KeyEvents : event
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/KeyEvents/OnKeyEvents.hpp
        # MouseEvents : event
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/MouseEvents/MouseButtonEvent.hpp
            # OnMouseEvents : MouseButtonEvent : event
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/MouseEvents/OnMouseEvents.hpp
        # AppEvent : event
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/events/AppEvents/OnAppEvents.hpp



    



    # window interface and PLATFORM Layers
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/platform/Window.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/platform/Windows/WindowWin.hpp


    

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
set(PROJECT_LIST Tests TestImgui MyTFMDescent MH_Editor)


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