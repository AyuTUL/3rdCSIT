#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;

void drawEllipse(int xc, int yc, int rx, int ry)
{
    int x = 0, y = ry; // Starting point on the ellipse
    int rx2 = rx * rx, ry2 = ry * ry; // Square of semi-major axis
    int tworx2 = 2 * rx2, twory2 = 2 * ry2; // Square of semi-minor axis

    // Decision parameter for region 1
    int p1 = ry2 - (rx2 * ry) + (0.25f * rx2);
    int dx = 0;
    int dy = tworx2; // Change in y

    // Region 1
    while (dx < dy)
    {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        x++;
        dx += twory2;
        if (p1 < 0)
            p1 += ry2 + dx;
        else
        {
            y--;
            dy -= tworx2;
            p1 += ry2 + dx - dy;
        }
    }

    // Decision parameter for region 2
    int p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

    // Region 2
    while (y >= 0)
    {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        y--;
        dy -= tworx2;
        if (p2 > 0)
            p2 += rx2 - dy;
        else
        {
            x++;
            dx += twory2;
            p2 += rx2 - dy + dx;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Initialize graphics mode
    int xc, yc, rx, ry;
    
    // Taking user input
    cout << "Enter the centre of ellipse (xc, yc): ";
    cin >> xc >> yc;
    cout << "Enter the semi-major axis (rx): ";
    cin >> rx;
    cout << "Enter the semi-minor axis (ry): ";
    cin >> ry;

    // Drawing ellipse
    drawEllipse(xc, yc, rx, ry);

    getch(); // Wait for user input before closing the window
    closegraph(); // Close graphics mode

    return 0;
}
