#include <GL/glut.h>
#include "chess.hpp"

/* Declaring callback functions */
static void onDisplay(void);

int main(int argc, char **argv)
{

    Game* game = new Game();
    game->cb->print();
    cout << endl << endl << endl;
    Field* f = new Field(0,3);
    ChessPiece* cp = game->cb->board[0][1];
    game->playMove(f,cp);
    game->cb->print();
    game->undoMove();

    cout << endl << endl << endl;
    game->cb->print();

    /* Initializing GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Creating a window. */
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    /* Registering callback functions. */
    glutDisplayFunc(onDisplay);

    /* Initialize OpenGL stuff. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* The program is entering the main loop. */
    glutMainLoop();

    return 0;
}

static void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //TODO: Make the magic happen

    /* Swap Buffer with the new one */
    glutSwapBuffers();
}