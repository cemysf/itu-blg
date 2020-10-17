


// Program 9.1 - Gauss method for solving linear systems Release 1.3 on 30.08.2006

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <mpi/mpi.h>


int ProcNum;            // Number of the available processes
int ProcRank;           // Rank of the current process
int *pParallelPivotPos; // Number of rows selected as the pivot ones
int *pProcPivotIter;    // Number of iterations, at which the processor
                        // rows were used as the pivot ones

int* pProcInd; // Number of the first row located on the processes
int* pProcNum; // Number of the linear system rows located on the processes

// Function for simple definition of matrix and vector elements
void DummyDataInitialization (double* pMatrix, double* pVector, int Size) {
  int i, j;  // Loop variables

  for (i=0; i<Size; i++) {
    pVector[i] = i+1;
    for (j=0; j<Size; j++) {
      if (j <= i)
        pMatrix[i*Size+j] = 1;
      else
        pMatrix[i*Size+j] = 0;
    }
  }
}

// Function for random definition of matrix and vector elements
void RandomDataInitialization (double* pMatrix, double* pVector, int Size) {
  int i, j;  // Loop variables
  srand(unsigned(clock()));
  for (i=0; i<Size; i++) {
    pVector[i] = rand()/double(1000);
    for (j=0; j<Size; j++) {
      if (j <= i)
            pMatrix[i*Size+j] = rand()/double(1000);
      else
            pMatrix[i*Size+j] = 0;
    }
  }
}

