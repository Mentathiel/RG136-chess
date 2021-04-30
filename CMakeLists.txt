cmake_minimum_required(VERSION 3.10.2)
project(KnockItDown VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_compile_options(-g -Wall -Wextra -Wno-unused-parameter -I/usr/X11R6/include -I/usr/pkg/include -L/usr/X11R6/lib -L/usr/pkg/lib -lglut -lGLU -lGL -lm)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.*;
    -checks=-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,modernize-*,google-*,misc-*;
    -fix;
    -quiet;)

set (SRC_LIST 
    main.cc
    Bishop.cc
    Chessboard.cc
    ChessPiece.cc
    Field.cc
    Game.cc
    King.cc
    Knight.cc
    Move.cc
    ObjHandler.cc
    Pawn.cc
    Queen.cc
    Rook.cc
    chess.hpp
)

add_library(
    lchess
    chess.hpp
    Bishop.cc
    Chessboard.cc
    ChessPiece.cc
    Field.cc
    Game.cc
    King.cc
    Knight.cc
    Move.cc
    ObjHandler.cc
    Pawn.cc
    Queen.cc
    Rook.cc
)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_executable(chess ${PROJECT_SOURCE_DIR}/main.cc)

target_link_libraries(chess ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} lchess)
