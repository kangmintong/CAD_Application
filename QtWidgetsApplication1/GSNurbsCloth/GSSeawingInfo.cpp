#include "GSSeawingInfo.h"


void GSSeawingInfo::AddPair(GSNurbsCurve * c1, GSNurbsCurve * c2, bool trans)
{
	pairs.push_back(FreeCurvePair(CurvePair(c1->id, c2->id, trans)));
}
void GSSeawingInfo::AddPair(int id1, int id2, bool trans)
{
	pairs.push_back(FreeCurvePair(CurvePair(id1, id2, trans)));
}
void GSSeawingInfo::AddFreePair(FreeCurvePair & pair)
{
	pairs.push_back(pair);

}
void GSSeawingInfo::DeletePair(GSNurbsCurve * c)
{
	for (auto it = pairs.begin(); it != pairs.end(); it++)
	{
		if (it->isSimple)
		{
			if (c->id == it->first || c->id == it->second)
			{
				pairs.erase(it);
				return;
			}
		}
		else
		{
			//������������
			//�������߶˵��������߶��и��ģ�ֱ��ɾ��
			//�����Ż����������Ե����ʵ�ְ�
			if (c->id == it->curveOneStartId || c->id == it->curveTwoStartId)
			{
				pairs.erase(it);
				return;
			}
		}
	}
}

void GSSeawingInfo::DeletePair(FreeCurvePair * p)
{
	for (auto it = pairs.begin(); it != pairs.end(); it++)
	{
		if (p == &(*it))
		{
			pairs.erase(it);
			return;
		}
	}
}

int GSSeawingInfo::FindPairedCurve(GSNurbsCurve * c)
{
	//δ�ҵ�����-1
	for (auto &pair : pairs)
	{
		if (c->id == pair.first)
			return pair.second;
		if (c->id == pair.second)
			return pair.first;
	}

	return -1;
}

void GSSeawingInfo::UnselectAll()
{
	for (auto &cp : pairs)
	{
		cp.SetSelected(false);
	}
}

void CurvePair::SetSelected(bool isSel)
{
	isSelected = isSel;
}
