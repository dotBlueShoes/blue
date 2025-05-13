1. See what tests other then unit can be applied.
2. Expirement with wave implementation (rename, asm, simd).
3. Add information on how to build the all-build target on github.
4. Restructure CMake files and Quail files to enable all-build + submodule build:

```PWSH
-------------------------------------------------------
RELEASE
-------------------------------------------------------

cmake -S project\bluecycle -B build\bluecycle\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\bluecycle\x64-win-release

cmake -S project\bluemetric -B build\bluemetric\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\bluemetric\x64-win-release

cmake -S project\blueunit -B build\blueunit\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\blueunit\x64-win-release

-------------------------------------------------------
DEBUG
-------------------------------------------------------

cmake -S project\bluecycle -B build\bluecycle\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\bluecycle\x64-win-debug

cmake -S project\bluemetric -B build\bluemetric\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\bluemetric\x64-win-debug

cmake -S project\blueunit -B build\blueunit\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\blueunit\x64-win-debug
```
