# Toolchain file for aarch64

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Set the compilers for cross-compiling
set(CMAKE_C_COMPILER /path/to/your/aarch64/compiler/gcc)
set(CMAKE_CXX_COMPILER /path/to/your/aarch64/compiler/g++)

# Set the root directory for the target environment
set(CMAKE_FIND_ROOT_PATH /path/to/your/aarch64/sysroot)

# Other settings...

# Add additional search paths for libraries if needed
# set(CMAKE_LIBRARY_PATH /path/to/your/aarch64/libraries)

# Add additional search paths for header files if needed
# set(CMAKE_INCLUDE_PATH /path/to/your/aarch64/includes)
