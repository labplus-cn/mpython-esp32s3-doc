# `vfs`{.interpreted-text role="mod"} \-- 虚拟文件系统控制

::: {.module synopsis="虚拟文件系统控制"}
vfs
:::

该模块提供了虚拟文件系统控制功能。

## 函数

::: function
mount(fsobj, mount_point)

挂载文件系统对象到指定的挂载点。

参数:

:   - `fsobj`: 文件系统对象
    - `mount_point`: 挂载点路径
:::

::: function
umount(mount_point)

卸载指定挂载点的文件系统。

参数:

:   - `mount_point`: 挂载点路径
:::

::: function
mkfs(fsobj)

在文件系统对象上创建文件系统。

参数:

:   - `fsobj`: 文件系统对象
:::

::: function
chdir(path)

更改当前工作目录。

参数:

:   - `path`: 目标路径
:::

::: function
getcwd()

获取当前工作目录。

返回值:

:   当前工作目录路径（字符串）
:::
