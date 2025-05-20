#include<iostream>
#include <cmath>
#include <graphics.h>  // Include graphics.h if using a graphics library (e.g., Turbo C++)

using namespace std;

void drawCircle(int h, int k, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;  // Initial decision parameter

    // Draw the 8 symmetrical points
    while (x <= y) {
        // Plot the points in all eight octants
        putpixel(h + x, k + y, WHITE); // (x, y)
        putpixel(h - x, k + y, WHITE); // (-x, y)
        putpixel(h + x, k - y, WHITE); // (x, -y)
        putpixel(h - x, k - y, WHITE); // (-x, -y)
        putpixel(h + y, k + x, WHITE); // (y, x)
        putpixel(h - y, k + x, WHITE); // (-y, x)
        putpixel(h + y, k - x, WHITE); // (y, -x)
        putpixel(h - y, k - x, WHITE); // (-y, -x)

        // Update the decision parameter and coordinates
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm,"");  // Initialize graphics mode

    int h = 320, k = 240, r = 100;  // Center (320, 240) and radius 100

    drawCircle(h, k, r);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics window
    return 0;
}
