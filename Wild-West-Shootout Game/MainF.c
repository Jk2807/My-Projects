#include "MainF.h"
#include "PData.h"
#include "graphics.h"
#include "raylib.h"

void drawTutorials() {
    ClearBackground(RAYWHITE);
    Image tutorialbg = LoadImage("Tutorial background.png");
    Texture2D texture1 = LoadTextureFromImage(tutorialbg);
    UnloadImage(tutorialbg);
    DrawText("Wild West Shootout", 350, 70, 70, PINK);
    DrawText("This game involves a revolver cylinder with 3 to 10 slots, containing both random", 200, 200, 30, RAYWHITE);
    DrawText("bullets and blank slots. At the beginning of the game, each player is randomly", 200, 230, 30, RAYWHITE);
    DrawText("assigned 6 skills from a pool of 6 possible skills:", 200, 260, 30, RAYWHITE);
    DrawText("1. Deadly Shot: Does DOUBLE the damage (-2 life points).", 200, 300, 25, RAYWHITE);
    DrawText("2. Mystic Heal: HEAL with 2 options:", 200, 330, 25, RAYWHITE);
    DrawText("   a. Option 1: Auto-HEAL 1 life point.", 220, 360, 25, RAYWHITE);
    DrawText("   b. Option 2: GAMBLE for a better heal:", 220, 390, 25, RAYWHITE);
    DrawText("      - Outcome 1: +2 life points.", 240, 420, 25, RAYWHITE);
    DrawText("      - Outcome 2: -2 life points.", 240, 450, 25, RAYWHITE);
    DrawText("3. Magic Bullet: Change the bullet into a blank one (no life points deducted).", 200, 480, 25, RAYWHITE);
    DrawText("4. Bullet Removal: Remove 1 bullet from the chamber.", 200, 510, 25, RAYWHITE);
    DrawText("5. Skill Theft: Steal 1 skill from the enemy.", 200, 540, 25, RAYWHITE);
    DrawText("6. Swift Reckoning: Nullify the enemy's turn, granting yourself an additional turn.", 200, 570, 25, RAYWHITE);
    Rectangle returnButton = { 10, 10, 100, 45 };
    DrawRectangleRec(returnButton, BLACK);
    DrawText("Return", returnButton.x + returnButton.width / 2 - MeasureText("Return", 20) / 2, returnButton.y + 10, 20, WHITE);
}

