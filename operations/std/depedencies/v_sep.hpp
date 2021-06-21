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

#ifdef __cpp_concepts  
#define MATRIX_TYPENAME Matrix
#else
#define MATRIX_TYPENAME typename
#endif

#ifdef __cpp_concepts  
#define RUNTIME_MATRIX_TYPENAME RuntimeMatrix
#else
#define RUNTIME_MATRIX_TYPENAME typename
#endif

#ifdef __cpp_concepts  
#define CONSTEXPR_MATRIX_TYPENAME ConstexprMatrix
#else
#define CONSTEXPR_MATRIX_TYPENAME typename
#endif