# Parallel-Processing
# All Commands you need to run c language with MPI and OpenMP program 

## ============ c compile and run ============
### compile
### gcc –o out testprog.c

### run
### ./out

## ============ mpi ==============
### compile
### mpicc –o greetings.out greetings.c
### run
### mpiexec -n 3 greetings.out

## ============ open mp =============
### to compile:
### gcc -fopenmp FILENAME.c

### set number of threads:
### export OMP_NUM_THREADS=4

### run
### ./a.out 

## ============ open mp with mpi ==============
### to complile
### mpicc -fopenmp FILENAME.c -lm

### set number of threads per process
### export OMP_NUM_THREADS=4

### to run
### mpiexec -n numberOfProcesses ./a.out 
