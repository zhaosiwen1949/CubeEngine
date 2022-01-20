//
//  RenderState.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <cstring>
#include "RenderState.hpp"

RenderState::RenderState() {
    mPrimitiveType = GL_TRIANGLES;
    mbBlend = false;
    mSRCBlendFunc = GL_SRC_ALPHA;
    mDSTBlendFunc = GL_ONE_MINUS_SRC_ALPHA;
    mbAlphaTest = false;
    mAlphaTestFunction = GL_GREATER;
    mAlphaTestValue = 0.0f;
    mbZTest = true;
    mZTestFunction = GL_LEQUAL;
    mbWriteZ = true;
    mbWriteR = true;
    mbWriteG = true;
    mbWriteB = true;
    mbWriteA = true;
    mbWriteStencil = true;
    mbCull = true;
    mCullFace = GL_BACK;
    mOffsetFactor = 0.0f;
    mOffsetUnit = 0.0f;
    mbEnablePointSprite = true;
    mPolygonMode = GL_FILL;
    mClearStencilValue = -1;
}

void RenderState::operator=(const RenderState&rs) {
    std::memcpy(this, &rs, sizeof(RenderState));
}

void RenderState::Bind() {
    GlobalRenderState::EnableBlend(mbBlend);
    GlobalRenderState::BlendFunc(mSRCBlendFunc, mDSTBlendFunc);
    GlobalRenderState::EnableAlphaTest(mbAlphaTest);
    GlobalRenderState::AlphaTest(mAlphaTestFunction, mAlphaTestValue);
    GlobalRenderState::EnableDepthTest(mbZTest);
    GlobalRenderState::ZTest(mZTestFunction);
    GlobalRenderState::EnableZWrite(mbWriteZ);
    GlobalRenderState::ColorMask(mbWriteR, mbWriteG, mbWriteB, mbWriteA);
    GlobalRenderState::StencilMask(mbWriteStencil);
    GlobalRenderState::EnableCull(mbCull);
    GlobalRenderState::CullFace(mCullFace);
    GlobalRenderState::ZOffset(mOffsetFactor, mOffsetUnit);
    GlobalRenderState::EnablePointSprite(mbEnablePointSprite);
    GlobalRenderState::PolygonMode(mPolygonMode);
}

RenderState GlobalRenderState::mRenderState;
float GlobalRenderState::mClearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
bool GlobalRenderState::mEnableAttributes[16];

void GlobalRenderState::Init() {
    glad_glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]);
    glDisable(GL_BLEND);
    glBlendFunc(mRenderState.mSRCBlendFunc, mRenderState.mDSTBlendFunc);
    glDisable(GL_ALPHA_TEST);
    glAlphaFunc(mRenderState.mAlphaTestFunction, mRenderState.mAlphaTestValue);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(true);
    glColorMask(true,true,true,true);
    glStencilMask(true);
    glEnable(GL_CULL_FACE);
    glCullFace(mRenderState.mCullFace);
    glPolygonOffset(mRenderState.mOffsetFactor, mRenderState.mOffsetUnit);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPolygonMode(GL_FRONT_AND_BACK, mRenderState.mPolygonMode);
    for (int i = 0; i < 16; ++i) {
        mEnableAttributes[i] = false;
    }
}

