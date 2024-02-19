#include "Window.hpp"

Window::Window()
{
    width = 800;
    height = 600;
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}
int Window::Initialise()
{
    //Inicialización de GLFW
    if (!glfwInit())
    {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return 1;
    }
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //CREAR VENTANA
    mainWindow = glfwCreateWindow(width, height, "Practica 2: Proyecciones, transformaciones", NULL, NULL);

    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }
    //Obtener tamaño de Buffer
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //asignar el contexto
    glfwMakeContextCurrent(mainWindow);

    //MANEJAR TECLADO y MOUSE
    createCallbacks();


    //permitir nuevas extensiones
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
                             // Asignar valores de la ventana y coordenadas
                             
                             //Asignar Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    //Callback para detectar que se está usando la ventana
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, ManejaTeclado);
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
        printf("se presiono la tecla: %s\n",key_name);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
            printf("se presiono la tecla %d'\n", key);
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
            printf("se solto la tecla %d'\n", key);
        }
    }
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();

}
