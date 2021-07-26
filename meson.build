project('matrix', 'cpp', default_options : ['cpp_std=c++17'])

matrix_cuda_dep = []
if get_option('matrix_use_cuda').enabled()
	matrix_cuda_dep = subproject('matrix-cuda').get_variable('matrix_cuda_dep')
endif

matrix_inc = include_directories('.')
matrix_dep = declare_dependency(include_directories : matrix_inc, dependencies : matrix_cuda_dep)

if not meson.is_subproject()
	executable('handwritten_vs_generic', 'benchmarks/handwritten_vs_generic.cpp', dependencies : matrix_dep)
endif
