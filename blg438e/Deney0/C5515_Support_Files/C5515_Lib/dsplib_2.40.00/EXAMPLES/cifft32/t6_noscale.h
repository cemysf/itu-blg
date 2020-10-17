/*Test for cifft: rand*/
#define NX 256
#define FNAME "t256"
#define MAXERROR 520
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
-15479904, 9577438,
-47176498, 27719069,
-12567129, -272546,
-15801159, 28804405,
58763730, 25997579,
25274024, 43820254,
2180680, 41322368,
-9823538, 32164059,
2779074, -55517408,
25709120, -33232176,
75056227, 22992706,
10968498, -32711210,
28967673, -20358334,
22796432, 23044974,
18614577, 672728,
33609140, 35695223,
42257282, -44998166,
1481464, 16089700,
-10540711, -54827069,
7607046, -48407805,
33443432, 9857669,
40799227, -4709837,
-18210071, -37927942,
30609304, -9815948,
-5776098, -19546660,
-11272767, -30076457,
18169281, 8341668,
31276462, -49984809,
-19134504, 10519605,
-50284852, -67950557,
-1689319, 17749949,
18556432, 11524971,
2801724, 25440722,
52932905, -23217660,
-11098941, 22823005,
26680969, -35988505,
-26333523, 30191341,
-42383324, -71239160,
22369229, 9553359,
-46728983, -24606234,
-43639635, -25950180,
-20301175, 5094963,
-49947936, -11302580,
18741592, 32573324,
-9306466, -3598255,
-43408857, 34007144,
-29810938, -15949990,
-33102121, 2313516,
-2403089, 13374530,
-81020227, 37457693,
-23298487, 20818885,
-46687268, -9652754,
11061145, -46029075,
20083820, -23013926,
4938387, 11129493,
-3403728, -33477989,
-88415285, 9778369,
941316, 37147387,
-29404089, 8219447,
-8907945, 5535669,
-10991691, 13630862,
-38864337, 40801559,
19463356, 48601056,
8044867, -34397906,
-11773744, 6892685,
29933858, 19759607,
52958921, -8859163,
-37184147, 83728971,
-870102, 28720838,
-37266482, -28553266,
25193814, 27242133,
16782821, 23496213,
-17356395, 25499299,
-18763957, -57475695,
-25278923, 51573875,
31065119, -54017495,
-8338958, 37229514,
-5027612, -37235488,
-42225413, 12934207,
10489782, 32387771,
90270715, 27457499,
9720595, 1243151,
-47741347, -31071820,
8280755, -3755367,
-48176544, -26945205,
4985287, -55868329,
-56810088, -30245985,
24131961, 19741739,
38311539, 18594500,
52074340, -13930881,
46426923, 2073491,
-25437355, 15348857,
14853297, 6677799,
30571373, 8642206,
-36040333, 69817705,
6770006, -76411377,
25597442, 11375705,
-43224390, 9727225,
-31976093, 22221787,
26111203, -19490435,
-212435, 29788011,
17598857, 5767035,
45777365, 28481721,
16174556, 32338723,
-26409547, 44356208,
25232908, -2159057,
-5599829, 44192968,
-27388071, 7650992,
70265168, -47970663,
2689473, -5023132,
-31450404, -16943900,
21331854, -58020360,
56439494, -14008043,
19919057, -20634920,
26513131, 24185252,
3531733, 11387159,
-5321014, 29623365,
29222805, 9537687,
-6535025, -4883557,
2532503, -3008017,
-17670933, 9702629,
-23001039, 39085237,
-9005595, 27035791,
-39874274, -45487846,
8340926, 4056492,
3437706, -7455054,
-1375962, 19184154,
-75416348, -10071042,
-17138815, 38060015,
8363195, -6018202,
12388186, -49226590,
6012841, 46820034,
-1251024, 14791991,
-53798152, 18971141,
11387436, -23274112,
-4400154, 27980009,
16280268, -75073961,
20090740, 36830824,
-2886718, -54255,
10914990, -54176090,
-11245541, -41229230,
-10819600, 6959343,
-12830347, 7413583,
-31989820, -33758210,
7837497, -15202409,
41447933, 46957859,
-19412299, -15500939,
-16828802, 1097764,
24255275, 26802717,
1325349, 30092144,
51716734, 4626879,
-57077862, -54329539,
-34686602, -55250920,
-25625776, 14385016,
73028737, -24737362,
14482499, 18955776,
-14890289, -46444927,
1006494, 15444031,
-10592157, 21118611,
32811057, 12745561,
613874, -34001708,
27446278, -11651534,
23566657, 14828116,
-7760152, -53359610,
-3814789, -23535639,
4292971, -36158278,
-26823738, 33628912,
-8006489, 58031736,
-3001888, 23791173,
-34335048, -25095254,
31458552, 7679347,
-37974198, -7499302,
-23847205, -28631167,
-39241937, 11597311,
35750138, 3683085,
-22830226, -38018479,
-57907321, -22921822,
27286451, -9323308,
48381015, 21971102,
22557712, -41889153,
4652824, -20050083,
-28841173, -16166946,
-25241340, 32996495,
41259036, 59126958,
38612909, 47895652,
-20401934, 30593691,
27050171, 10966348,
7285770, 2336011,
-12531274, -50323684,
-27918309, -14033242,
9625636, -705878,
-61031875, 7664655,
-52782846, -33829437,
67634517, -22301019,
-2415316, 18729298,
88211562, -39880854,
-8164362, -26020841,
5814194, 9094663,
30977689, 51505236,
-5991244, -35308748,
-17505512, 20990263,
48048671, -26763890,
-29196297, -10520052,
27096606, -20206806,
-17134055, 42247054,
24948194, 28805952,
28450746, -70641873,
-27846847, -12111042,
17884325, 18574281,
34656642, -52223576,
-35300067, -6934551,
12150521, -14279677,
-1234354, 16568449,
-41192614, -29222810,
-9230786, 2678572,
-5383313, -17502634,
-36358738, -47441299,
-65572499, -12894739,
-30517328, -15365320,
-187191, -9780133,
-57830724, -10107401,
42381840, -53304363,
-20147201, 36718167,
-69253825, 44431667,
3721554, -4243952,
49916051, -24735113,
1778457, 7171214,
5435172, -13439528,
-901873, 2178949,
5824251, -58988544,
29600638, 56597872,
6116786, 10985728,
25343509, 24023858,
17046811, 53641723,
4425163, -69281208,
9398734, -24952137,
-32978891, 5911771,
-31678318, 17711332,
-438138, -18560722,
11889854, 10008611,
-30021446, -41158094,
27249924, -6364473,
3675464, -10123819,
91658762, 32110113,
13793528, -17896789,
-43851011, -30235288,
12878409, -29949060,
16760562, 9352174,
-17139120, -25025121,
7882676, 53803307,
-20059682, 19269291,
696953, 10759383,
14074164, -5079570,
39966810, 10595221,
25877656, 45087178,
-88725365, -75089180,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
-89016449, -378150624,
-450122665, -447389311,
875628018, -342750274,
1053402753, 1037260229,
495045068, 1151671832,
-257095461, 330261076,
-1393771207, -206917370,
-310906931, 336727643,
-525228710, 931809628,
-327855961, 162499807,
123932710, 633363929,
-163631410, -547260652,
-343672627, -18309810,
-788703778, -378841212,
-345730450, -144149923,
287722669, 137868045,
18093242, 246437104,
72567508, 523303498,
-833533276, 103770732,
287669679, -880725862,
-578143845, -173700633,
64678151, 74834945,
347843095, -843871342,
-380205108, -39582064,
-102226864, -377492943,
-94041058, -185226642,
-170125842, -108003763,
-1523944969, -1196782107,
-806593902, -773097177,
402016478, 252661431,
-151459413, -262146402,
-634900407, 15134194,
83645470, 860877755,
271981775, -341569505,
-514906557, -453733870,
235596134, 236240095,
-131475905, 363492590,
-446917581, -901355452,
-167861542, 1384919,
-762765530, 95116746,
-31310621, 699713386,
483108768, 359379835,
-864238339, 402069348,
161191153, -455997991,
-55942185, -574814710,
-382492019, -373824077,
486786405, -466484242,
-387319945, -831295966,
277634017, -57299616,
-37832840, 564557934,
486341156, 280268931,
-725130906, -937577774,
-818488685, 801621401,
-72328447, 257357278,
-454410844, -28464937,
335362235, 1356768731,
-194472036, -226021068,
463200828, -527089664,
407494140, 522636876,
-497605107, -58006328,
2591547, -259585488,
189693064, -721287678,
-637428072, 918556635,
178803861, -651074626,
-447696220, -509119021,
109229021, 416338927,
304336001, -494919447,
183018838, -168726439,
-933001027, 450101278,
-713557187, 98679373,
628396454, -4162507,
137524202, 14317802,
-275783285, 135159597,
-706422230, -234929163,
103371541, 967444207,
585360170, -124255476,
387603598, 479578125,
-1012779462, -79582345,
-8181567, 886409470,
-203524975, 534022167,
114841516, 1120880595,
766152635, 64199460,
-8961551, -577010926,
-152429348, -348196639,
-671101492, 766340403,
68189270, -848750502,
-66533305, 266333383,
87591570, 716726465,
-102324680, 3314548,
-357879637, -276120006,
137209422, 181364087,
-909635172, 560208922,
-426520653, 46805796,
7128826, -1054590544,
-336823553, -292547649,
-285295827, 309889087,
-385841572, 187350899,
309853002, -260200942,
164246677, -582871606,
5852101, 128637758,
-18703270, 1071366729,
466140424, 665788046,
783271210, -371075474,
351286686, 523247552,
-978720580, 310574830,
-349675353, -433089001,
287182735, 187287248,
286110210, -252119149,
-585825013, 474611446,
202803309, 131029701,
-466374486, 370832869,
71195127, -327244209,
209554183, 301353492,
520213068, -327899721,
-328740905, 438111157,
-895195871, 387280028,
257125735, -796760737,
1009980980, 18590901,
-39867965, 631304051,
79982497, 205633474,
366373545, 558778987,
132337002, 435469439,
-270704579, -265879515,
398591067, -711111203,
354302190, -273903113,
794307809, 146137560,
752199, -1211004009,
88922159, -121249490,
-40529231, 703081724,
-688905446, 8179716,
888996303, -200470089,
-482075626, -238809426,
246907288, -702312356,
-121377195, 193605301,
758082663, 612394847,
654564991, 490569070,
-145203561, 864769189,
-625861024, 953178009,
743803677, 322053429,
-347694673, 10868760,
959621907, -485010419,
-403132657, -372427084,
175904580, 713583362,
30773769, -1040389348,
-126220865, -35374980,
-62133761, 1041143904,
243043602, 67706398,
693233718, -362879355,
1051052082, 357480129,
-39784931, 698236894,
202107685, 580950765,
301427644, 23238690,
69187494, 279638281,
420045381, -723515676,
638236796, -122242248,
740959247, 839095439,
-603332584, -182285624,
202899409, 1245235844,
59002782, 321088242,
578687843, -706980764,
300288272, -973035013,
-268614232, -645688720,
215308560, -557313116,
-324946004, 154794077,
86756586, 116999801,
-729393598, 20359121,
-24685912, 369702165,
-79970438, 185917922,
1005866938, -366551068,
108318116, 147999740,
48912335, -260871661,
446003565, 397034034,
-317146568, 44465976,
443857328, -590245774,
319853099, 641347506,
348762491, -912613668,
1048190557, 49449393,
-1334171498, 288127307,
868477569, -88214341,
797338492, 85129130,
33361767, 703215284,
662131595, 227730336,
602201321, 479799140,
525100276, -561198954,
-741927617, -410980835,
-675887514, -478544451,
-600702438, -343622126,
238790215, -246031284,
196037378, -335883178,
-5951245, -522843204,
484653468, -149886965,
100018664, -136635239,
-57774772, -688656923,
-666896825, 721429347,
730650050, -430909904,
-52041933, 61673239,
204912243, 110955475,
940721553, -874823673,
644499795, 329202811,
387580037, -148407137,
-606585572, -879966619,
286188830, -798333543,
-32469224, 199709659,
661575484, 267913030,
33259465, -399379354,
543411494, 252964177,
23389812, -92624904,
60276608, -299126150,
229429247, -728018215,
-88221729, 810987536,
-1165096900, 573499463,
-229737593, 41838786,
-1292379318, -211998070,
635976549, 801480284,
-487728919, 115777625,
-433759281, 71377641,
-562434821, 163071152,
324226889, 227861767,
271712871, 504766812,
-166311848, 140793777,
-584162157, -142839695,
1556436, 181936891,
-389327545, 9881104,
-122669882, -465556542,
-376801194, -312623629,
-681821301, 521015744,
-79511876, -529934152,
-141786173, -125371749,
201841456, -431298195,
-610410543, -549699015,
-316977513, -276987413,
59525781, -425912184,
-300716801, -433381790,
1015676634, 267959767,
-309463450, 1120802644,
-181283959, -396509795,
1043724767, -415485055,
-759656328, -69220020,
424218579, 96845533,
431628660, 347653092,
200871671, -740925037,
-992556059, -11357546,
-74079902, 217406383,
45491681, -156077645,
-1020981275, -148821090,
-25157755, 977781390,
-393222943, 32173835,
573240034, -428298809,
104736420, 318023798,
-268173664, 114267346,
-762169801, 193951560,
76487443, 186841919,
-523789468, 94936329,
627173348, -372427560,
259266316, 188038169,
540505274, -45280974,
};
