INCLUDE(GNUInstallDirs)
ADD_DEFINITIONS("-DGLFW_INCLUDE_NONE")

SET(LIBRARIES
    glad
    glm
    assimp
    dl
    pthread
)
SET(VOID_SOURCES
    "Core/Application.cpp"
    "Core/Allocator.cpp"
    "Core/Time.cpp"
    "Core/World.cpp"
    "Debug/Log.cpp"
    "Debug/SignalHandler.cpp"
    "ECS/Entity.cpp"
    "Math/Color.cpp"
    "Misc/File.cpp"
    "Misc/ModelLoader.cpp"
    "Misc/Vector.cpp"
    "Misc/Resource.cpp"
    "Misc/Texture.cpp"
    "Misc/String.cpp"
    "Input/InputManager.cpp"
    "Rendering/Shader.cpp"
    "Rendering/Renderer.cpp"
)

##
## HANDLE OPTIONS
##

ADD_DEFINITIONS("-DVOID_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}")
ADD_DEFINITIONS("-DVOID_VERSION_MINOR=${PROJECT_VERSION_MINOR}")
ADD_DEFINITIONS("-DVOID_VERSION_PATCH=${PROJECT_VERSION_PATCH}")

IF(${VOID_ENABLE_OPENGL})
    PKG_SEARCH_MODULE(OPENGL REQUIRED gl)

    SET(VOID_SOURCES
        ${VOID_SOURCES}
        "Platforms/GL/Shader.cpp"
        "Platforms/GL/Window.cpp"
        "Platforms/GL/Renderer.cpp"
    )

    SET(LIBRARIES
        ${LIBRARIES}
        glfw
        ${OPENGL_LIBRARIES}
    )

    ADD_DEFINITIONS("-DVOID_ENABLE_OPENGL")
ENDIF()

##
## LINKING DEPENDENCIES
##

ADD_LIBRARY(Void STATIC ${VOID_SOURCES})
ADD_LIBRARY(Void::Void ALIAS Void)
TARGET_LINK_LIBRARIES(Void PUBLIC
    ${LIBRARIES}
)

##
## INSTALLATION
##

INSTALL(
    TARGETS       Void
    EXPORT        VoidTargets
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

INSTALL(
    DIRECTORY "."
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VoidEngine
    FILES_MATCHING
        REGEX   ".*\.hpp$"
)
