#include "openmv.h"
#include "stdio.h"
#include <stdlib.h>
int GetOpenmvDataCount = 0;
uint8_t Num = 0, LoR = 0, Finded_flag = 0, FindTask = 0;
uint8_t LastNum;
uint8_t NumCount = 0;
int Open_Num = 0;
uint16_t RxBuffer1[10] = {0};
Point Red_Point[Red_Num];
int A_Num = 0;	  // 收的是第几个数
int AVer_Num = 0; // 中心点坐标算出
int Long;
int Hide;
Point Black_Point[4] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0}};

// extern Point Red_center[1];
//  Point Black_Point[4] = {pointA, pointB, pointC, pointD};
extern uint8_t tem;

Point calculateCenter(Point points[], int numPoints) // 中心点坐标计算
{
	Point center;
	int sumX = 0;
	int sumY = 0;

	for (int i = 0; i < numPoints; i++)
	{
		sumX += points[i].x;
		sumY += points[i].y;
	}

	center.x = round(sumX / numPoints);
	center.y = round(sumY / numPoints);

	return center;
}
PointCount findMostFrequentPoint(Point points[], int numPoints)
{
	PointCount mostFrequent;
	mostFrequent.point = points[0];
	mostFrequent.count = 1;

	for (int i = 0; i < numPoints; i++)
	{
		int count = 1;

		for (int j = i + 1; j < numPoints; j++)
		{
			if (points[i].x == points[j].x && points[i].y == points[j].y)
			{
				count++;
			}
		}

		if (count > mostFrequent.count)
		{
			mostFrequent.point = points[i];
			mostFrequent.count = count;
		}
	}

	return mostFrequent;
}

void Open_Recive(void) // 放在定时器里接收
{

	if ((USART3_RX_STA & 0x8000)) // 摄像头部分
	{

		// LED_text;
		if (USART3_RX_BUF[0] == 0x2b)
		{

			Red_Point[A_Num].x = (int)USART3_RX_BUF[1];
			Red_Point[A_Num].y = (int)USART3_RX_BUF[2];
			A_Num++;
			if (A_Num == Red_Num)
			{
				A_Num = 0;
				// Red_center[0] = findMostFrequentPoint(Red_Point,Red_Num ).point;//求出现次数最多
				Red_center[0] = calculateCenter(Red_Point, Red_Num); // 求中心点
				AVer_Num = 1;
			}
		}

		USART3_RX_STA = 0;
		// u3_printf("%c", USART3_RX_BUF[0]);
		// HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		// USART3_RX_STA = 0;
	}
	if (USART2_RX_STA & 0x8000)

	{
		LED_text;
		if (USART3_RX_BUF[0] == 0x0d) // 帧头
		{
			{
				//				Black_Point[3].x = (int)USART3_RX_BUF[1]; // D点
				//				Black_Point[3].y = (int)USART3_RX_BUF[2];

				//				Black_Point[2].x = (int)USART3_RX_BUF[3]; // C点
				//				Black_Point[2].y = (int)USART3_RX_BUF[4];

				//				Black_Point[1].x = (int)USART3_RX_BUF[5]; // B点
				//				Black_Point[1].y = (int)USART3_RX_BUF[6];

				//				Black_Point[0].x = (int)USART3_RX_BUF[7]; // A点
				//				Black_Point[0].y = (int)USART3_RX_BUF[8];
				Black_Point[0].x = (int)USART3_RX_BUF[1];
				Black_Point[0].y = (int)USART3_RX_BUF[2];
				Hide = (int)USART3_RX_BUF[3];
				Long = (int)USART3_RX_BUF[4];
				Red_Point[A_Num].x = (int)USART3_RX_BUF[6];
				Red_Point[A_Num].y = (int)USART3_RX_BUF[7];
				A_Num++;
				if (A_Num == Red_Num)
				{
					A_Num = 0;
					// Red_center[0] = findMostFrequentPoint(Red_Point,Red_Num ).point;//求出现次数最多
					Red_center[0] = calculateCenter(Red_Point, Red_Num); // 求中心点
					AVer_Num = 1;
				}
			}
		}
	}
}
float distance(Point p1, Point p2) // 计算两点坐标
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(dx * dx + dy * dy);
}

