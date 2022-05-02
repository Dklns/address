# address
大一工程实践
## 前情提要
由于我主要学习前端知识，所以对与C/C++不是很熟悉。老师给出了很多个项目，由我们自己选择完成，我也就选择了我认为最简单的**个人通讯录管理系统**
这个项目也是我一边学C++ 一边做的
主要用到的知识有 对象与类、文件操作

## 程序功能特点
我个人觉得这个项目唯一有体现技术的点就是实现对中文的排序，也就是根据联系人的名字给联系人在组内的显示顺序排序
C++本身是没有关于拼音的编码的，所以不可能凭空生成拼音，那么就需要创建一个储存有所有汉字与其拼音的键值对的文本文件，通过
将其保存在一个map容器中，就得到了一个“字典”，也就是通过 map[汉字] 的访问方式就可以得到拼音了
然后就根据字母大小排序就行了
具体实现代码在 pinYinMapParser.cpp 文件中
