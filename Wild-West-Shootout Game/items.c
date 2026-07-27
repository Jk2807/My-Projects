#include "MainF.h"
#include "PData.h"
#include "raylib.h"
#include "graphics.h"

//Print out the list of a player's current items
void items_getlist(int pl) {
	printf("<%s> items: ", player[pl]);
	for (int j = 0; j < 3; j++) {
		printf("\n%d. ", j + 1);
		switch (items[pl][j]) {
		case 0:
			printf("Deadly-Shot (x2 damage)");
			break;
		case 1:
			printf("Mystic-Heal (heal)");
			break;
		case 2:
			printf("Inverter (Bullet swap)");
			break;
		case 3:
			printf("Bullet-Removal (Remove 1 bullet)");
			break;
		case 4:
			printf("Thief (Take 1 item from opponent, use it immediately)");
			break;
		case 5:
			printf("Handcuff (bans 1 opponent's turn)");
			break;
		default:
			printf("");
			break;

		}
	}
	return;
}


//Item heal function: return the healing value


void items_useitem(int* chamber, int* ptr, int turn, int* health, int* IsCuffed, int* dmg, int item_id, int IsThief) {
	//Item Mystic-Heal(heal)
	if (items[turn][item_id] == 1) {
		
		Rectangle button_Safe = { 100, 500,600, 100 };
		Rectangle button_Double_down = { 900, 500, 600,100 };
		Rectangle odd_Button = { 100, 300,600, 100 };
		Rectangle even_Button = { 900, 300, 600,100 };

		// Safe, double_down MENU
		Color charclr = RED;
		char message[100];
		int haveDone = 0;
		if (IsCuffed[((turn + IsThief) % 2 + 1) % 2] == 1) charclr = BLUE;
		while (1) {
			if (haveDone) break;
			BeginDrawing();
			ClearBackground(BLACK);
			DrawRectangleRec(button_Safe, YELLOW);
			DrawRectangleRec(button_Double_down, GREEN);

			DrawText("Choose an option", 400, 100, 100, charclr);
			DrawText("Safe", 100, 500, 100, PINK);
			DrawText("Double down", 900, 500, 100, PINK);

			if (isButtonClicked(button_Safe)) {
				while (1) {
					BeginDrawing();
					ClearBackground(BLACK);
					snprintf(message, sizeof(message), "Player < %s > got a live!", player[(turn + IsThief) % 2]);
					DrawText(message, 200, 100, 70, charclr);
					EndDrawing();
					CloseWindow();
					if (IsKeyPressed(KEY_ENTER)) {
						health[(turn + IsThief) % 2] += 1;
						haveDone = 1;
						break;
					}
				}

			}
			else if (isButtonClicked(button_Double_down)){
				int ran = rand() % 10 + 1;
				BeginDrawing();
				ClearBackground(BLACK);
				while (1)
				{
					BeginDrawing();
					ClearBackground(BLACK);
					DrawRectangleRec(odd_Button, PINK);
					DrawRectangleRec(even_Button, RED);
					DrawText("Pick a side: ", 400, 600, 100, charclr);
					DrawText("ODD", 100, 300, 100, BLUE);
					DrawText("EVEN", 900, 300, 100, BLUE);
					if (isButtonClicked(odd_Button)) {
						while (1) {
							BeginDrawing();
							snprintf(message, sizeof(message), "The random number is: %d!", ran);
							DrawText(message, 350, 100, 70, charclr);
							if (ran % 2 == 0) {
								snprintf(message, sizeof(message), "Player < %s > lost a live!", player[(turn + IsThief) % 2]);
								DrawText(message, 350, 200, 70, charclr);
								if (IsKeyPressed(KEY_ENTER)) {
									health[(turn + IsThief) % 2] -= 1;
									if (health[(turn + IsThief) % 2] == 0) health[(turn + IsThief) % 2] += 1;
									haveDone = 1;
									break;
								}
								
							}
							else {
								snprintf(message, sizeof(message), "Player < %s > gained 2 lives!", player[(turn + IsThief) % 2]);
								DrawText(message, 350, 200, 70, charclr);
								if (IsKeyPressed(KEY_ENTER)){
									health[(turn + IsThief) % 2] += 2;
									haveDone = 1;
									break;
								}
							}
							EndDrawing();
							CloseWindow();
						}
					}
					else if (isButtonClicked(even_Button)) {
						while (1) {
							BeginDrawing();
							snprintf(message, sizeof(message), "The random number is: %d!", ran);
							DrawText(message, 350, 100, 70, charclr);
							if (ran % 2 != 0) {
								snprintf(message, sizeof(message), "Player < %s > lost a live!", player[(turn + IsThief) % 2]);
								DrawText(message, 350, 200, 70, charclr);
								if (IsKeyPressed(KEY_ENTER)) {
									health[(turn + IsThief) % 2] -= 1;
									haveDone = 1;
									break;
								}

							}
							else {
								snprintf(message, sizeof(message), "Player < %s > gained 2 lives!", player[(turn + IsThief) % 2]);
								DrawText(message, 350, 200, 70, charclr);
								if (IsKeyPressed(KEY_ENTER)) {
									health[(turn + IsThief) % 2] += 2;
									haveDone = 1;
									break;
								}
							}
							EndDrawing();
							CloseWindow();
						}
					}

					// End odd,even MENU
					if (haveDone) break;
					EndDrawing();
					CloseWindow();
				}
				
				EndDrawing();
				CloseWindow();


			}
			EndDrawing();
			CloseWindow();

		}
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
	}

	//Item Deadly-Shot (x2 damage)
	if (items[turn][item_id] == 0) {
		*dmg = 2;
		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(BLACK);
			char message[1000];
			snprintf(message, sizeof(message), "Player < %s > activates < Deadly-Shot >\n", player[(turn + IsThief) % 2]);
			if ((turn + IsThief) % 2 == 0) {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, RED);
				DrawText("x2 damage for the next shot", (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, RED);
			}
			else {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, BLUE);
				DrawText("x2 damage for the next shot", (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, BLUE);
			}

			EndDrawing();
			CloseWindow();
			if (IsKeyPressed(KEY_ENTER)) break;

		}
	}

	//Item Inverter (Round swap)
	if (items[turn][item_id] == 2) {
		if (chamber[*ptr] == 0) chamber[*ptr] = 1;
		else chamber[*ptr] = 0;

		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(BLACK);
			char message[1000];
			snprintf(message, sizeof(message), "Player < %s > activates < Item Inverter >\n", player[(turn + IsThief) % 2]);
			if ((turn + IsThief) % 2 == 0) {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, RED);
				DrawText("The top bullet in the chamber has been inverted", (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, RED);
			}
			else {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, BLUE);
				DrawText("The top bullet in the chamber has been inverted", (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, BLUE);
			}

			EndDrawing();
			CloseWindow();
			if (IsKeyPressed(KEY_ENTER)) break;
		}

	}

	//Bullet-Removal (Remove 1 bullet)
	if (items[turn][item_id] == 3) {
		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(BLACK);
			char message[100], tp[100];

			strcpy(tp, "The removed bullet was a ");
			if (chamber[*ptr] == 1) strcat(tp, "live round");
			else strcat(tp, "blank round");


			if (chamber[*ptr] == 1) printf("live round!\n");
			else printf("blank round!\n");
			snprintf(message, sizeof(message), "Player < %s > activates < Bullet-Removal >", player[(turn+IsThief)%2]);
			if (turn == 0) {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, RED);
				DrawText(tp, (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, RED);
			}
			else {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, BLUE);
				DrawText(tp, (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, BLUE);
			}

			EndDrawing();
			CloseWindow();
			if (IsKeyPressed(KEY_ENTER)) break;
		}
		*ptr += 1;

	}

	//Thief (Take 1 item from opponent)
	if (items[turn][item_id] == 4) {
		int noitem = 1;
		Texture2D item[12] = { LoadTexture("DEADLY-SHOT.png"),
								LoadTexture("HEAL.png"),
								LoadTexture("Invortes.png"),
								LoadTexture("Removal.png"),
								LoadTexture("Thief.png"),
								LoadTexture("Handcuf.png"),
								LoadTexture("DEADLY-SHOT_used.png"),
								LoadTexture("HEAL_used.png"),
								LoadTexture("Invortes_used.png"),
								LoadTexture("Removal_used.png"),
								LoadTexture("Thief_used.png"),
								LoadTexture("Handcuf_used.png")};

		Rectangle button_item_1 = { (screenWidth / 2) - 750, screenHeight / 2 - 200, 130, 130 };
		Rectangle button_item_2 = { (screenWidth / 2) - 750 + 153, screenHeight / 2 - 200, 130, 130 };
		Rectangle button_item_3 = { (screenWidth / 2) - 750 + 153*2, screenHeight / 2 - 200, 130, 130 };

		Color txtclr;
		if (turn == 0) txtclr = RED;
		else txtclr = BLUE;
		char message[100];
		while (1) {
			BeginDrawing();
			ClearBackground(BLACK);
			snprintf(message, sizeof(message), "Pick an item from player < %s >: ", player[(turn + 1) % 2]);

			DrawRectangleRec(button_item_1, GREEN);
			DrawRectangleRec(button_item_2, GREEN);
			DrawRectangleRec(button_item_3, GREEN);

			DrawText(message, (screenWidth / 2) - 750, screenHeight / 2 - 300, 60, txtclr);
			int valx = (screenWidth / 2) - 750, valy = screenHeight / 2 - 200;
			for (int j = 0; j < 3; j++) {
				int itemsD = items[(turn + 1) % 2][j];
				if (itemsD < 6) noitem = 0;
				if (itemsD == 4) itemsD += 6;
				drawItem(item[itemsD], valx, valy);
				valx += 153;
			}
			if (noitem) break;
			EndDrawing();
			CloseWindow();


			if (isButtonClicked(button_item_1) && items[(turn+1)%2][0] < 6 && items[(turn + 1) % 2][0] != 4) {
				printf("hihiihh1---------");
				items_useitem(chamber, ptr, (turn+1)%2, health, IsCuffed, dmg, 0, 1);
				break;
			}
			if (isButtonClicked(button_item_2) && items[(turn + 1) % 2][1] < 6 && items[(turn + 1) % 2][1] != 4) {
				printf("hihiihh2---------");
				items_useitem(chamber, ptr, (turn + 1) % 2, health, IsCuffed, dmg, 1, 1);
				break;
			}
			if (isButtonClicked(button_item_3) && items[(turn + 1) % 2][2] < 6 && items[(turn + 1) % 2][2] != 4) {
				printf("hihiihh3---------");
				items_useitem(chamber, ptr, (turn + 1) % 2, health, IsCuffed, dmg, 2, 1);
				break;
			}

			//if (IsKeyPressed(KEY_ENTER)) break;
		}

	}

		//printf("Choose an item from ");
		//items_getlist(((turn + IsThief) % 2 + 1) % 2);
		//int choice;
		//while (1) {
		//	printf("\n--> "); (void)scanf("%d", &choice);
		//	if ((choice > 3) || (choice < 0) || (items[(turn + 1) % 2][choice - 1] == -1) || (items[(turn + 1) % 2][choice - 1] == 4)) printf("Invalid option! Try again\n");
		//	else break;
		//}
		//items_useitem(chamber, ptr, (turn + 1) % 2, health, IsCuffed, dmg, choice - 1, 1);
		//items[((turn + IsThief) % 2 + 1) % 2][choice - 1] = -1;

	//Item Handcuff (bans 1 opponent's turn) 
	if (items[turn][item_id] == 5) {
		char PlayerReceive = ((turn + IsThief) % 2 + 1) % 2;
		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(BLACK);
			char message[100], msg2[100];

			snprintf(message, sizeof(message), "Player < %s > activates < Handcuff >", player[(turn + IsThief) % 2]);
			snprintf(msg2, sizeof(message), "Player < %s > has been Handcuffed!", player[PlayerReceive]);
			if ((turn + IsThief) % 2 == 0) {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, RED);
				DrawText(msg2, (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, BLUE);
			}
			else {
				DrawText(message, (screenWidth / 2) - 750, screenHeight / 2, 60, BLUE);
				DrawText(msg2, (screenWidth / 2) - 750, screenHeight / 2 + 60, 60, RED);
			}
			EndDrawing();
			CloseWindow();
			if (IsKeyPressed(KEY_ENTER)) break;
		}
		IsCuffed[PlayerReceive] = 1;
	}
	items[turn][item_id] += 6;
	return;
}

