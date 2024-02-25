#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>

#include<glew.h>

class Shader
{
public:
    Shader();
    void CreatefromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
    std::string ReadFile(const char*  fileLocation);
    GLuint getProjectLocation();
    GLuint getModelLocation();
    //Ir agregando nuevas funciones get para cada variable Uniform

    void useShader();
    void ClearShader();
    void setColor(GLfloat* colorRGB);
    ~Shader();

private:
    GLuint shaderID, uniformProjection, uniformModel, uniformColor;     //Ir agregando nuevas variables Uniform
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* ShaderCode, GLenum shaderType);
};

