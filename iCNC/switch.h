#define DEBUG 1


#if DEBUG

#define CyclingTime 0.02 //[s]

#else

#define CyclingTime 0.02 //[s]
#define HD_interval 1000*CyclingTime //[ms]
#define uvPerTick 0.0018  //[deg/tick]
#define wPerTick 0.0025 //[mm/tick]

#endif