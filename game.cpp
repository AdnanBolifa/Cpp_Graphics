#include <iostream>
#include <graphics.h>
#include <ctime>
#include <Windows.h>
#include <cstdio> // Include the <cstdio> header for sprintf

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPACESHIP_SIZE = 50;
const int BULLET_SIZE = 5;
const int ASTEROID_SIZE = 40;
const int SPEED = 5;
const int DELAY_MS = 50;
const int MAX_ASTEROIDS = 10;
const int MAX_POWER_UPS = 1;

struct Point {
    int x, y;
};

enum PowerUpType {
    SHIELD,
    RAPID_FIRE,
    INVINCIBILITY
};

struct PowerUp {
    Point position;
    PowerUpType type;
    bool active;
};

enum AsteroidType {
    SMALL,
    MEDIUM,
    LARGE
};

struct Asteroid {
    Point position;
    AsteroidType type;
    int speed;
    bool active;
};

class SpaceShooterGame {
private:
    Point spaceship;
    Point bullets[MAX_ASTEROIDS];
    Asteroid asteroids[MAX_ASTEROIDS];
    PowerUp powerUps[MAX_POWER_UPS];
    int score;
    int spaceshipColor;
    int spaceshipShape;
    int asteroidTimer;
    int powerUpTimer;

    void SetSpaceshipColor(int color) {
        spaceshipColor = color;
    }

    void SetSpaceshipShape(int shape) {
        spaceshipShape = shape;
    }

    void DrawSpaceship() {
        setcolor(spaceshipColor);
        setfillstyle(SOLID_FILL, spaceshipColor);
        if (spaceshipShape == 1) { // Triangle
            int spaceshipPoints[] = {spaceship.x, spaceship.y + SPACESHIP_SIZE,
                                     spaceship.x + SPACESHIP_SIZE / 2, spaceship.y,
                                     spaceship.x + SPACESHIP_SIZE, spaceship.y + SPACESHIP_SIZE};
            fillpoly(3, spaceshipPoints);
        } else if (spaceshipShape == 2) { // Rectangle
            rectangle(spaceship.x, spaceship.y, spaceship.x + SPACESHIP_SIZE, spaceship.y + SPACESHIP_SIZE);
            floodfill(spaceship.x + SPACESHIP_SIZE / 2, spaceship.y + SPACESHIP_SIZE / 2, spaceshipColor);
        }
    }

    void DrawBullets() {
        setcolor(GREEN);
        for (int i = 0; i < MAX_ASTEROIDS; ++i)
            rectangle(bullets[i].x, bullets[i].y, bullets[i].x + BULLET_SIZE, bullets[i].y + BULLET_SIZE);
    }

