# CubeEngine 2.0
经过几个月的准备，CubeEngine 2.0 开始更新，这是一次颠覆式的重构，1.0 的代码全部弃用，整体会采用 Cmake 来构建管理工程，目前的目标是先在 Windows/Mac 端跑起来，之后引入 Android 端，除此之外，底层的图形 API 也从 OpenGL 3.3 升级到 Vulkan 1.1（为了兼容 Mac 和 Android，暂时没有选择 Vulkan 1.2），这一次让我们从头开始。

# 整体目标
- [ ] Cmake Project
- [ ] Vulkan RHI
- [ ] GPU Driven Rendering
- [ ] PBR
- [ ] Soft Shadow
- [ ] Compute Shader Culling
- [ ] Global Lighting
- [ ] ECS
- [ ] Render Graph

# 项目配置
对于 MacOS 系统，由于底层使用的是 MoltenVK，需要做以下兼容设置
1. 设置环境变量 MVK_CONFIG_USE_METAL_ARGUMENT_BUFFERS=1，同时使用 Intel 的集显，才能使用 texture array；

# 参考项目
1. https://github.com/google/filament
2. https://github.com/openscenegraph/OpenSceneGraph
3. https://github.com/vsg-dev/VulkanSceneGraph
4. https://github.com/EmbarkStudios/kajiya
5. https://github.com/ConfettiFX/The-Forge

# 参考文献
本项目主要参考了《3D Graphics Rendering Cookbook》，电子书我放在 Reference 文件夹里了，这里安利一下。
