# LilouCalc

[![Build](https://github.com/Antidote1911/liloucalc/actions/workflows/build.yml/badge.svg)](https://github.com/Antidote1911/liloucalc/actions/workflows/build.yml)
[![Release](https://img.shields.io/github/v/release/Antidote1911/liloucalc)](https://github.com/Antidote1911/liloucalc/releases/latest)
[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](LICENSE)

A cross-platform scientific calculator written in C++20 and Qt6.

![Preview](liloucalc.png)

## Features

- Expression-based input with full parenthesis support
- Scientific functions: trigonometry, logarithms, powers, factorials
- Equation solver
- Unit conversions (length, mass, time, energy, pressure, and more)
- Variables and user-defined functions
- Constants library
- Session history
- Dark, light, and system theme
- Cross-platform: Linux, macOS, Windows

The expression engine and unit system are derived from the [SpeedCrunch](https://speedcrunch.org/) project.

## Download

Pre-built binaries are available on the [Releases](https://github.com/Antidote1911/liloucalc/releases) page:

| Platform | Format |
|----------|--------|
| Linux    | AppImage |
| macOS    | DMG (universal arm64 + x86_64) |
| Windows  | ZIP (MinGW) |

## Build from source

### Requirements

- CMake ≥ 3.16
- Qt6 (Core, Widgets, Gui, Svg)
- GSL (GNU Scientific Library)
- A C++20 compiler

### Linux

```bash
sudo apt install libgsl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

### macOS

```bash
brew install gsl qt6
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

### Windows (MSYS2 MinGW64)

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-qt6-base mingw-w64-x86_64-qt6-svg \
          mingw-w64-x86_64-qt6-tools mingw-w64-x86_64-gsl mingw-w64-x86_64-cmake \
          mingw-w64-x86_64-ninja
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/mingw64
cmake --build build --parallel
```

## License

GPL-2.0-or-later
