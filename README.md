# KrxkCompiler

## 项目简介

1. 本项目为自行实现的简单编译器，意图为学习编译器的编写。
2. 项目分为 Windows 平台 和 Linux 平台，其中 Windows 平台仅演示 `flex & bison` 的使用，且使用 `Visual Studio` IDE 进行构建；Linux 平台将使用 CMake 跨平台构建系统完成构建，同时利用 `llvm` 进一步强化项目功能。

## 构建

### Windows 平台

Windows 平台下只需要使用 Visual Studio 打开 `.sln` 文件即可使用 IDE 完成一步构建。

### Linux 平台

#### 前置依赖

Linux 平台采用 Visual Studio Code 编写代码，基于 CMake 完成构建。构建前需要安装项目核心依赖：

```bash
sudo apt install flex bison llvm
```

其他非核心依赖如 C/C++ 工具链请自行安装配置。

#### 构建

采用下列命令完成构建

```bash
cd Linux
chmod + x build.sh
./build.sh
```



