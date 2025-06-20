# 基于 OpenGL 实现的3D模型加载渲染程序

模型来自于 [模之屋](https://www.aplaybox.com/u/680828836)

**思路**

- 使用 assimp 实现模型的加载；
- 模型的贴图使用 opencv 来加载材质信息；
- 动态背景使用的是 [shadertoy](https://www.shadertoy.com/view/WfcGWj) 的 GLSL 示例代码进行渲染；

**主要的工作内容**

- 构建 shader 类，可以加载不同类型的 GLSL 创建对应的 shader，同时提供设置 GLSL 中 uniform 变量的方法；
- 构建 vertex array类，提供手动设置 vertex buffer 的数据属性；
- texture 类，使用 opencv 加载图像数据用于纹理创建；
- camera 类，可以实现鼠标左键对模型进行旋转；

**后续改进计划**

- 鼠标左键旋转模型针对单个模型来进行；
- 整合 [lmgui](https://github.com/ocornut/imgui) 来实现一些输入控制；

同时提供了一些键盘和鼠标的操控功能，具体信息罗列如下：

|按键|功能|
|:---:|:---:|
|W|视角向前移动|
|A|视角向后移动|
|S|视角向左移动|
|D|视角向右移动|
|Q|向下移动|
|E|向上移动|
|鼠标左键|旋转|
|鼠标滑轮|缩放视角|

[B站视频展示](https://www.bilibili.com/video/BV1Maj5z1Ehi/?vd_source=0bc24278cd7a0c76a9cea9d12245ddd8)

效果展示：

![img](./img/res.gif)

![img](./img/pic1.png)

![img](./img/pic2.png)

![img](./img/pic3.png)