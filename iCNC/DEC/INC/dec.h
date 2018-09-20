#ifndef DEC_h
#define DEC_h

#include "..\..\SYS\INC\SYS.h"

#include <string>
using namespace std;

enum DEC_State
{
	DEC_NULL = 0,
	DEC_idle,
	DEC_init,
	DEC_read,
	DEC_pre,
	DEC_line_loop,
	DEC_line_end,
	DEC_write_block,
	DEC_dec2fifo,
	DEC_waitM30,
	DEC_error= 99
};




class DEC{

public:
    DEC();

	//
	//dec main
	//
	void DEC_main();
	void DEC_initialization(); //initial in cnc init
	void DEC_reset();


	//
	//dec<>sys
	//
	SYS* sys;
	void sys2dec();
	void dec2sys();
	bool dec2sys_valid;


private:
	//
	//dec main
	//
	void idle(); //wait for Nc File
	void init(); //initialization
	void readNcText();
	void pre();
	void line_loop();
	void line_end();
	void write_block();
	void dec2fifo();
	void m30_wait();
	void error();

	//
	//string dealing
	//
	void DeleteComment();
	void NcGetLine(); //copy the first line in A into B
	void FunctionGenerator();

	 /*==Function Generator==*/
    void nFunction(string);
    void gFunction(string);
    void fFunction(string);
    void mFunction(string);
    void xyzFunction(string);
    void uvwFunction(string);
    void ijkFunction(string);
	void rFunction(string);

	DEC2FIFO_BLOCK* dec_data;
	FIFO_DATA* fifo_data;

	 /*==DEC Data==*/
	DEC_State DEC_state;
	string NcLoc;
	string NcCode; 
    string linedata;

	//
	//m30 end
	//
	bool m30_End;

	//
	//mark
	//
	void clearMark();

	bool ncCommandMarker; 
	bool relAbsMarker;// G90: false; G91:true
	bool m00Marker;
	bool m30Marker;
	bool m01Marker;
	bool g60Marker; 
	bool xyzMarker[3];
	bool uvwMarker[3];
	bool ijkMarker[3];
	bool nMarker;
	bool fMarker;
	bool rMarker;
};

#endif
