//
//  PicoPNG.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef PicoPNG_hpp
#define PicoPNG_hpp

#include <vector>

namespace Bengine {

    extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true)
    ;
}

#endif /* PicoPNG_hpp */
