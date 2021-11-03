# YachtSimulator

[![CodeFactor](https://www.codefactor.io/repository/github/snowapril/YachtSimulator/badge)](https://www.codefactor.io/repository/github/snowapril/YachtSimulator)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/65172c3bc18b4398b0cd7c42954e2483)](https://www.codacy.com/gh/Snowapril/YachtSimulator/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Snowapril/YachtSimulator&amp;utm_campaign=Badge_Grade)
[![Ubuntu github action](https://github.com/Snowapril/YachtSimulator/actions/workflows/ubuntu.yml/badge.svg?branch=main)](https://github.com/snowapril/YachtSimulator/actions)
[![Window github action](https://github.com/Snowapril/YachtSimulator/actions/workflows/window.yml/badge.svg?branch=main)](https://github.com/snowapril/YachtSimulator/actions)
[![MacOS github action](https://github.com/Snowapril/YachtSimulator/actions/workflows/macos.yml/badge.svg?branch=main)](https://github.com/snowapril/YachtSimulator/actions)
[![codecov](https://codecov.io/gh/Snowapril/YachtSimulator/branch/main/graph/badge.svg?token=DEXQCY7L76)](https://codecov.io/gh/Snowapril/YachtSimulator)

## reference

[![Yacht Thumbnail](https://img.youtube.com/vi/I-DsOVUYxXw/0.jpg)](https://youtu.be/I-DsOVUYxXw?t=94 "Yacht Thumbnail")

## Install Conan package manager (if you dont have)
```bash
pip install conan
```

## How to Build
```bash
git clone https://github.com/snowapril/YachtSimulator
cd YachtSimulator
mkdir build
conan install . -if build --build missing -s build_type=Debug
cd build
cmake ..
```

## dependency
*   Vulkan[1.2.182.0]
*   physx[4.1]
*   vulkan-headers[1.2.162]
*   vulkan-loader[1.2.162.0]
*   glslang[>=11.5.0]
*   doctest[>=2.4.6]
*   glfw[>=3.3.4]
*   glm[>=0.9.9]
*   imgui[>=1.83]
*   tinygltf[>=2.5.0]
*   vk-bootstrap[>=0.3.1]
*   vulkan-memory-allocator[>=2.3.0]

## License
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright (c) 2021 Snowapril
*   [Jihong Shin](https://github.com/Snowapril)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
