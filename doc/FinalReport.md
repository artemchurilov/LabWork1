# Parallelization Performance Report: Image Processing Operations

This report details the performance improvements achieved through parallelization of image rotation and Gaussian filter operations using OpenMP.

## Test Environment
- **Processor**: Multi-core CPU
- **Parallelization Framework**: OpenMP
- **Optimization Flags**: `-O3 -fopenmp`
- **Test Suite**: Google Test Framework

## Performance Results Summary

| Test Case | Sequential Time (ms) | Parallel Time (ms) | Speedup Ratio | Time Reduction (ms) |
| --------- | -------------------- | ------------------ | ------------- | ------------------- |
| SpeedTest | 109                  | 58                 | 1.88          | 51                  |
| GaussTest | 2343                 | 981                | 2.39          | 1362                |
| FinalTest | 2375                 | 1025               | 2.32          | 1350                |

## Detailed Analysis

### 1. Image Rotation (SpeedTest)
- **Operation**: 90° clockwise/counter-clockwise rotation
- **Parallelization Approach**: 
  - Outer loop parallelization across image rows
  - Independent processing of each output row
- **Results**:
  - 1.88× speedup 
  - 51ms absolute time reduction

### 2. Gaussian Filter Application (GaussTest)
- **Operation**: 2D convolution with Gaussian kernel
- **Parallelization Approach**:
  - Row-based parallel processing
  - Kernel precomputation optimization
- **Results**:
  - 2.39× speedup
  - 1362ms absolute time reduction
### 3. Combined Operations (FinalTest)
- **Operation**: Rotation + Gaussian filter pipeline
- **Results**:
  - 2.32× speedup
  - 1350ms absolute time reduction
- **Analysis**:
  - Consistent speedup across combined operations
  - Parallelization benefits maintained through processing pipeline

## Conclusion
The parallelization of image processing operations using OpenMP has delivered substantial performance improvements:
- Average speedup of 2.2× across all operations
- Total execution time reduced by 2763ms across test cases
- Most significant gains in computationally intensive filters (2.39× speedup)