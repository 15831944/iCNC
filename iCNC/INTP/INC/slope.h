#ifndef SLOPE_h
#define SLOPE_h

class SLOPE
{
public:
    SLOPE(double d,double v,double s,double t);
    SLOPE(double s,double t);
    //initialize machine data
    
    void init();
    //initialize all data

    void inputData(double d,double v);//set new distance
    void stop();//deceleration to 0

    int length();
    double remainDistance();
    
    double read();
    bool endInNextCycle();
    
private:
    //define by user
    double _distance_total;    //input in [mm]
    double _velocity_max;      //input in [mm/s]
    double _acceleration;      //input in [mm/s^2]
    double _cycleTime;         //input in [s]
    
    //define by function
    double _distanceCal;           //using in calcu step
    double _distanceRead;           //using in read step
    double _nowVelocity;
    double _time;                  //total time [s] = length*cycletime
    int _length;                //total number of cycle
    double _cycleAccel;            //accelaration every cycle [m/s]
    double _cycleLength;           //define by _cycleAccel*_cycleTime [m]
    double _maxSpeed;
    
    int _accelStep;                //accelaration step before max speed
    int _decelStep;                //deceleration step before max speed
    int _otherStep;                 //step for high speed
    
    //calculate remain distance
    double _rem_distance;          //remain distance
    double _rem_velocity;          //remain velocity = remain distance/cycletime
    
    //read out
    int rdIndex;
    //end signal
    bool endValid;

    void Main();
    
    void StepCalculate();
    void Interpolation();

    //output[] = [mm/s] every cycle time
    
    //
    //output number
    //
    int acStep;
    int peStep;
    int deStep;
    int reStep;
    
    //
    //stop function
    //
    bool stopValid;

};


#endif 