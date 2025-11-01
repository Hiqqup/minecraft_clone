cmake_minimum_required(VERSION 3.28)
project(minecraft_clone)

set(CMAKE_CXX_STANDARD 20)


set(EXE_FILE minecraft_clone)

add_executable(${EXE_FILE}
        src/main.cpp
        src/WindowManager.cpp
        src/Shader.cpp
        src/ChunkMesh.cpp
        src/ChunkMesh.h
        src/Camera.cpp
        src/Camera.h
        src/Chunk.cpp
        src/Chunk.h
        src/Block.cpp
        src/Block.h
        src/ChunkMeshDataStruct.h
        src/ChunkMeshRenderDistance.cpp
        src/ChunkMeshRenderDistance.h
)

include(cmake/Libraries.cmake)
include(cmake/Assets.cmake)
