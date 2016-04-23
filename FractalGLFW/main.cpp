//
//  main.cpp
//  FractalGLFW
//
//  Created by Владислав Афанасьев on 21/04/16.
//  Copyright © 2016 Владислав Афанасьев. All rights reserved.
//


#include "main.h"

GLfloat Width = 400, Height = 400;

float points[] = {
    -Width/2,  -Height/2,  0.0f,
    -Width/2,  Height/2,  0.0f,
    Width/2,  Height/2,  0.0f,
    Width/2,  -Height/2, 0.0f
};

void Reshape(GLFWwindow* window, int w, int h)
{
    Width = w;
    Height = h;
    
    glViewport(0, 0, Width, Height);
    
    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2, -Height/2, Height/2, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit ();
    
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    glViewport(0, 0, Width, Height);
    
    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2, -Height/2, Height/2, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glfwSetFramebufferSizeCallback(window, Reshape);
    /////////////////////////////////////////////////
    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (float), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
     ////////////////////////////////////////////////
    //////////////////SHADER////////////////////////
    ////////////////////////////////////////////////
    const char* vertex_shader = LoadShader("fractal_vs.glsl");
    const char* fragment_shader = LoadShader("red_fs.glsl");
    
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, NULL);
    glCompileShader (vs);
    
    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, NULL);
    glCompileShader (fs);
    
    GLuint shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, vs);
    glAttachShader (shader_programme, fs);
    glLinkProgram (shader_programme);
    
    ////////////////////////////////////////////////
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (shader_programme);
        glBindVertexArray (vao);
        glDrawArrays (GL_POLYGON, 0, 4);
        glfwPollEvents ();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers (window);
    }
    
    glfwTerminate();
    return 0;
}

const char* LoadShader(std::string filename)
{
    std::string output = "";
    std::string line;
    std::ifstream shader;
    shader.open(filename, std::ios::in);
    if (shader.is_open())
    {
        while(getline(shader, line))
        {
            output += line;
        }
        shader.close();
        const char* coutput = output.c_str();
        return coutput;
    }
    return NULL;
}

