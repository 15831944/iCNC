#ifndef UTIL_h
#define UTIL_h

const double PI =3.141592653589793238463;
const float PI_F=3.14159265358979f;
#include <cmath>

#include <string>
using std::string;


void DeleteSpace(string*);
double theta(double,double);
double point_distance(double,double,double,double);
double rem(double*,int);
//
//degree
//
double DegreeToRad(double);
double Rad2Deg(double);
double arg(double,double);
double Force360(double);

void clearMat(double mat[3]);

//
//	CLEAR BYTE SPACE
//
void clearByteSpace(char*, int);


double xyzDistance(double,double,double);




#endif /* UTIL_hpp */
