# miniz-cpp

## 使用方式

直接将 `zip_file.hpp` 头文件拷贝到项目中即可。

经过测试，在 `Ubuntu 22.04 x86_64` 上使用 gcc 12 编译器、 windows11 中使用 visual studio2022 工具链以及`macOS 15.3`上使用 clang 19.1.6 没有问题。

## 使用示例

```cpp
#include <iostream>
#include "zip_file.hpp"

int main(){
    miniz_cpp::zip_file zip;

    // 将 test.txt 写入压缩包的根目录
    zip.write("./test.txt", "test.txt");

    // 将 1MB_file.dat 写入压缩包的根目录
    zip.write("./1MB_file.dat", "1MB_file.dat");

    zip.save("miniz_cpp.zip");
    
    std::clog << "Saved to test.zip" << std::endl;
}
```

更多示例参见 examples 文件夹。

## Build

```cpp
git clone https://github.com/Mq-b/miniz-cpp
cd miniz-cpp
mkdir build
cd .\build\
cmake ..
cmake --build .
```
