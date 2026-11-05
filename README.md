English | [中文](README_zh.md)

# LightlyShaders v3.0

LightlyShaders rounds window corners and adds configurable outlines and shadow handling. It works correctly with the stock Plasma effects and supports KDE Plasma/KWin 6.7 and newer. Tested on Arch Linux with Plasma/KWin 6.8.2.

![screenshot](screenshot.webp)

## Features

- Rounded or squircle window corners
- Inner and outer outlines with configurable colors and widths
- Configurable shadow offset
- Optional disabling for maximized windows
- Per-application blacklist with selectable matching scope
- Blacklist support for both corner rounding and rounded blur regions

## Dependencies

You need Qt 6, KF6, KWin, KDecoration3, X11, and XCB development files.

**Arch Linux** (Plasma/KWin 6.8):

```bash
sudo pacman -S --needed base-devel cmake extra-cmake-modules gettext git \
    qt6-base qt6-tools kwin kdecoration libepoxy libx11 libxcb \
    vulkan-headers
```

`vulkan-headers` is pulled in by `kwin/core/drm_formats.h` since KWin 6.8; without it configuration fails with `Could NOT find Vulkan`.

## Manual installation

```bash
git clone https://github.com/YuKongA/LightlyShaders
cd LightlyShaders; mkdir qt6build; cd qt6build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr && make
sudo make install
```

## Configuration

Open **System Settings → Window Management → Desktop Effects → LightlyShaders**.

The main options control:

- Corner size and shadow offset
- Inner and outer outlines, including colors and widths
- Whether the effect is disabled for maximized windows
- Rounded or squircle corner shape and the squircle ratio
- Applications excluded from the effect

The separate **Blur (LightlyShaders)** effect provides blur strength and noise settings. Its rounded blur regions share the application blacklist configured in LightlyShaders.

### Application blacklist

Use **Excluded applications** to prevent LightlyShaders from affecting selected applications. Matching is case-insensitive and uses substring matching against:

- Window class
- Window role
- Window title
- Process name and executable name

Each entry can control its own matching scope:

| Entry                 | Matching behavior                                                                                |
| --------------------- | ------------------------------------------------------------------------------------------------ |
| `TinyPasture`         | Matches window information and the process name. This is the default and is backward compatible. |
| `process:TinyPasture` | Matches the process name only, excluding every window created by that process.                   |
| `window:TinyPasture`  | Matches the window class, role, and title only. It does not match the process name.              |
| `steam_app_3167550`   | Matches the window class.                                                                        |

Example for TinyPasture:

- The main window has window class `steam_app_3167550` and title `TinyPasture`.
- The farm window has the same window class but an empty title.
- `TinyPasture` or `process:TinyPasture` excludes both windows.
- `window:TinyPasture` excludes only the main window because the farm window has no matching title.
- `steam_app_3167550` matches both windows through their shared window class.

After saving, both LightlyShaders effects are reconfigured immediately. After installing or upgrading the plugin, log out and back in so KWin loads the new plugin binary; toggling the effect off and on does not reload it.

## Note

After Plasma/KWin updates, rebuild the plugin so it can follow KWin API changes. If CMake reports missing headers, install the packages listed above and rerun the configure command.
