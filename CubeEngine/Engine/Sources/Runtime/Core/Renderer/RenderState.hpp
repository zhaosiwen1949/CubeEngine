//
//  RenderState.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef RenderState_hpp
#define RenderState_hpp

#include <stdio.h>
#include <glad/glad.h>

struct RenderState {
    GLenum mPrimitiveType;
    bool mbBlend;
    bool mbZTest;
    bool mbAlphaTest;
    bool mbWriteR;
    bool mbWriteG;
    bool mbWriteB;
    bool mbWriteA;
    bool mbWriteZ;
    bool mbWriteStencil;
    bool mbCull;
    bool mbEnablePointSprite;
    int mCullFace;
    int mZTestFunction;
    int mAlphaTestFunction;
    float mAlphaTestValue;
    float mOffsetFactor;
    float mOffsetUnit;
    unsigned int mSRCBlendFunc;
    unsigned int mDSTBlendFunc;
    int mClearStencilValue;
    unsigned int mPolygonMode;
    RenderState();
    void operator=(const RenderState&rs);
    void Bind();
};
class GlobalRenderState {
public:
    static RenderState mRenderState;
    static float mClearColor[4];
    static bool mEnableAttributes[16];
    static void BlendFunc(unsigned int src, unsigned int dst);
    static void EnableBlend(bool enable);
    static void EnableDepthTest(bool enable);
    static void EnablePointSprite(bool enable);
    static void EnableRenderTwoSide(bool enable);
    static void EnableCull(bool enable);
    static void CullFace(int face);
    static void PolygonMode(int mode);
    static bool EnableZWrite(bool enable);
    static void ZTest(int func);
    static void ClearZ();
    static bool EnableAlphaTest(bool enable);
    static void AlphaTest(int func,float v);
    static void ZOffset(float factor,float unit);
    static void ClearColor(float r, float g, float b, float a);
    static void ClearColorFBO(float r, float g, float b, float a, int color_buffer_index = 0);
    static void ColorMask(bool r, bool g, bool b, bool a);
    static void StencilMask(bool write);
    static void ClearStencil(int value);
    static void EnableAttribute(int index, bool enable);
    static void EnableTextureUnit(int index, bool enable = true);
    static void BindTexture(int texture_type, unsigned int texture);
    static void Init();
};

#endif /* RenderState_hpp */
