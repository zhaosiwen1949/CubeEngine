//
//  Texture2D.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/10.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#include "Texture2D.hpp"
#include "../../Utils/stb_image.h"

std::unordered_map<std::string, std::weak_ptr<Texture2D>> Texture2D::_mTextureMap;

std::shared_ptr<Texture2D> Texture2D::LoadTexture(std::string path) {
    // 查找 Texture 缓存
    std::shared_ptr<Texture2D> texture;
    const auto& iter = _mTextureMap.find(path);
    if(iter != _mTextureMap.cend() && (texture = iter->second.lock())) {
        return texture;
    }
    // 没有在缓存中查找到，需要新建
    texture = std::make_shared<Texture2D>();
    // 设置纹理图像上下翻转
    stbi_set_flip_vertically_on_load(true);
    // 加载纹理图片
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data){
        // 设置不同图片的格式
        GLenum format = GL_RGB;
        if(nrChannels == 1) {
            format = GL_RED;
        } else if (nrChannels == 3){
            format = GL_RGB;
        } else if (nrChannels == 4){
            format = GL_RGBA;
        };
        // 设置纹理对象内容
        texture->Init(data, width, height, format);
        // 加入到缓存中
        _mTextureMap.insert({path, texture});
        // 释放图片数据
        stbi_image_free(data);
        return texture;
    }else{
        printf("图片加载失败");
        // 释放图片数据
        stbi_image_free(data);
        return nullptr;
    }
}

void Texture2D::Init(unsigned char *data, int width, int height, GLenum format) {
    glad_glGenTextures(1, &_mTextureID);
    glad_glBindTexture(_mTextureType, _mTextureID);
    // 设置纹理对象属性
    glad_glTexParameteri(_mTextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(_mTextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(_mTextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(_mTextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glad_glTexImage2D(_mTextureType, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glad_glGenerateMipmap(_mTextureType);
    glad_glBindTexture(_mTextureType, 0);
}
