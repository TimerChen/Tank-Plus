
#当前版本的问题
* 缺少main函数
* cannot find -lglut32

#使用帮助手册
Edited by TimeMachine at 2016-8-10.
##目录
###Father

    父类以及namespace GAME

###Geometry

    计算几何的相关类
    
###Draw

    和图形化有关的工具类

###SandBox

    计算碰撞、运动的类
 
###Sprite
 
    控制画图的精灵类

###Main

    主函数Main

##Father
###GAME(namespace)
    
    程序中用到的各种常量

###Object

    所有类的父类（存在意义不明）

###Entity : Object

    实体类：可以在屏幕上画出的类

###Ghost : Object
    
    非实体类：不可以画出

##Geometry
###Geometry : Ghost
    
    所有几何类的父类

###Geo_Clac : Ghost
    
    几何计算的类（全是静态函数）
    
###Point : Geometry    

    点
    
###Circle : Geometry

    圆形
    
###Line : Geomery

    线段

###Polygon : Geomery

    多边形

##SandBox
###Body : Ghost

    Sandbox中的物体

###Wall : Body

    静态的障碍物

###Ball : Body

    可以运动的物体
    
###Ball_Polygon : Ball

    形状为多边形的物体

###SandBox : Ghost

    处理Wall&Ball运动的类
    
    
##Draw

###Color : Ghost

    存储颜色的类
    
###Rect : Ghost
    
    存储矩形的类

###Draw_Tool : Ghost

    包含绘画函数的类

##Sprite

###Sprite_Base
    
    所有Sprite的父类
    
###Sprite_Polygon
    
    画Polygon的Sprite
    
###Sprite_Circle
    
    画Circle的Sprite
    
###Sprite_SandBox

    画SandBox的Sprite（可能被删除）