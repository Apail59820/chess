cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        include/ChessBoard.h
        src/ChessBoard.cpp
        include/GameContext.h
        src/GameContext.cpp
        include/ChessPiece.h
        include/ChessPieces/Pawn.h
        src/ChessePieces/Pawn.cpp
        include/ChessPieces/Rook.h
        src/ChessePieces/Rook.cpp
        include/ChessPieces/Knight.h
        src/ChessePieces/Knight.cpp
        include/Globals.h
        include/ChessPieces/Bishop.h
        src/ChessePieces/Bishop.cpp
        include/ChessPieces/Queen.h
        src/ChessePieces/Queen.cpp
        include/ChessPieces/King.h
        src/ChessePieces/King.cpp
        include/TextureManager.h
        src/TextureManager.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
