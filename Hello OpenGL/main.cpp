//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.hpp"
#include"Shader.hpp"
#include"Window.hpp"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shader.vert";
static const char* fShader = "shader.frag";
static const char* vShaderColor = "shadercolor.vert";
static const char* fShaderColor = "shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
    unsigned int indices[] = {
        0,1,2,
        1,3,4,
        1,2,4,
        3,0,4,
        1,0,3,
        0,2,4
        
    };
    GLfloat vertices[] = {
        0.0f,0.5f, -0.25f, //0
        0.5f,-0.5f,0.5f,    //1
        -0.5f,-0.5f,0.5f,    //2
        0.5f,-0.5f, -0.5f,    //3
        -0.5f,-0.5f,-0.5f,    //4

    };
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 18, 18);
    meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
    unsigned int cubo_indices[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
    };

GLfloat cubo_vertices[] = {
    // front
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // back
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
    GLfloat vertices_letras[] = {
            //X            Y            Z            R        G        B
            -1.0f,    -1.0f,       0.5f,            0.0f,    0.0f,    1.0f,
            -0.5f,    -1.0f,       0.5f,            0.0f,    0.0f,    1.0f,
            -0.5f,    0.7f,        0.5f,            0.0f,    0.0f,    1.0f,
            -0.3f,    0.5f,        0.5f,            0.0f,    0.0f,    1.0f,
            0.3f,     0.5f,        0.5f,            0.0f,    0.0f,    1.0f,
            0.5f,     0.7f,        0.5f,            0.0f,    0.0f,    1.0f,
            0.5f,    -1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
            1.0f,    -1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
            1.0f,     1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
            0.3f,     1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
            0.0f,     0.7f,        0.5f,            0.0f,    0.0f,    1.0f,
           -0.3f,     1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
           -1.0f,     1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
            
    };
    MeshColor *letras = new MeshColor();
    letras->CreateMeshColor(vertices_letras,78);
    meshColorList.push_back(letras);

    // Letra M
    GLfloat vertices_M[] = {
        // X       Y       Z       R     G     B
        -0.9f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Punto inferior izquierdo
        -0.9f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Pico superior izquierdo
        -0.5f,  0.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Valle medio
        -0.1f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Pico superior derecho
        -0.1f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f  // Punto inferior derecho
    };
    
    MeshColor *letra_M = new MeshColor();
    letras->CreateMeshColor(vertices_M,30);
    meshColorList.push_back(letra_M);

    // Letra R
    GLfloat vertices_R[] = {
        // X       Y       Z       R     G     B
        -0.5f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Punto inferior izquierdo
        -0.5f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Pico superior izquierdo
         0.0f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Parte superior derecha de la curva
         0.0f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Parte inferior derecha de la curva
        -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Punto de conexión de la pierna
         0.2f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f  // Final de la pierna derecha
    };
    
    MeshColor *letra_R = new MeshColor();
    letras->CreateMeshColor(vertices_R,36);
    meshColorList.push_back(letra_R);
    
    // Letra U
    GLfloat vertices_U[] = {
        // X       Y       Z       R     G     B
        0.1f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // Punto superior izquierdo
        0.1f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // Punto inferior izquierdo
        0.4f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // Punto inferior derecho
        0.4f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f   // Punto superior derecho
    };
    
    MeshColor *letra_U = new MeshColor();
    letras->CreateMeshColor(vertices_U,24);
    meshColorList.push_back(letra_U);
    
    GLfloat vertices_triangulorojo[] = {
        //X            Y            Z            R        G        B
        -1.0f,    -1.0f,        0.5f,            1.0f,    0.0f,    0.0f,
        1.0f,    -1.0f,        0.5f,            1.0f,    0.0f,    0.0f,
        0.0f,    1.0f,        0.5f,            1.0f,    0.0f,    0.0f,
        
    };
    

    MeshColor* triangulorojo = new MeshColor();
    triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
    meshColorList.push_back(triangulorojo);
    
    GLfloat vertices_trianguloazul[] = {
        //X            Y            Z            R        G        B
        -1.0f,    -1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
        1.0f,    -1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
        0.0f,    1.0f,        0.5f,            0.0f,    0.0f,    1.0f,
        
    };

    MeshColor* trianguloazul = new MeshColor();
    trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
    meshColorList.push_back(trianguloazul);
    
    GLfloat vertices_trianguloverde[] = {
        //X            Y            Z            R        G        B
        -0.6f,    -1.0f,        0.5f,            0.0f,    0.5f,    0.0f,
        0.6f,    -1.0f,        0.5f,            0.0f,    0.5f,    0.0f,
        0.0f,    1.0f,        0.5f,            0.0f,    0.5f,    0.0f,
        
    };

    MeshColor* trianguloverde = new MeshColor();
    trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
    meshColorList.push_back(trianguloverde);

    GLfloat vertices_cuadradorojo[] = {
        //X            Y            Z            R        G        B
        -0.5f,    -0.7f,        0.5f,            1.0f,    0.0f,    0.0f,
        0.5f,    -0.7f,        0.5f,            1.0f,    0.0f,    0.0f,
        0.5f,    0.7f,        0.5f,            1.0f,    0.0f,    0.0f,
        -0.5f,    -0.7f,        0.5f,            1.0f,    0.0f,    0.0f,
        0.5f,    0.7f,        0.5f,            1.0f,    0.0f,    0.0f,
        -0.5f,    0.7f,        0.5f,            1.0f,    0.0f,    0.0f,

    };

    MeshColor* cuadradorojo = new MeshColor();
    cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
    meshColorList.push_back(cuadradorojo);
    
    GLfloat vertices_cuadradoverde[] = {
        //X            Y            Z            R        G        B
        -0.5f,    -0.6f,        0.5f,            0.0f,    1.0f,    0.0f,
        0.5f,    -0.6f,        0.5f,            0.0f,    1.0f,    0.0f,
        0.5f,    0.6f,        0.5f,            0.0f,    1.0f,    0.0f,
        -0.5f,    -0.6f,        0.5f,            0.0f,    1.0f,    0.0f,
        0.5f,    0.6f,        0.5f,            0.0f,    1.0f,    0.0f,
        -0.5f,    0.6f,        0.5f,            0.0f,    1.0f,    0.0f,

    };

    MeshColor* cuadradoverde = new MeshColor();
    cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
    meshColorList.push_back(cuadradoverde);
    

    GLfloat vertices_cuadradocafe[] = {
        //X            Y            Z            R        G        B
        -0.5f,    -0.5f,        0.5f,           0.478f, 0.255f, 0.067f,
        0.5f,    -0.5f,        0.5f,            0.478f, 0.255f, 0.067f,
        0.5f,    0.5f,        0.5f,             0.478f, 0.255f, 0.067f,
        -0.5f,    -0.5f,        0.5f,           0.478f, 0.255f, 0.067f,
        0.5f,    0.5f,        0.5f,             0.478f, 0.255f, 0.067f,
        -0.5f,    0.5f,        0.5f,            0.478f, 0.255f, 0.067f

    };

    MeshColor* cuadradocafe = new MeshColor();
    cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
    meshColorList.push_back(cuadradocafe);

}


