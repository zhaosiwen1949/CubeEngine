# 注意
### 本项目暂时废弃，不再更新，目前会把精力放在新的引擎项目中，主要是采用 Cmake 和 Vulkan 的方式，来实现跨平台和更加现代性的 API
# CubeEngine
尝试动手构建一个渲染引擎

主要特点：
- [x] ECS 系统
- [x] PBR 材质
  - [x] 材质球 
  - [ ] IBL 光照
- [ ] 跨端渲染

# 开发环境搭建
## Mac 环境
安装 GLFW、GLAD、assimp 作为基础依赖

### 安装 GLFW
直接用 brew 安装
```
brew install glfw
```
安装后，找到安装文件的位置
```
brew list glfw
```
![image](https://user-images.githubusercontent.com/13034272/128997575-cad5e121-1ff1-41cc-a61c-01234cc4a064.png)

配置 Xcode 中 头文件 和 库文件 的位置
![image](https://user-images.githubusercontent.com/13034272/128997520-991892bf-2946-4e1a-9eb7-aaa4c4d80757.png)
将图中的动态链接库，拖拽到 Xcode 链接库的位置
![image](https://user-images.githubusercontent.com/13034272/128998006-0886a08e-624b-45f3-8d21-1904a0d48a18.png)
添加成功后，在 Library Search Paths 中，会自动添加链接库的位置
![image](https://user-images.githubusercontent.com/13034272/128998177-62c20898-9a05-413f-b125-446410506b47.png)
将头文件所在的位置，添加到 Header Search Paths 中
![image](https://user-images.githubusercontent.com/13034272/128998385-fa2a129c-ee5d-44f8-a855-ddaf8669f07f.png)

### 安装 assimp
用同样的方式添加 assimp
![image](https://user-images.githubusercontent.com/13034272/128998664-191ec69d-184d-45d9-91d5-c1da77699d10.png)
![image](https://user-images.githubusercontent.com/13034272/128998797-d9593e95-212b-4789-a9ce-9bd27997096a.png)

### 安装 GLAD
这里参考 LearnOpenGL 教程上的方法
https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/#glad

下载到本地后，将 Headers 所在的文件夹位置添加到 Header Search Paths 中
![image](https://user-images.githubusercontent.com/13034272/129000394-8b1ec59d-1390-4fea-b141-62d355c79a7c.png)
将 glad.c 文件添加到项目中
![image](https://user-images.githubusercontent.com/13034272/129000848-c61660d9-d2a7-4455-944d-aa31887e31f0.png)

### 配置文件路径
参考[Xcode 读取代码所在目录txt或文件](https://blog.csdn.net/u010053344/article/details/51379222)

<img width="1680" alt="截屏2022-01-20 下午7 16 14" src="https://user-images.githubusercontent.com/13034272/150329019-224f778d-efb1-436f-ba4d-144791f5a3dd.png">
<img width="1680" alt="截屏2022-01-20 下午7 16 45" src="https://user-images.githubusercontent.com/13034272/150329025-25114751-98b0-466d-916c-f667e2c3409d.png">
<img width="1680" alt="截屏2022-01-20 下午7 17 02" src="https://user-images.githubusercontent.com/13034272/150329054-f55f48a2-1785-417b-9d47-7aeb3a5cd347.png">
