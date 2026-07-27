#include "MainF.h"
#include "PData.h"
#include "raylib.h"

void PData_UpdateScore(int winner, int looser) {
    FILE* file;
    file = fopen("Data.txt", "r");

    int cnt = 0, NameFound = 0;
    char str[1000], name[1000][1000];
    int score[1000];

    while (fgets(str, 255, file) != NULL) {
        char deststring[1000];
        strncpy(deststring, str, strlen(str) - 1);
        deststring[strlen(str) - 1] = '\0';

        if (cnt % 2 == 0) {
            strcpy(name[cnt / 2], deststring);
            if (!strcmp(player[winner], deststring)) NameFound = 1;
            if (!strcmp(player[looser], deststring)) NameFound = 2;
        }
        else {
            score[cnt / 2] = atoi(str);
            if (NameFound == 1) {
                NameFound = 0;
                score[cnt / 2] += 1;
            }
            if (NameFound == 2) {
                NameFound = 0;
                score[cnt / 2] = 0;
            }
        }

        cnt += 1;
    }
    fclose(file);

    // Sort the names with respect to score
    for (int i = 0; i < (cnt / 2) - 1; i++) {
        for (int j = i + 1; j < (cnt / 2); j++) {
            if (score[j] > score[i]) {
                char temp[1000];
                strcpy(temp, name[j]);
                strcpy(name[j], name[i]);
                strcpy(name[i], temp);
                int tempval = score[i];
                score[i] = score[j];
                score[j] = tempval;
            }
        }
    }

    file = fopen("Data.txt", "w");
    for (int i = 0; i < cnt / 2; i++) {
        fprintf(file, "%s\n%d\n", name[i], score[i]);
    }
    fclose(file);
}

void drawleaderboard() {
    ClearBackground(RAYWHITE); // Ensure screen is cleared before drawing
    Image leaderboardbg = LoadImage("Leaderboard background.png");
    Texture2D texture2 = LoadTextureFromImage(leaderboardbg);
    UnloadImage(leaderboardbg);

    FILE* file;
    file = fopen("Data.txt", "r");
    if (file == NULL) {
        DrawText("No data available", 10, 10, 20, RED);
        return;
    }

    int cnt = 0;
    char str[1000];
    int yPos = 147; // Starting position for drawing text
    int xPos = 500;
    int numval = 0;
    while (fgets(str, 255, file) != NULL) {
        numval += 1;
        if (numval > 6) {
            break;
        }
        str[strcspn(str, "\n")] = 0;
        if (cnt % 2 == 0) {
            char rank[10];
            int position = (cnt / 2) + 1;
            const char* suffix = "th";
            if (position % 10 == 1 && position % 100 != 11) suffix = "st";
            else if (position % 10 == 2 && position % 100 != 12) suffix = "nd";
            else if (position % 10 == 3 && position % 100 != 13) suffix = "rd";

            snprintf(rank, sizeof(rank), "%d%s place:", position, suffix);

            DrawText(rank, xPos, yPos, 35, YELLOW);
            yPos += 40;
            DrawText(str, xPos, yPos, 35, LIGHTGRAY);
        }
        else {
            DrawText(TextFormat(" --- %s win(s)---", str), xPos + 300, yPos, 35, YELLOW);
            yPos += 70;
        }
        cnt += 1;
    }
    fclose(file);
    Rectangle returnButton = { 10, 10, 100, 45 };
    DrawRectangleRec(returnButton, BLACK);
    DrawText("Return", returnButton.x + returnButton.width / 2 - MeasureText("Return", 20) / 2, returnButton.y + 10, 20, WHITE);
}




#define MAX_INPUT_CHARS 64

int DisplayConfirmation(const char* name);
void PData_PlayerMenu();


