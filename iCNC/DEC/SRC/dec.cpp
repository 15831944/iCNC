#include <StdAfx.h>
#include <stdio.h>
#include "..\INC\DEC.h"
#include "..\..\UTIL\INC\UTIL.h"

using namespace std;


DEC::DEC(){
	 /*==Initiallization==*/

}

void DEC::DEC_main()
{

	switch(DEC_state)
	{
	case DEC_idle:
		idle();
		break;
	case DEC_init:
		init();
		break;
	case DEC_read:
		readNcText();
		break;
	case DEC_pre:
		pre();
		break;
	case DEC_line_loop:
		line_loop();
		break;
	case DEC_line_end:
		line_end();
		break;
	case DEC_write_block:
		write_block();
		break;
	case DEC_dec2fifo:
		dec2fifo();
		break;
	case DEC_waitM30:
		m30_wait();
		break;
	case DEC_error:
		error();
		break;
	default:
		error();
		break;
	}
}
void DEC::DEC_initialization()
{
	DEC_state = DEC_init;
	
}

void DEC::DEC_reset()
{
	NcLoc = "";
	NcCode = ""; 
    linedata ="";


	sys->start = false;
	DEC_state = DEC_init;
}

void DEC::idle()
{
	//
	//check if press start bottom and sys has file path
	//
	if (sys->start)
	{
		if(sys->OpenFile)
		{
			NcLoc = sys->NcLoc;
			NcCode = sys->NcCode;
			sys->M30 = false;

			DEC_state = DEC_read; //change state
			//
			//PGM signal light
			//
			sys->PGM = true;
		}
		else
		{
			//未成功開啟
			sys->errorSet(4,1);
			//idle
		}
		//idle
	}
}
void DEC::init()
{ 
	DEC_state = DEC_idle;
	clearMark();
	m30_End = false;
	
}
void DEC::readNcText()
{

	DeleteComment();
	DeleteSpace(&NcCode);

	DEC_state = DEC_line_loop;

}
void DEC::pre()
{
	//do something
}
void DEC::line_loop()
{
	dec_data = new DEC2FIFO_BLOCK;
	clearByteSpace((char*)dec_data,sizeof(DEC2FIFO_BLOCK));
	//init data

	NcGetLine();
	FunctionGenerator();

}
void DEC::line_end()
{
	//check data correction
	DEC_state = DEC_write_block;
}
void DEC::write_block()
{
	fifo_data = new FIFO_DATA;
	fifo_data->block = dec_data;

	DEC_state = DEC_dec2fifo;
}
void DEC::dec2fifo()
{
	sys->fifo->wrFIFO(fifo_data);

	clearMark();
	DEC_state = DEC_line_loop;
	if(m30_End)
	{
			DEC_state = DEC_waitM30;
	}

} 
void DEC::m30_wait()
{
	if(sys->m30Msg)
	{
		DEC_state = DEC_init;
		sys->start = false;
		
	}
}
void DEC::error()
{
}




void DEC::DeleteComment()
{
	while( NcCode.find("/*") <  NcCode.length())
    {
     NcCode.erase( NcCode.find("/*"), NcCode.find("*/")- NcCode.find("/*")+2);
    }
}
void DEC::NcGetLine()
{
	linedata = NcCode.substr(0,NcCode.find(";")+1);
	NcCode.erase( 0, NcCode.find(";")+1);
}
