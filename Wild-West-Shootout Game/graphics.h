#include "MainF.h"
#include "raylib.h"
#define NUM_IMAGES 10
#define screenWidth 1600
#define screenHeight  900

typedef enum {
    MENU,
    GAME,
    GAMEPLAY,
    Tutorials,
    Leaderboard,
    Credits,
} GameState;


typedef enum {
    SLIDE,
    FADE,
    SCALE
} TransitionType;


void drawMenu();
int drawGame();
void drawTutorials();
void drawCredits();

void handleMenuInput(GameState* state);
void handleGameInput(GameState* state);
void handleTutorialsInput(GameState* state);
void handleLeaderboardInput(GameState* state);
void handleCreditsInput(GameState* state);
bool isButtonClicked(Rectangle button);
void DrawSlideTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void DrawFadeTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void DrawScaleTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void TransitionToNextImage(int* currentImage, int* nextImage, int* transitionStep, TransitionType* transitionType, int imageSet[], int setSize);

