#ifndef FIFO_h
#define FIFO_h
//*****************************************************************
// DEC_TO_INTP_BLOCK
//*****************************************************************
// NC command
//*****************************************************************
enum NC_CMD {
    NULL_CMD = 0,
    G00_MOTION,
    G01_MOTION,
    G02_MOTION,
    G03_MOTION,
    FUNCTION_CMD,
    G04_DWELL_TIME,
    GO_REFERENCE_POINT,
    M30_PROGRAM_END
};

//���Ѧ��I
//*****************************************************************
struct REFERENCE_POINT {
    int   axisPriority[3];  // xyz or uvw, 0: no; 1 first priority,
                            // [0][2][1] : z first go ref. point the y , x not
};
    
//M30�{������
//*****************************************************************
struct PROGRAM_END {
    char  programName[80];
    int   programNumber;
};

//G04���ݮɶ�
//*****************************************************************
struct DWELL_TIME {
    double   value;
    // time in s
};

//�Y�ɥ\��J�`
//*****************************************************************
union RT_FUNCTION {
    REFERENCE_POINT    referencePoint;
    PROGRAM_END        programEnd;
    DWELL_TIME         dwellTime;
};//rt function

//�ꥭ��
//*****************************************************************
enum PLANE {
    XY, YZ, XZ
};

//���V
//*****************************************************************
enum DIRECTION {
    CW,  CCW
};

//����|��J��T
//*****************************************************************
struct CIRCLE_INPUT {
    enum PLANE        plane;        /* XY, YZ, XZ, main plane for circle  */
    enum DIRECTION    direction;    /* cw or ccw                          */
    double            iCenter;      /* circle center correspond to x      */
    double            jCenter;      /* circle center correspond to y      */
    double            kCenter;      /* circle center correspond to z      */
	double			radius;
	bool			CenterValid;  //define use r or ijk
};

//�B�ʸ��|��T
//*****************************************************************
struct MOTION {
    double        feedrate;
    bool          relative; // G90:false; G91:true
    bool          m00;
    bool          m01;
    bool          g60;
    double        xyzCoordinate[3];    // end or goal position in xyz
    bool          xyzValid[3];         // xyz coordinate value sent
    double        uvwCoordinate[3];    // end or goal position in uvw
    bool          uvwValid[3];         // uvw coordinate value sent
    CIRCLE_INPUT  circleInput;
};//motion

//�B�ʩΥ\����O
//*****************************************************************
union MOTION_FUNCTION {
    MOTION       motion;
    RT_FUNCTION  rtFunction;
};

//NC��`
//*****************************************************************
class DEC2FIFO_BLOCK
{
public:
    int             lineNumber;
    NC_CMD          ncCommand;
    MOTION_FUNCTION motionFunction;
};





//
//fifo data
//
struct FIFO_DATA
{
    FIFO_DATA(); //init
    void dispose();
    
    
    //data
    void* block;
    
    int ID;
    FIFO_DATA* nextPtr;
};


//
//FIFO MAIN
//
class FIFO
{
public:
    FIFO();
    void init();
    void reset();
    
    //
    //write in
    //
    void wrFIFO(FIFO_DATA*);
    //
    //read out
    //
    FIFO_DATA* rdFIFO();
    
private:
    FIFO_DATA* initPtr;
    
    FIFO_DATA* last_wrPtr;
    FIFO_DATA* now_wrPtr;
    
    FIFO_DATA* last_rdPtr;
    FIFO_DATA* now_rdPtr;
    
    int wrIndex;
    int rdIndex;
    int length;
    int status;
    
};

#endif 