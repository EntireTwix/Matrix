Opt for checking with `constexpr if` inside operation definitions, for how you want to deal with the object depending on type of `Matrix`, instead of function overloading. Attempt to avoid function overloading, as this opens up ambiguity for when called from C++17 rather then C++20.

Try to make operations as generic as possible, that being use the `*_MATRIX` macros for `constexpr_if`, and `*_MATRIX_TYPENAME` macros for and templating respectively, this is so that future implementations can still work with these operations. 

Use `static_assert` and `EXEC_IF_NOT_20` for type checking compile time, examples can be found in current operations, this is for C++17 as it lacks concepts.
