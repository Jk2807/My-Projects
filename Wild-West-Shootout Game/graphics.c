#include "graphics.h"

void drawMenu() {
    DrawText("GAME MENU", screenWidth / 2 - MeasureText("GAME MENU", 60) / 2 - 65, screenHeight / 2 - 150, 80, PURPLE);

    Rectangle startButton = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 50 };
    Rectangle tutorialsButton = { screenWidth / 2 - 100, screenHeight / 2 + 10, 200, 50 };
    Rectangle leaderboardButton = { screenWidth / 2 - 100, screenHeight / 2 + 70, 200, 50 };
    Rectangle creditsButton = { screenWidth / 2 - 100 , screenHeight / 2 + 130, 200, 50 };

    DrawRectangleRec(startButton, LIGHTGRAY);
    DrawRectangleRec(tutorialsButton, LIGHTGRAY);
    DrawRectangleRec(leaderboardButton, LIGHTGRAY);
    DrawRectangleRec(creditsButton, LIGHTGRAY);

    DrawText("Start Game", startButton.x + startButton.width / 2 - MeasureText("Start Game", 20) / 2 - 40, startButton.y + 10, 35, DARKGREEN);
    DrawText("Tutorials", tutorialsButton.x + tutorialsButton.width / 2 - MeasureText("Tutorials", 20) / 2 - 35, tutorialsButton.y + 10, 35, YELLOW);
    DrawText("Leaderboard", leaderboardButton.x + leaderboardButton.width / 2 - MeasureText("Exit", 20) / 2 - 71, leaderboardButton.y + 10, 29, DARKBLUE);
    DrawText("Credits", creditsButton.x + creditsButton.width / 2 - MeasureText("Credits", 20) / 2 - 28, creditsButton.y + 10, 35, BLACK);
}



void handleMenuInput(GameState* state) {
    Rectangle startButton = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 50 };
    Rectangle tutorialsButton = { screenWidth / 2 - 100, screenHeight / 2 + 10, 200, 50 };
    Rectangle leaderboardButton = { screenWidth / 2 - 100, screenHeight / 2 + 70, 200, 50 };
    Rectangle creditsButton = { screenWidth / 2 - 100, screenHeight / 2 + 130, 200, 50 };

    if (isButtonClicked(startButton)) {
        *state = GAME;
    }
    else if (isButtonClicked(tutorialsButton)) {
        *state = Tutorials;
    }
    else if (isButtonClicked(leaderboardButton)) {
        *state = Leaderboard;
    }
    else if (isButtonClicked(creditsButton)) {
        *state = Credits;
    }
}

void handleGameInput(GameState* state) {
    Rectangle returnButton = { 10, 10, 100, 50 };
    if (isButtonClicked(returnButton)) {
        *state = MENU;
    }
    else if (IsKeyPressed(KEY_ESCAPE)) {
        *state = MENU;
    }
}

void handleTutorialsInput(GameState* state) {
    Rectangle returnButton = { 10, 10, 100, 50 };
    if (isButtonClicked(returnButton)) {
        *state = MENU;
    }
    else if (IsKeyPressed(KEY_ESCAPE)) {
        *state = MENU;
    }
}

void handleLeaderboardInput(GameState* state) {
    Rectangle returnButton = { 10, 10, 100, 50 };
    if (isButtonClicked(returnButton)) {
        *state = MENU;
    }
    else if (IsKeyPressed(KEY_ESCAPE)) {
        *state = MENU;
    }
}

void handleCreditsInput(GameState* state) {
    Rectangle returnButton = { 10, 10, 100, 50 };
    if (isButtonClicked(returnButton)) {
        *state = MENU;
    }
    else if (IsKeyPressed(KEY_ESCAPE)) {
        *state = MENU;
    }
}

bool isButtonClicked(Rectangle button) {
    Vector2 mousePoint = GetMousePosition();
    return (CheckCollisionPointRec(mousePoint, button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}



void DrawSlideTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress) {
    float currentPos = -transitionProgress * GetScreenWidth();
    float nextPos = (1.0f - transitionProgress) * GetScreenWidth();

    // Draw current and next images with a sliding effect
    DrawTexture(images[currentImage], currentPos, 0, WHITE);
    DrawTexture(images[nextImage], nextPos, 0, WHITE);
}

void DrawFadeTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress) {
    // Draw current and next images with a fading effect
    DrawTexture(images[currentImage], 0, 0, Fade(WHITE, 1.0f - transitionProgress));
    DrawTexture(images[nextImage], 0, 0, Fade(WHITE, transitionProgress));
}

void DrawScaleTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress) {
    float scale = 1.0f + transitionProgress;
    float nextScale = 2.0f - transitionProgress;

    Vector2 currentPos = { (GetScreenWidth() - images[currentImage].width * scale) / 2, (GetScreenHeight() - images[currentImage].height * scale) / 2 };
    Vector2 nextPos = { (GetScreenWidth() - images[nextImage].width * nextScale) / 2, (GetScreenHeight() - images[nextImage].height * nextScale) / 2 };

    // Draw current and next images with a scaling effect
    DrawTextureEx(images[currentImage], currentPos, 0.0f, scale, WHITE);
    DrawTextureEx(images[nextImage], nextPos, 0.0f, nextScale, WHITE);
}

void DrawSlideTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void DrawFadeTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void DrawScaleTransition(Texture2D images[], int currentImage, int nextImage, float transitionProgress);
void TransitionToNextImage(int* currentImage, int* nextImage, int* transitionStep, TransitionType* transitionType, int imageSet[], int setSize);
int transition() {


    Texture2D images[NUM_IMAGES];
    images[0] = LoadTexture("redshot.png");
    images[1] = LoadTexture("blueshot.png");
    images[2] = LoadTexture("reddead.png");
    images[3] = LoadTexture("bluedead.png");
    images[4] = LoadTexture("blankR.png");
    images[5] = LoadTexture("liveR.png");


        //1->?? b?n n? xanh
        //2->?? b?n x?t xanh
        //3->?? b?n n? ??
        //4->?? b?n x?t ??
        //5 -> xanh b?n n? ??
        //6->xanh b?n x?t ??
        //7->xanh b?n n? xanh
        //8->xanh b?n x?t xanh

    int imageSet1[] = { 0, 5, 3 }; // Set of images for shoot opponent successfully (Red shot blue)
    int imageSet2[] = { 0, 4 }; // Set of images for shoot opponent unsuccessfully (Red shot blue)
    int imageSet3[] = { 5, 2 }; // Set of images for shoot self successfully (Red shot self)
    int imageSet4[] = { 4 };// set of images for shoot self unsuccessfully (Red shot self)
    int imageSet5[] = { 1, 5, 2 };
    int imageSet6[] = { 1, 4 };
    int imageSet7[] = { 5, 3};
    int imageSet8[] = { 4};
    int setSize1 = sizeof(imageSet1) / sizeof(imageSet1[0]);
    int setSize2 = sizeof(imageSet2) / sizeof(imageSet2[0]);
    int setSize3 = sizeof(imageSet3) / sizeof(imageSet3[0]);
    int setSize4 = sizeof(imageSet4) / sizeof(imageSet4[0]);
    int setSize5 = sizeof(imageSet5) / sizeof(imageSet5[0]);
    int setSize6 = sizeof(imageSet6) / sizeof(imageSet6[0]);
    int setSize7 = sizeof(imageSet7) / sizeof(imageSet7[0]);
    int setSize8 = sizeof(imageSet8) / sizeof(imageSet8[0]);

    int currentImage = -1; // Start with a default screen
    int nextImage = 0;
    int transitionStep = 0; // 0: No transition, 1: Transition in progress
    float transitionProgress = 0.0f;
    TransitionType transitionType = SLIDE;
    int* currentSet = NULL; // Current set of images for transition
    int currentSetSize = 0;
    int currentIndex = 0; // Index in the current image set

    while (!WindowShouldClose()) {
        // Handle input
        if (IsKeyPressed(KEY_ENTER)) break;
        if (transitionStep == 0) {
            if (update == 1) {
                currentSet = imageSet1;
                currentSetSize = setSize1;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 2) {
                currentSet = imageSet2;
                currentSetSize = setSize2;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }

            else if (update == 3) {
                currentSet = imageSet3;
                currentSetSize = setSize3;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 4) {
                currentSet = imageSet4;
                currentSetSize = setSize4;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 5) {
                currentSet = imageSet5;
                currentSetSize = setSize5;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 6) {
                currentSet = imageSet6;
                currentSetSize = setSize6;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 7) {
                currentSet = imageSet7;
                currentSetSize = setSize7;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
            else if (update == 8) {
                currentSet = imageSet8;
                currentSetSize = setSize8;
                currentIndex = 0;
                TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
            }
        }

        // Update transition progress
        if (transitionStep != 0) {
            transitionProgress += 0.01f; // Adjust this value to change transition speed (slower transition)
            if (transitionProgress >= 1.0f) {
                transitionProgress = 0.0f;
                currentImage = nextImage;
                currentIndex++;
                if (currentIndex >= currentSetSize) {
                    currentImage = -1; // Return to blank screen
                    transitionStep = 0;
                    break;
                }
                else {
                    TransitionToNextImage(&currentImage, &nextImage, &transitionStep, &transitionType, currentSet, currentSetSize);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);


        if (transitionStep != 0) {
            switch (transitionType) {
            case SLIDE:
                DrawSlideTransition(images, currentImage, nextImage, transitionProgress);
                break;
            case FADE:
                DrawFadeTransition(images, currentImage, nextImage, transitionProgress);
                break;
            case SCALE:
                DrawScaleTransition(images, currentImage, nextImage, transitionProgress);
                break;
            }
        }
        else {
            DrawTexture(images[currentImage], 0, 0, WHITE);
        }

        EndDrawing();
        
    }

    // Unload textures
    for (int i = 0; i < NUM_IMAGES; i++) {
        UnloadTexture(images[i]);
    }
    return;
}

void TransitionToNextImage(int* currentImage, int* nextImage, int* transitionStep, TransitionType* transitionType, int imageSet[], int setSize) {
    *transitionType = (TransitionType)(GetRandomValue(0, 2)); // Randomly choose transition type
    if (*currentImage == -1) {
        *nextImage = imageSet[0];
    }
    else {
        int currentIndex = 0;
        for (int i = 0; i < setSize; i++) {
            if (*currentImage == imageSet[i]) {
                currentIndex = i;
                break;
            }
        }
        *nextImage = imageSet[(currentIndex + 1) % setSize];
    }
    *transitionStep = 1;
}
