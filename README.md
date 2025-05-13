# BlueLIB -> MyPersonal C/CPP Standard Library

- Uses [GoogleBenchmark](https://github.com/google/benchmark) for benchmarks.
- Uses [GoogleTest](https://github.com/google/googletest) for unit tests.

### Individually generating subprojects

- `bluelib` itself does not require building. Simply include it's headers.

- `bluecycle`
```pwsh
cmake -S project\bluecycle -B build\bluecycle -G Ninja -DCMAKE_C_COMPILER="@" -DCMAKE_CXX_COMPILER="@" -DCMAKE_RC_COMPILER="@" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build build\bluecycle
```

- `bluemetric`
```pwsh
cmake -S project\bluemetric -B build\bluemetric -G Ninja -DCMAKE_C_COMPILER="@" -DCMAKE_CXX_COMPILER="@" -DCMAKE_RC_COMPILER="@" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build build\bluemetric
```

- `blueunit`
```pwsh
cmake -S project\blueunit -B build\blueunit -G Ninja -DCMAKE_C_COMPILER="@" -DCMAKE_CXX_COMPILER="@" -DCMAKE_RC_COMPILER="@" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build build\blueunit
```
