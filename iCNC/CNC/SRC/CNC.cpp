#include <StdAfx.h>
#include "..\INC\CNC.h"

/*
idle: read input signal, run block main
init: act in form load
close: end program
emergstop: stop all motion
error: stop and show error code
*/
 
CNC::CNC()
{
	mmi = new MMI;
	dec = new DEC;
	sys = new SYS;
	intp = new INTP;

	//
	//sys link
	//
	mmi->sys = sys;
	dec->sys = sys;
	intp->sys = sys;
}
void CNC::CNC_initialization()
{
	CNC_state = CNC_init;
}


void CNC::CNC_main_nrt()
{
	//
	//block main
	//
	mmi->MMI_main();
	dec->DEC_main();

	//
	//cnc <> sys
	//
	if(cnc2sys_valid)
	{
		cnc2sys();
	}
	if(sys->sys2cnc_valid)
	{
		sys2cnc();
	}

	//
	//cnc main
	//
	switch(CNC_state)
	{
	case CNC_idle:
		idle();
		break;
	case CNC_init:
		init();
		break;
	case CNC_reset:
		reset();
		break;
	case CNC_close:
		close();
		break;
	case CNC_emerg_stop:
		emerg_stop();
		break;
	case CNC_error:
		error();
		break;

	default:
		error();
		break;
	}


}
void CNC::CNC_main_rt()
{
	intp->INTP_main();
}

void CNC::cncReset()
{
	CNC_state = CNC_reset;
}


void CNC::idle()
{
	
	//
	//emerg stop
	//
	if(sys->emerg_stop == true)
	{

	}

	
}


void CNC::init()
{


	CNC_state = CNC_idle;
	//CNC init state
	cnc2sys_valid = false;

	//
	//block init
	//
	mmi->MMI_initialization();
	dec->DEC_initialization();
	intp->INTP_initialization();
	sys->init();

}
void CNC::reset()
{
	sys->SYS_reset();
	dec->DEC_reset();
	intp->INTP_reset();
	CNC_state = CNC_idle;
}
void CNC::close()
{
}
void CNC::emerg_stop()
{
}
void CNC::error()
{
}


void CNC::cnc2sys()
{
	
	cnc2sys_valid = false; //寫入完畢
}
void CNC::sys2cnc()
{
	sys->sys2cnc_valid = false; //讀取完畢
}