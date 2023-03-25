## Quantum Graphics Toolkit
Quantum Graphics Toolkit (以下简称 QGT) 是一个基于OpenGL封装出的图形库<br>
它保留了OpenGL极致灵活的特性，可以很简单也可以很复杂，你可以用寥寥几行代码写出一个GUI应用，也甚至可以用稍稍多一些的代码，做出一个好玩的2D游戏... （不过因为还处于非常早期的开发阶段，不少功能还没做全... 呜...）

> <一张小贴纸><br>
> 看看这满篇的WIP... 我们的精力已经不足以翻译文档全文了... 所以 有人可以来帮忙嘛！

## 试试看？
首先需要这些库： `glfw-x11` （如果用 Wayland 就  `glfw-wayland`），`freetype2`，`glm` 和 `mesa`。
之后只需 clone 并 cd 进本仓库，用你喜欢的编译系统编译 `main.cpp` 就好了哦 （比如这里用的是 `ninja`）:

```bash
mkdir build
cd build
cmake -G Ninja ../
ninja
./QuantumGraphicsToolkit
```

## 一些资源
[英文介绍传送门](./README.md)<br>

[`任意门::API参考手册(英)`](./doc/ref/en/intro.md) `::WIP`<br>
[`任意门::API参考手册(中)`](./doc/ref/zh/intro.md)
<br>

[`任意门::构建指南(英)`](./doc/ins/en/building.md) `::WIP`<br>
[`任意门::构建指南(中)`](./doc/ins/zh/building.md)
<br>

[`任意门::示例代码集(英)`](./doc/ex/en/intro.md) `::WIP`<br>
[`任意门::示例代码集(中)`](./doc/ex/zh/intro.md) `::WIP`
<br>

## 贡献代码

_// 贡献的不一定是代码 也可能是情怀_

联系[Telegram](https://t.me/Timicasto)或给timicasto@gmail.com塞邮件就可以得到更多信息啦...<br>
一般来说在晚上9:00到次日凌晨5:00之间都可以半小时内回复.? (当然这里是GMT+8 &>&) <br>
这个项目毕竟还是在超早期的发展阶段... 自己一个人的开发效率往往也没办法做到很高 所以当然欢迎贡献&~&
> 话说写这种东西是真的很难还是我太垃圾了...? 反正自己当年写游戏引擎和现在写这个都会是那种很长时间只写得出特别少代码的...<br>
> 一杯茶，一包烟，一个功能写一周（不可能的吧？
<br>

### 一点提醒: 小心AGPL3.
项目使用 Affero GNU Public License 3开源
> 抱歉自己对开源协议的要求并不了解所以...

## 项目相关人物
#### 作者:
目前只有 Timicasto 自己一个人在开发...
#### 感谢以下支持者:
[@QiuYuanqing](https://github.com/QiuYuanqing) 帮忙贡献的文档翻译—— <br>
[@aisuneko](https://github.com/aisuneko) 帮忙编辑，修改和润色英文文档... <br>
当然还有日日夜夜在调试的时候陪着自己聊天的大家~
<br><br>
如果观光者大人开恩的话也可以给这个项目和此作者贡献一个star和follow &~<br><br>

最后 感谢看完了这篇README... 这是自己的第一个开放使用的正式项目 如果有什么用语不太合适的地方或者什么其他的问题.. enm... 贴issue就好.. 吧=