// Function for memory allocation and data initialization
void ProcessInitialization (double* &pMatrix, double* &pVector,
  double* &pResult, double* &pProcRows, double* &pProcVector,
  double* &pProcResult, int &Size, int &RowNum) {

  int RestRows; // Number of rows, that haven't been distributed yet
  int i;        // Loop variable

  if (ProcRank == 0) {
    do {
      printf("\nEnter the size of the matrix and the vector: ");
      scanf("%d", &Size);
      if (Size < ProcNum) {
        printf("Size must be greater than number of processes! \n");
      }
    }
    while (Size < ProcNum);
  }
  MPI_Bcast(&Size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  RestRows = Size;
  for (i=0; i<ProcRank; i++)
    RestRows = RestRows-RestRows/(ProcNum-i);
  RowNum = RestRows/(ProcNum-ProcRank);

  pProcRows = new double [RowNum*Size];
  pProcVector = new double [RowNum];
  pProcResult = new double [RowNum];

  pParallelPivotPos = new int [Size];
  pProcPivotIter = new int [RowNum];

  pProcInd = new int [ProcNum];
  pProcNum = new int [ProcNum];

  for (int i=0; i<RowNum; i++)
    pProcPivotIter[i] = -1;

  if (ProcRank == 0) {
    pMatrix = new double [Size*Size];
    pVector = new double [Size];
    pResult = new double [Size];
    // DummyDataInitialization (pMatrix, pVector, Size);
    RandomDataInitialization(pMatrix, pVector, Size);
  }
}

// Function for the data distribution among the processes
void DataDistribution(double* pMatrix, double* pProcRows, double* pVector,
  double* pProcVector, int Size, int RowNum) {

  int *pSendNum;     // Number of the elements sent to the process
  int *pSendInd;     // Index of the first data element sent
                     // to the process
  int RestRows=Size; // Number of rows, that have not been
                     // distributed yet
  int i;             // Loop variable

  // Alloc memory for temporary objects
  pSendInd = new int [ProcNum];
  pSendNum = new int [ProcNum];

  // Define the disposition of the matrix rows for the current process
  RowNum = (Size/ProcNum);
  pSendNum[0] = RowNum*Size;
  pSendInd[0] = 0;
  for (i=1; i<ProcNum; i++) {
    RestRows -= RowNum;
    RowNum = RestRows/(ProcNum-i);
    pSendNum[i] = RowNum*Size;
    pSendInd[i] = pSendInd[i-1]+pSendNum[i-1];
  }

  // Scatter the rows
  MPI_Scatterv(pMatrix, pSendNum, pSendInd, MPI_DOUBLE, pProcRows,
    pSendNum[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // Define the disposition of the matrix rows for current process
  RestRows = Size;
  pProcInd[0] = 0;
  pProcNum[0] = Size/ProcNum;
  for (i=1; i<ProcNum; i++) {
    RestRows -= pProcNum[i-1];
    pProcNum[i] = RestRows/(ProcNum-i);
    pProcInd[i] = pProcInd[i-1]+pProcNum[i-1];
  }

  MPI_Scatterv(pVector, pProcNum, pProcInd, MPI_DOUBLE, pProcVector,
    pProcNum[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // Free the memory
  delete [] pSendNum;
  delete [] pSendInd;
}

// Function for gathering the result vector
void ResultCollection(double* pProcResult, double* pResult) {
  //Gather the whole result vector on every processor
  MPI_Gatherv(pProcResult, pProcNum[ProcRank], MPI_DOUBLE, pResult,
    pProcNum, pProcInd, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

// Function for formatted matrix output
void PrintMatrix (double* pMatrix, int RowCount, int ColCount) {
  int i, j; // Loop variables
  for (i=0; i<RowCount; i++) {
    for (j=0; j<ColCount; j++)
      printf("%7.4f ", pMatrix[i*ColCount+j]);
    printf("\n");
  }
}

// Function for formatted vector output
void PrintVector (double* pVector, int Size) {
  int i;
  for (i=0; i<Size; i++)
    printf("%7.4f ", pVector[i]);
}

// Function for formatted result vector output
void PrintResultVector (double* pResult, int Size) {
  int i;
  for (i=0; i<Size; i++)
      printf("%7.4f ", pResult[pParallelPivotPos[i]]);
}


// Fuction for the column elimination
void ParallelEliminateColumns(double* pProcRows, double* pProcVector, double* pPivotRow, int Size, int RowNum, int Iter) {
  double multiplier;
  for (int i=0; i<RowNum; i++) {
    if (pProcPivotIter[i] == -1) {
      multiplier = pProcRows[i*Size+Iter] / pPivotRow[Iter];
      for (int j=Iter; j<Size; j++) {
        pProcRows[i*Size + j] -= pPivotRow[j]*multiplier;
      }
      pProcVector[i] -= pPivotRow[Size]*multiplier;
    }
  }
}


// Function for the Gausian elimination
void ParallelGaussianElimination (double* pProcRows, double* pProcVector, int Size, int RowNum) {
  double MaxValue;   // Value of the pivot element of thе process
  int    PivotPos;   // Position of the pivot row in the process stripe
  // Structure for the pivot row selection
  struct { double MaxValue; int ProcRank; } ProcPivot, Pivot;

  // pPivotRow is used for storing the pivot row and the corresponding
  // element of the vector b
  double* pPivotRow = new double [Size+1];

  // The iterations of the Gaussian elimination stage
  for (int i=0; i<Size; i++) {

    // Calculating the local pivot row
    double MaxValue = 0;
    for (int j=0; j<RowNum; j++) {
      if ((pProcPivotIter[j] == -1) && (MaxValue < fabs(pProcRows[j*Size+i]))) {
        MaxValue = fabs(pProcRows[j*Size+i]);
        PivotPos = j;
      }
    }
    ProcPivot.MaxValue = MaxValue;
    ProcPivot.ProcRank = ProcRank;

    // Finding the pivot process (process with the maximum value of MaxValue)
    MPI_Allreduce(&ProcPivot, &Pivot, 1, MPI_DOUBLE_INT, MPI_MAXLOC,
                  MPI_COMM_WORLD);

    // Broadcasting the pivot row
    if ( ProcRank == Pivot.ProcRank ){
      pProcPivotIter[PivotPos]= i; //iteration number
      pParallelPivotPos[i]= pProcInd[ProcRank] + PivotPos;
    }
    MPI_Bcast(&pParallelPivotPos[i], 1, MPI_INT, Pivot.ProcRank, MPI_COMM_WORLD);

    if ( ProcRank == Pivot.ProcRank ){
      // Fill the pivot row
      for (int j=0; j<Size; j++) {
        pPivotRow[j] = pProcRows[PivotPos*Size + j];
      }
      pPivotRow[Size] = pProcVector[PivotPos];
    }
    MPI_Bcast(pPivotRow, Size+1, MPI_DOUBLE, Pivot.ProcRank, MPI_COMM_WORLD);

    ParallelEliminateColumns(pProcRows, pProcVector, pPivotRow, Size, RowNum, i);
  }
}

// Function for finding the pivot row of the back substitution
void FindBackPivotRow(int RowIndex, int Size, int &IterProcRank, int &IterPivotPos) {
  for (int i=0; i<ProcNum-1; i++) {
    if ((pProcInd[i]<=RowIndex) && (RowIndex<pProcInd[i+1]))
      IterProcRank = i;
  }
  if (RowIndex >= pProcInd[ProcNum-1])
    IterProcRank = ProcNum-1;
  IterPivotPos = RowIndex - pProcInd[IterProcRank];
}

// Function for the back substitution
void ParallelBackSubstitution (double* pProcRows, double* pProcVector,
  double* pProcResult, int Size, int RowNum) {
  int IterProcRank;    // Rank of the process with the current pivot row
  int IterPivotPos;    // Position of the pivot row of the process
  double IterResult;   // Calculated value of the current unknown
  double val;

  // Iterations of the back substitution stage
  for (int i=Size-1; i>=0; i--) {

    // Calculating the rank of the process, which holds the pivot row
    FindBackPivotRow(pParallelPivotPos[i], Size, IterProcRank, IterPivotPos);

    // Calculating the unknown
    if (ProcRank == IterProcRank) {
      IterResult = pProcVector[IterPivotPos]/pProcRows[IterPivotPos*Size+i];
      pProcResult[IterPivotPos] = IterResult;
    }
    // Broadcasting the value of the current unknown
    MPI_Bcast(&IterResult, 1, MPI_DOUBLE, IterProcRank, MPI_COMM_WORLD);

    // Updating the values of the vector b
    for (int j=0; j<RowNum; j++)
      if ( pProcPivotIter[j] < i ) {
        val = pProcRows[j*Size + i] * IterResult;
        pProcVector[j]=pProcVector[j] - val;
    }
  }
}

void TestDistribution(double* pMatrix, double* pVector, double* pProcRows,
  double* pProcVector, int Size, int RowNum) {

  if (ProcRank == 0) {
    printf("Initial Matrix: \n");
    PrintMatrix(pMatrix, Size, Size);
    printf("Initial Vector: \n");
    PrintVector(pVector, Size);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  for (int i=0; i<ProcNum; i++) {
    if (ProcRank == i) {
      printf("\nProcRank = %d \n", ProcRank);
      printf(" Matrix Stripe:\n");
      PrintMatrix(pProcRows, RowNum, Size);
      printf(" Vector: \n");
      PrintVector(pProcVector, RowNum);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
}


// Function for the execution of the parallel Gauss algorithm
void ParallelResultCalculation(double* pProcRows, double* pProcVector,
  double* pProcResult, int Size, int RowNum) {
  ParallelGaussianElimination (pProcRows, pProcVector, Size, RowNum);
  ParallelBackSubstitution (pProcRows, pProcVector, pProcResult, Size, RowNum);
}

// Function for computational process termination
void ProcessTermination (double* pMatrix, double* pVector, double* pResult,
  double* pProcRows, double* pProcVector, double* pProcResult) {
  if (ProcRank == 0) {
    delete [] pMatrix;
    delete [] pVector;
    delete [] pResult;
  }
  delete [] pProcRows;
  delete [] pProcVector;
  delete [] pProcResult;

  delete [] pParallelPivotPos;
  delete [] pProcPivotIter;

  delete [] pProcInd;
  delete [] pProcNum;
}


// Function for testing the result
void TestResult(double* pMatrix, double* pVector, double* pResult, int Size) {
  /* Buffer for storing the vector, that is a result of multiplication
     of the linear system matrix by the vector of unknowns */
  double* pRightPartVector;
  // Flag, that shows wheather the right parts vectors are identical or not
  int equal = 0;
  double Accuracy = 1.e-6; // Comparison accuracy

  if (ProcRank == 0) {
    pRightPartVector = new double [Size];
    for (int i=0; i<Size; i++) {
      pRightPartVector[i] = 0;
      for (int j=0; j<Size; j++) {
        pRightPartVector[i] += pMatrix[i*Size+j]*pResult[pParallelPivotPos[j]];
      }
    }

    for (int i=0; i<Size; i++) {
      if (fabs(pRightPartVector[i]-pVector[i]) > Accuracy))
        equal = 1;
    }
    if (equal == 1)
      printf("The result of the parallel Gauss algorithm is NOT correct. Check your code.");
    else
      printf("The result of the parallel Gauss algorithm is correct.");
    delete [] pRightPartVector;
  }
}



void main(int argc, char* argv[]) {
  double* pMatrix;        // Matrix of the linear system
  double* pVector;        // Right parts of the linear system
  double* pResult;        // Result vector
  double *pProcRows;      // Rows of the matrix A
  double *pProcVector;    // Block of the vector b
  double *pProcResult;    // Block of the vector x
  int     Size;           // Size of the matrix and vectors
  int     RowNum;         // Number of  the matrix rows
  double start, finish, duration;

  setvbuf(stdout, 0, _IONBF, 0);

  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &ProcRank );
  MPI_Comm_size ( MPI_COMM_WORLD, &ProcNum );

  if (ProcRank == 0)
      printf("Parallel Gauss algorithm for solving linear systems\n");

  // Memory allocation and data initialization
  ProcessInitialization(pMatrix, pVector, pResult,
    pProcRows, pProcVector, pProcResult, Size, RowNum);

  // The execution of the parallel Gauss algorithm

  DataDistribution(pMatrix, pProcRows, pVector, pProcVector, Size, RowNum);

  ParallelResultCalculation(pProcRows, pProcVector, pProcResult, Size, RowNum);

  ResultCollection(pProcResult, pResult);

  TestResult(pMatrix, pVector, pResult, Size);

  // Computational process termination
  ProcessTermination(pMatrix, pVector, pResult, pProcRows, pProcVector, pProcResult);
  MPI_Finalize();
}

