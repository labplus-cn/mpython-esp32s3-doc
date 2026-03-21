# 2.2 VSCode环境代码编程

## 2.2.1. vsode简介

Visual Studio Code（简称 VSCode）
是由微软开发的一款免费、开源、跨平台（Windows/macOS/Linux）的代码编辑器，于
2015
年正式发布。它以轻量级、高扩展性和强大的开发体验著称，广泛应用于前端开发、后端编程、数据分析、DevOps
等场景，支持几乎所有主流编程语言。

> - 多语言支持与智能提示
>   - 原生支持 JavaScript、TypeScript、Python、Java、C++
>     等语言，通过插件可扩展至更多小众语言（如 Go、Rust、Kotlin 等）。
>   - 内置 IntelliSense
>     智能提示系统，支持代码补全、语法高亮、函数定义跳转，甚至能根据上下文推荐代码片段。
> - 强大的插件生态
>   - 通过 VSCode Marketplace 可安装数万款插件，覆盖代码格式化（如
>     Prettier）、调试工具（如 Python Debugger）、版本控制（如
>     GitLens）、UI 美化（如 Material Theme）等功能。
>   - 支持自定义插件开发，满足个性化需求。
> - 集成化开发体验
>
> > - 内置 Git
> >   版本控制功能，可直接在编辑器中查看提交历史、对比代码差异、推送 /
> >   拉取分支。
> > - 支持多终端集成，无需切换工具即可执行命令行操作（如 npm
> >   install、git commit）。
> > - 内置调试器，支持断点调试、变量监视、调用栈查看，适配多种编程语言。

## 2.2.2. 安装配置VSCode

1.  下载VSCode

    - 访问 [VSCode官网](https://code.visualstudio.com/)
      ，选择适合您操作系统的版本进行下载。
    - 安装过程中，建议勾选 "添加到PATH" 选项，以便在命令行中直接使用
      VSCode。

    | 

    ![image](/_static/image/vscode.png){.align-center width="1257px"}

    | 

2.  安装Python扩展

    - 打开 VSCode，点击左侧活动栏中的 "扩展" 图标，搜索 "Python" 并安装
      "Python" 扩展。
    - 安装完成后，VSCode 会自动识别 Python
      环境，并提供智能提示、代码格式化等功能。

3.  安装esp-idf扩展
