#include "StdAfx.h"
#include "..\INC\circle.h"
#include "..\..\UTIL\INC\UTIL.h"


CIRCLE::CIRCLE(double A[2],double B[2],double O[2], bool dir)
{
    double r1 = sqrt(pow((A[0]-O[0]),2)+pow((A[1]-O[1]),2));
    double r2 = sqrt(pow((B[0]-O[0]),2)+pow((B[1]-O[1]),2));
    r = (r1+r2)/2;
    ST[0]=A[0];
    ST[1]=A[1];
    ED[0]=B[0];
    ED[1]=B[1];
    
    direct=dir;
    
    double ABdiv2[2];
    ABdiv2[0] = (A[0]+B[0])/2;
    ABdiv2[1] = (A[1]+B[1])/2;
    
    double d;
	if(pow(r,2)-pow((A[0]-ABdiv2[0]),2)-pow((A[1]-ABdiv2[1]),2)>1e-6)
	{
		d=sqrt(pow(r,2)-pow((A[0]-ABdiv2[0]),2)-pow((A[1]-ABdiv2[1]),2));
	}
	else
	{
		d=0;
	}
		  
	if((B[1]-A[1])<1e-6)
	{
		double a=pow((ABdiv2[0]+d),2)+pow((ABdiv2[1]),2);
		double b=pow((ABdiv2[0]-d),2)+pow((ABdiv2[1]),2);
		if(a<b)
		{
			OC[0]=ABdiv2[0];
			OC[1]=ABdiv2[1]+d;
		}
		else
		{
			OC[0]=ABdiv2[0];
			OC[1]=ABdiv2[1]-d;
		}
		
	}
	else
	{
		double dydx=-(B[0]-A[0])/(B[1]-A[1]);
    
		double a=pow(ABdiv2[0]+d*cos(atan(dydx)),2)+pow(ABdiv2[1]+d*sin(atan(dydx)),2);
		double b=pow(ABdiv2[0]-d*cos(atan(dydx)),2)+pow(ABdiv2[1]-d*sin(atan(dydx)),2);
		if(a<b)
		{
		OC[0]=ABdiv2[0]+d*cos(atan(dydx));
		OC[1]=ABdiv2[1]+d*sin(atan(dydx));
		}
		else
		{
		OC[0]=ABdiv2[0]-d*cos(atan(dydx));
		OC[1]=ABdiv2[1]-d*sin(atan(dydx));
		}
	}
    
}

void CIRCLE::nextPoint(double X[2],double Y[2], double speed)
{
    double theta=speed/r;
    double thetaX=arg((X[0]-OC[0]),(X[1]-OC[1]));
    double thetaY;
    if(direct)
    {
        thetaY=thetaX-theta;
    }
    else
    {
        thetaY=thetaX+theta;
    }
    
    Y[0]=OC[0]+r*cos(thetaY);
    Y[1]=OC[1]+r*sin(thetaY);
    
}

double CIRCLE::distance()
{
    //
    //determine cw or ccw
    //
    double theta=abs(arg((ED[0]-OC[0]),(ED[1]-OC[1]))-arg((ST[0]-OC[0]),(ST[1]-OC[1])));
    if(((ED[1]-OC[1])*(ST[0]-OC[0])-(ED[0]-OC[0])*(ST[1]-OC[1]))<0)
    {
       //ccw
        if (direct) {
            return r*theta;
        }
        else
        {
            return r*(2*PI-theta);
        }
        
    }
    else
    {
        //cw
        if (direct) {
            return r*(2*PI-theta);
        }
        else
        {
            return r*theta;
        }
        
    }
}
