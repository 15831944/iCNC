#ifndef MMI_h
#define MMI_h

#include "..\..\SYS\INC\SYS.h"



enum MMI_State{MMI_idle = 0,MMI_init,MMI_error = 99};

class MMI
{
public:
    MMI();

	//
	//mmi main
	//
	void MMI_initialization(); //initial in cnc init
	void MMI_main();
	

	//
	//mmi<>form
	//
	void form2mmi(int ID, bool Click);
	void form2mmi(int ID, string text);
	void form2mmi(int ID, int value);
	bool mmi2form(int ID);

	//
	//block
	//
	SYS* sys;

	
	


private:
	MMI_State MMI_state;

	//
	//mmi main
	//
	void idle();
	void init();
	void error();

	//
	//mmi<>sys
	//
	void mmi2sys();
	void sys2mmi();
	bool mmi2sys_valid; //¿é¤J½T»{

	//
	//form2mmi
	//

	//ID 1~2
	bool OpenFile;
	bool UVW;

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

	//ID 18~19
	bool start;
	bool reset;

	//ID 20~25
	bool mem;
	bool mdi;
	bool jog;
	bool wheel;
	bool teach;
	bool home;

	//ID 26
	bool emerg_stop;

	//ID 27~29
	bool para;
	bool simu;
	bool diag;

	//ID 30~31
	string NcLoc;
	string NcCode;

	//ID 32
	int feedOverride;

	
	//
	//mmi2form
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

	


};



#endif /* MMI_h */
