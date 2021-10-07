#pragma once
#include <vector>
#include <unordered_set>
#include <list>
#include <memory>


class PieceTexCoordInfo
{
	//这部分直接存在piece中
public:
	PieceTexCoordInfo();
	
	float scaleX;
	float scaleY;
	float degree;
	float offsetX;
	float offsetY;
	
};


//工具类
//PieceTexCoordController作用主要体现在
//更新delfempuv中的坐标
//只要有衣片重三角剖分,texcoord重规划的时候
//使用PieceTexCoordController来对每个衣片各自的texcoord进行变换
//一般的逻辑是 缩放->旋转->平移
class PieceTexCoordController
{
	
public:

	PieceTexCoordController() {}

public:
	
	static void SetScaleX(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double x, double new_x);
	static void SetScaleY(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_y, double y, double new_y);
	static void SetScale(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double x, double new_x, double y, double new_y);
	static void SetRotate(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double deg, double new_deg);
	static void SetOffsetX(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double x, double new_x);
	static void SetOffsetY(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double y, double new_y);
	static void SetOffset(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double x, double new_x, double y, double new_y);

	static void SetScaleX(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double x, double new_x);
	static void SetScaleY(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_y, double y, double new_y);
	static void SetScale(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double x, double new_x, double y, double new_y);
	static void SetRotate(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double deg, double new_deg);
	static void SetOffsetX(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double x, double new_x);
	static void SetOffsetY(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double y, double new_y);
	static void SetOffset(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double x, double new_x, double y, double new_y);

	static void Update(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, const  PieceTexCoordInfo &oldTexCoord, const PieceTexCoordInfo &newTexCoord);
	static void Update(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, const  PieceTexCoordInfo &oldTexCoord, const PieceTexCoordInfo &newTexCoord);
	
};
