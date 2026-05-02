# enginemath

A small, header-only C++17 math library for game development.

## What you get

`enginemath` is header-only. The main type right now is `enginemath::Vec2`.

In CMake, you link to the target `enginemath::enginemath`. Even though it’s header-only, this is still useful because it:

- Adds the correct include path (`#include <enginemath/...>`)
- Sets the required C++ standard (C++17)

## Use in code

```cpp
#include <enginemath/enginemath.hpp>

enginemath::Vec2 a{1.0f, 2.0f};
enginemath::Vec2 b{3.0f, 4.0f};
auto c = a + b;
```

## Use in CMake (pick ONE)

### Option A: Vendor it (recommended simplest)

Put this repo in your project, for example at `external/enginemath/`, then:

```cmake
add_subdirectory(external/enginemath)
target_link_libraries(your_target PRIVATE enginemath::enginemath)
```

### Option B: Install + `find_package`

Build and install enginemath somewhere:

```bash
cmake -S enginemath -B enginemath/build
cmake --build enginemath/build
cmake --install enginemath/build --prefix <install-dir>
```

Then, in your project:

```cmake
find_package(enginemath CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE enginemath::enginemath)
```

And configure your project with a prefix so CMake can find it:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=<install-dir>
```

## Testing

```bash
cmake -S . -B build -DENGINEMATH_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

## Examples

```bash
cmake -S . -B build -DENGINEMATH_BUILD_EXAMPLES=ON
cmake --build build
```
