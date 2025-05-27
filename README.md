# 基于 OpenGL 实现的3D模型加载渲染程序

模型来自于 [模之屋](https://www.aplaybox.com/u/680828836)

思路：使用 assimp 实现模型的加载，动态背景使用的是 [shadertoy](https://www.shadertoy.com/view/WfcGWj) 的 GLSL 示例代码进行渲染

键盘按键功能：

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
<div style="text-align: center;">
    <img src="./img/res.gif"/>
</div>

![img](./img/pic1.png)

![img](./img/pic2.png)

![img](./img/pic3.png)