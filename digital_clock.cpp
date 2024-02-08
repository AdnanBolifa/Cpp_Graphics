#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clock(int, int, int);

int main()
{
    int h, m, s;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");

    while (!kbhit())
    {
        // getting time in variables
        time_t now = time(NULL);
        struct tm *now_tm;
        now_tm = localtime(&now);
        h = now_tm->tm_hour;
        m = now_tm->tm_min;
        s = now_tm->tm_sec;

        // function calling
        clock(h, m, s);

        delay(1000);
        cleardevice();
    }
    closegraph();
    return 0;
}

void clock(int h, int m, int s)
{
    char buffer[9];
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    // Define box coordinates
    int boxLeft = 150;
    int boxTop = 150;
    int boxRight = 350;
    int boxBottom = 250;

    // Calculate the center of the box
    int boxWidth = boxRight - boxLeft;
    int boxHeight = boxBottom - boxTop;
    int centerX = boxLeft + boxWidth / 2;
    int centerY = boxTop + boxHeight / 2;

    // Display digital clock inside a box
    setcolor(WHITE);
    rectangle(boxLeft, boxTop, boxRight, boxBottom);

    sprintf(buffer, "%02d:%02d:%02d", h, m, s);

    // Calculate the position to center the text
    int textWidth = textwidth(buffer);
    int textHeight = textheight(buffer);
    int textX = centerX - textWidth / 2;
    int textY = centerY - textHeight / 2;

    outtextxy(textX, textY, buffer);
}
