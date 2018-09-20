#include <StdAfx.h>
#include <stdio.h>
#include "..\INC\DEC.h"
#include "..\..\UTIL\INC\UTIL.h"

using namespace std;

void DEC::FunctionGenerator()
{
	 int now_i=0,next_i=1;
    //now_i:現在字串處理位置;next_i:下一個字串處理的位置;
    
    string dealing = "";
    //暫存單位資料
    

    while (next_i < linedata.length()) {
        
        while (next_i < linedata.length() && 
			(linedata.at(next_i)<'A' || linedata.at(next_i)>'Z') &&
			linedata.at(next_i) != ';'
			)
		{
			next_i++;
		}
        //PassDigit
        
        dealing.assign(linedata,now_i,next_i-now_i);
        //dealing:字串單位 ex.G00,M30...etc
        
        switch (linedata.at(now_i)) {
            case 'N':
                nFunction(dealing);
                break;
			case 'M':
                mFunction(dealing);
                break;
            case 'G':
                gFunction(dealing);
                break;
            case 'F':
                fFunction(dealing);
                break;
            
            case 'X':
                xyzFunction(dealing);
                break;
            case 'Y':
                xyzFunction(dealing);
                break;
            case 'Z':
                xyzFunction(dealing);
                break;
			case 'U':
                uvwFunction(dealing);
                break;
            case 'V':
                uvwFunction(dealing);
                break;
            case 'W':
                uvwFunction(dealing);
                break;
			case 'I':
                ijkFunction(dealing);
                break;
            case 'J':
                ijkFunction(dealing);
                break;
            case 'K':
                ijkFunction(dealing);
                break;
			case 'R':
                rFunction(dealing);
                break;

            default:

                break;
        }
		if(linedata.at(next_i) == ';')
		{
			DEC_state = DEC_line_end;
		}
		

        now_i = next_i;
        next_i++;
        //進行下個字串的處理
        }

}

//
//clear mark
//
void DEC::clearMark()
{
	ncCommandMarker = false; 
	relAbsMarker = false;// G90: false; G91:true
	m00Marker = false;
	m30Marker = false;
	m01Marker = false;
	g60Marker = false;
	xyzMarker[0] = false;
	xyzMarker[1] = false;
	xyzMarker[2] = false;
	uvwMarker[0] = false;
	uvwMarker[1] = false;
	uvwMarker[2] = false;
	ijkMarker[0] = false;
	ijkMarker[1] = false;
	ijkMarker[2] = false;
	nMarker = false;
	fMarker = false;
	rMarker = false;
}

//
//NC Function
//

