#ifndef INTP_h
#define INTP_h
#include "..\..\SYS\INC\SYS.h"
#include "slope.h"
#include "circle.h"

#define doubleError 1e-6

#include <string>
#include <cmath>
using namespace std;

enum INTP_State
{
	INTP_NULL = 0, 
	INTP_IDLE, 
	INTP_INIT,
	INTP_PRE,
	INTP_EXE,
	INTP_CLOSE,
	INTP_FUNCTION,
	INTP_G04_WAIT,
	INTP_RESET,
	INTP_ERROR= 99
};


class INTP{

public:
    INTP();

	//
	//INTP main
	//
	void INTP_main();
	void INTP_initialization(); //initial in cnc init
	void INTP_reset();

	void INTP_stop();
	void INTP_input(int,double, double);


	//
	//INTP<>sys
	// 
	SYS* sys;
	void sys2INTP();
	void INTP2sys();
	bool INTP2sys_valid;


private:
	INTP_State INTP_state;

	void mk2wk(double mk[3],double wk[3]);
	void wk2mk(double wk[3],double mk[3],double mkold[3]);


	//
	//INTP data
	//
	double xyzStart[3];
	double xyzEnd[3];
	double xyzNew[3];
	double xyzOld[3];
	double xyzRelative[3];
	double deltalength;
	double ijkCenter[3];

	double uvwStart[3];
	double uvwEnd[3];
	double uvwNew[3];
	double uvwOld[3];
	double uvwRelative[3];

	double linearFactor[3];

	int g04Counter;
	double cyclingTime;
	//system cycle time 20ms
	double acceleration;
	//0.1G = 1m/s^2

	double g00Speed;
	//[mm/s]
	bool	m30ProgramEnd;

	double L1;
	double L2;

	//
	//INTP main
	//
	void idle(); //wait for Nc File
	void init(); //initialization
	void pre();
	void exe();
	void close();
	void function();
	void g04_wait();
	void reset();
	void error();

	//
	//intp function
	//
	void G00_motion();
	void G01_motion();
	void G02_motion();
	void G03_motion();
	void Function_cmd();
	void G04_dwell_time();
	void Go_reference_point();
	void M30_program_end();

	DEC2FIFO_BLOCK* intp_data;
	FIFO_DATA* fifo_data;

	SLOPE* slope;
	CIRCLE* circle;
	
};

#endif /* INTP_h */