void GlobalRenderState::EnableBlend(bool enable) {
    if (mRenderState.mbBlend != enable){
        mRenderState.mbBlend = enable;
        if (mRenderState.mbBlend){
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }
}

void GlobalRenderState::BlendFunc(unsigned int src, unsigned int dst) {
    if (mRenderState.mSRCBlendFunc != src || mRenderState.mDSTBlendFunc != dst){
        mRenderState.mSRCBlendFunc = src;
        mRenderState.mDSTBlendFunc = dst;
        glBlendFunc(mRenderState.mSRCBlendFunc, mRenderState.mDSTBlendFunc);
    }
}

bool GlobalRenderState::EnableAlphaTest(bool enable) {
    bool old = mRenderState.mbAlphaTest;
    if (mRenderState.mbAlphaTest!=enable){
        mRenderState.mbAlphaTest = enable;
        if (enable){
            glEnable(GL_ALPHA_TEST);
        } else {
            glDisable(GL_ALPHA_TEST);
        }
    }
    return old;
}

void GlobalRenderState::AlphaTest(int func, float v) {
    if (mRenderState.mAlphaTestFunction != func || mRenderState.mAlphaTestValue != v) {
        mRenderState.mAlphaTestFunction = func;
        mRenderState.mAlphaTestValue = v;
        glAlphaFunc(func, v);
    }
}

void GlobalRenderState::EnableDepthTest(bool enable) {
    if (mRenderState.mbZTest != enable) {
        mRenderState.mbZTest = enable;
        if (mRenderState.mbZTest) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

void GlobalRenderState::ZTest(int func) {
    if (mRenderState.mZTestFunction != func) {
        mRenderState.mZTestFunction = func;
        glDepthFunc(mRenderState.mZTestFunction);
    }
}

void GlobalRenderState::ClearZ() {
    if (mRenderState.mbZTest) {
        glad_glClear(GL_DEPTH_BUFFER_BIT);
    }
}

bool GlobalRenderState::EnableZWrite(bool enable) {
    bool original = mRenderState.mbWriteZ;
    if (mRenderState.mbWriteZ != enable) {
        mRenderState.mbWriteZ = enable;
        glDepthMask(mRenderState.mbWriteZ);
    }
    return original;
}

void GlobalRenderState::ColorMask(bool r,bool g,bool b,bool a){
    if (mRenderState.mbWriteR != r || mRenderState.mbWriteG != g || mRenderState.mbWriteB != b || mRenderState.mbWriteA != a) {
        mRenderState.mbWriteR = r;
        mRenderState.mbWriteG = g;
        mRenderState.mbWriteB = b;
        mRenderState.mbWriteA = a;
        glColorMask(r,g,b,a);
    }
}

void GlobalRenderState::StencilMask(bool write) {
    if (mRenderState.mbWriteStencil != write) {
        mRenderState.mbWriteStencil = write;
        glStencilMask(write);
    }
}

void GlobalRenderState::EnableRenderTwoSide(bool enable) {
    if (mRenderState.mbCull != enable) {
        mRenderState.mbCull = enable;
        if (mRenderState.mbCull) {
            glDisable(GL_CULL_FACE);
        } else {
            glEnable(GL_CULL_FACE);
        }
    }
}

void GlobalRenderState::EnableCull(bool enable) {
    if (mRenderState.mbCull != enable) {
        mRenderState.mbCull = enable;
        if (mRenderState.mbCull) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
    }
}

void GlobalRenderState::CullFace(int face) {
    if (mRenderState.mCullFace != face) {
        mRenderState.mCullFace = face;
        glCullFace(mRenderState.mCullFace);
    }
}

void GlobalRenderState::ZOffset(float factor, float unit) {
    if (mRenderState.mOffsetFactor != factor || mRenderState.mOffsetUnit != unit) {
        mRenderState.mOffsetFactor = factor;
        mRenderState.mOffsetUnit = unit;
        glPolygonOffset(mRenderState.mOffsetFactor, mRenderState.mOffsetUnit);
    }
}

void GlobalRenderState::EnablePointSprite(bool enable) {
    if (mRenderState.mbEnablePointSprite != enable) {
        mRenderState.mbEnablePointSprite = enable;
        if (mRenderState.mbEnablePointSprite) {
            glEnable(GL_PROGRAM_POINT_SIZE);
        } else {
            glDisable(GL_PROGRAM_POINT_SIZE);
        }
    }
}

void GlobalRenderState::PolygonMode(int mode) {
    if (mRenderState.mPolygonMode != mode) {
        mRenderState.mPolygonMode = mode;
        glPolygonMode(GL_FRONT_AND_BACK, mRenderState.mPolygonMode);
    }
}

void GlobalRenderState::ClearColor(float r, float g, float b, float a) {
    if (mClearColor[0]!=r||mClearColor[1]!=g||mClearColor[2]!=b||mClearColor[3]!=a){
        mClearColor[0] = r;
        mClearColor[1] = g;
        mClearColor[2] = b;
        mClearColor[3] = a;
        glad_glClearColor(r, g, b, a);
    }
    glad_glClear(GL_COLOR_BUFFER_BIT);
}

void GlobalRenderState::ClearColorFBO(float r, float g, float b, float a, int color_buffer_index) {
    if (mClearColor[0]!=r||mClearColor[1]!=g||mClearColor[2]!=b||mClearColor[3]!=a){
        mClearColor[0] = r;
        mClearColor[1] = g;
        mClearColor[2] = b;
        mClearColor[3] = a;
        glClearBufferfv(GL_COLOR, color_buffer_index,mClearColor);
    }
}

void GlobalRenderState::ClearStencil(int value) {
    if (mRenderState.mClearStencilValue != value) {
        mRenderState.mClearStencilValue = value;
        glClearStencil(mRenderState.mClearStencilValue);
    }
}

void GlobalRenderState::EnableAttribute(int index, bool enable) {
    if (mEnableAttributes[index] != enable) {
        mEnableAttributes[index] = enable;
        if (enable) {
            glEnableVertexAttribArray(index);
        } else {
            glDisableVertexAttribArray(index);
        }
    }
}

void GlobalRenderState::EnableTextureUnit(int index, bool enable) {
    glActiveTexture(GL_TEXTURE0 + index);
}

void GlobalRenderState::BindTexture(int textureType, unsigned int texture) {
    glBindTexture(textureType, texture);
}