/*
1. Declare which code is (ex. N code)
2. Check Mark, if mark = true, break
3. Check if data is correspond to setting
4. If anything is OK, write in data and set mark
*/
void DEC::nFunction(string nc_code)
{
	try
	{
		if( nMarker)throw 3;
		if( stoi(nc_code.substr(1)) < 0)throw 2;

		dec_data->lineNumber = stoi(nc_code.substr(1));
		nMarker = true;
	}
	catch(int err)
	{
		sys->errorSet(4,err);
	}
}
void DEC::gFunction(string nc_code)
{
	switch(stoi(nc_code.substr(1)))
	{
	case 00:
		try
		{
			if(ncCommandMarker)throw 5;

			dec_data->ncCommand = G00_MOTION;
			ncCommandMarker = true;
		}
		catch(int err)
		{
			sys->errorSet(4,err);
		}
		break;
	case 01:
		if(!ncCommandMarker)
		{
			dec_data->ncCommand = G01_MOTION;
			ncCommandMarker = true;
		}
		else
		{
			//error
		}
		break;
	case 02:
		if(!ncCommandMarker)
		{
			dec_data->ncCommand = G02_MOTION;
			dec_data->motionFunction.motion.circleInput.direction = CW;
			ncCommandMarker = true;
		}
		else
		{
			//error
		}
		break;
	case 03:
		if(!ncCommandMarker)
		{
			dec_data->ncCommand = G03_MOTION;
			dec_data->motionFunction.motion.circleInput.direction = CCW;
			ncCommandMarker = true;
		}
		else
		{
			//error
		}
		break;
	case 04:
		dec_data->ncCommand = G04_DWELL_TIME;
		//dec_data->motionFunction.rtFunction.dwellTime.value = ;
		break;

	case 17:
		dec_data->motionFunction.motion.circleInput.plane = XY;
		break;
	case 18:
		dec_data->motionFunction.motion.circleInput.plane = XZ;
		break;
	case 19:
		dec_data->motionFunction.motion.circleInput.plane = YZ;
		break;

	case 60:
		if(!g60Marker)
		{
			dec_data->motionFunction.motion.g60 = true;
			g60Marker = true;
		}
		else
		{
			//error
		}
		 break;

	case 90:
		if(!relAbsMarker)
		{
			dec_data->motionFunction.motion.relative = false;
			relAbsMarker = true;
		}
		else
		{
			//error
		}
		break;
	case 91:
		if(!relAbsMarker)
		{
			dec_data->motionFunction.motion.relative = true;
			relAbsMarker = true;
		}
		else
		{
			//error
		}
		break;

	default:
		sys->errorSet(4,4);
		break;
	}

}
void DEC::fFunction(string nc_code)
{
		if(fMarker == false)
	{
		if( stoi(nc_code.substr(1)) < 0)
		{
			//sys->errorSet(4,2);
		}
		dec_data->motionFunction.motion.feedrate = stod(nc_code.substr(1));
		fMarker = true;
	}
	else
	{
		//error
		//sys->errorSet(4,3);
	}

}
void DEC::mFunction(string nc_code)
{
	switch(stoi(nc_code.substr(1)))
	{
	case 00:
		if(!m00Marker)
		{
			dec_data->motionFunction.motion.m00 = true;
			m00Marker = true;
		}
		else
		{
			//error
		}
		break;
	case 01:
		if(!m01Marker)
		{
			dec_data->motionFunction.motion.m01 = true;
			m01Marker = true;
		}
		else
		{
			//error
		}
		break;
	case 30:
		if(!m30Marker)
		{
			dec_data->ncCommand = M30_PROGRAM_END;
			m30Marker = true;
			m30_End = true;
		}
		else
		{
			//error
		}
		break;

	default:
		//sys->errorSet(4,4);
		break;
	}

}
void DEC::xyzFunction(string nc_code)
{
	//if uvw, return
	if(uvwMarker[0]||uvwMarker[1]||uvwMarker[2])
	{
		//error
		return;
	}
	switch(nc_code.at(0))
	{
	case 'X':
		if(!xyzMarker[0])
		{
			if(dec_data->ncCommand == G04_DWELL_TIME)
			{
				dec_data->motionFunction.rtFunction.dwellTime.value = stod(nc_code.substr(1));
			}
			else
			{
			dec_data->motionFunction.motion.xyzCoordinate[0] = stod(nc_code.substr(1));
			dec_data->motionFunction.motion.xyzValid[0] = true;
			}
			xyzMarker[0] = true;
		}
		else
		{
			//error
		}
		break;
	case 'Y':
		if(!xyzMarker[1])
		{
			dec_data->motionFunction.motion.xyzCoordinate[1] = stod(nc_code.substr(1));
	    	dec_data->motionFunction.motion.xyzValid[1] = true;
			xyzMarker[1] = true;
		}
		else
		{
			//error
		}
		break;
	case 'Z':
		if(!xyzMarker[2])
		{
			dec_data->motionFunction.motion.xyzCoordinate[2] = stod(nc_code.substr(1));
			dec_data->motionFunction.motion.xyzValid[2] = true;
			xyzMarker[2] = true;
		}
		else
		{
			//error
		}
		break;
	default:
		break;
	}
}
void DEC::uvwFunction(string nc_code)
{
	//if xyz, return
	if(xyzMarker[0]||xyzMarker[1]||xyzMarker[2])
	{
		//error
		return;
	}
	switch(nc_code.at(0))
	{
	case 'U':
		if(!uvwMarker[0])
		{
			dec_data->motionFunction.motion.uvwCoordinate[0] = stod(nc_code.substr(1));
		    dec_data->motionFunction.motion.uvwValid[0] = true;
			uvwMarker[0] = true;
		}
		else
		{
			//error
		}
		break;
	case 'V':
		if(!uvwMarker[1])
		{
			dec_data->motionFunction.motion.uvwCoordinate[1] = stod(nc_code.substr(1));
		    dec_data->motionFunction.motion.uvwValid[1] = true;
			uvwMarker[1] = true;
		}
		else
		{
			//error
		}
		break;
	case 'W':
		if(!uvwMarker[2])
		{
			dec_data->motionFunction.motion.uvwCoordinate[2] = stod(nc_code.substr(1));
		    dec_data->motionFunction.motion.uvwValid[2] = true;
			uvwMarker[2] = true;
		}
		else
		{
			//error
		}
		break;
	default:
		break;
}
}

void DEC::ijkFunction(string nc_code)
{
	if(rMarker)
	{
		//error
		return;
	}

	switch(nc_code.at(0))
	{
	case 'I':
		if(!ijkMarker[0])
		{
			dec_data->motionFunction.motion.circleInput. iCenter = stod(nc_code.substr(1));
			dec_data->motionFunction.motion.circleInput.CenterValid = true;
			ijkMarker[0] = true;
		}
		else
		{
			//error
		}
		break;
	case 'J':
		if(!ijkMarker[1])
		{
			dec_data->motionFunction.motion.circleInput. jCenter = stod(nc_code.substr(1));
			dec_data->motionFunction.motion.circleInput.CenterValid = true;
			ijkMarker[1] = true;
		}
		else
		{
			//error
		}
		break;
	case 'K':
		if(!ijkMarker[2])
		{
			dec_data->motionFunction.motion.circleInput. kCenter = stod(nc_code.substr(1));
			dec_data->motionFunction.motion.circleInput.CenterValid = true;
			ijkMarker[2] = true;
		}
		else
		{
			//error
		}
		break;
	default:
		break;
	}
}


void DEC::rFunction(string nc_code)
{
	if(ijkMarker[0]||ijkMarker[1]||ijkMarker[2])
	{
		//error
		return;
	}
	if(!rMarker)
	{
		dec_data->motionFunction.motion.circleInput.radius = stod(nc_code.substr(1));
		dec_data->motionFunction.motion.circleInput.CenterValid = false;
		rMarker = true;
	}
	else
	{
		//error
	}
		
}
