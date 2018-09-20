#include <StdAfx.h>
#include "..\INC\DEC.h"
#include "..\..\UTILITY\INC\UTILITY.h"
#include <fstream>

using std::ios;
using std::fstream;
using std::getline;
using std::stod;
using std::stoi;

DECCore::DECCore(){
    decData = nullptr;
    ncLoc = "";
}
DECCore::~DECCore(){
    delete decData;
}

/*****/
//Start or Restart
/*********/
bool DECCore::DECStart(){
    if (ncLoc != "" && ReadNcFile() && DealData());
    //小括號內的東西會由左檢查到右
    else {return false;}
    return true;
}
bool DECCore::DECRestart(){
    decData = nullptr;
    if (ncLoc != "" && ReadNcFile() && DealData());
    else {return false;}
    return true;
}

/*****/
//添加Dec串列節點
/*********/
void DECCore::AddDecNode(DECData *newPtr){
    DECData *currentPtr;
    
    if (decData == nullptr) {
        decData = newPtr;
    }
    else {
        currentPtr = decData;
        while (currentPtr != nullptr) {
            if (currentPtr -> Next == nullptr) {
                currentPtr -> Next = newPtr;
                newPtr -> Prev = currentPtr;
                break;
            }
            currentPtr = currentPtr -> Next;
        }
    }
}

/*****解碼核心*********************************/
bool DECCore::ReadNcFile(){
    fstream NCfile;
    NCfile.open(ncLoc,ios::in);
    //檢查檔案是否成功開啟
    if(!NCfile){return false;}
    //在檔案讀取失敗的情形下，回傳false
    else{
        DECData *newPtr;

        string org_temp,line_temp;
        while (getline(NCfile,org_temp)) {
            newPtr = new DECData;
            newPtr -> SetOrgLineData(org_temp);
            line_temp = org_temp.substr(0,org_temp.find("//"));//除去雙斜線後的數值
            DeleteSpace(&line_temp);
            if (line_temp != "") {
                newPtr->SetLineData(line_temp);
                AddDecNode(newPtr);
            }
            //若是單行無數值，除去
        }
        NCfile.close();
    }
    return true;
    
}
bool DECCore::DealData(){
    int now_i=0,next_i=1;
    //now_i:現在字串處理位置;next_i:下一個字串處理的位置;
    
    DECData *nowPtr;
    nowPtr = this->decData;
    //現在處理的指標
    string dealing = "";
    //暫存單位資料
    bool end_mark = false;
    //檢驗m30是否存在，若是存在，則會在DEC檢查到m30時改為true
    
    while (nowPtr != nullptr){

        
    while (next_i < nowPtr->GetLineData().length()) {
        
        while (next_i < nowPtr->GetLineData().length()&& (nowPtr->GetLineData().at(next_i)<'A' || nowPtr->GetLineData().at(next_i)>'Z')){next_i++;}
        //PassDigit
        
        dealing.assign(nowPtr->GetLineData(),now_i,next_i-now_i);
        //dealing:字串單位 ex.G00,M30...etc
        
        switch (nowPtr->GetLineData().at(now_i)) {
            case 'N':
                nFunction(nowPtr,dealing);
                break;
            case 'G':
                gFunction(nowPtr,dealing);
                break;
            case 'M':
                if (mFunction(nowPtr,dealing)){
                    end_mark = true;
                }
                break;
            case 'X':
                xFunction(nowPtr,dealing);
                break;
            case 'Y':
                yFunction(nowPtr,dealing);
                break;
            case 'D':
                dFunction(nowPtr,dealing);
                break;
            case 'F':
                fFunction(nowPtr,dealing);
                break;
            default:
                nowPtr->SetMode(error);
                break;
        }

        now_i = next_i;
        next_i++;
        //進行下個字串的處理
        }
        
        /*****檢驗最終資料正確性*********************************/
        if (nowPtr->GetLineNum() == 0) {
            nowPtr->SetMode(error);
        }
        if (nowPtr->GetMode() == idle) {
            nowPtr->SetMode(error);
        }
        if (nowPtr->GetMode() == move && nowPtr->GetSpeed() ==0 && (nowPtr->GetX() != 0 || nowPtr->GetY() != 0)) {
            DECData *prevPtr;
            prevPtr = nowPtr;
            while (prevPtr != nullptr && prevPtr->GetSpeed() == 0) {
                prevPtr = prevPtr->Prev;
            }
            if (prevPtr != nullptr && prevPtr->GetSpeed() != 0) {
                nowPtr->SetSpeed(prevPtr->GetSpeed());
            }
            else{
                nowPtr->SetMode(error);
            }
        }
        if (nowPtr->GetMode() == rotate && nowPtr->GetDegree() == 0) {
            nowPtr->SetMode(error);
        }
        if (nowPtr->GetMode() == move && nowPtr->GetCoo() == NaN) {
            nowPtr->SetMode(error);
        }
        if (nowPtr->GetMode() == move && nowPtr->GetCoo() == rele && nowPtr->GetX() != 0) {
            nowPtr->SetMode(error);
        }
        if (nowPtr->GetMode() == rotate && nowPtr->GetCoo() == NaN) {
            nowPtr->SetMode(error);
        }
        /*****檢驗最終資料正確性*********************************/
        
        now_i=0,next_i=1;
        nowPtr = nowPtr->Next;
        //進行下段資料的處理
    }
    if (end_mark != true) {
        return false;
        //若是沒有結束碼，視同編譯失敗
    }
    
    return true;
    //例外情況不發生視同編譯成功
    
}



/*************
 單位解碼器
 *************/
//nFunction
/************************************************/
void DECCore::nFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    c->SetLineNum(stoi(s.substr(1)));
}
//gFunction
/************************************************/
void DECCore::gFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    if (s.substr(1) == "00") {
        c->SetMode(move);
    }
    else if (s.substr(1,2) == "04") {
        c->SetMode(timedelay);
        if (s.length() > 3) {
            c->SetDelay(stod(s.substr(3)));
        }
        else{
            c->SetMode(error);
        }
    }
    else if (s.substr(1) == "06") {
        c->SetMode(rotate);
        c->SetClockwise(cw);
    }
    else if (s.substr(1) == "07") {
        c->SetMode(rotate);
        c->SetClockwise(ccw);
    }
    else if (c->GetMode() != error && s.substr(1) == "90") {
        if (c->GetCoo() != NaN) {
            c->SetMode(error);
            return;
        }
        c->SetCoo(abso);
    }
    else if (c->GetMode() != error && s.substr(1) == "91") {
        if (c->GetCoo() != NaN) {
            c->SetMode(error);
            return;
        }
        c->SetCoo(rele);
    }
    else{
        c->SetMode(error);
    }
    
    
}
//mFunction
/************************************************/
bool DECCore::mFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return false;
    }
    if ( s.substr(1) == "30"){
        c->SetMode(close);
        return true;
    }
    else{
        c->SetMode(error);
        return false;
    }
}
//xFunction
/************************************************/
void DECCore::xFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    c->SetX(stod(s.substr(1)));
}
//yFunction
/************************************************/
void DECCore::yFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    c->SetY(stod(s.substr(1)));
}
//dFunction
/************************************************/
void DECCore::dFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    c->SetDegree(stod(s.substr(1)));
}
//fFunction
/************************************************/
void DECCore::fFunction(DECData *c,string s){
    if (c->GetMode() == error) {
        return;
    }
    c->SetSpeed(stod(s.substr(1)));
}
/************************************************/
