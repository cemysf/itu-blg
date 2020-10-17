/*Test for cfft: rand*/
#define NX 64
#define FNAME "t64"
#define MAXERROR 64
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
-34263829, -21968344,
-13477699, -36260995,
5827253, -1601582,
-3896290, 12728690,
35705914, -11085077,
-8233798, -16773802,
-50920164, -1207242,
326624, -5863984,
2394876, -32120486,
10621179, 43370711,
16771366, 14794473,
42885388, 42981246,
-18381660, -16701041,
8751278, -37537901,
-442136, 27100224,
-19470429, 1382428,
71682616, -25374150,
-8644196, -2990678,
-47295928, -67405832,
59394730, 36370254,
10923511, -32923292,
-37548737, -23101845,
20815497, 44945473,
42606809, -30509138,
-30066197, -13853207,
4535735, -16984018,
-4665409, 54349717,
-39037068, 2714577,
39719037, -36274236,
-517734, -37732556,
17992514, 58239634,
-24039356, 65010323,
-21996923, 54863785,
10548264, -42142359,
3584086, -7165130,
62015845, -6675052,
-9231015, 10317960,
74240995, -19204056,
50617725, -32804436,
-65266008, -14992436,
-56389658, 36308979,
-19244612, 79612854,
-6234968, 7693640,
299779, -8946388,
28083378, 23544211,
-24235382, -16360822,
-24209203, 62494449,
-6750514, 37139760,
-686663, -41190271,
9357996, -22477614,
35510481, 44994126,
20859894, 13021915,
-58740902, 13188869,
23399101, -57288608,
27228947, 7645667,
21352193, 23006021,
43959002, -21367131,
10975571, -33641860,
-22581903, -6228396,
-5010599, -35367469,
-82175400, -2400467,
15880830, 9368344,
3924045, 46079474,
-19834154, 6034464,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
69303925, 42780367,
-264000746, -251189192,
55546608, 35447248,
-121082753, 56416416,
-295997027, -209145408,
1604959, 55292795,
-170122340, 44016726,
287449880, -221758781,
-224173560, 72919846,
168727482, -331599310,
-425938396, 321951684,
-391540237, -111929685,
-535321440, -167443531,
552743886, 47445503,
-238581293, 108915445,
-25074285, 156286384,
-473566532, -358930104,
127919586, -259294704,
-36101229, -314590226,
48200572, 102774954,
100345586, 93623603,
-317318964, -523432387,
-279738848, 275909971,
-3899692, 177242702,
483495763, -326082235,
243108422, -77143389,
-357881955, 95386470,
93071709, 547750880,
150995695, -91368255,
-36945024, 121374807,
169769086, 206911057,
101081726, -81259074,
-176387345, 227000355,
-314489494, -165955922,
-257664038, 127563806,
224999049, -212929528,
-14688213, 193396984,
-63895647, -287618723,
191605200, 51013337,
-83966524, -498377935,
-64490172, 30529144,
393497616, 49487166,
638096, 133544045,
-653989616, 461621947,
281535525, -10677104,
157184405, 96450912,
-422145705, 128689419,
254502433, 143331381,
262794300, -378986210,
-197795593, -378100664,
131823790, 388216965,
-573115991, -289813960,
475008337, -134072330,
-192984243, -247778460,
-288619524, -527210249,
294433725, -129039439,
-79910587, 173162237,
278121413, -123201711,
186794133, 551259600,
52917412, -73778920,
276818960, 304588962,
-478690617, -111959250,
-295490865, -35667506,
46684161, -97942941,
};
