#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void hexa ()
{
    line(200, 100, 200, 150);
    line(200, 100, 230, 60);
    line(230, 60, 280, 60);
    line(280, 60, 310, 100);
    line(310, 100, 310, 150);
    line(310, 150, 280, 190);
    line(280, 190, 230, 190);
    line(230, 190, 200, 150);
}

int main(void) 
{
    int gdriver = DETECT, gmode;
    int area;

    printf("Digite a area: ");
    scanf("%d", &area);

    initgraph(&gdriver, &gmode, "");
    hexa();
    /*
    line(200, 50, 200, 150);
    line(300, 200, 400, 300);
    line(300, 200, 200, 300);
    line(200, 300, 300, 400);
    line(300, 400, 400, 300);
    */

    getch();
    closegraph();

    return 0;
}