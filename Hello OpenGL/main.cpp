//
//  main.cpp
//  Hello OpenGL
//
//  Created by Manuel Rodriguez Urdapilleta on 31/01/24.
//

#include <stdio.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

int main(void)
{
    //Inicialización de GLFW
    if (!glfwInit())
    {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return -1;
    }
    
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //CREAR VENTANA
    GLFWwindow* mainWindow;
    mainWindow = glfwCreateWindow(800, 600, "Primer ventana", NULL, NULL);

    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }
    //Obtener tamaño de Buffer
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    //asignar el contexto
    glfwMakeContextCurrent(mainWindow);

    //permitir nuevas extensiones
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Asignar valores de la ventana y coordenadas
    //Asignar Viewport
    glViewport(0, 0, BufferWidth, BufferHeight);
    printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
    printf("Marca: %s \n", glGetString(GL_VENDOR));
    printf("Renderer: %s \n", glGetString(GL_RENDERER));
    printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    //Loop mientras no se cierra la ventana
    while (!glfwWindowShouldClose(mainWindow))
    {
        //Recibir eventos del usuario
        glfwPollEvents();

        //Limpiar la ventana
        glClearColor(0.0f,1.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);

    }


    return 0;
}
