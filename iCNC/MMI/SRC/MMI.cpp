#include "StdAfx.h"
#include "..\INC\MMI.h"

MMI::MMI()
{

}

void  MMI::MMI_main()
{
	switch(MMI_state)
	{
	case MMI_idle:
		idle();
		break;

	case MMI_init:
		init();
		break;

	case MMI_error:
		error();
		break;

	default:
		error();
		break;
	}
}
void MMI::MMI_initialization()
{
	MMI_state = MMI_init;
}

void MMI::idle()
{
	if(mmi2sys_valid)
	{
		mmi2sys();
	}
	
	if(sys->sys2mmi_valid)
	{
		sys2mmi();
	}

}


void MMI::init()
{

	mmi2sys_valid = false;

	MMI_state = MMI_idle;

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

	//ID 20~25
	 mem = false;
	 mdi = false;
	 jog = false;
	 wheel = false;
	 teach = false;
	 home = false;

	//ID 26
	 emerg_stop = false;

	//ID 27~29
	 para = false;
	 simu = false;
	 diag = false;

	//ID 30~31
	NcLoc = "";
	NcCode = "";

	//ID 32
	feedOverride = 100;

	
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
}

void MMI::error()
{
}

void MMI::mmi2sys()
{
	//
	//impulse Click
	//
	sys->start = start; start = false;
	sys->emerg_stop = emerg_stop; emerg_stop = false;

	//
	//step Click
	//
	sys->OpenFile = OpenFile;

	

	sys->NcLoc = NcLoc;
	sys->NcCode = NcCode;

	mmi2sys_valid = false; //寫入完畢

	//
	//clear bottom pulse
	//

	//OpenFile = false;
	sys->feedOverride = feedOverride;

	
	
	mem = false;
	mdi = false;
	jog = false;
	wheel = false;
	teach = false;
	home = false;

}

void MMI::sys2mmi()
{
	
	sys->sys2mmi_valid = false; //讀取完畢
}



void MMI::form2mmi(int ID, bool Click)
{
	switch(ID)
	{
	case 1:
		OpenFile = Click;
		break;
	case 2:
		UVW = Click;
		break;
	case 3:
		X_p = Click;
		break;
	case 4:
		X_m = Click;
		break;
	case 5:
		Y_p = Click;
		break;
	case 6:
		Y_m = Click;
		break;
	case 7:
		Z_p = Click;
		break;
	case 8:
		Z_m = Click;
		break;
	case 9:
		speed_1 = Click;
		break;
	case 10:
		speed_10 = Click;
		break;
	case 11:
		speed_100 = Click;
		break;
	case 12:
		teach_start = Click;
		break;
	case 13:
		record = Click;
		break;
	case 14:
		teach_end = Click;
		break;
	case 15:
		M01 = Click;
		break;
	case 16:
		FH = Click;
		break;
	case 17:
		SB = Click;
		break;
	case 18:
		start = Click;
		break;
	case 19:
		reset = Click;
		break;
	case 20:
		sys->cnc_mode=MEM;
		break;
	case 21:
		sys->cnc_mode=MDI;
		break;
	case 22:
		sys->cnc_mode=JOG;
		break;
	case 23:
		sys->cnc_mode=WHEEL;
		break;
	case 24:
		sys->cnc_mode=TEACH;
		break;
	case 25:
		sys->cnc_mode=HOME;
		break;
	case 26:
		emerg_stop = Click;
		break;
	case 27:
		para = Click;
		break;
	case 28:
		simu = Click;
		break;
	case 29:
		diag = Click;
		break;
	default:
		MMI_state = MMI_error;
		break;
	}
	
	mmi2sys_valid = true;
}
void MMI::form2mmi(int ID, string text)
{
	switch(ID)
	{
	case 30:
		NcLoc = text;
		break;
	case 31:
		NcCode = text;
		break;
	default:
		MMI_state = MMI_error;
		break;
	}

	mmi2sys_valid = true;
}
void MMI::form2mmi(int ID, int value)
{
	switch(ID)
	{
	case 32:
		feedOverride = value;
		break;
	default:
		MMI_state = MMI_error;
		break;
	}

	mmi2sys_valid = true;
}
bool MMI::mmi2form(int ID)
{
	bool  msg_valid;
	switch(ID)
	{
	case 1:
		msg_valid = M00;
		break;
	case 2:
		msg_valid = M30;
		break;
	case 3:
		msg_valid = PGM;
		break;
	case 4:
		msg_valid = ERR;
		break;
	case 5:
		msg_valid = HX;
		break;
	case 6:
		msg_valid = INX;
		break;
	case 7:
		msg_valid = HY;
		break;
	case 8:
		msg_valid = INY;
		break;
	case 9:
		msg_valid = HZ;
		break;
	case 10:
		msg_valid = INZ;
		break;
	case 11:
		msg_valid = PX;
		break;
	case 12:
		msg_valid = NX;
		break;
	case 13:
		msg_valid = PY;
		break;
	case 14:
    	msg_valid = NY;
	    break;
	case 15:
		msg_valid = PZ;
		break;
	case 16:
		msg_valid = NZ;
		break;
	default:
		MMI_state = MMI_error;
		break;
	}

	return msg_valid;
}