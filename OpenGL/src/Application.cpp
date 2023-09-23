#include <GL/glew.h>    //finds the drivers and gets us access to OpenGL functions accordingly
#include <GLFW/glfw3.h> //used to open windows in a partciular os (used for cross platform compatibility)
#include <iostream>
#include <fstream>
#include <sstream>

static std::string GetShader(const std::string& filepath) {
       
    std::ifstream stream(filepath);
    std::string shaderCode;

    if (stream) {
        std::ostringstream ss;
        ss << stream.rdbuf();
        shaderCode = ss.str();
    }
    
    std::cout << shaderCode;
    return shaderCode;
}

static unsigned int CompileShader(unsigned int type, const std::string& source){   

    //creates empty shader object
    unsigned int id = glCreateShader(type);
    //pointer to the first byte of the source code
    const char* src = source.c_str();
    //places the source code in the given shader object
    glShaderSource(id, 1, &src, nullptr);
    //compiles the given shader
    glCompileShader(id);

    int result;
    //gets the given param value and adds it to the given result 
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    //error handling in case the compilation fails
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;

    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    
    //creates a program object and compiles the given shaders
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //linkes the shaders to the proogram
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //deletes the shader as they have been attached to the object
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void){
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

    //source code for vs and fs shaders
    //std::string vs = "#version 330 core\n"
    //    "layout(location = 0) in vec4 position;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   gl_Position = position;\n"
    //    "};";
    //
    //std::string fs = "#version 330 core\n"
    //    "layout (location = 0) out vec4 color;\n"
    //    "void main()\n"
    //    "{\n"
    //    "    color = vec4(1, 0, 0, 1);\n"
    //    "};";

    std::string vs = GetShader("res/shaders/vs/basic.shader");
    std::string fs = GetShader("res/shaders/fs/basic.shader");
    std::cout << "#SHADER CODE\n" << vs << "#FRAGMENT CODE\n" << fs;

    unsigned int shader = CreateShader(vs, fs);
    glUseProgram(shader);

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