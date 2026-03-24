# EasyWin32 - C++ wrapper for Win32 window management

[![License](https://img.shields.io/github/license/WenchaoHuang/EasyWin32)](LICENSE)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/y/WenchaoHuang/EasyWin32/main)](https://github.com/WenchaoHuang/EasyWin32/commits/main)

> [!WARNING]
**This project is in development.** The API is unstable, features may be added or removed, and breaking changes are likely to occur frequently and without notice as the design is refined.

## Overview
EasyWin32 is a lightweight, header-only C++ wrapper for Win32 window management, designed for scenarios where cross-platform compatibility is not required. It is ideal for rapid prototyping and quick result previews during the development stage.

## Key Features:
 - Header-only and lightweight: EasyWin32 requires no additional libraries or dependencies, making integration simple and efficient.
 - Fine-grained event handling: Offers more detailed control over Win32 events than libraries like GLFW, allowing developers to handle window messages with greater precision.
 - High code readability: The API is developer-friendly and easy to understand, making maintenance and extension straightforward.

## Installation

### Prerequisites
- CMake (version 3.10 or above)
- C++17 compatible compiler

### Build Instructions

```bash
git clone https://github.com/WenchaoHuang/EasyWin32.git
cd EasyWin32
mkdir build
cd build
cmake .. -DEZWIN32_BUILD_EXAMPLES=ON -DEZWIN32_BUILD_TESTS=ON
cmake --build .
```

## Example:
```cpp
#define EZWIN32_IMPLEMENTATION
#include "easywin32.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    EzWindow window;
    window.open("EasyWin32", 900, 700, EzStyle::OverlappedWindow);
    window.centerToScreen();
    window.show();

    // Setup callbacks
    window.onKeyboardPress = [&](EzKey key, EzKeyAction action)
    {
        if ((key == EzKey::Escape) && (action == EzKeyAction::Press))
        {
            window.close();
        }

        return 0;
    };

    // Main loop
    while (window.isOpen())
    {
        if (!window.processEvents())
        {
            std::this_thread::sleep_for(1ms);
        }
    }

    return 0;
}

```

## License
EasyWin32 is distributed under the terms of the [MIT License](LICENSE).
