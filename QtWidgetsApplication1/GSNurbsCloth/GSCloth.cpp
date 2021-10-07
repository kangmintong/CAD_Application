

#include "GSCloth.h"








void GSCloth::RefreshPair()
{

	for (auto &pair : seawingInfo.pairs)
	{
		if (pair.isSimple)
		{
			bool firstExist = false;
			bool secondExist = false;

			for (auto &p : pieces)
			{
				for (auto &c : p.curves)
				{
					if (pair.first == c.id) firstExist = true;
					if (pair.second == c.id) secondExist = true;
				}

				for (auto ip : p.innerPieces)
				{
					for (auto &c : ip.curves)
					{
						if (pair.first == c.id) firstExist = true;
						if (pair.second == c.id) secondExist = true;
					}
				}
				for (auto id : p.innerDarts)
				{
					for (auto &c : id.curves)
					{
						if (pair.first == c.id) firstExist = true;
						if (pair.second == c.id) secondExist = true;
					}
				}
			}

			if (firstExist && secondExist) continue;

			else pair.first = -1;
		}
		else
		{
			//free curve
			//����
		}
	}

	//��first==-1��pair���л����Դ���

	for (auto iter = seawingInfo.pairs.begin(); iter != seawingInfo.pairs.end();)
	{
		if (iter->isSimple)
		{
			if (iter->first == -1)
				seawingInfo.pairs.erase(iter++);
			else
				++iter;
		}
		else
		{
			//free curve
			//����֤һ��
			if( !this->GetCurveByID(iter->curveOneStartId) ||
				!this->GetCurveByID(iter->curveOneEndId) ||
				!this->GetCurveByID(iter->curveTwoStartId) ||
				!this->GetCurveByID(iter->curveTwoEndId))
			{
				seawingInfo.pairs.erase(iter++);
			}
			else if (this->GetCurveByID(iter->curveOneStartId)->parentPiece != this->GetCurveByID(iter->curveOneEndId)->parentPiece ||
				this->GetCurveByID(iter->curveTwoStartId)->parentPiece != this->GetCurveByID(iter->curveTwoEndId)->parentPiece)
			{
				seawingInfo.pairs.erase(iter++);
			}
			else
				++iter;
		}
	}
	
	return;
}





bool GSCloth::HasPiece(GSNurbsPiece * p)
{
	for (auto &piece : pieces)
	{
		if (p == &piece) return true;
	}
	return false;
}

void  GSCloth::AddPiece(const GSNurbsPiece &p)
{
	pieces.push_back(p);
	pieces.back().id = commonID++;

	for (auto &c : pieces.back().curves)
	{
		c.id = commonID++;
	}
	for (auto &id : pieces.back().innerDarts)
	{
		id.id = commonID++;
		for (auto &c : id.curves)
		{
			c.id = commonID++;
		}
	}
	for (auto &ip : pieces.back().innerPieces)
	{
		ip.id = commonID++;
		for (auto &c : ip.curves)
		{
			c.id = commonID++;
		}
	}

	pieces.back().Refresh();
	return;
}

void GSCloth::RemovePiece(GSNurbsPiece * p)
{

	for (auto iter = GetPiecesVector().begin(); iter != GetPiecesVector().end(); iter++)
	{
		if (p == &(*iter))
		{
			iter = GetPiecesVector().erase(iter);
			break;
		}
	}
}

void GSCloth::BendPiece(GSNurbsPiece * p)
{

	for (auto iter = GetPiecesVector().begin(); iter != GetPiecesVector().end(); iter++)
	{
		if (p == &(*iter))
		{
			iter->radius = 0.1 ;
			break;
		}
	}
}

GSNurbsPiece * GSCloth::GetPieceByID(int id)
{
	for (auto &piece : pieces)	if (id == piece.id) return &piece;
	return nullptr;
}

GSNurbsCurve * GSCloth::GetCurveByID(int id)
{
	for (auto &piece : pieces)
	{
		for (auto &curve : piece.curves)
		{
			if (id == curve.id) return &curve;
		}
	}
	return nullptr;
}








void GSCloth::AddEdgeDart(GSNurbsCurve * curve, float posPercent, float width, float depth, bool isLeftSide)
{
	//��һ���������dart
	//�Զ��趨�����

	GSVec3D dartPos = curve->GetVecPercent(posPercent);

	float total = curve->GetLength();

	float p = width / total / 2;

	float startPercent = posPercent - p;
	float endPercent = posPercent + p;

	//�߽�Խ��Ļ����ܱ��и�
	if (startPercent <= 0.05f || endPercent >= 0.95f) return;

	//���Ķ�
	int newId1 = this->commonID;
	int newId2 = this->commonID+1;
	int newId3 = this->commonID+2;
	this->commonID += 3;
	GSVec3D pos1 = curve->GetVecPercent(startPercent);
	GSVec3D pos2 = curve->GetVecPercent(posPercent);
	GSVec3D pos3 = curve->GetVecPercent(endPercent);
	GSNurbsCurve *c = curve;
	c->parentPiece->SplitCurve(newId1, c, pos1);
	c = GetCurveByID(newId1);
	c->parentPiece->SplitCurve(newId2, c, pos2);
	c = GetCurveByID(newId2);
	c->parentPiece->SplitCurve(newId3, c, pos3);

	//ƽ���м��--�ݲ�ƽ�ƣ����û����е���


	//���id1��id2
	this->seawingInfo.AddPair(newId1, newId2, false);

	//�ֶ��������

}

