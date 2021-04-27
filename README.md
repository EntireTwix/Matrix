# Matrix
a collection of single header zero cost abstraction Matrix implementations

## Usage 
add to your project's CMake. 
```cmake
target_include_directories(${PROJECT_NAME} PUBLIC Matrix)
```
for CUDA add 
```cmake
target_include_directories(${PROJECT_NAME} PUBLIC Matrix)
add_subdirectory(Matrix/CUDA)
target_link_libraries(${PROJECT_NAME} matrix_cuda)
```

## sMat
STACK based Matrix

## hMat
HEAP based Matrix

## CUDA
Cuda operations for the different Matrix implementations
