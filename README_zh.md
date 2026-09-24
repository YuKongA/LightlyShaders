[English](README.md) | 中文

# LightlyShaders v3.0

LightlyShaders 用于窗口圆角，并提供可配置的内外描边和阴影处理。此效果可以与 Plasma 自带特效一起正常工作，支持 KDE Plasma/KWin 6.7 及更高版本。本 Kubuntu 分支已在 Kubuntu 26.04 上测试。

![default](screenshot.png)

## 功能

- 圆角或超椭圆窗口
- 可配置颜色和宽度的内外描边
- 可配置的阴影偏移
- 可选择对最大化窗口禁用效果
- 支持按应用设置黑名单，并可单独选择匹配范围
- 黑名单同时作用于窗口圆角和模糊区域的圆角处理

## 依赖关系

需要 Qt 6、KF6、KWin、KDecoration3、X11 和 XCB 开发包。

**Kubuntu 26.04 / Ubuntu 系统**：

```bash
sudo apt update
sudo apt install \
    build-essential cmake extra-cmake-modules gettext git \
    qt6-base-dev qt6-base-private-dev qt6-tools-dev \
    libkf6config-dev libkf6configwidgets-dev libkf6coreaddons-dev \
    libkf6crash-dev libkf6globalaccel-dev libkf6guiaddons-dev \
    libkf6i18n-dev libkf6kcmutils-dev libkf6kio-dev \
    libkf6notifications-dev libkf6service-dev libkf6widgetsaddons-dev \
    libkf6windowsystem-dev kwin-dev libkdecorations3-dev libepoxy-dev \
    libx11-dev libxcb1-dev
```

## 手动安装

```bash
git clone https://github.com/YuKongA/LightlyShaders-kubuntu
cd LightlyShaders-kubuntu; mkdir qt6build; cd qt6build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr && make
sudo make install
```

## 配置

打开「系统设置 → 窗口管理 → 桌面特效 → LightlyShaders」。

主要选项包括：

- 圆角大小和阴影偏移
- 内外描边、描边颜色和宽度
- 是否对最大化窗口禁用效果
- 圆角或超椭圆模式，以及超椭圆比例
- 应用黑名单

独立的 **Blur (LightlyShaders)** 效果提供模糊强度和噪点设置。它的模糊区域圆角会共享 LightlyShaders 中配置的应用黑名单。

### 应用黑名单

通过 **Excluded applications** 可以阻止 LightlyShaders 影响指定应用。匹配不区分大小写，并使用子串匹配，检查以下内容：

- 窗口类名
- 窗口角色
- 窗口标题
- 进程名和可执行文件名

每个条目可以单独控制匹配范围：

| 写法                  | 匹配行为                                               |
| --------------------- | ------------------------------------------------------ |
| `TinyPasture`         | 同时匹配窗口信息和进程名，这是默认行为，并兼容旧配置。 |
| `process:TinyPasture` | 只匹配进程名，排除该进程创建的所有窗口。               |
| `window:TinyPasture`  | 只匹配窗口类名、角色和标题，不匹配进程名。             |
| `steam_app_3167550`   | 按窗口类名匹配。                                       |

TinyPasture 示例：

- 主窗口的窗口类为 `steam_app_3167550`，标题为 `TinyPasture`。
- 牧场窗口使用相同的窗口类，但标题为空。
- `TinyPasture` 或 `process:TinyPasture` 会排除这两个窗口。
- `window:TinyPasture` 只会排除主窗口，因为牧场窗口没有匹配的标题。
- `steam_app_3167550` 会通过共同的窗口类匹配两个窗口。

保存后，两个 LightlyShaders 效果都会立即重新配置。安装或升级插件后，需要注销重新登录，或者关闭再启用对应效果，以便 KWin 加载新的插件二进制文件。

## 注

Plasma/KWin 更新后可能需要重新编译插件，以适配 KWin API 的变化。如果 CMake 报告缺少头文件，请先安装上面的开发包，再重新执行配置命令。
