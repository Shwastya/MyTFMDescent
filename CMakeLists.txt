cmake_minimum_required(VERSION 3.10)

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

    # old classes
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/deps.cpp # ficheros de depencias

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/camera.cpp    
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/mesh.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/geometry/cube.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/geometry/geometry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/geometry/quad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/geometry/sphere.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/geometry/teapot.cpp

    ########################
    # TFM From scratchs
    ########################

    # ImGUI 
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_impl_glfw.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/ImGui/imgui.cpp
    

    # ECS
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/object/ebo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/object/vbo.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/handleGLerrors.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/renderer.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/system/render.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/manager/entitymanager.cpp)

set(ENGINE_HEADER_FILES

    # old classes        
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/input.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/mesh.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/model.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/shader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/window.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/cube.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/geometry.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/quad.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/sphere.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/teapot.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/geometry/teapotdata.hpp

    ########################
    # TFM From scratchs
    ########################  

    # ECS 

    ${CMAKE_CURRENT_LIST_DIR}/include/engine/object/ebo.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/object/vbo.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/handleGLerrors.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/renderer.hpp


    ${CMAKE_CURRENT_LIST_DIR}/include/engine/system/render.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/manager/entitymanager.hpp)

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
#****************************************************
# Projects
#****************************************************
# List of projects
set(PROJECT_LIST AG01 AG02 AG03 AG04 AG05 AG06 AG07 AG08_01 AG08_02
    AG09_01 AG09_02 AG09_03 AG09_04 AG10 AG11_01 AG11_02 AG11_03 AG12 AG13 AG14 AG15
    MyTFMDescent study study2 tests)

#Root path of the projects
set(PROJECTS_PATH ${CMAKE_CURRENT_LIST_DIR}/games)
#Configure All Projects
foreach(PROJECT ${PROJECT_LIST})
    message("Generating Project " ${PROJECT})

    #Create Directory and main.cpp
    file(MAKE_DIRECTORY ${PROJECTS_PATH}/${PROJECT})
    file(TOUCH ${PROJECTS_PATH}/${PROJECT}/main.cpp)

    #Create Project and configure
    add_executable(${PROJECT} ${PROJECTS_PATH}/${PROJECT}/main.cpp ${DEPS_SRC_FILES})
    target_include_directories(${PROJECT} PRIVATE ${INCLUDE_PATHS})
    target_compile_definitions(${PROJECT} PRIVATE -D_GLFW_USE_OPENGL=1)
    target_link_libraries(${PROJECT} PRIVATE EngineLib)
    target_compile_features(${PROJECT} PRIVATE cxx_std_14)
    configure_platform(${PROJECT})
    configure_compiler(${PROJECT})
endforeach()