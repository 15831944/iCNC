#ifndef Circle_h
#define Circle_h

class CIRCLE
{
public:
    CIRCLE(double A[2],double B[2],double O[2], bool dir);
    void nextPoint(double X[2],double Y[2],double speed);
    double distance();
    //from X to Y
    //direct: false:cw, true:ccw
private:
    bool direct;
    double r;
    double ST[2],ED[2],OC[2];
};
#endif /* Circle_h */