#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED
#include "Utilities.h"

class Camera
{
protected:
    int w;
    int h;
    int wcx;
    int wcy;
    int mx;
    int my;
    float f_mx;
    float f_my;
    float * sin_tab;
    float * cos_tab;

    //lookup table variables
    int lt_idx; //lookup table index
    int dir_delta;  //which direction to rotate
    float st;   //sin of theta
    float ct;   //cos of theta

public:

    Camera(int _w, int _h) : w(_w), h(_w), wcx(_w / 2), wcy(_h / 2), mx(0), my(0)
    {
        lt_idx = 0;
        dir_delta = 0;
        f_mx = 0.0f;
        f_my = 0.0f;
        sin_tab = spacebash::sin_table;
        cos_tab = spacebash::cos_table;
        UpdateRotation(dir_delta);
    }

    void UpdateMouse(int x, int y)
    {
        mx = wcx - x;
        my = wcy - y;
        float percx = (float)mx / (float)wcx;
        float percy = (float)my / (float)wcy;
        float nx = percx * 35.0f;
        float ny = percy * 35.0f;

        f_mx = (nx * ct - ny * st);   //then rotate
        f_my = (ny * ct + nx * st);

        //f_mx = nx;
        //f_my = ny;
    }
    void StartBatch()
    {
        UpdateRotation(dir_delta);
    }
    void Transform(int * cx, int * cy, float * x, float * y, float z)
    {
        float tx = *x + f_mx;   //first translate
        float ty = *y + f_my;
        float nx = tx * ct - ty * st;   //then rotate
        float ny = ty * ct + tx * st;
        *cx = ((nx / z) * w) + wcx;
        *cy = ((ny / z) * h) + wcy;
    }
    void TransformRotate(int * cx, int * cy, float * x, float * y, float z)
    {
        float tx = *x;   //first translate
        float ty = *y;
        float nx = tx * ct - ty * st;   //then rotate
        float ny = ty * ct + tx * st;
        *cx = ((nx / z) * w) + wcx;
        *cy = ((ny / z) * h) + wcy;
    }
    void Project(int * cx, int * cy, float * x, float * y, float z)
    {
        float tx = *x;   //first translate
        float ty = *y;
        //float nx = tx * ct - ty * st;   //then rotate
        //float ny = ty * ct + tx * st;
        *cx = ((tx / z) * w) + wcx;
        *cy = ((ty / z) * h) + wcy;
    }
    void SetRotation(int delta)
    {
        dir_delta = delta;
    }
    void UpdateRotation(int dir)
    {
        lt_idx += dir;
        if (lt_idx > 360)
            lt_idx = lt_idx % 360;
        if (lt_idx < 0)
            lt_idx = 360 + lt_idx;
        st = sin_tab[lt_idx];
        ct = cos_tab[lt_idx];
    }
    int GetWidth()
    {
        return w;
    }
    int GetHeight()
    {
        return h;
    }

    //arbitrary functions to rotate objects in place around different axes
    void RotateArbX(float x, float * y, float * z, float yc, float zc, int angle)
    {
        int idx = angle;
        if (idx > 360)
            idx = idx % 360;
        if (idx < 0)
            idx = 360 + idx;
        float _st = sin_tab[idx];
        float _ct = cos_tab[idx];
        float ty = *y - (yc);
        float tz = *z - (zc);
        float ny = ty * _ct - tz * _st;
        float nz = ty * _st + tz * _ct;
        *y = ny + yc;
        *z = nz + zc;
    }

    void RotateArbY(float * x, float y, float * z, float xc, float zc, int angle)
    {
        int idx = angle;
        if (idx > 360)
            idx = idx % 360;
        if (idx < 0)
            idx = 360 + idx;
        float _st = sin_tab[idx];
        float _ct = cos_tab[idx];
        float tx = *x - (xc);
        float tz = *z - (zc);
        float nz = tz * _ct - tx * _st;
        float nx = tz * _st + tx * _ct;
        *x = nx + xc;
        *z = nz + zc;
    }
    void RotateArbZ(float * x, float * y, float z, float xc, float yc, int angle)
    {
        int idx = angle;
        if (idx > 360)
            idx = idx % 360;
        if (idx < 0)
            idx = 360 + idx;
        float _st = sin_tab[idx];
        float _ct = cos_tab[idx];
        float tx = *x - (xc);
        float ty = *y - (yc);
        float nx = tx * _ct - ty * _st;
        float ny = tx * _st + ty * _ct;
        *x = nx + xc;
        *y = ny + yc;
    }

};

#endif // CAMERA_HPP_INCLUDED
