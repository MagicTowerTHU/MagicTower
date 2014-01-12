MagicTower
======================
> powered by QT 5.2.0

> > 2013·秋·程序设计与算法基础  

项目成果
----------
* 按21层版本魔塔地图制作；
* 丰富多彩的图形和小动画；
* 集成全部原版音效；
* 完整的地图加载和存档功能；
* 较完备的轻量级地图编辑；
* 扩展和改编简单易行。

开发环境
----------
* ![Alt text](http://qt-project.org/images/qt13a/Qt-logo.png)基于QT 5.2.0的`QMainWindow`(Core GUI)和QT多媒体库`QMultiMedia`环境，以及最新的C++11编译器；
* 2D绘图、文字绘制均使用`QPainter`，配合`QTimer`发送重画信号，形成动画；
* 输入事件主要为键盘，可触发或相应游戏中的相关事件。该事件由继承了`QMainWindow`的`MainWindow`类发出。


面向对象
----------
* 充分利用C++的面向对象特点，过程和对象几乎完全封装于类中，并且充分利用类继承的多态特性，在触发事件、对象重画、获取对象属性等方面都起到了至关重要的作用。另外构造函数的继承方式非常有助于批量设置同类项对象属性，同时避免代码重复(Don't Repeat Yourself)和低级错误。
* 类结构简要说明及类图

> * 程序主界面由继承自`QMainWindow`类的`MainWindow`类管理，辅助两个`QWidget`派生类`Widget`（主界面）和`Status`（左侧状态栏）。

> * 画图的工作主要由`MagicObject`及其子类*`MagicDisplayObject`*派生出的各类地图元素类完成。

> * 程序中需要用户交互和播放动画的部分由*`MagicAnimate`*派生类管理，每个动画管理各自的生存周期。
![Alt text](http://220.113.7.105/MagicTower/ClassDiagram.png)

* 对象事件触发（当主角即将与该对象碰撞时）

```c++
virtual bool MagicDisplayObject::move(MagicMap *) = 0;
```

* 对象绘图方法

```c++
virtual void MagicDisplayObject::paint(QPainter *) = 0;
virtual void MagicAnimateObject::paint(QPainter *) = 0;
```

* 获取对象属性（对象的所有动态属性均在QHash<QString, MagicVariant> MagicObject::property中）

```c++
virtual void MagicObject::setProperty(QString key, MagicVarient value)
{
    property[key] = value;
}
```

可用于劫持某些关键属性（比如物体的位置需要与画图坐标同步、用global的message变量接受弹出消息），达到特殊目的：

```c++
void MagicDisplayObject::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "position_x")
        x = propertyValue.getInt() * 32;
    if (propertyName == "position_y")
        y = propertyValue.getInt() * 32;
    MagicObject::setProperty(propertyName, propertyValue);
}

void MagicMap::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "sound")
    {
        QSound::play(propertyValue.getString());
        return;
    }
    else if (propertyName == "message")
    {
        appendAnimate(new MagicMessage(this, propertyValue.getString()), true);
        return;
    }
    MagicObject::setProperty(propertyName, propertyValue);
}
```

脚本语言
----------
* 脚本语言的语法解释和脚本语言的元编程(Metaprogramming)特性是本程序的亮点。魔塔程序具有解释固定语法的文本地图文件的能力，支持以下功能

> * C语言的基本运算符

```c++
+, -, *, /, %, ^, &, <<, >>, ~, =, <, <=, >, >=, ==, !=
```

> * if分支结构，goto跳转语句（变量不用声明就可以用的哦~）

```c++
i = 0
:for_i
print = i // print为输出至控制台
i = i + 1
if (i <= 3)
    goto for_i
```

> * 对象的属性获取与设置

```c++
tom->health = 10000
emeny_3->attack = 300
```
        
> * 像CSS选择器一样好用的对象选择功能

```css
.hidden->enabled = 0
wall.hidden
#axe->pix = ":/images/axe"
```

> * 对象事件触发（主角即将到达时生效）

```python
on (.fragile)
{
    this->enabled = 0
}

on (.hard)
    return = 0

on (wall.mistery)
    message = "这堵墙看起来有机关……"

on (merchant_exp.floor5)
{
    ret = input("You can use your extra exp to grow your power, please choose: ", "1. 50 exp -> 10 attack",
                "2. 30 exp -> 7 defend", "3. 100 exp -> {15 attack, 15 defend}", "4. Not this time.")
    if (ret == 1)
        if (tom->exp >= 50)
        {
            tom->exp = tom->exp - 50
            tom->attack = tom->attack + 10
        }
    if (ret == 2)
        if (tom->exp >= 30)
        {
            tom->exp = tom->exp - 30
            tom->defend = tom->defend + 7
        }
    if (ret == 3)
        if (tom->exp >= 100)
        {
            tom->exp = tom->exp - 100
            tom->attack = tom->attack + 15
            tom->defend = tom->defend + 15
        }
}
```

> * 输入整层地图

```
at (1)
up      d_1	    k_0 	e_29   	e_28   	e_29   	.   	.   	.   	.   	.
w	    w   	w   	w   	w   	w	    w   	w   	w   	w   	.
m_1.s	.   	e_25	dr_0	.   	w	    m_1.m  	k_0 	m_1.m	w   	.
k_0	    e_25	m_3.s	w   	.	    w	    m_1.m	k_0 	m_1.m	w	    .
w   	dr_0	w   	w   	.   	w   	w   	w   	e_26	w   	.
k_0	    e_24	.   	w	    .   	dr_0	e_8 	e_29	e_21	w   	.
m_4	    .   	k_1	    w   	.   	w   	w   	w   	w   	w   	.
w   	dr_0   	w   	w   	.   	.   	.   	.   	.   	.   	.
.   	e_24   	.   	w   	w   	dr_2	w   	w   	w   	dr_0	w
m_1.m  	m_2.b  	k_0	    w	    k_2 	d_0	    .	    w   	k_0     e_23	k_1
m_1.m	wi  	k_0	    w   	.	    down    .	    w	    k_0	    k_0	    k_0
```

```
w -> wall, k->key, dr->door, e->enemy, d_0->destionation_when_upstair, d_1->destionatoin_when_downstair, m->medicine
```

* MagicTower的存档功能与脚本逻辑密不可分。地图的布局、事件选择器与事件、每个对象的属性哈希表可以完备地表达地图状态，所以存储时只需要存储以上信息即可。存档功能暂时还没有进行压缩和加密，所以存档文件的体积相对较大，并且容易被玩家修改。



