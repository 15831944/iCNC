#include <StdAfx.h>
#include "..\INC\UTIL.h"



void DeleteSpace(string *s){
    int index=0;
    *s += ' '; //強制後方補空格，避免出現後方s->at(index)溢位
    
    while (index < s->length()) {
        while (
               s->at(index) != ' ' &&
               s->at(index) != '\t' &&
               s->at(index) != ' ' 
               )
        {
            index++;
        }//尋找空白位置
        s->erase(index,1); //去空白
    }
}

double theta(double x,double y){
    double degree;
    //首先判斷象限
    degree = atan2(y, x)*360/2/PI;

    
    
    return degree;
}
//從原點到某點的直線與x_axis的夾角
double point_distance(double x1,double y1,double x2,double y2){
    double x,y,d;
    x = x2 - x1;x = pow(x, 2);
    y = y2 - y1;y = pow(y, 2);
    d = sqrt(x+y);
    
    return d;
}

double rem(double *a,int b){
    double r;
    int a_R;
    a_R = (int)*a;
    
    r = (a_R % b) + *a - a_R;
    return r;
}
double DegreeToRad(double d){
    return d*PI/180;
}
double Rad2Deg(double rad){
    return rad*180/PI;
}

double arg(double RE, double IM)
{
    double theta = 0;
    //-180 < theta <= 180
    if (RE == 0 && IM == 0)
    {
        //(0,0)
        theta = 0;
    }
    else if(RE == 0 && IM>0)
    {
        //90
        theta = PI/2;
    }
    else if(RE == 0 && IM<0)
    {
        //270
        theta = 3*PI/2;
    }
    else if(RE > 0 && IM==0)
    {
        //0
        theta = 0;
    }
    else if(RE < 0 && IM==0)
    {
        //180
        theta = PI;
    }
    else if(RE > 0 && IM>0)
    {
        //I
        theta = atan(IM/RE);
    }
    else if(RE < 0 && IM>0)
    {
        //II
        theta = PI+atan(IM/RE);
    }
    else if(RE < 0 && IM<0)
    {
        //III
        theta = atan(IM/RE)+PI;
    }
    else if(RE > 0 && IM<0)
    {
        //IV
        theta = 2*PI+atan(IM/RE);
    }
    
    
    return theta;
}



void clearMat(double mat[3])
{


	for (int i = 0; i<3; i++)
	{
		mat[i] = 0;
	}
}

void clearByteSpace(char *startPtr, int size)
{
	for(int i = 0 ; i < size ; i++)
	{
		*startPtr = 0; 
		startPtr ++;
	}
}

double xyzDistance(double x,double y, double z)
{
    return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));

}

double Force360(double deg)
{
    int int_deg = (int)deg;
    double rem_deg = deg-int_deg;
    if(deg>=0)
    {
        return int_deg%360+rem_deg;
    }
    else
    {
        return int_deg%360+rem_deg+360;
    }

}