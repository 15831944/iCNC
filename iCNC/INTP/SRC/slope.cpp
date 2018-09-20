#include "StdAfx.h"
#include "..\INC\SLOPE.h"


SLOPE::SLOPE(double d,double v,double s,double t)
{
    _distance_total = d;
    _velocity_max = v;
    _acceleration = s;
    _cycleTime = t;

    init();
    
    Main();
    
}

SLOPE::SLOPE(double s,double t)
{

    _acceleration = s;
    _cycleTime = t;
    
    init();
    
}

void SLOPE::inputData(double d,double v)
{
    
    _distance_total = d;
    _velocity_max = v;
    
    init();

    
    Main();
    
}

void SLOPE::init()
{
    _distanceCal = _distance_total;
    _distanceRead = _distance_total;
    _time = 0;
    _length = 0;
    _cycleAccel = _acceleration*_cycleTime;
    _cycleLength = _cycleAccel*_cycleTime;
    _maxSpeed = 0;
    _nowVelocity = 0;
    
    _accelStep = 0;
    _decelStep = 0;
    _otherStep = 0;
    
    _rem_distance = 0;
    _rem_velocity = 0;
    
    acStep = 0;
    peStep = 0;
    deStep = 0;
    reStep = 0;
    
    rdIndex = 0;
    endValid = false;
    
    stopValid = false;
    
}

void SLOPE::stop()
{
    stopValid = true;
}

int SLOPE::length()
{
    return _length;
}
double SLOPE::remainDistance()
{
    if (_distanceRead<1e-6) {
        return 0;
    }
    return _distanceRead;
}

double SLOPE::read()
{
    double _output=0;
    if (rdIndex>_length-2) {
        endValid = true;
    }

    
    if (stopValid) {
        
        if (_nowVelocity<=_cycleAccel) {
            _output=0;
            endValid = true;
        }
        else
        {
            _output = _nowVelocity-_cycleAccel;
        }
    }
    else
    {
        if (rdIndex == 0)
        {
            _output=0;
        }
        else if (acStep<=rdIndex && rdIndex<peStep)
        {
            _output = _cycleAccel*rdIndex;
        }
        else if (peStep<=rdIndex && rdIndex<deStep)
        {
            _output = _velocity_max;
        }
        else if (deStep<=rdIndex && rdIndex<_length-1)
        {
            if (rdIndex < reStep && reStep!= 0) {
                _output = _cycleAccel*(_length-rdIndex-2);
            }
            else if (rdIndex == reStep && reStep!= 0) {
                _output = _rem_velocity;
            }
            else if (rdIndex > reStep && reStep!= 0)
            {
                _output = _cycleAccel*(_length-rdIndex-1);
            }
            else
            {
                _output = _cycleAccel*(_length-rdIndex-2);
            }
        }
        else if (rdIndex == _length-2)
        {
            _output = 0;
        }
        
    }
    _nowVelocity = _output;
    _distanceRead -= _output*_cycleTime;
    rdIndex++;
    return _output;
}

bool SLOPE::endInNextCycle()
{
    return endValid;
}



void SLOPE::Main()
{
    StepCalculate();
    Interpolation();
}

void SLOPE::StepCalculate()
{
    //
    //calculate steps
    //
    while (_distanceCal>0 ) {
        if (_velocity_max-_maxSpeed < _cycleAccel) {
            _otherStep++;
            _distanceCal -= _cycleTime*_velocity_max;
            _maxSpeed = _velocity_max;
        }
        else
        {
            if (_distanceCal>0) {
                _accelStep++;
                _distanceCal -= _accelStep*_cycleLength;
                _maxSpeed = _accelStep*_cycleAccel;
            }
            if (_distanceCal>0) {
                _decelStep++;
                _distanceCal -= _accelStep*_cycleLength;
            }
        }
        
    }
    
    //
    //deal remain distance
    //
    if (_distanceCal<0) {
        if (_otherStep>0) {
            _distanceCal += _cycleTime*_velocity_max;
            _otherStep--;
        }
        else if(_accelStep > _decelStep)
        {
            _distanceCal += _accelStep*_cycleLength;
            _accelStep--;
        }
        else
        {
            _distanceCal += _accelStep*_cycleLength;
            _decelStep--;
        }
        _rem_distance = _distanceCal;
        _rem_velocity = _rem_distance/_cycleTime;
        _distanceCal = 0;
    }
    else
    {
        _rem_distance = _distanceCal;
        _rem_velocity = _rem_distance/_cycleTime;
        _distanceCal = 0;
    }
    
    _length = 1+_accelStep+_otherStep+_decelStep+1 +1;
    //0, accel, other, decel, 0, remain
    _time = _length*_cycleTime;
    
    acStep = 1;
    peStep = acStep+_accelStep;
    deStep = peStep+_otherStep;
    
}



void SLOPE::Interpolation()
{
    if (_rem_distance<=1e-6) {
        return;
        //remain distance is less than motion tick
    }
    
    int index = 0;
    while (true) {
        if (index*_cycleAccel < _rem_velocity && _rem_velocity <= (index+1)*_cycleAccel)break;
        index++;
    }
    reStep=_length-2-index;
    
}