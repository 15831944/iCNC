#ifndef CNC_h
#define CNC_h

#define mode DEBUG

#include "..\..\SYS\INC\SYS.h"
#include "..\..\UTIL\INC\UTIL.h"
#include "..\..\MMI\INC\MMI.h"
#include "..\..\DEC\INC\DEC.h"
#include "..\..\INTP\INC\INTP.h"

enum CNC_State{
	CNC_NULL = 0,
	CNC_idle = 1,
	CNC_init = 2, 
	CNC_reset = 3,
	CNC_close = 100,
	CNC_emerg_stop = 98,
	CNC_error = 99
};

class CNC
{
public:

	//
	//CNC main
	//
	CNC();
	void CNC_initialization(); //initial in form load

	void CNC_main_nrt();
	void CNC_main_rt();

	void cncReset();


	//
	//block
	//
	MMI* mmi;
	DEC* dec;
	INTP* intp;
	SYS* sys;

	
private:
	//
	//cnc<>sys
	//
	void cnc2sys();
	void sys2cnc();
	bool cnc2sys_valid;
	//
	//state machine in cnc main
	//
	void idle();
	void init();
	void reset();
	void close();
	void emerg_stop();
	void error();

	CNC_State CNC_state; //CNC狀態
    
};



#endif
