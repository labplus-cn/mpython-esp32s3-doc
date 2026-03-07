#!/bin/bash

# 打开浏览器的函数
open_browser() {
    local url="$1"
    
    # 检测系统类型并使用适当的命令打开浏览器
    if command -v xdg-open > /dev/null; then
        # Linux
        xdg-open "$url"
        echo "已自动打开浏览器查看文档"
        return 0
    elif command -v open > /dev/null; then
        # macOS
        open "$url"
        echo "已自动打开浏览器查看文档"
        return 0
    elif command -v start > /dev/null; then
        # Windows
        start "$url"
        echo "已自动打开浏览器查看文档"
        return 0
    else
        echo "无法自动打开浏览器，请手动访问: $url"
        return 1
    fi
}

# 编译文档
echo "正在编译文档..."
make html

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "文档编译成功！"
    
    # 停止当前运行的服务器（如果有）
    echo "正在停止当前服务器..."
    pkill -f "python3 -m http.server 8000" 2>/dev/null
    sleep 1
    
    # 重新启动服务器
    echo "正在启动服务器..."
    python3 -m http.server 8000 > server.log 2>&1 &
    sleep 2
    
    # 文档页面地址
    DOC_URL="http://localhost:8000/_build/html/"
    
    # 显示服务器状态
    echo "服务器已启动，运行在 http://localhost:8000"
    echo "文档页面地址: $DOC_URL"
    echo ""
    
    # 自动打开页面
    open_browser "$DOC_URL"
    
    # 无论是否成功打开浏览器，都返回成功
    exit 0
else
    echo "文档编译失败，请检查错误信息"
    exit 1
fi