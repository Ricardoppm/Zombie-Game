//
//  GLSLProgram.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef GLSLProgram_hpp
#define GLSLProgram_hpp

#include <string>

#include <OpenGL/gl3.h>
namespace Bengine {

    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();
        
        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        
        void linkShaders();
        
        void addAttribute(const std::string& attributeName);
        
        GLint getUniformLocation( const std::string& uniformName);
        
        void use();
        void unuse();
        
    private:
        void compileShader( const std::string filePath, GLuint id);
        
        int _numAttributes;

        
        GLuint _programID;
        
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;
    };
}
#endif /* GLSLProgram_hpp */
