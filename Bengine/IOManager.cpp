//
//  IOManager.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "IOManager.hpp"

#include <fstream>

namespace Bengine {

    bool IOManager::readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if( file.fail()){
            perror(filePath.c_str());
            return false;
        }
        // seek to the end of the file
        file.seekg(0, std::ios::end);
        
        // get the file size
        long long fileSize = file.tellg();
        
        // Seek to the start of the file
        file.seekg(0, std::ios::beg);
        
        // reduce the file size by any header bytes that might be present
        fileSize -= file.tellg();
        
        buffer.resize(fileSize);
        file.read( (char*)&(buffer[0]), fileSize );
        file.close();
        
        return true;
    }
}
