/* Test for div32by32: rand */
#define NX 16
#define FNAME "t3"
#define MAXERROR 10

float x[16] = {
-1.105933e-001, 
2.308647e-001, 
5.838741e-001, 
8.436259e-001, 
4.764145e-001, 
-6.474677e-001, 
-1.885876e-001, 
8.709394e-001, 
8.338089e-001, 
-1.794596e-001, 
7.872991e-001, 
-8.842174e-001, 
-2.942637e-001, 
6.263330e-001, 
-9.802774e-001, 
-7.222182e-001, 
}; 

DATA rtest[16] = {
-3624, 
7564, 
19132, 
27643, 
15611, 
-21217, 
-6180, 
28538, 
27322, 
-5881, 
25798, 
-28975, 
-9643, 
20523, 
-32122, 
-23666, 
}; 

DATA r[16];
