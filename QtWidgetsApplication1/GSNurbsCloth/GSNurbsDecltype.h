#pragma once 

//#define NURBS_U_MAX 1024
#define NURBS_U_MAX 128
#define NURBS_U_MAX_SIMULATION 8

//不考虑视图操作引入的误差，用于数据内部的重叠运算
#define ABS_DETECTION_LIMIT 0.1f

#define NURBS_DEG 2

enum ScaleDirection
{
	U,D,L,R,UL,UR,DL,DR
};
