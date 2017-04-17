//
//  GLSLProgram.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "GLSLProgram.hpp"

#include <fstream>
#include <vector>
#include <iostream>

#include "errors.hpp"

namespace Bengine {

    GLSLProgram::GLSLProgram()
    : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
    {}

    GLSLProgram::~GLSLProgram(){}

    void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
    {
        //Get a program object.
        _programID = glCreateProgram();
        
        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if( _vertexShaderID==0)
            fatalError("Vertex shader failed to be created");
        
        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if( _fragmentShaderID==0)
            fatalError("Fragment shader failed to be created");
        
        compileShader(vertexShaderFilePath, _vertexShaderID);
        compileShader(fragmentShaderFilePath, _fragmentShaderID);
    }

    void GLSLProgram::linkShaders()
    {
        //Vertex and fragment shaders are successfully compiled.
        //Now time to link them together into a program.
       
        
        //Attach our shaders to our program
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);
        
        //Link our program
        glLinkProgram(_programID);
        
        //Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
            
            //The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
            
            //We don't need the program anymore.
            glDeleteProgram(_programID);
            //Don't leak shaders either.
            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);
            
            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader failed to link!");
        }
        
        //Always detach shaders after a successful link.
        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);
        
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void GLSLProgram::addAttribute(const std::string &attributeName)
    { 
        glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation( const std::string& uniformName)
    {
        GLint location = glGetUniformLocation(_programID, uniformName.c_str());
        if( location == GL_INVALID_INDEX){
            fatalError("Uniform " + uniformName + "not found in shader!");
        }
        return location;
    }


    void GLSLProgram::use()
    {
        glUseProgram(_programID);
        for(int i=0; i<_numAttributes; i++){
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse()
    {
        glUseProgram(0);
        for(int i=0; i<_numAttributes; i++){
            glDisableVertexAttribArray(i);
        }
    }

    void GLSLProgram::compileShader(const std::string filePath, GLuint id)
    {
        std::ifstream vertexFile( filePath);
        if(vertexFile.fail()){
            perror(filePath.c_str());
            fatalError("Failed to open " + filePath);
        }
        
        std::string fileContents = "";
        std::string line;
        while( getline(vertexFile, line)){
            fileContents += line + "\n";
        }
        vertexFile.close();
        
        const char* contentsPtr = fileContents.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);
        
        glCompileShader(id);
        
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if( success == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
            
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(id); // Don't leak the shader.
            
            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader " + filePath + " failed to compile");
        }
    }
}
