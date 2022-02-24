# CubeEngine 2.0
经过几个月的准备，CubeEngine 2.0 开始更新，这是一次颠覆式的重构，1.0 的代码全部弃用，整体会采用 Cmake 来构建管理工程，目前的目标是先在 Windows/Mac 端跑起来，之后引入 Android 端，除此之外，底层的图形 API 也从 OpenGL 3.3 升级到 Vulkan 1.1（为了兼容 Mac 和 Android，暂时没有选择 Vulkan 1.2），这一次让我们从头开始。

# 整体目标
- [x] Cmake Project
- [ ] Vulkan RHI
- [x] GPU Driven Rendering
- [x] PBR
- [ ] Soft Shadow
- [ ] Compute Shader Culling
- [ ] Global Lighting
- [ ] ECS
- [ ] Render Graph
- [ ] Cross Platform
- [ ] MutilpleThread

# 项目配置
本项目通过 [https://github.com/corporateshark/bootstrapping](https://github.com/corporateshark/bootstrapping) 管理第三方依赖，需要提前安装的只有下面两个：

### Vulkan SDK
前往 [https://www.vulkan.org/](https://www.vulkan.org/) 下载合适的SDK

### 编译器
1. 对于 Windows，推荐安装 visual studio 2019 及以上；
2. 对于 Mac，推荐安装 ninja，
  ```
  brew install ninja
  ```
3. 对于 Linux，推荐安装 ninja.

### 编辑器
编辑器推荐安装 CLion，并设置 CWD 为项目根目录
<img width="1680" alt="截屏2022-02-24 下午7 22 08" src="https://user-images.githubusercontent.com/13034272/155515173-b7fd9572-238b-4621-9a7b-85247c358e4e.png">


# Get Started
1. Cmake 编译
```
mkdir build
cd build
cmake ..
cmake --build .
```
2. SceneCovert 工具转换
首先，配置 `data/sceneconverter.json` 中关于模型的属性
```
[
	{
		"input_scene":  "deps/src/glTF-Sample-Models/2.0/DamagedHelmet/glTF/DamagedHelmet.gltf",
		"output_mesh": "data/meshes/test_DamagedHelmet.meshes",
		"output_scene": "data/meshes/test_DamagedHelmet.scene",
		"output_materials": "data/meshes/test_DamagedHelmet.materials",
		"scale": 1.0,
		"calculate_LODs": false,
		"merge_instances": false
	}
]
```
之后运行编译好的程序 `./build/tools/SceneConvert/SceneConver `，来将模型转换到引擎使用的内部格式。
3. 将 CWD 设置为当前项目的根目录，运行示例项目

# Samples
### Hello Triangle
基本的 Vulkan 三角形渲染
<img width="1595" alt="截屏2022-02-23 下午9 41 11" src="https://user-images.githubusercontent.com/13034272/155517760-8e31196d-8d82-4409-bf18-59f660e4842d.png">

### Damaged Helmet
基于 PBR 的头盔
<img width="1598" alt="截屏2022-02-23 下午9 42 28" src="https://user-images.githubusercontent.com/13034272/155517850-10ade82a-2913-4449-9076-d8e7ef67c7a3.png">

### SkyBox
天空盒（待实现）

### 阴影
PCF 软阴影（待实现）

### SSAO
SSAO（待实现）

# 说明文档
奔引擎主要用来学习使用，对于引擎内部的实现逻辑，可以参照以下文档
1. [引擎架构之场景数据](https://zhaosiwen1949.github.io/graphics-collection/engine/sceneData.html)
2. [引擎架构之应用封装](https://zhaosiwen1949.github.io/graphics-collection/engine/application.html)
3. [引擎架构之资源管理](https://zhaosiwen1949.github.io/graphics-collection/engine/resource.html)
4. [引擎架构之 FrameworkRenderer 封装](https://zhaosiwen1949.github.io/graphics-collection/engine/frameworkRenderer.html)
5. [引擎架构之 后处理 Renderer 封装](https://zhaosiwen1949.github.io/graphics-collection/engine/postprocessorRenderer.html)（正在加工中）

# 注意事项
对于 MacOS 系统，由于底层使用的是 MoltenVK，不支持超过 18 个纹理资源的绑定，所以在使用大场景模型时，如果纹理数量过多，需要做以下兼容设置
1. 设置环境变量 MVK_CONFIG_USE_METAL_ARGUMENT_BUFFERS=1，同时使用 Intel 的集显，才能使用 texture array；

# 参考项目
1. https://github.com/google/filament
2. https://github.com/openscenegraph/OpenSceneGraph
3. https://github.com/vsg-dev/VulkanSceneGraph
4. https://github.com/EmbarkStudios/kajiya
5. https://github.com/ConfettiFX/The-Forge

# 参考文献
本项目主要参考了《3D Graphics Rendering Cookbook》，电子书我放在 Reference 文件夹里了，这里安利一下。
