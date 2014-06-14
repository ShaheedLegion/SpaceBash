#include "Overlay.h"
#include "Utilities.h"


//    int nGyroPoints;
//    spacebash::Point * gyro;

Overlay::Overlay(BufferObject * surf, Camera * cam) : PlaneObject(surf, cam), nOculusPoints(8), nGyroPoints(12)
{
    oculus = new spacebash::Point[nOculusPoints];
    float oSize = 0.05f;
    SetPoint(&oculus[0], -oSize, 0.0f);
    SetPoint(&oculus[1], oSize, 0.0f);
    SetPoint(&oculus[2], 0.0f, -oSize);
    SetPoint(&oculus[3], 0.0f, oSize);

    float bSize = 0.1f;
    SetPoint(&oculus[4], -bSize, -bSize);
    SetPoint(&oculus[5], bSize, -bSize);
    SetPoint(&oculus[6], bSize, bSize);
    SetPoint(&oculus[7], -bSize, bSize);

    for (int i = 0; i < nOculusPoints; ++i)
        oculus[i].z = 6.0f;
    gyro = new spacebash::Point[nGyroPoints];
    float gSize = 0.25f;
    float tSize = 0.07f;
    SetPoint(&gyro[0], 0.0f, -gSize);
    SetPoint(&gyro[1], 0.0f, gSize);
    SetPoint(&gyro[2], -gSize, 0.0f);
    SetPoint(&gyro[3], gSize, 0.0f);
    SetPoint(&gyro[4], -tSize, -gSize);
    SetPoint(&gyro[5], tSize, -gSize);
    SetPoint(&gyro[6], gSize, -tSize);
    SetPoint(&gyro[7], gSize, tSize);
    SetPoint(&gyro[8], -tSize, gSize);
    SetPoint(&gyro[9], tSize, gSize);
    SetPoint(&gyro[10], -gSize, -tSize);
    SetPoint(&gyro[11], -gSize, tSize);

    for (int i = 0; i < nGyroPoints; ++i)
        gyro[i].z = 5.0f;
}

Overlay::~Overlay()
{
    delete [] gyro;
    delete [] oculus;
}

void Overlay::SetPoint(spacebash::Point * pt, float x, float y)
{
    pt->x = x;
    pt->y = y;
}

void Overlay::Update()
{
    spacebash::Point * p;
    for (int i = 0; i < nOculusPoints; ++i)
    {
        p = &oculus[i];
        camera->Project(&p->tx, &p->ty, &p->x, &p->y, p->z);
    }
    for (int i = 0; i < nGyroPoints; ++i)
    {
        p = &gyro[i];
        camera->TransformRotate(&p->tx, &p->ty, &p->x, &p->y, p->z);
    }

    spacebash::line(surface, 0xff1468E3, gyro[0].tx, gyro[0].ty, gyro[0].z, gyro[1].tx, gyro[1].ty, gyro[1].z);
    spacebash::line(surface, 0xff1468E3, gyro[2].tx, gyro[2].ty, gyro[2].z, gyro[3].tx, gyro[3].ty, gyro[3].z);

    spacebash::line(surface, 0xff14E333, gyro[4].tx, gyro[4].ty, gyro[4].z, gyro[5].tx, gyro[5].ty, gyro[5].z);
    spacebash::line(surface, 0xffE34114, gyro[6].tx, gyro[6].ty, gyro[6].z, gyro[7].tx, gyro[7].ty, gyro[7].z);
    spacebash::line(surface, 0xffE34114, gyro[8].tx, gyro[8].ty, gyro[8].z, gyro[9].tx, gyro[9].ty, gyro[9].z);
    spacebash::line(surface, 0xffE34114, gyro[10].tx, gyro[10].ty, gyro[10].z, gyro[11].tx, gyro[11].ty, gyro[11].z);

    spacebash::line(surface, 0xffff0000, oculus[0].tx, oculus[0].ty, oculus[0].z, oculus[1].tx, oculus[1].ty, oculus[1].z);
    spacebash::line(surface, 0xffff0000, oculus[2].tx, oculus[2].ty, oculus[2].z, oculus[3].tx, oculus[3].ty, oculus[3].z);

    spacebash::line(surface, 0xffffff00, oculus[4].tx, oculus[4].ty, oculus[4].z, oculus[5].tx, oculus[5].ty, oculus[5].z);
    spacebash::line(surface, 0xffffff00, oculus[5].tx, oculus[5].ty, oculus[5].z, oculus[6].tx, oculus[6].ty, oculus[6].z);
    spacebash::line(surface, 0xffffff00, oculus[6].tx, oculus[6].ty, oculus[6].z, oculus[7].tx, oculus[7].ty, oculus[7].z);
    spacebash::line(surface, 0xffffff00, oculus[7].tx, oculus[7].ty, oculus[7].z, oculus[4].tx, oculus[4].ty, oculus[4].z);
}
