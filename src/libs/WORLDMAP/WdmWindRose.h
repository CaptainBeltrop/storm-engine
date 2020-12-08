//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
//	WdmWindRose
//--------------------------------------------------------------------------------------------
//
//============================================================================================

#ifndef _WdmWindRose_H_
#define _WdmWindRose_H_

#include "WdmRenderModel.h"

class WdmWindRose : public WdmRenderModel
{
    struct Vertex
    {
        float x, y, z;
        dword c;
        float tu, tv;
    };
    //--------------------------------------------------------------------------------------------
    //Конструирование, деструктурирование
    //--------------------------------------------------------------------------------------------
  public:
    WdmWindRose();
    virtual ~WdmWindRose();

    //Расчёты
    void Update(float dltTime);

    void PRender(VDX8RENDER *rs){};
    void MRender(VDX8RENDER *rs){};
    void LRender(VDX8RENDER *rs);

    //--------------------------------------------------------------------------------------------
    //Инкапсуляция
    //--------------------------------------------------------------------------------------------
  private:
    long shadowTexture;
};

#endif