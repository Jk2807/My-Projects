#include "MainF.h"
#include "PData.h"
#include "graphics.h"
#include "raylib.h"


void StartGame() {
	//Start the player setting 
    int* chamber;
    MainF_generate(&chamber);
    int winner = drawGame();
    //int winner = MainF_play(chamber);

    if (winner != 3) PData_UpdateScore(winner - 1, (winner % 2));
    free(chamber);
	
	return;
}
int main(void) {
    InitWindow(screenWidth, screenHeight, "Wild West Shootout");
    SetTargetFPS(60);

    // Load image and convert it to a texture once
    Image image = LoadImage("image.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);  // Unload image data from CPU memory (RAM)

    GameState currentState = MENU;

    int NameChosen = 0;
    while (1) {
        //  if (NameChosen) break;
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the texture as the background
        DrawTexture(texture, 0, 0, WHITE);
        Image image = LoadImage("image.png");
        switch (currentState) {
            case MENU:
                drawMenu();
                UnloadTexture(texture);
                Texture2D texture = LoadTextureFromImage(image);
                handleMenuInput(&currentState);
                UnloadImage(image);  // Unload image data from CPU memory (RAM)
                break;
            case GAME:
                UnloadTexture(texture);
                //  handleGameInput(&currentState);
                PData_PlayerMenu();
                currentState = GAMEPLAY;
                StartGame();
                currentState = MENU;
                break;
            case Tutorials:
                UnloadTexture(texture);
                drawTutorials();
                handleTutorialsInput(&currentState);
                break;
            case Leaderboard:
                UnloadTexture(texture);
                drawleaderboard();
                handleLeaderboardInput(&currentState);
                break;
            case Credits:
                printf("-----------------------------------------------------------------");
                drawCredits();
                handleCreditsInput(&currentState);
                break;
        
    }
    /*
    	while (1) {
		//Game title and menu
		clrscr;
		printf("Russian Roulette Xpanded\nChoose an option:\n1 - New game\n2 - Leaderboard\n3 - Tutorials\n4 - Credits\n5 - Quit\n--> ");
		int option;
		(void)scanf("%d", &option);
		if (option == 5) break;	
		if (option == 2) PData_ShowLeaderBoard();
		if (option == 3) {
			MainF_Tutorials();
		}
		if (option == 4) {
			MainF_Credits();
		}
		if (option == 1) {
			StartGame();
		}
	}
    */
        EndDrawing();
        CloseWindow();
    }


    // Unload texture and close window
    UnloadTexture(texture);
    return 0;
}
/*int main() {
	while (1) {
		//Game title and menu
		clrscr;
		printf("Russian Roulette Xpanded\nChoose an option:\n1 - New game\n2 - Leaderboard\n3 - Tutorials\n4 - Credits\n5 - Quit\n--> ");
		int option;
		(void)scanf("%d", &option);
		if (option == 5) break;	
		if (option == 2) PData_ShowLeaderBoard();
		if (option == 3) {
			MainF_Tutorials();
		}
		if (option == 4) {
			MainF_Credits();
		}
		if (option == 1) {
			StartGame();
		}
	}
	return 0;
}
*/