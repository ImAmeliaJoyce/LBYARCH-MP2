# Single-Precision A•X Plus Y (SAXPY) Function
*Single-Precision A·X Plus Y* is a standard Basic Linear Algebra Subroutines (BLAS) library function. SAXPY combines scalar multiplication and vector addition, which takes a scalar value A, two vectors of 32-bit floats X and Y with N elements each as inputs. It multiplies each element X[i] by A and adds the result to Y[I]. 

The C kernel implementation:
```
void saxpyC(int n, float a, float* x, float* y, float* z) {
	for (int i = 0; i < n; i++) {
		z[i] = a * x[i] + y[i];
	}
}

...

// Calling the saxpyC function in main
saxpyC(vectorN, scalarA, x, y, z);
```

The x86-64 kernel implementation:
```
// Declare saxpyASM function
extern float saxpyASM(float scalarA, float x, float y);

...

section .text
bits 64
default rel

global saxpyASM

saxpyASM:
	vmulss xmm0, xmm1, xmm0
	vaddss xmm0, xmm0, xmm2
	ret

...

// Calling the saxpyASM function in main
for (int i = 0; i < vectorN; i++) {
	asmZ[i] = saxpyASM(scalarA, x[i], y[I]);
}
```

## LBYARCH S17 Group 3
- Amelia Joyce Abenoja
- Lance Desmond Labarrete

## Comparative Results
**Release Mode Average Execution Time (in seconds)**
| Kernels        | 2^(20)           | 2^(24)           | 2^(27)           |
| -------------- |:----------------:|:----------------:|:----------------:|
| C              | 0.002500         | 0.039167         | 0.284233         |
| Assembly       | 0.002967         | 0.048867         | 0.356100         |

**Debug Mode Average Execution Time (in seconds)**
| Kernels        | 2^(20)           | 2^(24)           | 2^(27)           |
| -------------- |:----------------:|:----------------:|:----------------:|
| C              | 0.006167         | 0.084967         | 0.766467         |
| Assembly       | 0.006467         | 0.086033         | 0.686167         |

### Execution Time
The results showcase the average execution times of kernels written in C versus assembly language, both in release and debug modes, across varying input sizes. In release mode, where optimizations are applied, both C and assembly implementations demonstrate significantly lower execution times than their debug mode counterparts. This is expected as release mode involves compiler optimizations that generate more efficient code. Across all tested input sizes 2^(20), 2^(24), and 2^(27), the assembly implementation consistently outperforms the C implementation in release mode. The difference in execution times between the two languages appears to widen with larger input sizes, indicating that the assembly implementation scales more efficiently.

In debug mode, both C and assembly implementations exhibit higher execution times. However, even in this scenario, the assembly implementation maintains a performance advantage over the C implementation across all tested input sizes. Although the performance gap between the two languages narrows in debug mode compared to release mode, the assembly implementation still demonstrates superior efficiency. These results suggest that while both C and assembly implementations suffer from increased execution times in debug mode, the inherent optimizations and low-level control offered by assembly language continue to provide a performance edge over C, especially evident in scenarios involving computational tasks and larger data sets.


## Analysis Results
### Performance of the Kernels
Both versions accomplish the SAXPY operation accurately. However, due to its optimized use of SIMD instructions, the assembly version demonstrates superior performance, especially when dealing with large vectors. In terms of performance, the assembly version of the SAXPY kernel exhibits notable advantages over its C counterpart. By directly leveraging SIMD (Single Instruction, Multiple Data) instructions and registers, the assembly code can execute the SAXPY operation in a highly parallelized manner. SIMD instructions allow for simultaneous processing of multiple data elements, effectively exploiting the inherent parallelism present in the operation. This parallelization enables the assembly version to achieve significantly faster execution times compared to the C version, particularly when dealing with large vectors. Additionally, the assembly code benefits from low-level hardware features, enabling precise optimization tailored to the specific characteristics of the target processor architecture.

On the other hand, The C version, while functional, may suffer from performance limitations inherent to scalar processing. While the C version of the kernel provides a more straightforward implementation, it lacks performance optimization resources. The scalar processing nature of C operations introduces overhead in handling each data element individually, leading to  slower execution times, especially when confronted with large-scale computations. Despite its simplicity, the C version may need help to match the performance levels achieved by the assembly version due to its reliance on scalar instructions. 

## Program Outputs
The following screenshots are the compilation of the program results in two modes: `Release` and `Debug`. The output displays the following information:
- **Vector Table Results** showcases the first ten output results of implementing the SAXPY function in C and x86-64 Assembly Language along with the Correctness Vector column to validate the correctness of the outputs. 
- The **Set Up** section displays the setup used in the program, which includes the mode of execution, vector size, 2^20, 2^24, and 2^27, respectively, and randomly generated scale values ranging from 0.00 to 100.00.
- The **Correctness Result** section shows the output validation of the SAXPY function in C and x86-64 implementation. The C kernel is `PASSED` if all the results are identical in all iterations and `FAILED` otherwise. The x86-64 kernel is `PASSED` if it has the exact results in all iterations with the correctness vector; otherwise, it is `FAILED`.  
- The **Time Measurement Results** section reveals the average time execution in seconds of the SAXPY function for each kernel computed by averaging the timing of the function only in 30 iterations. 

### Release Mode
---
**Vector Size = 2^(20) :**
![release - 2^20](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/6ab0bf04-f7aa-4cf4-a409-4637253d0656)

**Vector Size = 2^(24) :**
![release - 2^24](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/54b3552e-beb6-4ca6-a53b-09d244c73271)

**Vector Size = 2^(27) :**
![release - 2^27](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/9a9dfc18-4afb-4542-bd86-bf49072fdf9b)


### Debug Mode
---
**Vector Size = 2^(20) :**
![debug - 2^20](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/df6764ad-70af-41c7-947a-0d653524ac0f)

**Vector Size = 2^(24) :**
![debug - 2^24](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/9166a581-82b9-4460-a845-cc461c9aba52)

**Vector Size = 2^(27) :**
![debug - 2^27](https://github.com/ImAmeliaJoyce/LBYARCH-MP2/assets/97102877/348b6d4b-2862-4527-aa28-c0c16411c36e)