void drawCredits()
{
    ClearBackground(RAYWHITE);
    int positionx = 50;
    int positiony = 50;
    int y_increment = 50;

    // Draw each team member and their roles with specified colors
    DrawText("Nguyen Quoc An", positionx, positiony, 40, WHITE);
    DrawText("- 10223002", positionx + 500, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Responsible for the base code of the game", positionx, positiony, 40, GREEN);
    positiony += y_increment * 2;

    DrawText("Nguyen Do Nguyen", positionx, positiony, 40, WHITE);
    DrawText("- 10223056", positionx + 500, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Responsible for the design, cosmetics and the base of the game", positionx, positiony, 40, GREEN);
    positiony += y_increment * 2;

    DrawText("Nguyen Xuan Son", positionx, positiony, 40, WHITE);
    DrawText("- 10222042", positionx + 500, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Responsible for the design and cosmetics of the game", positionx, positiony, 40, GREEN);
    positiony += y_increment * 2;

    DrawText("Nguyen Dinh Thai Tue", positionx, positiony, 40, WHITE);
    DrawText("- 10223071", positionx + 500, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Items system maker, beta tester, and game balancer", positionx, positiony, 40, GREEN);
    positiony += y_increment * 2;

    DrawText("Nguyen Trung Son", positionx, positiony, 40, WHITE);
    DrawText("- 10223100", positionx + 500, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Planning game ideas and being our group consultant", positionx, positiony, 40, GREEN);
    positiony += y_increment * 2;

    DrawText("Bui Khanh Hung & Nguyen Dang Viet Khang", positionx, positiony, 40, WHITE);
    DrawText("- 10223026 & 10223082", positionx + 1000, positiony, 40, YELLOW);
    positiony += y_increment;
    DrawText("_ROLE_: Responsible for the making of menu, items’ designs", positionx, positiony, 40, GREEN);

    Rectangle returnButton = { 10, 10, 100, 45 };
    DrawRectangleRec(returnButton, BLACK);
    DrawText("Return", returnButton.x + returnButton.width / 2 - MeasureText("Return", 20) / 2, returnButton.y + 10, 20, WHITE);

}

void drawItem(Texture2D itm, int x, int y) {
    DrawTexture(itm, x, y, WHITE);
    return 0;
}

//Return: 1 if player 1 wins      2 if player 2 wins    3 if draw
int drawGame() {
    srand(time(NULL));
    int cnt = rand() % 2;
    int* chamber;
    int numL = MainF_generate(&chamber);

    ClearBackground(RAYWHITE);

    const int ScreenWidth = 1600;
    const int ScreenHeight = 900;

    //InitWindow(screenWidth, screenHeight, "Multiple Images Example");
    //SetTargetFPS(60);

    // Load your images (replace these paths with actual image files)
    Texture2D image1 = LoadTexture("character2.png");
    Texture2D image2 = LoadTexture("character1.png");
    Texture2D image3 = LoadTexture("Versus.png");
    Texture2D image4 = LoadTexture("heart.png");
    Texture2D image5 = LoadTexture("blueheart.png");
    Texture2D item[6] = { LoadTexture("DEADLY-SHOT.png") ,
        LoadTexture("HEAL.png"),
        LoadTexture("Invortes.png"), 
        LoadTexture("Removal.png"), 
        LoadTexture("Thief.png"), 
        LoadTexture("Handcuf.png") };

    
    Image backgroundImage = LoadImage("1GAMEPLAY.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    Texture2D liveI = LoadTexture("live.png");
    Texture2D blankI = LoadTexture("blank.png");
    UnloadImage(backgroundImage);

    while (1) {
        if (IsKeyPressed(KEY_ENTER)) break;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        char message[1000];
        if (cnt % 2 == 0) {
            snprintf(message, sizeof(message), "Player %s gets the first turn", player[0]);
            DrawText(message, (ScreenWidth / 2) - 470, 75, 60, RED);
        }
        else {
            snprintf(message, sizeof(message), "Player %s gets the first turn", player[1]);
            DrawText(message, (ScreenWidth / 2) - 470, 75, 60, BLUE);
        }
        

        int bposx = (ScreenWidth/2)-((chamber[0]*90)/2);
        int bposy = 150;

        for (int i = 1; i <= numL; i++) {
            DrawTexture(liveI, bposx, bposy, WHITE);
            bposx += 92;
        }
        bposy += 13;
        for (int i = 1; i <= chamber[0] - numL; i++) {
            DrawTexture(blankI, bposx, bposy, WHITE);
            bposx += 92;
        }

        int heart1pos = 215;
        int heart2pos = 1250;
        for (int i = 0; i < 3; i++) {
            DrawTexture(image4, heart1pos, 230, WHITE);
            heart1pos += 63;
        }

        for (int i = 0; i < 3; i++) {
            DrawTexture(image5, heart2pos , 230, RAYWHITE);
            heart2pos += 63;
        }
        int posix = 150, posiy = 750;
        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j < 3; j++) {
                drawItem(item[items[i][j]], posix, posiy);
                posix += 153;
            }
            posix += 500;

        }
        // Draw your images
        
        DrawTexture(image1, 150, 300, WHITE);
        DrawTexture(image2, 1100, 300, WHITE);
        DrawTexture(image3, 650, 300, WHITE);
       

        snprintf(message, sizeof(message), "%s", player[0]);
        DrawText(message, 225, 625, 90, RED);
        snprintf(message, sizeof(message), "%s", player[1]);
        DrawText(message, 1250, 625, 90, BLUE);

        EndDrawing();
    }

    UnloadTexture(image1);
    UnloadTexture(image2);
    CloseWindow();


    //Play function-----------------------------------------------------------
    int result = -1;
    int ptr = 1;

    


    ////Health of the players -- health[0] = value of p1-- - health[1] = value of p2;
    int health[2] = { 3, 3 };
    //current handcuffing effect status:        0--> no cuff        1 --> cuffed
    int IsCuffed[2] = { 0, 0 };
    int dmg = 1;
    HasEnded = 1;
    int cntcuff = 0;



    while (1) {
       
        char message[100];
        int action;
        do {
            action = MainF_maketurn(chamber, &ptr, cnt % 2, health, IsCuffed, &dmg);
            if (health[0] <= 0) return 1;
            if (health[1] <= 0) return 0;
            if (action == 3) 
                items_itemMain(chamber, &ptr, cnt % 2, health, IsCuffed, &dmg);
      
        } while (action == 3);
        HasEnded = 1;
         //Use an Items Button . click
       

        if (action != -1) {
            //Check winner + game ended (0 if ended and 1 if not)
            printf("hihi----------------------");
            HasEnded = MainF_proccessRes(chamber, action, &cnt, &ptr, health, &dmg);
        
            //Program to wait for keypress
            /*printf("Press ENTER to continue\n");
            (void)getch();*/

            if (ptr > chamber[0] && HasEnded == 0) {
                result = 3;
                clrscr;
                while (!WindowShouldClose()) {
                    ClearBackground(BLACK);
                    BeginDrawing();
                    if (health[0] > health[1]) {
                        snprintf(message, sizeof(message), "Player %s wins!!", player[0]);
                        DrawText(message, (screenWidth / 2) - ((30 * (23 + strlen(player[1]))) / 2), screenHeight / 2, 60, BLUE);
                    }
                    else if (health[1] > health[0]) {
                        snprintf(message, sizeof(message), "Player %s wins!!", player[1]);
                        DrawText(message, (screenWidth / 2) - ((30 * (23 + strlen(player[1]))) / 2), screenHeight / 2, 60, BLUE);
                    }
                    else if (health[1] == health[0]) {
                        DrawText("Chamber clear! It is a DRAW! ",screenWidth / 2, screenHeight / 2, 60, BLUE);
                    }
                    EndDrawing();
                        CloseWindow();
                        if (IsKeyPressed(KEY_ENTER)) break;
                }
                HasEnded = 3;
                    break;
            }
        }
        else {
            cnt += 1;
            HasEnded = 0;
        }


        if (HasEnded != 0) {
            break;
        }

    }

    


    return HasEnded;
}

//Generate a chamber of bullets, 1 represent a live round, 0 a blank        ||      Generate items --> Return num live
int MainF_generate(int** arr) {
    //Generate the chamber
    srand(time(NULL));
    int num_rounds = rand() % 10 + 3;

    *arr = (int*)malloc((num_rounds + 10) * sizeof(int));
    (*arr)[0] = num_rounds;

    num_live = (2 * num_rounds) / 3;
    // Ensure at least 1 live round if the calculation results in 0
    if (num_live == 0) {
        num_live = 1;
    }

    for (int i = 1; i <= num_rounds; i++) (*arr)[i] = 0;
    int inserted = 0;
    //printf("%d %d\n", num_rounds, num_live);
    while (inserted < num_live) {
        int pos = rand() % num_rounds + 1;


        //Debug code --> printout the selected location
        //Sleep(500);
        //printf("%d\n", pos);


        if ((*arr)[pos] == 0) {
            (*arr)[pos] = 1;
            inserted += 1;
        }
    }
    for (int i = 1; i < (*arr)[0]; i++) printf("%d--", (*arr)[i]);
    //Generate the items
    for (int i = 0; i < 6; i++) {
        int x = rand() % 6;
        items[i / 3][i % 3] = x;
       // items[i / 3][i % 3] = 1;
    }

    //Tesing ---          REMOVE ME
    //items[0][0] = 1;
    //items[1][0] = 1;
    //items[2][0] = 1;


    //Print out the Round's info
    //clrscr;
    //printf("GAME INFO:\n\n\n");

    //Print out bullet sequence ---------------- REMOVE ME (4 DEBUG)
 //   for (int i = 0; i <= (*arr)[0]; i++) printf("%d ", (*arr)[i]);
    //printf("\n");


    //printf("Total bullets: %d       Live Rounds: %d      Blanks: %d\n\n", num_rounds, num_live, num_rounds-num_live);
    //items_getlist(0);
    //printf("\n\n");
    //items_getlist(1); 


    return num_live;
}





int MainF_maketurn(int* chamber, int* ptr, int turn, int* health, int* IsCuffed, int *dmg) {


    int choice;

    Texture2D image[2] = { LoadTexture("character2.png"), LoadTexture("character1.png") };
    Texture2D image3 = LoadTexture("Versus.png");
    Texture2D image4 = LoadTexture("heart.png");
    Texture2D image5 = LoadTexture("blueheart.png");
    Texture2D item[6] = { LoadTexture("DEADLY-SHOT.png") ,
        LoadTexture("HEAL.png"),
        LoadTexture("Invortes.png"),
        LoadTexture("Removal.png"),
        LoadTexture("Thief.png"),
        LoadTexture("Handcuf.png") };
    Texture2D item_used[6] = {
        LoadTexture("items_used\\DEADLY-SHOT_used.png"),
        LoadTexture("items_used\\HEAL_used.png"),
        LoadTexture("items_used\\INVORTES_used.png"),
        LoadTexture("items_used\\REMOVAL_used.png"),
        LoadTexture("items_used\\THIEF_used.png"),
        LoadTexture("items_used\\HANDCUF_used.png")
    };
    
    

    Image backgroundImage = LoadImage("1GAMEPLAY.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
    



    //Check if  is handcuffed
    if (IsCuffed[turn] == 1) {
        char message[100];
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(backgroundTexture, 0, 0, WHITE);


            snprintf(message, sizeof(message), "Player %s is handcuffed!!", player[turn]);
            if (turn%2==0) DrawText(message, (screenWidth / 2)-((30*(23+strlen(player[turn]))) / 2), screenHeight / 2, 60, RED);
            else DrawText(message, (screenWidth / 2) - ((30 * (23+strlen(player[turn])))/2), screenHeight / 2, 60, BLUE);
            EndDrawing();
            CloseWindow();
            if (IsKeyPressed(KEY_ENTER)) {
                IsCuffed[turn] = 0;
                return -1;
            }
        }

    }

    Rectangle button1 = { 50, 100, 600, 150 };
    Rectangle button2 = { 50, 300, 600, 150 };
    Rectangle button3 = { 50, 500, 600, 150 };

    char message[1000];

    while (!WindowShouldClose()) {

        

        //Chamber cleared
        if (*ptr > chamber[0]) return 4;


        BeginDrawing();
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        ClearBackground(RAYWHITE);

        
        //Draw Player
        if (turn % 2 == 0) {
            DrawTexture(image[0], screenWidth- 600, screenHeight-600, WHITE);
            int posx = (screenWidth - 600+150)-((62*health[turn%2])/2);
            for (int i = 0; i < health[0]; i++) {
                DrawTexture(image4, posx, screenHeight - 700, WHITE);
                posx += 62;
            }
            snprintf(message, sizeof(message), "Player < %s > turn:", player[0]);
            DrawText(message, (screenWidth - 650), 650, 60, RED);

        }
        else {
            DrawTexture(image[1], screenWidth - 700, screenHeight - 600, WHITE);
            int posx = (screenWidth - 700+325) - ((62 * health[turn % 2]) / 2);
            for (int i = 0; i < health[1]; i++) {
                DrawTexture(image5, posx, screenHeight - 700, WHITE);
                posx += 62;
            }
            snprintf(message, sizeof(message), "Player < %s > turn:", player[1]);
            DrawText(message, (screenWidth - 650), 650, 60, BLUE);
        }
        
        
        DrawRectangleRec(button1, BROWN);
        DrawRectangleRec(button2, BEIGE);
        DrawRectangleRec(button3, DARKGRAY);

        DrawText("Shoot Opponent", button1.x + 70, button1.y + 60, 60, BLACK);
        DrawText("Shoot Yourself", button2.x + 70, button2.y + 60, 60, BLACK);
        DrawText("Use An Item", button3.x + 70, button3.y + 60, 60, BLACK);

        //Print out  state
        /*printf("Health Status:           <%s>: %d            <%s>: %d\n", player[0], health[0], player[1], health[1]);
        printf("<%s> turn: \n", player[(turn % 2)]);*/


        //Print out the pointer location (For testing)
        //printf("\nptr = %d\n", *ptr);

        /*printf("Make a Choice:\n1. Shoot yourself\n2. Shoot opponent\n3. Use an item(WIP)\n-->");
        (void)scanf("%d", &choice);*/

        EndDrawing();
        CloseWindow();

        //Item usage
        if (isButtonClicked(button1)) {
            return 1;
        }
        if (isButtonClicked(button2)) {

            return 2;
        }
        if (isButtonClicked(button3)) {

            return 3;
        }
        //if (choice == 3) {
            
            //items_itemMain(chamber, ptr, turn, health, IsCuffed, dmg);
            /*if (chamber[*ptr] == 1) *live -= 1;
            *ptr += 1;*/

        //}


    };


   /* return choice;*/

}

//Function to proccess the result -- return 3 if is a draw --- 0 if not ended --- 1, 2 if player 1/2 wins
//playerID: even->player 1; odd->player 2

int MainF_proccessRes(int* chamber, int action, int *turn, int* ptr, int* health, int* dmg) {
    printf("%d %d--------------------------------", *turn, chamber[*ptr]);
    HasEnded =0;        //   varible to check if game ended

    //process result and print out status       action = 3: clear chamber       action = 1: shot yourself       action = 2: shot opponent

    if (action == 4) {
        HasEnded = 3;
     
    }
    else{
        int playerReceived = (action % 2 + (*turn) % 2) % 2;

        //if a live round is in the first slot
        if (chamber[*ptr] == 1) {
        //   while (!WindowShouldClose()) {
                ClearBackground(BLACK);
                BeginDrawing();
                //DrawText("Live Round!", 650, 60, 60, RED);
                if (action == 1) {
                    if (playerReceived == 0) {
                        update = 5;
                        transition();
                    }
                    else if (playerReceived == 1) {
                        update = 1;
                        transition();
                    }
                }
                else if (action == 2) {
                    if (playerReceived == 0) {
                        update = 3;
                        transition();
                    }
                    else if (playerReceived == 1) {
                        update = 7;
                        transition();
                    }
                    
                }
                EndDrawing();
                CloseWindow();
            //   if (IsKeyPressed(KEY_ENTER)) break;
                //printf("Live Round!!!\n");
                //printf("<%s> lost %d live(s)\n", player[playerReceived], *dmg);

          // }
            health[playerReceived] -= *dmg;
            *turn += 1;
        }
        else {
           // while (!WindowShouldClose()) {
                ClearBackground(BLACK);
                BeginDrawing();
                //DrawText("Blank Round!", 650, 60, 60, RED);
                if (action == 1) {
                    if (playerReceived == 0) {
                        update = 6;
                        transition();
                    }
                    else if (playerReceived == 1) {
                        update = 2;
                        transition();
                    }
                    *turn += 1;
                }
                else if (action == 2) {
                    if (playerReceived == 0) {
                        update = 4;
                        transition();
                    }
                    else if (playerReceived == 1) {
                        update = 8;
                        transition();
                    }
                }
                EndDrawing();
                CloseWindow();
              //  if (IsKeyPressed(KEY_ENTER)) break;
                
            
            //if (action == 1 && ) {
                //printf("<%s> loses the turn\n", player[(*turn) % 2]);
                //*turn += 1;
            //}
            //else printf("<%s> keeps the turn\n", player[(*turn) % 2]);
        }



        //Check winner
        if ((health[0] <= 0) || (health[1] <= 0)) {
            if (health[0] <= 0) {
                char message[100];
                while (!WindowShouldClose()) {
                    ClearBackground(BLACK);
                    BeginDrawing();
                    snprintf(message, sizeof(message), "Player %s wins!!", player[1]);
                    DrawText(message, (screenWidth / 2) - ((30 * (23 + strlen(player[1]))) / 2), screenHeight / 2, 60, BLUE);
                    EndDrawing();
                    CloseWindow();
                    if (IsKeyPressed(KEY_ENTER)) break;
                }
                //printf("<%s> wins\n", player[1]);
                HasEnded = 2;
            }
            if (health[1] <= 0) {
                char message[100];
                while (!WindowShouldClose()) {
                    ClearBackground(BLACK);
                    BeginDrawing();
                    snprintf(message, sizeof(message), "Player %s wins!!", player[0]);
                    DrawText(message, (screenWidth / 2) - ((30 * (23 + strlen(player[0]))) / 2), screenHeight / 2, 60, RED);
                    CloseWindow();
                    if (IsKeyPressed(KEY_ENTER)) break;
                    EndDrawing();
                }
                //printf("<%s> wins\n", player[0]);
                HasEnded = 1;
            }
        }


        
        *ptr += 1;    //      increase the pointer value of the chamber

    }
  
    //return the damage value to 1
    if (*dmg != 1) *dmg = 1;

    return HasEnded;
}
