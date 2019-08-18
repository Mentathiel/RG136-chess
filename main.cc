#include "chess.hpp"

/* Declaring callback functions */
static void onDisplay(void);
static void onKeyboard(unsigned char key, int x, int y);
static void onSpecialKey(int key, int x, int y);

/*Global game variables*/
Game* game;
int selFieldFile = 0;
int selFieldRank = 0;

int main(int argc, char **argv)
{

    game = new Game();

    /* Initializing GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);

    /* Creating a window. */
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    /* Registering callback functions. */
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);
    glutSpecialFunc(onSpecialKey);

    /* Initialize OpenGL stuff. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* The program is entering the main loop. */
    glutMainLoop();

    return 0;
}

static void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

     /* Set the viewport. */
    glViewport(0, 0, 1280, 720);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        60,
        1280/(float)720,
        0, 25);
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(
        0, 0, 1,
        0, 0, 0,
        0, 1, 0
    );

    /* This is where the magic happens */
    game->display(selFieldFile, selFieldRank);

    /* Swap Buffer with the new one */
    glutSwapBuffers();
}

static void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

static void onSpecialKey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            if(selFieldFile<7)
                selFieldFile++;
            break;
        case GLUT_KEY_LEFT:
            if(selFieldFile>0)
                selFieldFile--;
            break;
        case GLUT_KEY_UP:
            if(selFieldRank<7)
                selFieldRank++;
            break;
        case GLUT_KEY_DOWN:
            if(selFieldRank>0)
                selFieldRank--;
            break;
    }
    glutPostRedisplay();
}