#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>

void drawPixel(int x, int y) {
    float nx = (x / 320.0f) - 1.0f;  
    float ny = (y / 240.0f) - 1.0f; 
    glBegin(GL_POINTS);
    glVertex2f(nx, ny);
    glEnd();
}
void drawLine(int x1, int y1, int x2, int y2) {
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int error = dx / 2;
    int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;
    for (int x = x1; x <= x2; x++) {
        if (steep)
            drawPixel(y, x);
        else
            drawPixel(x, y);
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "Bresenham's Line Drawing", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 640, 480);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 1.0f); 
        drawLine(100, 400, 500, 100);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}