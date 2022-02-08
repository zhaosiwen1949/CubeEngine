#include "TriangleRenderer.h"

TriangleRenderer::TriangleRenderer(
        VulkanRenderContext& ctx,
        const char* vtxShaderFile,
        const char* fragShaderFile): Renderer(ctx) {
    const PipelineInfo pInfo = initRenderPass(PipelineInfo {}, std::vector<VulkanTexture> {}, RenderPass(), ctx.screenRenderPass);

    initPipeline({ vtxShaderFile, fragShaderFile }, pInfo);
}

void TriangleRenderer::fillCommandBuffer(VkCommandBuffer cmdBuffer, size_t currentImage, VkFramebuffer fb, VkRenderPass rp) {
    beginRenderPass((rp != VK_NULL_HANDLE) ? rp : renderPass_.handle, (fb != VK_NULL_HANDLE) ? fb : framebuffer_, cmdBuffer, currentImage);

    vkCmdDraw(cmdBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(cmdBuffer);
}

void TriangleRenderer::updateBuffers(size_t currentImage) {

}
