Opt for checking with `constexpr if` inside operation definitions, for how you want to deal with the object depending on type of `Matrix`, instead of function overloading. Attempt to avoid function overloading, as this opens up ambiguity for when called from C++17 rather then C++20.

make use of the metaprogramming type function `copy_fast` to accept args as whatever is fastest to pass as that type e.g `copy_fast_t<int>` -> `int` (as int is `trivially_copyable`)

Try to make operations as generic as possible, that being use the `*_MATRIX` macros for `constexpr_if` e.g `if constexpr(CONSTEXPR_MATRIX<T>){}`, and `*_MATRIX_TYPENAME` macros for templating e.g `template <CONSTEXPR_MATRIX_TYPENAME M>`; this is so that future implementations can still work with these operations. If C++20 these macros will be made concepts, otherwise will be `typename`, also they increase readability. 

Use `static_assert` and `EXEC_IF_NOT_20` for type checking compile time, examples can be found in current operations, this is for C++17 as it lacks concepts. Only do this if the function makes use of `CONSTEXPR_MATRIX` xor `RUNTIME_MATRIX`.

# Matrix as Template Arg convention
what `*` in `template <* T>` should be depending on what types you want to accept 
| `CONSTEXPR_MATRIX` | `RUNTIME_MATRIX` | non-matrix types |      what `*` should be       |
| :----------------: | :--------------: | :--------------: | :---------------------------: |
|         T          |        T         |        T         |         `typename T`          |
|         T          |        T         |        F         |      `MATRIX_TYPENAME M`      |
|         T          |        F         |        T         |         `typename T`          |
|         T          |        F         |        F         | `CONSTEXPR_MATRIX_TYPENAME M` |
|         F          |        T         |        T         |         `typename T`          |
|         F          |        T         |        F         |  `RUNTIME_MATRIX_TYPENAME M`  |
|         F          |        F         |        T         |         `typename T`          |

here is the convention for what checks should be enforced depending on what the type of Matrix is acceptable
| `MATRIX_TYPENAME` | `CONSTEXPR_MATRIX_TYPENAME` | `RUNTIME_MATRIX_TYPENAME` | Implementation Differs between Matrix categories | Convention |
| :---------------: | :-------------------------: | :-----------------------: | :----------------------------------------------: | :--------- |
|         T         |            `N/A`            |           `N/A`           |                        T                         | 1          |
|         T         |            `N/A`            |           `N/A`           |                        F                         | 2          |
|         F         |              T              |             F             |                      `N/A`                       | 3          |
|         F         |              F              |             T             |                      `N/A`                       | 4          |

1. ```cpp
   if constexpr (CONSTEXPR_MATRIX(M)) 
   {

   } 
   else if constexpr (RUNTIME_MATRIX(M)) 
   {

   } 
   else 
   { 
       static_assert(false, "Func: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX"); 
   }
   ```
2. ```cpp 
   EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Func: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
   ```
3. ```cpp
   EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M), "Func: M must be a CONSTEXPR_MATRIX"));
   ```
4. ```cpp
   EXEC_IF_NOT_20(static_assert(RUNTIME_MATRIX(M), "Func: M must be a RUNTIME_MATRIX"));
   ```