/*
 DECCore的順序如下：
 1. 逐行讀取數據->String
 2. 將單行數據變成單元數據->Ex.N120, G00...etc
 3. 將數據轉化成內部數據->Ex.rotate 30º, move to (10,20)...etc
 */
#ifndef DECCore_hpp
#define DECCore_hpp

#include "DECData.h"


class DECCore{
public:
    /*****/
    //建構函數，解構函數
    /*********/
    DECCore();
    ~DECCore();
    
    /*****/
    //Start or Restart
    /*********/
    bool DECStart();
    bool DECRestart();
    //成功回傳true,失敗回傳false
    
    //資料核心
    DECData *decData;
    string ncLoc;
    
    /*****/
    //解碼核心
    //成功回傳true,失敗回傳false
    /*********/
    bool ReadNcFile();
    //讀檔失敗需要回傳值
    bool DealData();
    //處理字串內容

    /*****/
    //處理單位數據
    /*********/
    void nFunction(DECData*,string);
    void gFunction(DECData*,string);
    bool mFunction(DECData*,string);
    void xFunction(DECData*,string);
    void yFunction(DECData*,string);
    void dFunction(DECData*,string);
    void fFunction(DECData*,string);
    

    void AddDecNode(DECData*);
    //連結下一個節點

    
};

#endif /* DEC_hpp */
