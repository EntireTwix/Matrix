project('matrix-cuda', 'cuda')

# cuda code additionally requires `cuda` dependency
cuda_dep = dependency('cuda', modules : ['cublas'])

# add sources as you see fit
matrix_cuda_src = []
matrix_cuda_inc = include_directories('.')
matrix_cuda_lib = library('matrix-cuda', matrix_cuda_src, dependencies : cuda_dep)

matrix_cuda_dep = declare_dependency(link_with : matrix_cuda_lib, include_directories : matrix_cuda_inc, dependencies : cuda_dep)
