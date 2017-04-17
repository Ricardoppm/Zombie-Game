//
//  IOManager.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include <vector>
#include <string>

namespace Bengine {

    class IOManager
    {
    public:
        static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath);
    };
}

#endif /* IOManager_hpp */
