#include "PieceTexCoord.h"

using namespace std;

PieceTexCoordInfo::PieceTexCoordInfo()
{
	scaleX = 1;
	scaleY = 1;
	degree = 0;
	offsetX = 0;
	offsetY = 0;
}


void PieceTexCoordController::SetScaleX(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_x, double x, double new_x)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (x == new_x) return;

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio = new_x / x;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] = current_x + (pUVArray[id * 2] - current_x) * ratio;
	}
	return;
}

void PieceTexCoordController::SetScaleY(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_y, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y) return;

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio = new_y / y;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2 + 1] = current_y + (pUVArray[id * 2 + 1] - current_y) * ratio;
	}

	return;
}

void PieceTexCoordController::SetScale(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_x, double current_y, double x, double new_x, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y)
	{
		PieceTexCoordController::SetScaleX(pUVArray, pIA_Elem, nElem, current_x, x, new_x);
		return;
	}
	else if (x == new_x)
	{
		PieceTexCoordController::SetScaleY(pUVArray, pIA_Elem, nElem, current_y, y, new_y);
		return;
	}

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio_x = new_x / x;
	double ratio_y = new_y / y;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] = current_x + (pUVArray[id * 2] - current_x) * ratio_x;
		pUVArray[id * 2 + 1] = current_y + (pUVArray[id * 2 + 1] - current_y) * ratio_y;
	}

	return;
}


void PieceTexCoordController::SetRotate(double *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double deg, double new_deg)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (deg == new_deg) return;

	double cent_x = -current_x;
	double cent_y = -current_y;

	//theta: -180~180
	double theta = new_deg - deg;
	if (theta > 180) theta -= 360;
	if (theta < -180) theta += 360;
	theta /= 180;
	theta *= 3.1415926535897932;

	double c = cos(theta);
	double s = sin(theta);
	double ta = (1 - c) * cent_x + s *cent_y;
	double tb = (1 - c) * cent_y + s * cent_x;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);
	for (unsigned int id : idset)
	{
		double x = pUVArray[id * 2];
		double y = pUVArray[id * 2 + 1];
		pUVArray[id * 2] = c*x - s*y + ta;
		pUVArray[id * 2 + 1] = s*x + c*y + tb;
	}
}

void PieceTexCoordController::SetOffsetX(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double x, double new_x)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (x == new_x) return;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset) pUVArray[id * 2] += new_x - x;
}

void PieceTexCoordController::SetOffsetY(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y) return;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset) pUVArray[id * 2 + 1] += new_y - y;
}

void PieceTexCoordController::SetOffset(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double x, double new_x, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y)
	{
		PieceTexCoordController::SetOffsetX(pUVArray, pIA_Elem, nElem, x, new_x);
		return;
	}
	else if (x == new_x)
	{
		PieceTexCoordController::SetOffsetY(pUVArray, pIA_Elem, nElem, y, new_y);
		return;
	}

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] += new_x - x;
		pUVArray[id * 2 + 1] += new_y - y;
	}

	return;
}

void PieceTexCoordController::SetScaleX(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_x, double x, double new_x)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (x == new_x) return;

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio = new_x / x;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] = current_x + (pUVArray[id * 2] - current_x) * ratio;
	}
	return;
}

void PieceTexCoordController::SetScaleY(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_y, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y) return;

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio = new_y / y;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2 + 1] = current_y + (pUVArray[id * 2 + 1] - current_y) * ratio;
	}

	return;
}

void PieceTexCoordController::SetScale(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double current_x, double current_y, double x, double new_x, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y)
	{
		PieceTexCoordController::SetScaleX(pUVArray, pIA_Elem, nElem, current_x, x, new_x);
		return;
	}
	else if (x == new_x)
	{
		PieceTexCoordController::SetScaleY(pUVArray, pIA_Elem, nElem, current_y, y, new_y);
		return;
	}

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	double ratio_x = new_x / x;
	double ratio_y = new_y / y;

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] = current_x + (pUVArray[id * 2] - current_x) * ratio_x;
		pUVArray[id * 2 + 1] = current_y + (pUVArray[id * 2 + 1] - current_y) * ratio_y;
	}

	return;
}


