#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Open GL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }
    else
        std::cout << "WOW IT WORKS, ALSO IT LOOKS COOL TO ADD CONSOLE PRINT STATEMENTS HAHA" << std::endl;
        
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    //positions of the triangle
    float positions[6] = {
        -0.5, -0.5,
        0.0, 0.5,
        0.5, -0.5
    };
    
    //declaration of an unsigned int whose address is used as the buffer id
    unsigned int buffer;

    //generated a buffer, takes argument as the size of the buffer and buffer id
    glGenBuffers(1, &buffer);
    //selects the above buffer and usses it as buffer for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //creates a memory allocation in the GPU for the sleceted buffer 
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    //enables use of vertex attributes from the buffer
    glEnableVertexAttribArray(0);
    //defines the vertext attributes and how should they be interpreted for rendering
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw call for the bound/selected buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}