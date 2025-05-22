#include <GLFW/glfw3.h>
#include <GL/gl.h>         // Include the OpenGL header
#include <iostream>

// Vertex data for a triangle (3 vertices, 3 floats each)
float vertices[] = {
   -0.1f, 0.6f, 0.0f,    // Top vertex moved left and up
   -0.6f, -0.4f, 0.0f,   // Bottom-left vertex moved left and up
    0.4f, -0.4f, 0.0f    // Bottom-right vertex moved left and up
};


// Callback function to resize the viewport when the window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the initial viewport
    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen with a dark teal background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle in purple color
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 1.0f); // Purple (R=1, G=0, B=1)
        glVertex3f(vertices[0], vertices[1], vertices[2]);
        glVertex3f(vertices[3], vertices[4], vertices[5]);
        glVertex3f(vertices[6], vertices[7], vertices[8]);
        glEnd();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
