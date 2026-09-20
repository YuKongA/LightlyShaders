English | [中文](README_zh.md)

# LightlyShaders v3.0

This effect works correctly with the stock Plasma effects and supports KDE Plasma/KWin 6.7 and newer. This Kubuntu branch is tested on Kubuntu 26.04.

 ![default](screenshot.png)


# Dependencies

You need Qt 6, KF6, KWin, KDecoration3, X11, and XCB development packages.

**Kubuntu 26.04 / Ubuntu-based systems**:

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

## Manual installation

```bash
git clone https://github.com/YuKongA/LightlyShaders-kubuntu
cd LightlyShaders-kubuntu; mkdir qt6build; cd qt6build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr && make
sudo make install
```

## Note
After Plasma/KWin updates, rebuild the plugin so it can follow KWin API changes. If CMake reports missing headers, install the development packages above and rerun the configure command.
