#!/bin/bash

# 编译文档
make html

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "文档编译成功！"
    echo "HTML页面位于: _build/html/index.html"
    echo "请在浏览器中打开该文件查看文档"
else
    echo "文档编译失败，请检查错误信息"
fi