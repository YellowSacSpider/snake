#include <iostream>
#include <ctime>
#include "windows.h"
#include "conio.h"

const int matrix_size = 16;
int direction = 0; // 0 - default, 1 - top, 2 - down, 3 - left, 4 - right
int ax = 20;
int ay = 5;
bool snakeAlive = true;
int matrix[matrix_size][matrix_size*2] = { 0 };
int trail = 4;
int snake[256][4] = {
	5,5,5,5, // x,y,oldx,oldy
	5,6,5,6,
	5,7,5,7,
	5,8,5,8
};


void fillMatrix() {
	for (int i = 0; i < matrix_size; i++) {
			matrix[i][0] = -1;
			matrix[i][matrix_size * 2 - 1] = -1;
		}
		for(int j = 0; j < matrix_size * 2; j++) {
			matrix[0][j] = -1;
			matrix[matrix_size-1][j] = -1;
		}

		for (int i = 0; i < trail; i++) {
			matrix[snake[i][1]][snake[i][0]] = 1;
		}

		matrix[ay][ax] = 2;
}

void draw(){
	for(int i = 0; i < matrix_size; i++) {
		for(int j = 0; j < matrix_size*2; j++) {
			if (matrix[i][j] == 0) {
				std::cout << ' ';
			}
			else if (matrix[i][j] == -1) {
				std::cout << '#';
			}
			else if (matrix[i][j] == 1) {
				std::cout << 'O';
			}
			else if (matrix[i][j] == 2) {
				std::cout << 'A';
			}

		}
		std::cout << '\n';
	}
	std::cout << ax << " | " << ay << '\n';
	std::cout << snake[0][0] << " | " << snake[0][1] << '\n';
}


int main()
{
	srand(time(NULL));
	fillMatrix();
	while (snakeAlive) {
		for (int i = 0; i < trail; i++) {
			snake[i][2] = snake[i][0]; // move value from x to oldx
			snake[i][3] = snake[i][1]; // move value from y to oldy
		}

		// Head collision with body
		for (int i = 1; i < trail; i++) {
			if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
				draw();
				Sleep(1000);
				system("cls");
				std::cout << "GAME OVER";
				snakeAlive = false;
				Sleep(2000);
				break;
			}
		}

		// Collisions with walls
		if (snake[0][1] >= matrix_size-1 || snake[0][1] <= 0) {
			matrix[snake[0][1]][snake[0][0]] = -1;
			draw();
			Sleep(1000);
			system("cls");
			std::cout << "GAME OVER";
			snakeAlive = false;
			Sleep(2000);
			break;
		}
		else if (snake[0][0] >= matrix_size * 2 - 1 || snake[0][0] <= 0) {
			matrix[snake[0][1]][snake[0][0]] = -1;
			draw();
			Sleep(1000);
			system("cls");
			std::cout << "GAME OVER";
			snakeAlive = false;
			Sleep(2000);
			break;
		}

		//Apple collision
		if (snake[0][0] == ax && snake[0][1] == ay) {
			int temprandx = 0;
			int temprandy = 0;
			bool inSnakeBody = false;

			trail++;
			snake[trail][0] = snake[trail - 1][2];
			snake[trail][1] = snake[trail - 1][3];
			temprandx = std::abs(rand() % (matrix_size * 2) - 2) + 1;
			temprandy = std::abs(rand() % (matrix_size)-2) + 1;
			// Check generated apple position. If is in snake body set inSnakeBody = true
			for (int i = 0; i < trail; i++) {
				if (temprandx == snake[i][0] && temprandy == snake[i][1]) {
					inSnakeBody = true;
					break;
				}
				// Generate new coordinates until apple is not in snake body
				while (inSnakeBody) {
					for (int i = 0; i < trail; i++) {
						if (temprandx == snake[i][0] && temprandy == snake[i][1]) {
							temprandx = std::abs(rand() % (matrix_size * 2) - 2) + 1;
							temprandy = std::abs(rand() % (matrix_size) - 2) + 1;
							inSnakeBody = true;
							break;
						}
						else {
							inSnakeBody = false;
						}
					}
				}
				ax = temprandx;
				ay = temprandy;
				matrix[ay][ax] = 2;

			}
		}
		if (_kbhit()){
			int ch = _getch();
			Sleep(100);
			if (ch == 119 && direction != 2) {
				direction = 1; // top
			}
			else if (ch == 115 && direction != 1) {
				direction = 2; // down
			}
			else if (ch == 97 && direction != 4) {
				direction = 3; // left
			}
			else if (ch == 100 && direction != 3) {
				direction = 4; // right
			}
		}
		switch (direction) {
			case 0:
			break;
			case 1:
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 0;
				}
				snake[0][1]--;
				for (int i = 0; i < trail; i++) {
					snake[i + 1][0] = snake[i][2];
					snake[i + 1][1] = snake[i][3];
				}
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 1;
				}
			break;
			case 2:
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 0;
				}
				snake[0][1]++;
				for (int i = 0; i < trail; i++) {
					snake[i + 1][0] = snake[i][2];
					snake[i + 1][1] = snake[i][3];
				}
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 1;
				}
			break;
			case 3:
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 0;
				}
				snake[0][0]--;
				for (int i = 0; i < trail; i++) {
					snake[i + 1][0] = snake[i][2];
					snake[i + 1][1] = snake[i][3];
				}
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 1;
				}
			break;
			case 4:
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 0;
				}
				snake[0][0]++;
				for (int i = 0; i < trail; i++) {
					snake[i + 1][0] = snake[i][2];
					snake[i + 1][1] = snake[i][3];
				}
				for (int i = 0; i < trail; i++) {
					matrix[snake[i][1]][snake[i][0]] = 1;
				}
			break;
		}
		draw();
		Sleep(10);
		system("cls");
	}
}

