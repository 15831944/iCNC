#include "StdAfx.h"
#include "..\INC\INTP.h"
#include "..\..\UTIL\INC\UTIL.h"
#include "..\..\switch.h"
#include "..\..\DRV\INC\stepMotorDRV.h"


INTP::INTP()
{
}


void INTP::INTP_main()
{

	switch(INTP_state)
	{
	case INTP_IDLE:
		idle();
		break;
	case INTP_INIT:
		init();
		break;
	case INTP_PRE:
		pre();
		break;
	case INTP_EXE:
		exe();
		break;
	case INTP_CLOSE:
		close();
		break;
	case INTP_FUNCTION:
		function();
		break;
	case INTP_G04_WAIT:
		g04_wait();
		break;
	case INTP_RESET:
		reset();
		break;
	case INTP_ERROR:
		error();
		break;
	default:

		break;
	}
}
void INTP::INTP_initialization()
{
	INTP_state = INTP_INIT;
}


//
//intp main
//
void INTP::idle()
{
	//read fifo
	fifo_data = sys->fifo->rdFIFO();
	if(fifo_data != nullptr) //determine if fifo has data to read, if not, fifo->rdFIFO will return nullptr
	{
		intp_data = (DEC2FIFO_BLOCK*)fifo_data->block;
		
		

		switch (intp_data->ncCommand)
		{
		case G00_MOTION:
			G00_motion();
			break;
		case G01_MOTION:
			G01_motion();
			break;
		case G02_MOTION:
			G02_motion();
			break;
		case G03_MOTION:
			G03_motion();
			break;
		case FUNCTION_CMD:
			Function_cmd();
			break;
		case G04_DWELL_TIME:
			G04_dwell_time();
			break;
		case GO_REFERENCE_POINT:
			Go_reference_point();
			break;
		case M30_PROGRAM_END:
			M30_program_end();
			break;
		default:
			break;
		}
		
	}
}
void INTP::init()
{
	
	INTP_state = INTP_IDLE;

	clearMat(xyzStart);
	clearMat(xyzEnd);
	clearMat(xyzNew);
	clearMat(xyzOld);
	clearMat(xyzRelative);
	clearMat(linearFactor);
	deltalength = 0;
	clearMat(ijkCenter);
	clearMat(uvwStart);
	clearMat(uvwEnd);
	clearMat(uvwNew);
	clearMat(uvwOld);
	clearMat(uvwRelative);

	xyzStart[0] = 75.0;
	xyzStart[1] = 75.0;
	xyzStart[2] = 100; 

	uvwStart[0] = 0.0;  // [degree]
	uvwStart[1] = 90;   // [degree]
	uvwStart[2] = 100;

	for (int i = 0; i<3;i++)
	{
		xyzNew[i] = xyzStart[i];
		xyzEnd[i] = xyzStart[i];
		xyzOld[i] = xyzStart[i];

		uvwNew[i] = uvwStart[i];
		uvwEnd[i] = uvwStart[i];
		uvwOld[i] = uvwStart[i];

	}

	g04Counter = 0;
	cyclingTime = CyclingTime;
	acceleration = 1000;

	g00Speed = 100;
	m30ProgramEnd = true;

	L1 = L2 = 75.0;

	slope = new SLOPE(acceleration,cyclingTime);
	circle = nullptr;

	sys->x_valid = xyzOld[0];
	sys->y_valid = xyzOld[1];
	sys->z_valid = xyzOld[2];
	sys->u_valid = uvwOld[0];
	sys->v_valid = uvwOld[1];
	sys->w_valid = uvwOld[2];
}
void INTP::INTP_reset()
{
	if (INTP_state != INTP_ERROR)
	{
		slope->stop();
	}
	else
	{
		INTP_state = INTP_IDLE;
	}
}
void INTP::INTP_stop()
{
	slope->stop();
	delete intp_data;
}
void INTP::INTP_input(int axis,double value,double F)
{
	//0 1 2 XYZ 3 4 5 UVW
	intp_data = new DEC2FIFO_BLOCK;
	clearByteSpace((char*)intp_data,sizeof(DEC2FIFO_BLOCK));
	intp_data->lineNumber = 0;
	intp_data->ncCommand = G01_MOTION;
	intp_data->motionFunction.motion.relative = true;
	intp_data->motionFunction.motion.feedrate=F;
	if (axis == 0||axis == 1||axis == 2)
	{
		intp_data->motionFunction.motion.xyzCoordinate[axis] = value;
		intp_data->motionFunction.motion.xyzValid[axis]=true;
	}
	else if (axis == 3||axis == 4||axis == 5)
	{
		intp_data->motionFunction.motion.uvwCoordinate[axis-3] = value;
		intp_data->motionFunction.motion.uvwValid[axis-3]=true;
	}
	G01_motion();
}
void INTP::pre()
{
	//
	//init slope parameter
	//
	slope->inputData( deltalength,intp_data-> motionFunction.motion.feedrate);

	if(intp_data->ncCommand == G02_MOTION||intp_data->ncCommand == G03_MOTION)
	{
		if(deltalength>0)
		{
			INTP_state = INTP_EXE;
			return;
		}
		else
		{
			//no length, goto close
			INTP_state = INTP_CLOSE;
		}
	}
	
	
	if(deltalength>0)
	{
	   if
		(
			intp_data-> motionFunction.motion.xyzValid[0] ||
			intp_data-> motionFunction.motion.xyzValid[1] ||
			intp_data-> motionFunction.motion.xyzValid[2] 	
		)
		{
			if(intp_data-> motionFunction.motion.xyzValid[0]) linearFactor[0] = xyzRelative[0]/deltalength;
			if(intp_data-> motionFunction.motion.xyzValid[1]) linearFactor[1] = xyzRelative[1]/deltalength;
			if(intp_data-> motionFunction.motion.xyzValid[2]) linearFactor[2] = xyzRelative[2]/deltalength;
		}
		else if
		(
			intp_data-> motionFunction.motion.uvwValid[0] ||
			intp_data-> motionFunction.motion.uvwValid[1] ||
			intp_data-> motionFunction.motion.uvwValid[2] 	
		)
		{
			if(intp_data-> motionFunction.motion.uvwValid[0]) linearFactor[0] = uvwRelative[0]/deltalength;
			if(intp_data-> motionFunction.motion.uvwValid[1]) linearFactor[1] = uvwRelative[1]/deltalength;
			if(intp_data-> motionFunction.motion.uvwValid[2]) linearFactor[2] = uvwRelative[2]/deltalength;
		}

		INTP_state = INTP_EXE;
	}
	else
	{
		//no length, goto close
		INTP_state = INTP_CLOSE;
	}

	//
	//check the critical point
	//
	/*
	NOTE: critical point occur when end v = 0 or end(0,0)
	*/
	try
	{
		//x=0,y=0
		if(abs(xyzEnd[0])<=doubleError && abs(xyzEnd[1]) <= doubleError)throw 31;
		//v = 0
		else if(abs(uvwEnd[1])<=doubleError)throw 31;
	}
	catch(int err)
	{
		sys->errorSet(5,err);
		INTP_state = INTP_ERROR;
	}

}
void INTP::exe()
{
	//
	//speed =0, end in next cycle
	//
	if(slope->endInNextCycle())INTP_state = INTP_CLOSE;

	//
	//read speed
	//
	double speed = slope->read();

	//
	//last new point is old point
	//
	xyzOld[0] = xyzNew[0];
	xyzOld[1] = xyzNew[1];
	xyzOld[2] = xyzNew[2];

	uvwOld[0] = uvwNew[0];
	uvwOld[1] = uvwNew[1];
	uvwOld[2] = uvwNew[2];

	//
	//and show the location at form
	//
	sys->x_valid = xyzOld[0];
	sys->y_valid = xyzOld[1];
	sys->z_valid = xyzOld[2];
	sys->u_valid = uvwOld[0];
	sys->v_valid = uvwOld[1];
	sys->w_valid = uvwOld[2];


	
	if(intp_data->ncCommand == G00_MOTION||intp_data->ncCommand == G01_MOTION)
	{
		//
		// xyz linear motion
		//

		if
		(
			intp_data-> motionFunction.motion.xyzValid[0] ||
			intp_data-> motionFunction.motion.xyzValid[1] ||
			intp_data-> motionFunction.motion.xyzValid[2] 	
		)
		{
		//
		//now, calculate new xyz
		//
		xyzNew[0] += speed*linearFactor[0]*cyclingTime ;
		xyzNew[1] += speed*linearFactor[1]*cyclingTime ;
		xyzNew[2] += speed*linearFactor[2]*cyclingTime ;
		//
		//and do wk>mk
		//
		wk2mk(xyzNew,uvwNew,uvwOld);
		//
		//calculate relative. Note that in some case, espacially New = 359,Old = 1
		//For New-old>180, try to do New-old-360
		//Or New=1, Old = 359, New-old<-180, do New-Old+360 
		//
		uvwRelative[0] = Force360(uvwNew[0])-Force360(uvwOld[0]);
		if(uvwRelative[0]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[0]<-180){uvwRelative[0]+=360;}
		uvwRelative[1] = Force360(uvwNew[1])-Force360(uvwOld[1]);
		if(uvwRelative[1]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[1]<-180){uvwRelative[0]+=360;}
		uvwRelative[2] = uvwNew[2]-uvwOld[2];
		//
		//Check Critical point
		//
		try
		{
			//x=0,y=0
			if(abs(xyzNew[0])<=doubleError && abs(xyzNew[1]) <= doubleError)throw 31;
			//v = 0
			else if(abs(uvwNew[1])<=doubleError)throw 31;
			else if((pow(xyzNew[0],2)+pow(xyzNew[1],2))>(150*150-doubleError)) throw 31;
		}
		catch(int err)
		{
			sys->errorSet(5,err);
			INTP_state = INTP_ERROR;
		}
		}
		else if
		(
			intp_data-> motionFunction.motion.uvwValid[0] ||
			intp_data-> motionFunction.motion.uvwValid[1] ||
			intp_data-> motionFunction.motion.uvwValid[2] 	
		)
		{
		//
		//now, calculate new uvw
		//
		uvwNew[0] += speed*linearFactor[0]*cyclingTime ;
		uvwNew[1] += speed*linearFactor[1]*cyclingTime ;
		uvwNew[2] += speed*linearFactor[2]*cyclingTime ;
		//
		//and do mk>wk
		//
		mk2wk(uvwNew,xyzNew);

		uvwRelative[0] = Force360(uvwNew[0])-Force360(uvwOld[0]);
		if(uvwRelative[0]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[0]<-180){uvwRelative[0]+=360;}
		uvwRelative[1] = Force360(uvwNew[1])-Force360(uvwOld[1]);
		if(uvwRelative[1]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[1]<-180){uvwRelative[0]+=360;}
		uvwRelative[2] = uvwNew[2]-uvwOld[2];
		}
	}
	else if(intp_data->ncCommand == G02_MOTION||intp_data->ncCommand == G03_MOTION)
	{
		//
		//now, calculate new xyz
		//
		double x[2],y[2];
		if (intp_data-> motionFunction.motion.circleInput.plane==XY)
		{
			x[0]=xyzNew[0];
			x[1]=xyzNew[1];
			circle->nextPoint(x,y,speed*cyclingTime);
			xyzNew[0]=y[0];
			xyzNew[1]=y[1];
		}
		else if (intp_data-> motionFunction.motion.circleInput.plane==YZ)
		{
			x[1]=xyzNew[1];
			x[2]=xyzNew[2];
			circle->nextPoint(x,y,speed*cyclingTime);
			xyzNew[1]=y[1];
			xyzNew[2]=y[2];
		}
		else if (intp_data-> motionFunction.motion.circleInput.plane==XZ)
		{
			x[0]=xyzNew[0];
			x[2]=xyzNew[2];
			circle->nextPoint(x,y,speed*cyclingTime);
			xyzNew[0]=y[0];
			xyzNew[2]=y[2];
		}

		//
		//and do wk>mk
		//
		wk2mk(xyzNew,uvwNew,uvwOld);
		//
		//calculate relative. Note that in some case, espacially New = 359,Old = 1
		//For New-old>180, try to do New-old-360
		//Or New=1, Old = 359, New-old<-180, do New-Old+360 
		//
		uvwRelative[0] = Force360(uvwNew[0])-Force360(uvwOld[0]);
		if(uvwRelative[0]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[0]<-180){uvwRelative[0]+=360;}
		uvwRelative[1] = Force360(uvwNew[1])-Force360(uvwOld[1]);
		if(uvwRelative[1]>180){uvwRelative[0]-=360;}
		else if(uvwRelative[1]<-180){uvwRelative[0]+=360;}
		uvwRelative[2] = uvwNew[2]-uvwOld[2];
		//
		//Check Critical point
		//
		try
		{
			//x=0,y=0
			if(abs(xyzNew[0])<=doubleError && abs(xyzNew[1]) <= doubleError)throw 31;
			//v = 0
			else if(abs(uvwNew[1])<=doubleError)throw 31;
			else if((pow(xyzNew[0],2)+pow(xyzNew[1],2))>(150*150-doubleError)) throw 31;
		}
		catch(int err)
		{
			sys->errorSet(5,err);
			INTP_state = INTP_ERROR;
		}


	}

	//z = 0~200
	try
	{
		if(xyzNew[2]<0 || xyzNew[2] > 200)throw 31;
	}
	catch(int err)
	{
		sys->errorSet(5,err);
		INTP_state = INTP_ERROR;
	}


	//
	//check xyz limit and give signal
	//
	if(xyzNew[0]>0 && abs(uvwNew[1])<=10)sys->PX = true;
	else sys->PX = false;
	if(xyzNew[1]>0 && abs(uvwNew[1])<=10)sys->PY = true;
	else sys->PY = false;
	if(xyzNew[2]>200-1)sys->PZ = true;
	else sys->PZ = false;
	if(xyzNew[0]<0 && abs(uvwNew[1])<=10)sys->NX = true;
	else sys->NX = false;
	if(xyzNew[1]<0 && abs(uvwNew[1])<=10)sys->NY = true;
	else sys->NY = false;
	if(xyzNew[2]<1)sys->NZ = true;
	else sys->NZ = false;


	//
	//input data to machine
	//
#if !DEBUG
	putAxisValue(0,(int)(uvwRelative[0]/uvPerTick));
	putAxisValue(1,(int)((uvwRelative[1]+uvwRelative[0])/uvPerTick));
	putAxisValue(2,(int)(uvwRelative[2]/wPerTick));

#endif

	//do something
}
void INTP::close()
{
	INTP_state = INTP_IDLE;
	xyzStart[0] = xyzNew[0];
	xyzStart[1] = xyzNew[1];
	xyzStart[2] = xyzNew[2];

	xyzRelative[0]=xyzRelative[1]=xyzRelative[2]=0;

	//
	//force u v w in 0~360
	//
	 uvwNew[0] = Force360( uvwNew[0]);
	 uvwNew[1] = Force360( uvwNew[1]);
	 uvwNew[2] = Force360( uvwNew[2]);

	uvwStart[0] = uvwNew[0];
	uvwStart[1] = uvwNew[1];
	uvwStart[2] = uvwNew[2];

	uvwRelative[0]=uvwRelative[1]=uvwRelative[2]=0;

	linearFactor[0]=linearFactor[1]=linearFactor[2]=0;

	if (circle!=nullptr)
	{
		delete circle;
		circle=nullptr;
	}
}
void INTP::function()
{
}
void INTP::g04_wait()
{
	g04Counter -= (int)(cyclingTime*1000);
	if(g04Counter<0){INTP_state = INTP_IDLE;}
}
void INTP::reset()
{
	
	INTP_state = INTP_IDLE;
}
void INTP::error()
{
	//do something
}


