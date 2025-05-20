#include <iostream>
#include <graphics.h>  // Include graphics.h for graphics operations

using namespace std;

void drawEllipse(int h, int k, int a, int b) {
    int x = 0, y = b;
    int a2 = a * a, b2 = b * b;
    int twob2 = 2 * b2, twoda2 = 2 * a2;
    int d1 = b2 - a2 * b + a2 / 4;  // Initial decision parameter for region 1

    // Region 1 (the upper half of the ellipse)
    while (twob2 * x <= twoda2 * y) {
        // Plot points in all four quadrants
        putpixel(h + x, k + y, WHITE); // (x, y)
        putpixel(h - x, k + y, WHITE); // (-x, y)
        putpixel(h + x, k - y, WHITE); // (x, -y)
        putpixel(h - x, k - y, WHITE); // (-x, -y)

        // Check the decision parameter and update it
        if (d1 < 0) {
            d1 += twob2 * x + b2;
        } else {
            d1 += twob2 * x - twoda2 * y + b2;
            y--;
        }
        x++;
    }

    // Region 2 (the lower half of the ellipse)
    int d2 = b2 * (x + 1) * (x + 1) + a2 * (y - 1) * (y - 1) - a2 * b2; // Initial decision parameter for region 2

    while (y >= 0) {
        // Plot points in all four quadrants
        putpixel(h + x, k + y, WHITE); // (x, y)
        putpixel(h - x, k + y, WHITE); // (-x, y)
        putpixel(h + x, k - y, WHITE); // (x, -y)
        putpixel(h - x, k - y, WHITE); // (-x, -y)

        // Check the decision parameter and update it
        if (d2 > 0) {
            d2 -= twoda2 * y + a2;
        } else {
            d2 += twob2 * x - twoda2 * y + a2;
            x++;
        }
        y--;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");  // Initialize graphics mode

    int h = 320, k = 240, a = 150, b = 100;  // Center (320, 240), semi-major axis = 150, semi-minor axis = 100

    drawEllipse(h, k, a, b);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics window
    return 0;
}