Point nextVertex(Point P, Point vertices[], int numVertices)
{
	// 找到P点在Black数组中的索引
	int i;
	for (i = 0; i < numVertices; i++)
	{
		if (P.x == vertices[i].x && P.y == vertices[i].y)
		{
			break;
		}
	}

	// 根据索引i，找到P点的下一个顶点
	return vertices[(i + 1) % numVertices];
}
void Road_Go(Point *Black_Point, int numVertices)
{
	// Point Red_center = calculateCenter(Red_Point, 4); // 计算红点的中心点

	Point P = Black_Point[0];									  // 假设为最小距离点
	float min_distance = distance(Red_center[0], Black_Point[0]); // 寻找最小路径点
	for (int i = 1; i < numVertices; i++)
	{
		float temp_distance = distance(Red_center[0], Black_Point[i]);
		if (temp_distance < min_distance)
		{
			P = Black_Point[i]; // 寻找到最小距离点
			min_distance = temp_distance;
		}
	}

	PID_Duoji_Shang.target_val = P.y;
	PID_Duoji_Xia.target_val = P.x;
	while (abs(PID_Duoji_Shang.err) >= 2 || abs(PID_Duoji_Xia.err) >= 2)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		// next = nextVertex(P, vertices, 4);
	}

	for (int i = 0; i < numVertices; i++)
	{
		Point Start = P;
		Point next = nextVertex(P, Black_Point, numVertices); // 确认下一点的坐标
		// PID_Duoji_Shang.target_val = P.y;
		// PID_Duoji_Xia.target_val = P.x;
		//	while (((abs(next.x - P.x) > 2) || abs(next.y - P.y) > 2)) //没有和实际值比较
		while (abs(PID_Duoji_Shang.err) >= 2 || abs(PID_Duoji_Xia.err) >= 2)
		{
			// next = nextVertex(P, vertices, 4);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		P = next;
		PID_Duoji_Shang.target_val = next.y;
		PID_Duoji_Xia.target_val = next.x; // 进行舵机目标值的更换
										   // printf("Move to (%d, %d)\n\r", next.x, next.y);

		if (Start.x == P.x && Start.y == P.y) //
		{
			break;
		}
		// HAL_Delay(3000);
	}
}
Point *interpolatePoints(int x1, int y1, int x2, int y2, int *numPoints)
{
	int delta_x = abs(x2 - x1);
	int delta_y = abs(y2 - y1);

	*numPoints = (delta_x > delta_y) ? delta_x : delta_y;

	int dx = (x2 - x1) / *numPoints;
	int dy = (y2 - y1) / *numPoints;

	Point *points = (Point *)malloc((*numPoints + 1) * sizeof(Point));
	if (points == NULL)
	{
		printf("Error: Memory allocation failed.\n");
		return NULL;
	}

	for (int i = 0; i <= *numPoints; i++)
	{
		points[i].x = x1 + i * dx;
		points[i].y = y1 + i * dy;
	}

	return points;
}
void moveToPoint(Maichong target, Maichong *current)
{
	int dx = target.x - current->x;
	int dy = target.y - current->y;

	if (dx == 0 && dy == 0)
	{
		// 已经到达目标点，不需要移动
		return;
	}

	int stepX = dx > 0 ? 1 : -1;
	int stepY = dy > 0 ? 1 : -1;

	if (abs(dx) >= abs(dy))
	{
		// 在X轴上移动
		current->x += stepX;
	}
	else
	{
		// 在Y轴上移动
		current->y += stepY;
	}
}