void PieceTexCoordController::SetRotate(float *pUVArray, unsigned int *pIA_Elem, unsigned int nElem, double current_x, double current_y, double deg, double new_deg)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (deg == new_deg) return;

	double cent_x = -current_x;
	double cent_y = -current_y;

	//theta: -180~180
	double theta = new_deg - deg;
	if (theta > 180) theta -= 360;
	if (theta < -180) theta += 360;
	theta /= 180;
	theta *= 3.1415926535897932;

	double c = cos(theta);
	double s = sin(theta);
	double ta = (1 - c) * cent_x + s *cent_y;
	double tb = (1 - c) * cent_y + s * cent_x;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);
	for (unsigned int id : idset)
	{
		double x = pUVArray[id * 2];
		double y = pUVArray[id * 2 + 1];
		pUVArray[id * 2] = c*x - s*y + ta;
		pUVArray[id * 2 + 1] = s*x + c*y + tb;
	}
}

void PieceTexCoordController::SetOffsetX(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double x, double new_x)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (x == new_x) return;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset) pUVArray[id * 2] += new_x - x;
}

void PieceTexCoordController::SetOffsetY(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y) return;

	unordered_set<unsigned int> idset;
	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset) pUVArray[id * 2 + 1] += new_y - y;
}

void PieceTexCoordController::SetOffset(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, double x, double new_x, double y, double new_y)
{
	if (pUVArray == 0 || pIA_Elem == 0 || nElem == 0) return;
	if (y == new_y)
	{
		PieceTexCoordController::SetOffsetX(pUVArray, pIA_Elem, nElem, x, new_x);
		return;
	}
	else if (x == new_x)
	{
		PieceTexCoordController::SetOffsetY(pUVArray, pIA_Elem, nElem, y, new_y);
		return;
	}

	unordered_set<unsigned int> idset;

	for (unsigned int i = 0; i < nElem * 3; i++) idset.insert(pIA_Elem[i]);

	for (unsigned int id : idset)
	{
		pUVArray[id * 2] += new_x - x;
		pUVArray[id * 2 + 1] += new_y - y;
	}

	return;
}



void PieceTexCoordController::Update(double * pUVArray, unsigned int * pIA_Elem, unsigned int nElem,
	const PieceTexCoordInfo & oldTexCoord, const PieceTexCoordInfo & newTexCoord)
{
	//Âß¼­Ë³Ðò: scale->rotate->move

	//undo
	PieceTexCoordController::SetOffset(pUVArray, pIA_Elem, nElem,
		oldTexCoord.offsetX, 0, oldTexCoord.offsetY, 0);
	PieceTexCoordController::SetRotate(pUVArray, pIA_Elem, nElem,
		0, 0, oldTexCoord.degree, 0);
	PieceTexCoordController::SetScale(pUVArray, pIA_Elem, nElem,
		0, 0, oldTexCoord.scaleX, 1, oldTexCoord.scaleY, 1);

	//redo
	PieceTexCoordController::SetScale(pUVArray, pIA_Elem, nElem,
		0, 0, 1, newTexCoord.scaleX, 1, newTexCoord.scaleY);
	PieceTexCoordController::SetRotate(pUVArray, pIA_Elem, nElem,
		0, 0, 0, newTexCoord.degree);
	PieceTexCoordController::SetOffset(pUVArray, pIA_Elem, nElem,
		0, newTexCoord.offsetX, 0, newTexCoord.offsetY);

}

void PieceTexCoordController::Update(float * pUVArray, unsigned int * pIA_Elem, unsigned int nElem, const PieceTexCoordInfo & oldTexCoord, const PieceTexCoordInfo & newTexCoord)
{
	//Âß¼­Ë³Ðò: scale->rotate->move

	//undo
	PieceTexCoordController::SetOffset(pUVArray, pIA_Elem, nElem,
		oldTexCoord.offsetX, 0, oldTexCoord.offsetY, 0);
	PieceTexCoordController::SetRotate(pUVArray, pIA_Elem, nElem,
		0, 0, oldTexCoord.degree, 0);
	PieceTexCoordController::SetScale(pUVArray, pIA_Elem, nElem,
		0, 0, oldTexCoord.scaleX, 1, oldTexCoord.scaleY, 1);

	//redo
	PieceTexCoordController::SetScale(pUVArray, pIA_Elem, nElem,
		0, 0, 1, newTexCoord.scaleX, 1, newTexCoord.scaleY);
	PieceTexCoordController::SetRotate(pUVArray, pIA_Elem, nElem,
		0, 0, 0, newTexCoord.degree);
	PieceTexCoordController::SetOffset(pUVArray, pIA_Elem, nElem,
		0, newTexCoord.offsetX, 0, newTexCoord.offsetY);

}
