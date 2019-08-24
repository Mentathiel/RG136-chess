#include "chess.hpp"

/* Declaring callback functions */
static void onDisplay(void);
static void onKeyboard(unsigned char key, int x, int y);
static void onSpecialKey(int key, int x, int y);
static void onReshape(int width, int height);

/* Global game variables */
Game* game;
int selFieldFile = 0;
int selFieldRank = 0;

/* Global GLUT variables */
int winWidth = 1280;
int winHeight = 720;

int main(int argc, char **argv)
{
    /* Starting a New Game */
    game = new Game();

    /* Initializing GLUT. */
    glutInit(&argc, argv);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Creating a window. */
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    /* Registering callback functions. */
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);
    glutSpecialFunc(onSpecialKey);
    glutReshapeFunc(onReshape);

    /* Initializing clear color. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* Initializing light & materials. */
    GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1 };
    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };

    GLfloat light_position[] = { -20, 0, -600, 0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModeli(GL_LIGHT_MODEL_AMBIENT,1);
    

    /* The program is entering the main loop. */
    glutMainLoop();

    return 0;
}

static void onDisplay(void)
{
    /* Setting Clear Color and Depth */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     /* Set the viewport. */
    glViewport(0, 0, winWidth, winHeight);

    /*  Setting up perspective and camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        60,
        winWidth/(float)winHeight,
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
    /* If the game is finished (either by draw or one side winning) 
       this creates a new game on any input. */
    if(game->gameFinished){
        delete game;
        game = new Game();
    }

    /* Check key */
    switch (key) {

        case 13: //enter

            // if a piece is selected and we're picking a field to move it to
            if(game->pickingMove()){
                Field* target = new Field(selFieldFile, selFieldRank);
                ChessPiece* mov = game->cb->board[game->selFile][game->selRank];
                game->playMove(target, mov);
                //game->cb->print();
                game->checkState();
            }
            // if we're selecting a piece
            else{
                game->selectField();
            }
            break;

        case 27: //esc
            exit(0);
            break;
    }

    /* Refresh screen because the game state has changed.
       Refreshing here in case additional inputs are added later. */
    glutPostRedisplay();
}

static void onSpecialKey(int key, int x, int y){
    /* The player can still move around the board, but can't select
       anything anymore. */
    if(game->gameFinished)
        return;

    /* Selecting fields using arrow keys. */
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

    /* Refresh screen because the game state has changed.
    Refreshing here in case additional inputs are added later. */
    glutPostRedisplay();
}

/* Proportionally reshape everything when the user rezsizes
   the window. */
static void onReshape(int width, int height){
    float ratio = (float)width/height;
    winWidth = width;
    winHeight = (int)(width/ratio);
}