#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "dx8render.h"
#include "math3d/Triangle.h"
#include "matrix.h"

typedef bool (*ADD_POLYGON_FUNC)(const CVECTOR *v, long nv);

class COLLISION_OBJECT : public ENTITY
{
  public:
    virtual ~COLLISION_OBJECT(){};
    CMatrix mtx;

    virtual float Trace(const CVECTOR &src, const CVECTOR &dst) = 0;
    virtual bool Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius,
                      ADD_POLYGON_FUNC addpoly) = 0;

    virtual const char *GetCollideMaterialName() = 0;
    virtual bool GetCollideTriangle(Triangle &triangle) = 0;
};
#endif