//
//  Texture2D.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/10.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <stdio.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <glad/glad.h>

class Texture2D {
public:
    static std::shared_ptr<Texture2D> LoadTexture(std::string path);
    void Init(unsigned char* data, int width, int height, GLenum format);
    inline GLuint GetTextureID() const {
        return _mTextureID;
    }
    inline GLenum GetTextureType() const {
        return _mTextureType;
    }
private:
    static std::unordered_map<std::string, std::weak_ptr<Texture2D>> _mTextureMap;
    GLuint _mTextureID = 0;
    GLenum _mTextureType = GL_TEXTURE_2D;
};

#endif /* Texture2D_hpp */
