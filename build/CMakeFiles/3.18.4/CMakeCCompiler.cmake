<<<<<<< HEAD
set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc")
=======
set(CMAKE_C_COMPILER "/usr/bin/clang")
>>>>>>> 62dd8bd (more dev)
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_C_COMPILER_ID "Clang")
set(CMAKE_C_COMPILER_VERSION "11.0.1")
set(CMAKE_C_COMPILER_VERSION_INTERNAL "")
set(CMAKE_C_COMPILER_WRAPPER "")
set(CMAKE_C_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_C_COMPILE_FEATURES "c_std_90;c_function_prototypes;c_std_99;c_restrict;c_variadic_macros;c_std_11;c_static_assert")
set(CMAKE_C90_COMPILE_FEATURES "c_std_90;c_function_prototypes")
set(CMAKE_C99_COMPILE_FEATURES "c_std_99;c_restrict;c_variadic_macros")
set(CMAKE_C11_COMPILE_FEATURES "c_std_11;c_static_assert")

set(CMAKE_C_PLATFORM_ID "Linux")
set(CMAKE_C_SIMULATE_ID "")
set(CMAKE_C_COMPILER_FRONTEND_VARIANT "GNU")
set(CMAKE_C_SIMULATE_VERSION "")




<<<<<<< HEAD
set(CMAKE_AR "/usr/bin/aarch64-linux-gnu-ar")
set(CMAKE_C_COMPILER_AR "/usr/bin/aarch64-linux-gnu-gcc-ar-10")
set(CMAKE_RANLIB "/usr/bin/aarch64-linux-gnu-ranlib")
set(CMAKE_C_COMPILER_RANLIB "/usr/bin/aarch64-linux-gnu-gcc-ranlib-10")
set(CMAKE_LINKER "/usr/bin/aarch64-linux-gnu-ld")
=======
set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_C_COMPILER_AR "/usr/lib/llvm-11/bin/llvm-ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_C_COMPILER_RANLIB "/usr/lib/llvm-11/bin/llvm-ranlib")
set(CMAKE_LINKER "/usr/bin/ld")
>>>>>>> 62dd8bd (more dev)
set(CMAKE_MT "")
set(CMAKE_COMPILER_IS_GNUCC )
set(CMAKE_C_COMPILER_LOADED 1)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_C_COMPILER_ENV_VAR "CC")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_SOURCE_FILE_EXTENSIONS c;m)
set(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
set(CMAKE_C_SIZEOF_DATA_PTR "8")
set(CMAKE_C_COMPILER_ABI "ELF")
set(CMAKE_C_LIBRARY_ARCHITECTURE "aarch64-linux-gnu")

if(CMAKE_C_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_C_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
endif()

if(CMAKE_C_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "aarch64-linux-gnu")
endif()

set(CMAKE_C_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_C_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_C_CL_SHOWINCLUDES_PREFIX}")
endif()





<<<<<<< HEAD
set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES "/usr/lib/gcc/aarch64-linux-gnu/10/include;/usr/local/include;/usr/include/aarch64-linux-gnu;/usr/include")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "gcc;gcc_s;c;gcc;gcc_s")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/usr/lib/gcc/aarch64-linux-gnu/10;/usr/lib/aarch64-linux-gnu;/usr/lib;/lib/aarch64-linux-gnu;/lib")
=======
set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES "/usr/local/include;/usr/lib/llvm-11/lib/clang/11.0.1/include;/usr/include/aarch64-linux-gnu;/usr/include")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "gcc;gcc_s;c;gcc;gcc_s")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/usr/lib/gcc/aarch64-linux-gnu/10;/usr/lib/aarch64-linux-gnu;/lib/aarch64-linux-gnu;/usr/lib;/usr/lib/llvm-11/lib;/lib")
>>>>>>> 62dd8bd (more dev)
set(CMAKE_C_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
