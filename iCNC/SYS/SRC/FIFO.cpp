#include "StdAfx.h"
#include "..\INC\FIFO.h"

FIFO_DATA::FIFO_DATA()
{
    nextPtr = nullptr;
}
void FIFO_DATA::dispose()
{
	block = nullptr;
    delete this;
    
}

FIFO::FIFO()
{
    init();
}
void FIFO::init()
{
    //
    //init
    //
    wrIndex = 0;
    rdIndex = 0;
    length = 0;
    status = 0;
    
    initPtr = nullptr;
    last_wrPtr = nullptr;
    now_wrPtr = nullptr;
    last_rdPtr = nullptr;
    now_rdPtr = nullptr;
}
void FIFO::reset()
{
    init();
}

void FIFO::wrFIFO(FIFO_DATA* wr_block)
{
    now_wrPtr = wr_block;
    if (initPtr == nullptr) {
        initPtr = now_wrPtr;
    }
    now_wrPtr->ID = wrIndex;
    
    if (last_wrPtr != nullptr) {
        last_wrPtr->nextPtr = now_wrPtr;
    }
    
    
    wrIndex++;
    length++;
    last_wrPtr = now_wrPtr;
}

FIFO_DATA* FIFO::rdFIFO()
{
    FIFO_DATA* rd_block;
    if (initPtr == nullptr )
    {
        //init is null
        return nullptr;
    }
    else if (rdIndex == 0)
    {
        //first queue
        
        now_rdPtr = initPtr;
        rdIndex++;
    }
    else if (rdIndex < length)
    {
        //loop reading
        if(last_rdPtr != nullptr)
		{
        now_rdPtr = last_rdPtr->nextPtr;
		}
        rdIndex++;
    }
    else
    {
        //error
        return nullptr;
    }
    

    
    rd_block = now_rdPtr;
    if (last_rdPtr != nullptr) {
        last_rdPtr -> nextPtr = nullptr; //break link after use
    }
    
    last_rdPtr = now_rdPtr; //go forward
    
    //delete now_wrPtr; /*delete after using. DO IT AFTER MOTION*/
    
    return rd_block;
}