void PData_PlayerMenu()
{
    ClearBackground(RAYWHITE);
    const int screenWidth = 800;
    const int screenHeight = 600;
    int letterCount = 0;
    int chooseplayer = 0;
    char inputText[64] = ""; // Initialize an empty string to store user input

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        int key = GetCharPressed();
        if (key >= 32 && key <= 125 && letterCount < MAX_INPUT_CHARS)
        {
            inputText[letterCount] = (char)key;
            inputText[letterCount + 1] = '\0';
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            inputText[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
        {
            if (DisplayConfirmation(inputText, chooseplayer)) {
                strcpy(inputText, "");
                letterCount = 0;
                inputText[letterCount] = '\0';
                chooseplayer += 1;
                if (chooseplayer >= 2) break;
            }

        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        char message[1000];
        snprintf(message, sizeof(message), "Name of player %d: ", chooseplayer + 1);
        DrawText(message, screenWidth / 2 + 70, screenHeight / 2 - 80, 75, DARKGRAY);
        DrawRectangle(screenWidth / 2, screenHeight / 2, 780, 65, LIGHTGRAY);
        if (chooseplayer == 0) DrawText(inputText, screenWidth / 2, screenHeight / 2, 60, MAROON);
        else DrawText(inputText, screenWidth / 2, screenHeight / 2, 60, BLUE);
        EndDrawing();
        CloseWindow();
    }
    return;
}

int DisplayConfirmation(const char* name, int num)
{
    FILE* file;
    file = fopen("Data.txt", "r");
    if (file == NULL) {
        file = fopen("Data.txt", "w");
        fclose(file);
        file = fopen("Data.txt", "r");
    }

    int cnt = 0, NameFound = 0;
    char str[1000], temp[3][1000];
    strcpy(temp[0], name);

    while (fgets(str, 255, file) != NULL) {
        char deststring[1000];
        strncpy(deststring, str, strlen(str) - 1);
        deststring[strlen(str) - 1] = '\0';

        if (cnt % 2 == 0 && !strcmp(deststring, name)) NameFound = 1;
        if (NameFound && cnt % 2 != 0) {
            strcpy(temp[cnt % 2], deststring);
            break;
        }
        cnt += 1;
    }
    fclose(file);

    const int screenWidth = 800;
    const int screenHeight = 600;

    ClearBackground(RAYWHITE);

    Rectangle yesButton = { screenWidth / 2 + 200 , screenHeight / 2 + 100, 200, 72 };
    Rectangle noButton = { screenWidth / 2 + 500, screenHeight / 2 + 100, 200, 72 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        if (NameFound) {
            char message[1000];
            snprintf(message, sizeof(message), "Player <%s> exists with a win streak of %s.", temp[0], temp[1]);
            DrawText(message, screenWidth / 2 - 100, screenHeight / 2 - 30, 50, DARKGRAY);
        }

        else {
            char message[1000];
            snprintf(message, sizeof(message), "Player name <%s> does not exist!", name);
            DrawText(message, screenWidth / 2 - 100, screenHeight / 2 - 30, 50, DARKGRAY);
        }

        // Check if Yes or No button is clicked
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, yesButton))
            {
                if (!NameFound) {
                    file = fopen("Data.txt", "a");
                    char* newstr = malloc(strlen(name) + 3);
                    strcpy(newstr, name);
                    strcat(newstr, "\n");
                    fputs(newstr, file);
                    fputs("0", file);
                    fputs("\n", file);
                    fclose(file);
                    free(newstr);
                }
                CloseWindow();
                strcpy(player[num], name);

                return 1;
            }
            else if (CheckCollisionPointRec(mousePoint, noButton))
            {
                // No button clicked
                CloseWindow();
                return 0;
            }
        }

        // Draw
        /*BeginDrawing();
        ClearBackground(RAYWHITE);*/
        //DrawText(TextFormat("Are you sure about the name: %s?", name), screenWidth / 2, screenHeight / 2 , 50, DARKGRAY);
        DrawText(TextFormat("Are you sure about the name <%s>?", name), screenWidth / 2 - 100, (screenHeight / 2) - 80, 50, DARKGRAY);

        DrawRectangleRec(yesButton, GREEN);
        DrawRectangleRec(noButton, RED);
        DrawText("Yes", yesButton.x + (yesButton.width / 2) - 65, yesButton.y + (yesButton.height / 2) - 35, 70, BLACK);
        DrawText("No", noButton.x + (noButton.width / 2) - 45, noButton.y + (noButton.height / 2) - 35, 70, BLACK);
        EndDrawing();
    }

    CloseWindow();
}