void CreateShaders()
{
    
    Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras
    shader2->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shader2);
}


int main()
{

    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    CreaPiramide(); //índice 0 en MeshList
    CrearCubo();//índice 1 en MeshList
    CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
    CreateShaders();
    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    //Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
    glm::mat4 projection = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, 0.1f, 100.0f);
//    glm::mat4 projection = glm::perspective(glm::radians(60.0f)    ,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
    
    //Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
    glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
    
    //Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose())
    {
        //Recibir eventos del usuario
        glfwPollEvents();
        //Limpiar la ventana
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
        
                                                    
        //Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList
        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();
        
        
        //Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
        
        // Dibujar letras

//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(-0.0f, -0.0f, -2.0f));
//        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[1]->RenderMeshColor();
        
        // Dibujar cuadrados rojos
        
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0.0f, -1.4f, -4.0f));
//        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
//
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[4]->RenderMeshColor();
//
//        // Dibujar cuadrados verdes
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(-0.5f, -1.0f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[5]->RenderMeshColor();
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0.5f, -1.0f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[5]->RenderMeshColor();
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0.0f, -2.3f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.7f, 0.84f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[5]->RenderMeshColor();
//
//        // Dibujar triangulo azul
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0.0f, 0.8f, -2.0f));
//        model = glm::scale(model, glm::vec3(1.3f, 0.84f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[2]->RenderMeshColor();
//
//        // Dibujar Arboles
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(2.0f, -1.4f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.7f, 0.6f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[3]->RenderMeshColor();
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(2.0f, -2.3f, -3.0f));
//        model = glm::scale(model, glm::vec3(0.35f, 1.0f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[6]->RenderMeshColor();
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(-2.0f, -1.4f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.7f, 0.6f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[3]->RenderMeshColor();
//
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(-2.0f, -2.3f, -3.0f));
//        model = glm::scale(model, glm::vec3(0.35f, 1.0f, 0.7f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[6]->RenderMeshColor();
        
//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0, 0, -3.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshColorList[0]->RenderMeshColor();
        
        // Dibujar casa 3D

        //Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        angulo += .5;
        //Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas

        
        // Cuerpo de la Casa
        GLfloat red[3] = {1.0f, 0.0f, 0.0f};
        shaderList[0].setColor(red);
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, -3.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.3f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // Ventanas
        GLfloat green[3] = {0.0f, 1.0f, 0.0f};
        shaderList[0].setColor(green);
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.1f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.25f, -0.3f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.1f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        //Puerta
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, -0.85f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.55f, 0.1f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        //Techo
        GLfloat blue[3] = {0.0f, 0.0f, 1.0f};
        shaderList[0].setColor(blue);
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.63f, -3.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        //Arboles
        //Troncos
        GLfloat brown[3] = {0.478, 0.255, 0.067};
        shaderList[0].setColor(brown);
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(1.7f, -1.0f, -3.2f));
        model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.2));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-1.7f, -1.0f, -3.2f));
        model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.2));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        //Hojas
        GLfloat darkGreen[3] = {0.05, 0.425, 0.16};
        shaderList[0].setColor(darkGreen);
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(1.7f, -0.2f, -3.2f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-1.7f, -0.2f, -3.2f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();
        

//        model = glm::mat4(1.0);
//        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -3.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
//        meshList[0]->RenderMesh();

        glUseProgram(0);
        mainWindow.swapBuffers();

    }
    return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/

