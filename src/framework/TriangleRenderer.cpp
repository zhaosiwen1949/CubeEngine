#include "TriangleRenderer.h"

TriangleRenderer::TriangleRenderer(
        VulkanRenderContext& ctx,
        const char* vtxShaderFile,
        const char* fragShaderFile): Renderer(ctx) {
    // 1、初始化 RenderPass
    const PipelineInfo pInfo = initRenderPass(PipelineInfo {}, std::vector<VulkanTexture> {}, RenderPass(), ctx.screenRenderPass);

    // 2、初始化 buffer
    const size_t imgCount = ctx.vkDev.swapchainImages.size();
    indirect_.resize(imgCount);

    const uint32_t indirectDataSize = (uint32_t)sizeof(VkDrawIndirectCommand);

    for (size_t i = 0; i != imgCount; i++) {
        indirect_[i] = ctx.resources.addIndirectBuffer(indirectDataSize);
        updateIndirectBuffers(i);
    }

    // 3、初始化 pipeline
    initPipeline({ vtxShaderFile, fragShaderFile }, pInfo);
}

void TriangleRenderer::fillCommandBuffer(VkCommandBuffer cmdBuffer, size_t currentImage, VkFramebuffer fb, VkRenderPass rp) {
    beginRenderPass((rp != VK_NULL_HANDLE) ? rp : renderPass_.handle, (fb != VK_NULL_HANDLE) ? fb : framebuffer_, cmdBuffer, currentImage);

//    vkCmdDraw(cmdBuffer, 3, 1, 0, 0);
    // 验证 IndirectDraw
    vkCmdDrawIndirect(cmdBuffer, indirect_[currentImage].buffer, 0, 1, sizeof(VkDrawIndirectCommand));

    vkCmdEndRenderPass(cmdBuffer);
}

void TriangleRenderer::updateBuffers(size_t currentImage) {

}

void TriangleRenderer::updateIndirectBuffers(size_t currentImage) {
    // VkDrawIndirectCommand 数组指针
    VkDrawIndirectCommand* data = nullptr;

    // 映射指针
    vkMapMemory(ctx_.vkDev.device, indirect_[currentImage].memory, 0, sizeof(VkDrawIndirectCommand), 0, (void**)&data);

    // 填充数据
    *data = {
            .vertexCount = 3u,
            .instanceCount = 1u,
            .firstVertex = 0,
            .firstInstance = 0,
    };

    // 解除指针映射
    vkUnmapMemory(ctx_.vkDev.device, indirect_[currentImage].memory);
}
