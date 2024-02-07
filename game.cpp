#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <windows.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPACESHIP_WIDTH = 50;
const int SPACESHIP_HEIGHT = 50;
const int BULLET_WIDTH = 5;
const int BULLET_HEIGHT = 15;
const int ASTEROID_WIDTH = 40;
const int ASTEROID_HEIGHT = 40;
const int SPEED = 5;
const int DELAY_MS = 50;
const int MAX_ASTEROIDS = 5;

struct Point {
    int x, y;
};

class SpaceShooterGame {
private:
    Point spaceship;
    Point bullets[MAX_ASTEROIDS];
    Point asteroids[MAX_ASTEROIDS];
    int score;

    void DrawSpaceship() {
        setfillstyle(SOLID_FILL, YELLOW);
        bar(spaceship.x, spaceship.y, spaceship.x + SPACESHIP_WIDTH, spaceship.y + SPACESHIP_HEIGHT);
    }

    void DrawBullets() {
        setfillstyle(SOLID_FILL, GREEN);
        for (int i = 0; i < MAX_ASTEROIDS; ++i)
            bar(bullets[i].x, bullets[i].y, bullets[i].x + BULLET_WIDTH, bullets[i].y + BULLET_HEIGHT);
    }

    void DrawAsteroids() {
        setfillstyle(SOLID_FILL, RED);
        for (int i = 0; i < MAX_ASTEROIDS; ++i)
            bar(asteroids[i].x, asteroids[i].y, asteroids[i].x + ASTEROID_WIDTH, asteroids[i].y + ASTEROID_HEIGHT);
    }

    void MoveBullets() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            bullets[i].y -= SPEED;
            if (bullets[i].y < 0)
                bullets[i].y = -BULLET_HEIGHT;
        }
    }

    void MoveAsteroids() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            asteroids[i].y += SPEED;
            if (asteroids[i].y > WINDOW_HEIGHT) {
                asteroids[i].y = 0;
                asteroids[i].x = rand() % (WINDOW_WIDTH - ASTEROID_WIDTH);
                score++;
            }
        }
    }

    bool CollisionDetection() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            // Check collision between spaceship and asteroid
            if ((spaceship.x + SPACESHIP_WIDTH >= asteroids[i].x) &&
                (spaceship.x <= asteroids[i].x + ASTEROID_WIDTH) &&
                (spaceship.y + SPACESHIP_HEIGHT >= asteroids[i].y) &&
                (spaceship.y <= asteroids[i].y + ASTEROID_HEIGHT))
                return true;

            // Check collision between bullets and asteroids
            for (int j = 0; j < MAX_ASTEROIDS; ++j) {
                if ((bullets[i].x + BULLET_WIDTH >= asteroids[j].x) &&
                    (bullets[i].x <= asteroids[j].x + ASTEROID_WIDTH) &&
                    (bullets[i].y <= asteroids[j].y + ASTEROID_HEIGHT) &&
                    (bullets[i].y + BULLET_HEIGHT >= asteroids[j].y)) {
                    bullets[i].y = -BULLET_HEIGHT;
                    asteroids[j].y = 0;
                    asteroids[j].x = rand() % (WINDOW_WIDTH - ASTEROID_WIDTH);
                    return false;
                }
            }
        }
        return false;
    }

public:
    SpaceShooterGame() {
        initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Shooter Game");
        spaceship.x = (WINDOW_WIDTH - SPACESHIP_WIDTH) / 2;
        spaceship.y = WINDOW_HEIGHT - SPACESHIP_HEIGHT - 20;
        score = 0;

        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            bullets[i].x = spaceship.x + (SPACESHIP_WIDTH - BULLET_WIDTH) / 2;
            bullets[i].y = -BULLET_HEIGHT;
            asteroids[i].x = rand() % (WINDOW_WIDTH - ASTEROID_WIDTH);
            asteroids[i].y = rand() % (WINDOW_HEIGHT / 2);
        }
    }

    void Run() {
        while (true) {
            Draw();
            if (kbhit())
                Input();
            MoveBullets();
            MoveAsteroids();
            if (CollisionDetection()) {
                outtextxy(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2, "Game Over!");
                getch();
                closegraph();
                exit(0);
            }
            Sleep(DELAY_MS);
        }
    }

    void Draw() {
        cleardevice();
        DrawSpaceship();
        DrawBullets();
        DrawAsteroids();
        outtextxy(10, 10, ("Score: "));
    }

    void Input() {
        char key = getch();
        if (key == 'a' && spaceship.x > 0)
            spaceship.x -= 20;
        else if (key == 'd' && spaceship.x < WINDOW_WIDTH - SPACESHIP_WIDTH)
            spaceship.x += 20;
        else if (key == ' ')
            FireBullet();
    }

    void FireBullet() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (bullets[i].y < 0) {
                bullets[i].x = spaceship.x + (SPACESHIP_WIDTH - BULLET_WIDTH) / 2;
                bullets[i].y = spaceship.y - BULLET_HEIGHT;
                break;
            }
        }
    }
};

int main() {
    srand(time(NULL));
    SpaceShooterGame game;
    game.Run();
    return 0;
}
