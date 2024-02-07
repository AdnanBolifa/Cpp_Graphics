#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clock(int, int, int);
void alarm(int, int, int);
void clockshape();

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

        // functions calling
        clockshape();
        clock(h, m, s);

        delay(1000);
        cleardevice();
    }
    closegraph();
    return 0;
}

void clockshape()
{
    int points[18] = {100, 250, 200, 200, 350, 200, 450, 250, 450, 350, 350, 400, 200, 400, 100, 350, 100, 250};

    // clock shape
    rectangle(150, 250, 400, 350);
    drawpoly(9, points);
    line(233, 250, 233, 350);
    line(320, 250, 320, 350);
    settextstyle(1, HORIZ_DIR, 3);
    outtextxy(160, 251, "hours");
    outtextxy(238, 251, "min.");
    outtextxy(330, 251, "sec.");
    setfillstyle(XHATCH_FILL, RED);
    floodfill(130, 300, WHITE);
}

void clock(int h, int m, int s)
{
    char buffer[3];
    settextstyle(5, HORIZ_DIR, 5);

    sprintf(buffer, "%d", h);
    outtextxy(160, 270, buffer);

    sprintf(buffer, "%d", m);
    outtextxy(250, 270, buffer);

    sprintf(buffer, "%d", s);
    outtextxy(325, 270, buffer);

    rectangle(150, 250, 150, 270);
}
