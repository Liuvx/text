#ifndef __OPENMV_H
#define __OPENMV_H

#include "main.h"
#include "beep.h"
#include "pid_v.h"
#include "my_uart.h"
#include "math.h"

typedef struct
{
    int x;
    int y;
} Point; // 坐标储存

typedef struct
{
    int x;
    int y;
} Maichong; // 坐标储存

typedef struct
{
    Point point;
    int count;
} PointCount;

extern Point Red_Point[Red_Num];
extern Point Black_Point[4];
extern Point Red_center[1];
extern Point O_Center[1];
extern Point Bian_Point[5];

void Openmv_Receive_Data(uint8_t data);
void Open_Recive(void);
PointCount findMostFrequentPoint(Point points[], int numPoints);
float distance(Point p1, Point p2);
Point calculateCenter(Point points[], int numPoints); // 中心点坐标计算
Point nextVertex(Point P, Point vertices[], int numVertices);
void Road_Go(Point *Black_Point, int numVertices);
Point *interpolatePoints(int x1, int y1, int x2, int y2, int *numPoints); // 输出细分的数组
void moveToPoint(Maichong target, Maichong *current);
#endif