void items_itemMain(int* chamber, int* ptr, int turn, int* health, int* IsCuffed, int* dmg){

	// Load your images (replace these paths with actual image files)
	
	Texture2D item[12] = { LoadTexture("DEADLY-SHOT.png"),
						   LoadTexture("HEAL.png"),
					       LoadTexture("Invortes.png"),
		                   LoadTexture("Removal.png"),
						   LoadTexture("Thief.png"),
		                   LoadTexture("Handcuf.png"), 
						   LoadTexture("f4-SHOT_used.png"),
						   LoadTexture("HEAL_used.png"),
						   LoadTexture("Invortes_used.png"),
						   LoadTexture("Removal_used.png"),
						   LoadTexture("Thief_used.png"),
						   LoadTexture("Handcuf_used.png")
						 };

	int posix = 50, posiy = 700;


	
	Rectangle button_item_1 = { posix, posiy, 130, 130 };
	Rectangle button_item_2 = { posix + +170, posiy, 130, 130 };
	Rectangle button_item_3 = { posix + +170 * 2, posiy, 130, 130 };
	Rectangle buttonReturn = { posix + +170 * 3, posiy, 190, 50 };

	Rectangle GrayOut1 = { 120-30, 190, 540, 10 };
	Rectangle GrayOut2 = { 120 - 30, 390, 540, 10 };
	Rectangle GrayOut3 = { 120 - 30, 590, 540, 10 };

	while (1) {
		// draw item in "Use an Items Button"
		posix = 50, posiy = 700;
		BeginDrawing();

		DrawRectangleRec(button_item_1, GREEN);
		DrawRectangleRec(button_item_2, GREEN);
		DrawRectangleRec(button_item_3, GREEN);
		DrawRectangleRec(buttonReturn, DARKGRAY);
		DrawText("RETURN", posix + +170 * 3, posiy,45,BLACK);

		//Gray out shoot buttons
		DrawRectangleRec(GrayOut1, YELLOW);
		DrawRectangleRec(GrayOut2, YELLOW);
		DrawRectangleRec(GrayOut3, YELLOW);


		for (int j = 0; j < 3; j++) {
			drawItem(item[items[turn][j]], posix, posiy);
			posix += 170;
		}


		if (isButtonClicked(button_item_1) && items[turn][0] < 6) {
			items_useitem(chamber, ptr, turn, health, IsCuffed, dmg, 0, 0);
			EndDrawing();
			CloseWindow();
			return;
		}
		if (isButtonClicked(button_item_2) && items[turn][1] < 6) {
			items_useitem(chamber, ptr, turn, health, IsCuffed, dmg, 1, 0);
			EndDrawing();
			CloseWindow();
			return;
		}
		if (isButtonClicked(button_item_3) && items[turn][2] < 6) {
			items_useitem(chamber, ptr, turn, health, IsCuffed, dmg, 2, 0);
			EndDrawing();
			CloseWindow();
			return;
		}
		if (isButtonClicked(buttonReturn)) {
			CloseWindow();
			EndDrawing();
			return;
		}
		EndDrawing();
	}

	//int choose;
	//items_getlist(turn);
	//printf("\n4. Return (Don't use any item)\n");
	//while (1) {
	//	printf("--> "); (void)scanf("%d", &choose);
	//	if ((choose > 4) || (choose < 0) || (items[turn][choose - 1] == -1)) printf("Invalid option! Try again\n");
	//	else break;
	//}
	//
	////Return: no item used
	//if (choose == 4) return;
	//else items_useitem(chamber, ptr, turn, health, IsCuffed, dmg, choose-1, 0);


	////Update used item
	//items[turn][choose - 1] = -1;	

	////Program to wait for keypress
	//printf("Press enter to continue\n");
	//(void)getch();
	return;
}