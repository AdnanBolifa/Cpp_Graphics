#include <graphics.h>
#include <conio.h>
#include <dos.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    int x = 100, y = 100;
    int radius = 20;
    int xSpeed = 5;
    int ySpeed = 5;

    while (!kbhit()) {//keyboard hit
        // draw background
        cleardevice();

        // draw ball
        setcolor(GREEN);
        circle(x, y, radius);
        floodfill(x, y, GREEN);

        // update ball position
        x += xSpeed;
        y += ySpeed;

        delay(50);
    }

    closegraph();
    return 0;
}
