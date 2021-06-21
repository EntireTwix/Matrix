#pragma once

#ifdef __cpp_concepts 
#define EXEC_IF_20(expr) expr
#else
#define EXEC_IF_20(expr) 
#endif

#ifdef __cpp_concepts 
#define EXEC_IF_20_ELSE(expr, expr2) expr
#else
#define EXEC_IF_20_ELSE(expr, expr2) expr2
#endif

#define MATRIX_TYPENAME EXEC_IF_20_ELSE(Matrix, typename)
#define RUNTIME_MATRIX_TYPENAME EXEC_IF_20_ELSE(RuntimeMatrix, typename)
#define CONSTEXPR_MATRIX_TYPENAME EXEC_IF_20_ELSE(ConstexprMatrix, typename)