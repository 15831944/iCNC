#ifndef SYS_h
#define SYS_h

#include "FIFO.h"

#include <string> 

using std::string;

enum CNCmode{nullMode=0,MEM=1,MDI,JOG,WHEEL,TEACH,HOME};

class SYS
{
public:
	SYS();

	void init();
	void errorSet(int block, int ID);
	void errorReset();

	void SYS_reset();

	FIFO* fifo;

	CNCmode cnc_mode;
	//
	//xyz/uvw show
	//
	double x_valid;
	double y_valid;
	double z_valid;
	double u_valid;
	double v_valid;
	double w_valid;

	//
	//error
	//
	bool error_valid;
	int error_code;
	int error_block;

	//
	//block send valid
	//
	bool sys2cnc_valid;
	bool sys2mmi_valid;
	bool sys2dec_valid;
	bool sys2intp_valid;

	//CNC
	bool emerg_stop;
	
	//DEC
	bool start;
	bool reset;
	bool OpenFile;
	string NcLoc;
	string NcCode;
	bool m30Msg;

	//ID 3~8
	bool X_p; //plus
	bool X_m; //minus
	bool Y_p;
	bool Y_m;
	bool Z_p;
	bool Z_m;

	//ID 9~11
	bool speed_1;
	bool speed_10;
	bool speed_100;

	//ID 12~14
	bool teach_start;
	bool record;
	bool teach_end;

	//ID 15~17
	bool M01;
	bool FH;
	bool SB;

	bool UVW;
	//ID 27~29
	bool para;
	bool simu;
	bool diag;

	//ID 32
	int feedOverride;

	
	//
	//msg light
	//

	//ID 1~16
	bool M00;
	bool M30;
	bool PGM;
	bool ERR;
	bool HX;
	bool INX;
	bool HY;
	bool INY;
	bool HZ;
	bool INZ;
	bool PX;
	bool NX;
	bool PY;
	bool NY;
	bool PZ;
	bool NZ;

private:


};

#endif /* SYS_h */