    void DrawAsteroids() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (asteroids[i].active) {
                switch (asteroids[i].type) {
                    case SMALL:
                        setcolor(RED);
                        setfillstyle(SOLID_FILL, RED);
                        circle(asteroids[i].position.x + ASTEROID_SIZE / 2, asteroids[i].position.y + ASTEROID_SIZE / 2, ASTEROID_SIZE / 2);
                        floodfill(asteroids[i].position.x + ASTEROID_SIZE / 2, asteroids[i].position.y + ASTEROID_SIZE / 2, RED);
                        break;
                    case MEDIUM:
                        // Draw medium asteroid
                        break;
                    case LARGE:
                        // Draw large asteroid
                        break;
                }
            }
        }
    }

    void DrawPowerUps() {
        for (int i = 0; i < MAX_POWER_UPS; ++i) {
            if (powerUps[i].active) {
                switch (powerUps[i].type) {
                    case SHIELD:
                        setcolor(BLUE);
                        setfillstyle(SOLID_FILL, BLUE);
                        circle(powerUps[i].position.x + ASTEROID_SIZE / 2, powerUps[i].position.y + ASTEROID_SIZE / 2, ASTEROID_SIZE / 2);
                        floodfill(powerUps[i].position.x + ASTEROID_SIZE / 2, powerUps[i].position.y + ASTEROID_SIZE / 2, BLUE);
                        break;
                    case RAPID_FIRE:
                        // Draw rapid fire power-up
                        break;
                    case INVINCIBILITY:
                        // Draw invincibility power-up
                        break;
                }
            }
        }
    }

    void MoveBullets() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            bullets[i].y -= SPEED;
            if (bullets[i].y < 0)
                bullets[i].y = -BULLET_SIZE;
        }
    }

    void MoveAsteroids() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (asteroids[i].active) {
                asteroids[i].position.y += asteroids[i].speed;
                if (asteroids[i].position.y > WINDOW_HEIGHT) {
                    // Deactivate asteroid if it goes out of screen
                    asteroids[i].active = false;
                }
            }
        }
    }

    void GenerateAsteroid() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (!asteroids[i].active) {
                asteroids[i].position.x = rand() % (WINDOW_WIDTH - ASTEROID_SIZE);
                asteroids[i].position.y = -ASTEROID_SIZE;
                asteroids[i].type = static_cast<AsteroidType>(rand() % 3); // Randomly choose an asteroid type
                asteroids[i].speed = rand() % 3 + 1; // Random speed between 1 and 3
                asteroids[i].active = true;
                break;
            }
        }
    }

    void GeneratePowerUp() {
        for (int i = 0; i < MAX_POWER_UPS; ++i) {
            if (!powerUps[i].active) {
                int randomX;
                do {
                    randomX = rand() % (WINDOW_WIDTH - ASTEROID_SIZE);
                } while (abs(randomX - spaceship.x) < ASTEROID_SIZE); // Ensure power-up is not spawned near player's spaceship
                powerUps[i].position.x = randomX;
                powerUps[i].position.y = spaceship.y; // Align power-up Y position with spaceship Y position
                powerUps[i].type = static_cast<PowerUpType>(rand() % 3); // Randomly choose a power-up type
                powerUps[i].active = true;
                break;
            }
        }
    }




    void CheckPowerUpCollision() {
        for (int i = 0; i < MAX_POWER_UPS; ++i) {
            if (powerUps[i].active && (spaceship.x + SPACESHIP_SIZE >= powerUps[i].position.x) &&
                (spaceship.x <= powerUps[i].position.x + ASTEROID_SIZE) &&
                (spaceship.y + SPACESHIP_SIZE >= powerUps[i].position.y) &&
                (spaceship.y <= powerUps[i].position.y + ASTEROID_SIZE)) {
                // Apply power-up effect
                ApplyPowerUpEffect(powerUps[i].type);
                // Deactivate the power-up
                powerUps[i].active = false;
                break;
            }
        }
    }

    void ApplyPowerUpEffect(PowerUpType type) {
        switch (type) {
            case SHIELD:
                // Implement shield power-up effect
                break;
            case RAPID_FIRE:
                // Implement rapid fire power-up effect
                break;
            case INVINCIBILITY:
                // Implement invincibility power-up effect
                break;
        }
    }

    bool CollisionDetection() {
    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        if (!asteroids[i].active) continue; // Skip inactive asteroids

        // Check collision between spaceship and asteroid
        if ((spaceship.x + SPACESHIP_SIZE >= asteroids[i].position.x) &&
            (spaceship.x <= asteroids[i].position.x + ASTEROID_SIZE) &&
            (spaceship.y + SPACESHIP_SIZE >= asteroids[i].position.y) &&
            (spaceship.y <= asteroids[i].position.y + ASTEROID_SIZE))
            return true;

        // Check collision between bullets and asteroids
        for (int j = 0; j < MAX_ASTEROIDS; ++j) {
            if (i == j || !asteroids[j].active) continue; // Skip self-collision and inactive asteroids
            if ((bullets[i].y < 0)) continue; // Skip inactive bullets

            if ((bullets[i].x + BULLET_SIZE >= asteroids[j].position.x) &&
                (bullets[i].x <= asteroids[j].position.x + ASTEROID_SIZE) &&
                (bullets[i].y <= asteroids[j].position.y + ASTEROID_SIZE) &&
                (bullets[i].y + BULLET_SIZE >= asteroids[j].position.y)) {
                bullets[i].y = -BULLET_SIZE;
                asteroids[j].active = false;
                return false;
            }
        }
    }
    return false;
}


public:
    SpaceShooterGame() {
        initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Shooter Game");
        score = 0;
        spaceshipColor = WHITE; // Default color
        spaceshipShape = 1; // Default shape (Triangle)
        asteroidTimer = 0;
        powerUpTimer = 0;

        spaceship.x = (WINDOW_WIDTH - SPACESHIP_SIZE) / 2;
        spaceship.y = WINDOW_HEIGHT - SPACESHIP_SIZE - 20;

        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            bullets[i].x = spaceship.x + (SPACESHIP_SIZE - BULLET_SIZE) / 2;
            bullets[i].y = -BULLET_SIZE;
            asteroids[i].active = false;
            powerUps[i].active = false;
        }
    }

    void gameOver() {
        outtextxy(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2, (char*)"Game Over!");
        outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20, (char*)"Press R to restart");
        char key = getch();
        if (key == 'r' || key == 'R') {
            ResetGame();
            return;
        }
        getch();
        closegraph();
        exit(0);
    }

    void ResetGame() {
        score = 0;
        spaceship.x = (WINDOW_WIDTH - SPACESHIP_SIZE) / 2;
        spaceship.y = WINDOW_HEIGHT - SPACESHIP_SIZE - 20;

        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            bullets[i].x = spaceship.x + (SPACESHIP_SIZE - BULLET_SIZE) / 2;
            bullets[i].y = -BULLET_SIZE;
            asteroids[i].active = false;
            powerUps[i].active = false;
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
                gameOver();
            }
            CheckPowerUpCollision();
            GenerateAsteroid();
            GeneratePowerUp();
            Sleep(DELAY_MS);
        }
    }

    void Draw() {
        cleardevice();
        DrawSpaceship();
        DrawBullets();
        DrawAsteroids();
        DrawPowerUps();
        char scoreStr[20];
        sprintf(scoreStr, "Score: %d", score);
        outtextxy(10, 10, scoreStr);
    }

    void Input() {
        char key = getch();
        if (key == 'a' && spaceship.x > 0)
            spaceship.x -= 20;
        else if (key == 'd' && spaceship.x < WINDOW_WIDTH - SPACESHIP_SIZE)
            spaceship.x += 20;
        else if (key == ' ')
            FireBullet();
    }

    void FireBullet() {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (bullets[i].y < 0) {
                bullets[i].x = spaceship.x + (SPACESHIP_SIZE - BULLET_SIZE) / 2;
                bullets[i].y = spaceship.y - BULLET_SIZE;
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