//
//intp function
//	
/*
Note: 
in these function, we only calculate the total length and the end point
*/
void INTP::G00_motion()
{
	//
	//G00 speed
	//
	intp_data-> motionFunction.motion.feedrate = g00Speed;
	//
	//Do G01 cause G00 G01 do the same thing expect the speed
	//
	G01_motion();
}
void INTP::G01_motion()
{
	//declare xyz or uvw
	if
	(
		intp_data-> motionFunction.motion.xyzValid[0] ||
		intp_data-> motionFunction.motion.xyzValid[1] ||
		intp_data-> motionFunction.motion.xyzValid[2] 	
	)
	{

	for(int i=0;i<3;i++)
	{
		if(intp_data-> motionFunction.motion.xyzValid[i])
		{
			if(intp_data-> motionFunction.motion.relative)
			{
				//relative motion
				xyzEnd[i] = xyzOld[i]+intp_data-> motionFunction.motion.xyzCoordinate[i];
				//
				//cal relative point
				//
				xyzRelative[i] = xyzEnd[i] - xyzStart[i];
			}
			else
			{
				//absolute motion
				xyzEnd[i] =intp_data-> motionFunction.motion.xyzCoordinate[i];
				//
				//cal relative point
				//
				xyzRelative[i] = xyzEnd[i] - xyzStart[i];
			}
		}
	}
	wk2mk(xyzEnd,uvwEnd,uvwStart);
	deltalength = xyzDistance(xyzRelative[0],xyzRelative[1],xyzRelative[2]);

	}

	else if
	(
		intp_data-> motionFunction.motion.uvwValid[0] ||
		intp_data-> motionFunction.motion.uvwValid[1] ||
		intp_data-> motionFunction.motion.uvwValid[2] 	
	)
	{

		for(int i=0;i<3;i++)
		{
			if(intp_data-> motionFunction.motion.uvwValid[i])
			{
				if(intp_data-> motionFunction.motion.relative)
				{
				//relative motion
				uvwEnd[i] = uvwOld[i]+intp_data-> motionFunction.motion.uvwCoordinate[i];

				//
				//cal relative point
				//
				uvwRelative[i] = uvwEnd[i] - uvwStart[i];
				}
				else
				{
				//absolute motion
				uvwEnd[i] =intp_data-> motionFunction.motion.uvwCoordinate[i];
				
					//
					//cal relative point
					//
					if (i == 2) // don't deal z axis
					{
						uvwRelative[i] = uvwEnd[i] - uvwStart[i];
					}
					else
					{
						(abs(360+uvwEnd[i] - uvwStart[i])>abs(uvwEnd[i] - uvwStart[i]))?
						(uvwRelative[i] = uvwEnd[i] - uvwStart[i]):(uvwRelative[i] = uvwEnd[i]+360 - uvwStart[i]);
					}

				}
				
			}
		}
		mk2wk(uvwEnd,xyzEnd);
		deltalength = xyzDistance(uvwRelative[0],uvwRelative[1],uvwRelative[2]);
	}
	INTP_state = INTP_PRE;
}
void INTP::G02_motion()
{

	//
	//plane case
	//
	if (intp_data-> motionFunction.motion.circleInput.plane==XY)
	{
		intp_data-> motionFunction.motion.xyzValid[2]=false;
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==YZ)
	{
		intp_data-> motionFunction.motion.xyzValid[0]=false;
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==XZ)
	{
		intp_data-> motionFunction.motion.xyzValid[1]=false;
	}

	for(int i=0;i<3;i++)
	{
		if(intp_data-> motionFunction.motion.xyzValid[i])
		{
			if(intp_data-> motionFunction.motion.relative)
			{
				//relative motion
				xyzEnd[i] = xyzOld[i]+intp_data-> motionFunction.motion.xyzCoordinate[i];
			}
			else
			{
				//absolute motion
				xyzEnd[i] =intp_data-> motionFunction.motion.xyzCoordinate[i];
			}
		}
	}
	//
	//circle setup
	//
	double a[2],b[2],o[2];
	bool direction = true;
	if (intp_data-> motionFunction.motion.circleInput.plane==XY)
	{
		a[0]=xyzStart[0];
		a[1]=xyzStart[1];
		b[0]=xyzEnd[0];
		b[1]=xyzEnd[1];
		o[0]=intp_data-> motionFunction.motion.circleInput.iCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.jCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==YZ)
	{
		a[0]=xyzStart[1];
		a[1]=xyzStart[2];
		b[0]=xyzEnd[1];
		b[1]=xyzEnd[2];
		o[0]=intp_data-> motionFunction.motion.circleInput.jCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.kCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==XZ)
	{
		a[0]=xyzStart[0];
		a[1]=xyzStart[3];
		b[0]=xyzEnd[0];
		b[1]=xyzEnd[3];
		o[0]=intp_data-> motionFunction.motion.circleInput.iCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.kCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	
	deltalength=circle->distance();

	wk2mk(xyzEnd,uvwEnd,uvwStart);


	INTP_state = INTP_PRE;
	//do something
}
void INTP::G03_motion()
{
	
	//
	//plane case
	//
	if (intp_data-> motionFunction.motion.circleInput.plane==XY)
	{
		intp_data-> motionFunction.motion.xyzValid[2]=false;
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==YZ)
	{
		intp_data-> motionFunction.motion.xyzValid[0]=false;
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==XZ)
	{
		intp_data-> motionFunction.motion.xyzValid[1]=false;
	}

	for(int i=0;i<3;i++)
	{
		if(intp_data-> motionFunction.motion.xyzValid[i])
		{
			if(intp_data-> motionFunction.motion.relative)
			{
				//relative motion
				xyzEnd[i] = xyzOld[i]+intp_data-> motionFunction.motion.xyzCoordinate[i];
			}
			else
			{
				//absolute motion
				xyzEnd[i] =intp_data-> motionFunction.motion.xyzCoordinate[i];
			}
		}
	}
	//
	//circle setup
	//
	double a[2],b[2],o[2];
	bool direction = false;
	if (intp_data-> motionFunction.motion.circleInput.plane==XY)
	{
		a[0]=xyzStart[0];
		a[1]=xyzStart[1];
		b[0]=xyzEnd[0];
		b[1]=xyzEnd[1];
		o[0]=intp_data-> motionFunction.motion.circleInput.iCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.jCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==YZ)
	{
		a[0]=xyzStart[1];
		a[1]=xyzStart[2];
		b[0]=xyzEnd[1];
		b[1]=xyzEnd[2];
		o[0]=intp_data-> motionFunction.motion.circleInput.jCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.kCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	else if (intp_data-> motionFunction.motion.circleInput.plane==XZ)
	{
		a[0]=xyzStart[0];
		a[1]=xyzStart[3];
		b[0]=xyzEnd[0];
		b[1]=xyzEnd[3];
		o[0]=intp_data-> motionFunction.motion.circleInput.iCenter;
		o[1]=intp_data-> motionFunction.motion.circleInput.kCenter;
		circle = new CIRCLE(a,b,o,direction);
	}
	
	deltalength=circle->distance();

	wk2mk(xyzEnd,uvwEnd,uvwStart);


	INTP_state = INTP_PRE;
	//do something
}
void INTP::Function_cmd()
{
}
void INTP::G04_dwell_time()
{
	INTP_state = INTP_G04_WAIT;
	g04Counter = (int) intp_data-> motionFunction.rtFunction.dwellTime.value;
}
void INTP::Go_reference_point()
{
}
void INTP::M30_program_end()
{
	INTP_state = INTP_IDLE;
	sys->m30Msg = true;
	sys->M30 = true;
	//
	//close light
	//
	sys->PGM = false;
}

void INTP::mk2wk(double mk[3],double wk[3])
{
	wk[0] = L1*cos(DegreeToRad(mk[0]))+L2*cos(DegreeToRad(mk[0]+mk[1]));
	wk[1] = L1*sin(DegreeToRad(mk[0]))+L2*sin(DegreeToRad(mk[0]+mk[1]));
	wk[2] = mk[2];
}

void INTP::wk2mk(double wk[3],double mk[3],double mkold[3])
{

	//
	//input next work point, last machine point, return next machine point
	//

	//
	//Level1 caculate
	//
	/*
	alpha is the arg of the work point
	beta 
	gamma
	*/
	double alpha, beta, gamma;

	alpha =arg(wk[0],wk[1]);
	beta = acos((pow(L1,2)+pow(L2,2)-pow(wk[0],2)-pow(wk[1],2))/(2*L1*L2));
	gamma = (PI-beta)/2;

	//
	//determine use which solve
	//
	/*
	the calculate of beta will comes out duplicated solves
	*/
	double a = (pow(alpha-gamma-DegreeToRad(mkold[0]),2)+pow(PI-beta-DegreeToRad(mkold[1]),2));
	double b = (pow(alpha+gamma-DegreeToRad(mkold[0]),2)+pow(beta-PI-DegreeToRad(mkold[1]),2));

	bool solve= a<b?true:false;

	//
	//output
	//
	if (solve)
	{
	mk[0] = Rad2Deg(alpha-gamma);
	mk[1] = Rad2Deg(PI-beta);
	mk[2] = wk[2];
	}
	else
	{
	mk[0] = Rad2Deg(alpha+gamma);
	mk[1] = Rad2Deg(beta-PI);
	mk[2] = wk[2];
	}


	//
	//find last work point and compare
	//
	double wkold[3];
	mk2wk(mkold,wkold);

	//
	//critical motion
	//
	//BUG occur at from passover 0 point and I to IV
	if( abs(mk[0]-mkold[0])>30 ||abs(mk[1]-mkold[1])>30)
	{

		if(abs(abs(mk[0]-mkold[0])-360)<30 ||abs(abs(mk[1]-mkold[1])-360)<30)
		{
			//for some case, some value will over 360
			return;
		}
		/*
		30 means the max speed for the motor. This number is only used to check the degree change
		*/

		//change bool, re calculate
		if (!solve)
		{
			mk[0] = Rad2Deg(alpha-gamma);
			mk[1] = Rad2Deg(PI-beta);
			mk[2] = wk[2];
		}
		else
		{
			mk[0] = Rad2Deg(alpha+gamma);
			mk[1] = Rad2Deg(beta-PI);
			mk[2] = wk[2];
		}
	}

}