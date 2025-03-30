#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define WIDTH 50  // Width of the track
#define HEIGHT 20 // Height of the track
#define NITRO_BOOST 2 // Speed boost multiplier

int carX = WIDTH / 2, carY = HEIGHT - 2; // Car's initial position
int speed = 1;  // Initial speed
bool nitro = false; // Nitro boost status
int opponentX[3] = {10, 25, 40}; // Opponent car positions
int opponentY[3] = {5, 8, 12};

// Function to set cursor position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to draw the track and cars
void draw() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) printf("|"); // Track boundaries
            else if (x == carX && y == carY) printf("A"); // Player car
            else {
                bool printed = false;
                for (int i = 0; i < 3; i++) {
                    if (x == opponentX[i] && y == opponentY[i]) {
                        printf("O"); // Opponent car
                        printed = true;
                        break;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }
    printf("Speed: %d | Nitro: %s\n", speed, nitro ? "ON" : "OFF");
}

// Function to update game mechanics
void update() {
    for (int i = 0; i < 3; i++) {
        opponentY[i] += speed;
        if (opponentY[i] >= HEIGHT) opponentY[i] = 0;
    }
}

// Function to detect collisions
bool collision() {
    for (int i = 0; i < 3; i++) {
        if (carX == opponentX[i] && carY == opponentY[i]) return true;
    }
    return false;
}

// Main game loop
void gameLoop() {
    char input;
    while (1) {
        if (kbhit()) {
            input = getch();
            if (input == 'a' && carX > 1) carX--;     // Move left
            if (input == 'd' && carX < WIDTH - 2) carX++; // Move right
            if (input == 'n') nitro = !nitro; // Toggle nitro
        }

        speed = nitro ? NITRO_BOOST : 1;

        update();
        draw();

        if (collision()) {
            gotoxy(0, HEIGHT);
            printf("Game Over!\n");
            break;
        }

        Sleep(100 / speed); // Control game speed
    }
}

int main() {
    gameLoop();
    return 0;
}
