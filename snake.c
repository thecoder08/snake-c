#include <xgfx/window.h>
#include <xgfx/drawing.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Body;

Body snake[2500];
int length = 4;

void drawSnake() {
    for (int i = 0; i < length; i++) {
        rectangle(snake[i].x * 10, snake[i].y * 10, 10, 10, 0x0000ff00);
    }
}

void moveSnake(Body direction) {
    for (int i = length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0].x += direction.x;
    snake[0].y += direction.y;
    if (snake[0].x == 50) {
        snake[0].x = 0;
    }
    if (snake[0].x == -1) {
        snake[0].x = 49;
    }
    if (snake[0].y == 50) {
        snake[0].y = 0;
    }
    if (snake[0].y == -1) {
        snake[0].y = 49;
    }
}

int snakeTouchingItself() {
    for (int i = 1; i < length; i++) {
        if ((snake[i].x == snake[0].x) && (snake[i].y == snake[0].y)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    snake[0].x = 0; snake[0].y = 0;
    snake[1].x = 1; snake[1].y = 0;
    snake[2].x = 2; snake[2].y = 0;
    snake[3].x = 3; snake[3].y = 0;
    Body direction;
    direction.x = 0;
    direction.y = 1;
    Body apple;
    apple.x = rand() % 50;
    apple.y = rand() % 50;
    initWindow(500, 500, "Snake");
    while(1) {
        Event event;
        while (checkWindowEvent(&event)) {
            if (event.type == WINDOW_CLOSE) {
                return 0;
            }
            if (event.type == KEY_CHANGE) {
                if (event.keychange.state == 1) {
                if (event.keychange.key == 103) {
                    direction.y = -1;
                    direction.x = 0;
                }
                if (event.keychange.key == 108) {
                    direction.y = 1;
                    direction.x = 0;
                }
                if (event.keychange.key == 105) {
                    direction.y = 0;
                    direction.x = -1;
                }
                if (event.keychange.key == 106) {
                    direction.y = 0;
                    direction.x = 1;
                }
                }
            }
        }
        if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
            snake[length].x = snake[length - 1].x - direction.x;
            snake[length].y = snake[length - 1].y - direction.y;
            length++;
            apple.x = rand() % 50;
            apple.y = rand() % 50;
        }
        if (snakeTouchingItself()) {
            printf("You died! Score: %d\n", length);
            return 0;
        }
        moveSnake(direction);
        rectangle(0, 0, 500, 500, 0x00ffffff);
        rectangle(apple.x * 10, apple.y * 10, 10, 10, 0x00ff0000);
        drawSnake();
        updateWindow();
        usleep(100000);
    }
}
