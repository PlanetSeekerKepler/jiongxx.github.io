# Hello world

C语言见习

## 项目

- [x] 堆排序，Heap sort
- [x] 优先队列，Priority queue
- [ ] MODBUS-RTU服务
- [x] Windows Hello界面，摘自[演练：创建传统的 Windows 桌面应用程序 (C++)](https://learn.microsoft.com/zh-cn/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170)

## IDE

使用Visual Studio Code进行编辑，需要下载拓展C/C++和C/C++ Extension Pack。

## 编译

所有项目均使用gcc和g++编译，在Windows上需要下载[w64devkit](https://github.com/skeeto/w64devkit)。

编译所有项目文件，生成对象文件`.o`
```c
gcc -c *.c
```

将所有对象文件链接，生成可执行文件`.exe`
```c
gcc *.o -o {EXE_NAME}
```

部分项目编写了Makefile文件，可使用Makefile可编译。
```Makefile
make
```

## git使用

初始化仓库
```git
git init
```

添加远程连接信息。
```git
git remote add https "https://github.com/PlanetSeekerKepler/jiongxx.github.io.git"
```

将本地文件添加到缓存区
```git
git add {FILE NAME}
```

将缓存区提交到本地仓库，附更新备注
```git
git commit -m "Some info."
```

将本地仓库推送到github
```git
git push
```

将Github仓库拉取至本地工作区
```git
git pull https main
```



