cmake_minimum_required(VERSION 3.20)

project(MyTFMDescent CXX C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Config types" FORCE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Files for dependencies and platform specific config
include(cmake/deps_files.cmake)
include(cmake/platform.cmake)
include(cmake/compiler.cmake)



file(GLOB_RECURSE RECURSIVE_SRC_FILES    
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/*.h
    )


file(GLOB_RECURSE RECURSIVE_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/*.hpp    
    ${CMAKE_CURRENT_LIST_DIR}/include/engine/*.h
    )    

    set (ENGINE_SRC_FILES ${RECURSIVE_SRC_FILES})
    set (ENGINE_HEADER_FILES ${RECURSIVE_HEADER_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ PREFIX "Source Files" FILES ${ENGINE_SRC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/engine PREFIX "Header Files" FILES ${ENGINE_HEADER_FILES})

add_library(EngineLib STATIC ${ENGINE_SRC_FILES} ${ENGINE_HEADER_FILES} ${DEPS_SRC_FILES_COMMON})


target_include_directories(EngineLib PRIVATE ${INCLUDE_PATHS})



# De momento elimino las librerias dinamicas en Linux Paso de tantas de movidas ahora mismo
#if (UNIX)  # assimp files in linus   #
 #   target_link_libraries(EngineLib PRIVATE
  #  ${CMAKE_CURRENT_LIST_DIR}/lib/linux/libassimp.so)
#endif()

if (WIN32) # assimp files in windows #
    target_link_libraries(EngineLib PRIVATE
    debug ${CMAKE_CURRENT_LIST_DIR}/lib/Debug/assimp-vc142-mt.lib
    optimized ${CMAKE_CURRENT_LIST_DIR}/lib/Release/assimp-vc142-mt.lib)
endif()  

target_compile_definitions(EngineLib PRIVATE -D_GLFW_USE_OPENGL=1)
target_compile_features(EngineLib PRIVATE cxx_std_17)

configure_platform(EngineLib)
configure_compiler(EngineLib)

if (WIN32) # assimp files in windows macro #
    add_custom_command(TARGET EngineLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_LIST_DIR}/lib/$<CONFIGURATION>/assimp-vc142-mt.dll" 
    $<TARGET_FILE_DIR:EngineLib>)
endif()


# List of projects
set(PROJECT_LIST MyTFM ProjectExample)

#Root path of the projects
set(PROJECTS_PATH ${CMAKE_CURRENT_LIST_DIR}/projects)

#Configure All Projects
foreach(PROJECT ${PROJECT_LIST})

    message("Generating Project " ${PROJECT})
    
    #Create Directory and main.cpp
    file(MAKE_DIRECTORY ${PROJECTS_PATH}/${PROJECT}/Editor)
     

    # List of files in project
    set(FILESP
        ${PROJECTS_PATH}/${PROJECT}/${PROJECT}.cpp
        ${PROJECTS_PATH}/${PROJECT}/${PROJECT}.hpp
        ${PROJECTS_PATH}/${PROJECT}/${PROJECT}Layer1.cpp
        ${PROJECTS_PATH}/${PROJECT}/${PROJECT}Layer1.hpp
        ${PROJECTS_PATH}/${PROJECT}/SceneHierarchy.cpp
        ${PROJECTS_PATH}/${PROJECT}/SceneHierarchy.hpp
    )

    file(TOUCH ${FILESP})

    #Create Project and configure
    add_executable(${PROJECT} ${FILESP} ${DEPS_SRC_FILES})

    target_include_directories(${PROJECT} PRIVATE ${INCLUDE_PATHS} ${PROJECT_PATHS} ${PROJECT_DEPS_FILES})
    target_compile_definitions(${PROJECT} PRIVATE -D_GLFW_USE_OPENGL=1)
   
    target_link_libraries(${PROJECT} PRIVATE EngineLib)
    target_compile_features(${PROJECT} PRIVATE cxx_std_17)
    configure_platform(${PROJECT})
    configure_compiler(${PROJECT})    

endforeach()