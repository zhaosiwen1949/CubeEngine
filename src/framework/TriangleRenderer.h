#pragma once

#include "Renderer.h"

constexpr const char* DefaultTriangleVertexShader = "data/shaders/Triangle.vert";
constexpr const char* DefaultTriangleFragmentShader = "data/shaders/Triangle.frag";

struct TriangleRenderer: public Renderer {
    TriangleRenderer(
            VulkanRenderContext& ctx,
    const char* vtxShaderFile = DefaultTriangleVertexShader,
    const char* fragShaderFile = DefaultTriangleFragmentShader);

    void fillCommandBuffer(VkCommandBuffer cmdBuffer, size_t currentImage, VkFramebuffer fb = VK_NULL_HANDLE, VkRenderPass rp = VK_NULL_HANDLE) override;
    void updateBuffers(size_t currentImage) override;
};

