#include "StdAfx.h"
#include "..\INC\SYS.h"

SYS::SYS()
{
	fifo = new FIFO;
}

void SYS::init()
{
	fifo->init();

	cnc_mode=MEM;

	error_valid = false;
	error_code = 0;
	error_block = 0;

	sys2cnc_valid = false;
	sys2mmi_valid = false;
	sys2dec_valid = false;
	sys2intp_valid = false;

	//
	//intp<>dec
	//
	 m30Msg = false;

	//
	//form2mmi
	//

	//ID 1~2
	 OpenFile = false;
	 UVW = false;

	//ID 3~8
	 X_p = false; //plus
	 X_m = false; //minus
	 Y_p = false;
	 Y_m = false;
	 Z_p = false;
	 Z_m = false;

	//ID 9~11
	 speed_1 = false;
	 speed_10 = false;
	 speed_100 = false;

	//ID 12~14
	 teach_start = false;
	 record = false;
	 teach_end = false;

	//ID 15~17
	 M01 = false;
	 FH = false;
	 SB = false;

	//ID 18~19
	 start = false;
	 reset = false;

	//ID 26
	 emerg_stop = false;

	//ID 27~29
	 para = false;
	 simu = false;
	 diag = false;

	//ID 30~31
	string NcLoc = "";
	string NcCode = "";

	//ID 32
	feedOverride=100;


	
	//
	//mmi2form
	//
	 M00 = false;
	 M30 = false;
	 PGM = false;
	 ERR = false;
	 HX = false;
	 INX = false;
	 HY = false;
	 INY = false;
	 HZ = false;
	 INZ = false;
	 PX = false;
	 NX = false;
	 PY = false;
	 NY = false;
	 PZ = false;
	 NZ = false;

}

void SYS::SYS_reset()
{
	errorReset();
	delete fifo;
	fifo = new FIFO;
	fifo->init();

	sys2cnc_valid = false;
	sys2mmi_valid = false;
	sys2dec_valid = false;
	sys2intp_valid = false;

	//
	//intp<>dec
	//
	 m30Msg = false;

	//
	//form2mmi
	//

	//ID 1~2
	 OpenFile = false;
	 UVW = false;

	//ID 3~8
	 X_p = false; //plus
	 X_m = false; //minus
	 Y_p = false;
	 Y_m = false;
	 Z_p = false;
	 Z_m = false;

	//ID 9~11
	 speed_1 = false;
	 speed_10 = false;
	 speed_100 = false;

	//ID 12~14
	 teach_start = false;
	 record = false;
	 teach_end = false;

	//ID 15~17
	 M01 = false;
	 FH = false;
	 SB = false;

	//ID 18~19
	 start = false;
	 reset = false;

	//ID 26
	 emerg_stop = false;

	//ID 27~29
	 para = false;
	 simu = false;
	 diag = false;

	//ID 30~31
	string NcLoc = "";
	string NcCode = "";

	//ID 32
	feedOverride = 100;

	 M00 = false;
	 M30 = false;
	 PGM = false;
	 ERR = false;
	 HX = false;
	 INX = false;
	 HY = false;
	 INY = false;
	 HZ = false;
	 INZ = false;
	 PX = false;
	 NX = false;
	 PY = false;
	 NY = false;
	 PZ = false;
	 NZ = false;
}

void SYS::errorSet(int block, int ID)
{
	error_valid = true;
	error_code = ID;
	error_block = block;
	ERR = true;
}

void SYS::errorReset()
{
	error_valid = false;
	error_code = 0;
	error_block = 0;
	ERR = false;
}