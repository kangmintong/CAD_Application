#pragma once
#include <vector>
#include <unordered_set>
#include <list>
#include <memory>


class PieceTexCoordInfo
{
	//�ⲿ��ֱ�Ӵ���piece��
public:
	PieceTexCoordInfo();
	
	float scaleX;
	float scaleY;
	float degree;
	float offsetX;
	float offsetY;
	
};


//������
//PieceTexCoordController������Ҫ������
//����delfempuv�е�����
//ֻҪ����Ƭ�������ʷ�,texcoord�ع滮��ʱ��
//ʹ��PieceTexCoordController����ÿ����Ƭ���Ե�texcoord���б任
//һ����߼��� ����->��ת->ƽ��
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
