/* Test for div32by32: rand */
#define NX 128
#define FNAME "t6"
#define MAXERROR 10

float x[128] = {
-3.900026e-001, 
7.487343e-001, 
-9.699810e-001, 
5.359008e-001, 
9.416899e-001, 
9.801652e-001, 
5.777234e-001, 
-1.226829e-001, 
-3.377393e-003, 
-5.720733e-001, 
2.869846e-001, 
-3.599288e-001, 
9.201972e-001, 
4.532635e-001, 
-1.760936e-001, 
4.891316e-001, 
-4.641055e-001, 
-1.201514e-001, 
8.667602e-001, 
3.666646e-001, 
-5.748803e-001, 
6.784765e-001, 
2.575692e-001, 
-7.324545e-001, 
-5.857345e-001, 
2.143979e-001, 
2.597757e-001, 
-2.590463e-001, 
1.502956e-001, 
-9.715035e-002, 
-9.122093e-001, 
-9.456297e-001, 
-3.746299e-001, 
-9.742748e-001, 
-2.320654e-001, 
3.662319e-001, 
-8.143151e-001, 
-9.293233e-001, 
2.247910e-001, 
2.170807e-001, 
-9.684804e-001, 
-9.672901e-001, 
-6.198508e-001, 
1.738369e-001, 
-8.848378e-001, 
-2.648639e-001, 
2.629023e-001, 
4.352688e-001, 
3.853388e-001, 
-8.318419e-001, 
-9.128970e-002, 
-1.163434e-001, 
-2.934991e-001, 
-6.927873e-001, 
3.512893e-001, 
3.984267e-001, 
4.550183e-001, 
-4.323124e-002, 
1.096840e-001, 
-7.579058e-001, 
-9.849212e-002, 
4.317659e-001, 
7.856832e-001, 
-4.537951e-001, 
-4.904614e-001, 
7.312069e-001, 
-5.352993e-001, 
6.097435e-001, 
8.167951e-001, 
-5.362114e-001, 
-5.213749e-001, 
-9.004910e-001, 
-8.432318e-001, 
2.816308e-001, 
-6.182269e-001, 
6.877390e-001, 
-6.521995e-001, 
-6.584144e-001, 
9.885910e-001, 
-1.204183e-001, 
-3.199041e-001, 
-3.715654e-001, 
-2.698432e-001, 
-2.135209e-001, 
1.830504e-001, 
-7.605068e-001, 
-9.237424e-001, 
-8.280409e-002, 
7.397347e-001, 
8.684730e-001, 
-4.711017e-001, 
-6.793993e-001, 
7.457105e-001, 
-5.242394e-001, 
2.916625e-001, 
9.337748e-001, 
3.298624e-001, 
7.407620e-001, 
-9.801454e-001, 
-7.259802e-001, 
6.375116e-001, 
-1.396679e-001, 
7.806434e-001, 
4.698164e-001, 
3.746472e-001, 
-3.077761e-001, 
-6.679305e-001, 
-6.887748e-001, 
-6.177674e-001, 
-1.550969e-001, 
7.119514e-001, 
-1.950003e-002, 
6.318695e-001, 
-7.846034e-002, 
-8.529124e-002, 
-9.862224e-002, 
-1.755619e-001, 
8.032196e-001, 
-9.888321e-001, 
-4.051886e-001, 
-9.016750e-001, 
3.863609e-001, 
3.002128e-001, 
9.659756e-001, 
1.053465e-001, 
-1.998530e-001, 
-6.024230e-001, 
2.504020e-001, 
}; 

DATA rtest[128] = {
-12780, 
24534, 
-31785, 
17560, 
30857, 
32118, 
18930, 
-4021, 
-111, 
-18746, 
9403, 
-11795, 
30153, 
14852, 
-5771, 
16027, 
-15208, 
-3938, 
28401, 
12014, 
-18838, 
22232, 
8440, 
-24002, 
-19194, 
7025, 
8512, 
-8489, 
4924, 
-3184, 
-29892, 
-30987, 
-12276, 
-31926, 
-7605, 
12000, 
-26684, 
-30453, 
7365, 
7113, 
-31736, 
-31697, 
-20312, 
5696, 
-28995, 
-8680, 
8614, 
14262, 
12626, 
-27258, 
-2992, 
-3813, 
-9618, 
-22702, 
11511, 
13055, 
14910, 
-1417, 
3594, 
-24836, 
-3228, 
14148, 
25745, 
-14870, 
-16072, 
23960, 
-17541, 
19980, 
26764, 
-17571, 
-17085, 
-29508, 
-27632, 
9228, 
-20259, 
22535, 
-21372, 
-21575, 
32394, 
-3946, 
-10483, 
-12176, 
-8843, 
-6997, 
5998, 
-24921, 
-30270, 
-2714, 
24239, 
28458, 
-15438, 
-22263, 
24435, 
-17179, 
9557, 
30597, 
10808, 
24273, 
-32118, 
-23789, 
20889, 
-4577, 
25580, 
15394, 
12276, 
-10086, 
-21887, 
-22570, 
-20244, 
-5083, 
23329, 
-639, 
20705, 
-2571, 
-2795, 
-3232, 
-5753, 
26319, 
-32403, 
-13278, 
-29547, 
12660, 
9837, 
31653, 
3451, 
-6549, 
-19741, 
8205, 
}; 

DATA r[128];
