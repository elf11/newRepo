
#include "TankIncludes.h"

float ObstacleXoffset = 5.0;
float ObstacleZoffset = ObstacleXoffset;
float PathXoffset = ObstacleXoffset + 1.0;
float PathZoffset = PathXoffset;

MapNodeGraph::MapNodeGraph(void)
{
	NodeCount = -1;
}

MapNodeGraph::~MapNodeGraph(void)
{
}

int MapNodeGraph::GetIndex(MapNode &From,MapNode &To)
{
	if (NodeCount < 0)
	{
		return -1;
	}
	return From.IndexInList * NodeCount + To.IndexInList;
}

void MapNodeGraph::CreateFromLevelData(LevelData *Data)
{
	if (NodeCount >= 0)
	{
		return;
	}

	//Creaza lista de puncte

	NodeCount = Data->Buildings.Length() * 4;
	Nodes = new MapNode[NodeCount];

	BestDistances = new float[NodeCount * NodeCount];
	NextHop = new MapNode *[NodeCount * NodeCount];

	Vector3 pos1,pos2,posoff1,posoff2;
	Matrix mat,matoff;

	for (int i = 0;i < Data->Buildings.Length();i += 1)
	{
		Model *m = GAME->ModMan->GetModel(Data->Buildings[i]->Model);

		Matrix::CreateFromQuaternionTranslationScale(&Data->Buildings[i]->Orientation,&Data->Buildings[i]->Position,&Data->Buildings[i]->Scale,&mat);
		Matrix::CreateFromQuaternion(&Data->Buildings[i]->Orientation,&matoff);

		for (int k1 = 0;k1 < 4;k1 += 1)
		{
			Nodes[i * 4 + k1].IndexInList = i * 4 + k1;
			for (int k2 = 0;k2 < 4;k2 += 1)
			{
				Nodes[i * 4 + k1].BuildingNeighbours[k2] = &Nodes[i * 4 + k2];
			}
		}

		pos1 = m->BoundBox.center;
		pos1.x += m->BoundBox.offset.x;
		pos1.z += m->BoundBox.offset.z;
		posoff1.Set(PathXoffset,0.0,PathZoffset);
		Vector3::Transform(&pos1,&mat,&pos2);
		Vector3::Transform(&posoff1,&matoff,&posoff2);
		Nodes[i * 4 + 0].Pos = pos2 + posoff2;
		Nodes[i * 4 + 0].Pos.y = 5.0;

		pos1 = m->BoundBox.center;
		pos1.x += m->BoundBox.offset.x;
		pos1.z -= m->BoundBox.offset.z;
		posoff1.Set(PathXoffset,0.0,-PathZoffset);
		Vector3::Transform(&pos1,&mat,&pos2);
		Vector3::Transform(&posoff1,&matoff,&posoff2);
		Nodes[i * 4 + 1].Pos = pos2 + posoff2;
		Nodes[i * 4 + 1].Pos.y = 5.0;

		pos1 = m->BoundBox.center;
		pos1.x -= m->BoundBox.offset.x;
		pos1.z += m->BoundBox.offset.z;
		posoff1.Set(-PathXoffset,0.0,PathZoffset);
		Vector3::Transform(&pos1,&mat,&pos2);
		Vector3::Transform(&posoff1,&matoff,&posoff2);
		Nodes[i * 4 + 2].Pos = pos2 + posoff2;
		Nodes[i * 4 + 2].Pos.y = 5.0;

		pos1 = m->BoundBox.center;
		pos1.x -= m->BoundBox.offset.x;
		pos1.z -= m->BoundBox.offset.z;
		posoff1.Set(-PathXoffset,0.0,-PathZoffset);
		Vector3::Transform(&pos1,&mat,&pos2);
		Vector3::Transform(&posoff1,&matoff,&posoff2);
		Nodes[i * 4 + 3].Pos = pos2 + posoff2;
		Nodes[i * 4 + 3].Pos.y = 5.0;

	}

	//afla vecinii fiecarui punct
	Array<MapNode *> TempNodes;

	for (int i = 0;i < NodeCount;i += 1)
	{
		TempNodes.Clean();
		for (int j = 0;j < NodeCount;j += 1)
		{
			int direct = 1;
			for (int k = 0;k < Data->Buildings.Length();k += 1)
			{
				Model *m = GAME->ModMan->GetModel(Data->Buildings[k]->Model);
				m->BoundBox.offset.x += ObstacleXoffset / Data->Buildings[k]->Scale.x;
				m->BoundBox.offset.z += ObstacleZoffset / Data->Buildings[k]->Scale.z;

				Vector3 RS,RE;
				RS = Nodes[i].Pos;
				RE = Nodes[j].Pos;
				if (GameIntersection::RayBox3NoY(m->BoundBox,Data->Buildings[k]->Orientation,Data->Buildings[k]->Position,Data->Buildings[k]->Scale,RS,RE) >= 0.0)
				{
					m->BoundBox.offset.x -= ObstacleXoffset / Data->Buildings[k]->Scale.x;
					m->BoundBox.offset.z -= ObstacleZoffset / Data->Buildings[k]->Scale.z;
					direct = 0;
					goto outdincoldet;

				}
				m->BoundBox.offset.x -= ObstacleXoffset / Data->Buildings[k]->Scale.x;
				m->BoundBox.offset.z -= ObstacleZoffset / Data->Buildings[k]->Scale.z;

			}
			outdincoldet:;
			if (direct > 0)
			{
				TempNodes.Push(&Nodes[j]);
			}
		}
		Nodes[i].NeighboursCount = TempNodes.Length();
		if (Nodes[i].NeighboursCount == 0)
		{
			Nodes[i].Neighbours = NULL;
		}
		else
		{
			Nodes[i].Neighbours = new MapNode *[Nodes[i].NeighboursCount];
			for (int j = 0;j < Nodes[i].NeighboursCount;j += 1)
			{
				Nodes[i].Neighbours[j] = TempNodes[j];
			}
		}
	}

	//initializeaza distantele minime in graful initial

	for (int i = 0;i < NodeCount;i += 1)
	{
		for (int j = 0;j < NodeCount;j += 1)
		{
			BestDistances[GetIndex(Nodes[i],Nodes[j])] = 1e50;
			NextHop[GetIndex(Nodes[i],Nodes[j])] = ((MapNode *)(NULL));
		}
		for (int j = 0;j < Nodes[i].NeighboursCount;j += 1)
		{
			BestDistances[GetIndex(Nodes[i],*Nodes[i].Neighbours[j])] = (Nodes[i].Pos - Nodes[i].Neighbours[j]->Pos).Length();
			NextHop[GetIndex(Nodes[i],*Nodes[i].Neighbours[j])] = Nodes[i].Neighbours[j];
		}
	}

	//next hop

	for (int k = 0;k < NodeCount;k += 1)
	{
		for (int i = 0;i < NodeCount;i += 1)
		{
			for (int j = 0;j < NodeCount;j += 1)
			{
				float len = BestDistances[GetIndex(Nodes[i],Nodes[k])] + BestDistances[GetIndex(Nodes[k],Nodes[j])];
				if (len < BestDistances[GetIndex(Nodes[i],Nodes[j])])
				{
					BestDistances[GetIndex(Nodes[i],Nodes[j])] = len;
					NextHop[GetIndex(Nodes[i],Nodes[j])] = &Nodes[k];
				}
			}
		}
	}

}

void MapNodeGraph::DEBUG_DRAWNEIGHBOURS(void)
{
	if (NodeCount <= 0)
	{
		return;
	}

	VertexPosColor *Data = new VertexPosColor[NodeCount * 2];
	unsigned short *Index = new unsigned short[NodeCount * 2];
	for (int i = 0;i < NodeCount * 2;i += 1)
	{
		Index[i] = i;
	}
	for (int i = 0;i < NodeCount;i += 1)
	{
		for (int j = 0;j < Nodes[i].NeighboursCount;j += 1)
		{
			Data[j * 2 + 0].pos = Nodes[i].Pos;
			Data[j * 2 + 1].pos = Nodes[i].Neighbours[j]->Pos;

			Data[j * 2 + 0].color = Color::Magenta;
			Data[j * 2 + 1].color = Color::Magenta;
		}
		Matrix mat = Matrix::Identity;
		GAME->GameRenderer->SetModel(&mat);
		GAME->GameRenderer->DrawBuffer(GL_LINES,Data,Index,Nodes[i].NeighboursCount * 2);
	}

	delete[] Data;
	delete[] Index;
}

static float CenterX = 0.0;
static float CenterZ = 0.0;

int CompPoints(const void *p1,const void *p2)
{
	MapNode *N1 = *((MapNode **)(p1));
	MapNode *N2 = *((MapNode **)(p2));
	float D1 = ((N1->Pos.x - CenterX) * (N1->Pos.x - CenterX)) + ((N1->Pos.z - CenterZ) * (N1->Pos.z - CenterZ));
	float D2 = ((N2->Pos.x - CenterX) * (N2->Pos.x - CenterX)) + ((N2->Pos.z - CenterZ) * (N2->Pos.z - CenterZ));
	if (D1 > D2)
	{
		return 1;
	}
	if (D1 < D2)
	{
		return -1;
	}
	return 0;
}

float Atan2_360(float y,float x)
{
	float res = Math::Atan2(y,x);
	if (res < 0)
	{
		res += Math::TwoPi;
	}
	return res;
}

float Det3(Vector2 &p0,Vector2 &p1,Vector2 &p2)
{
	return 0.5 * (p1.x * p2.y - p1.y * p2.x - p0.x * p2.y + p0.y * p2.x + p0.x * p1.y - p0.y * p1.x);
}

float OrgInRect(MapNode *Nod)
{
	Vector2 P[4];
	Vector2 Z;
	Z.Set(0.0,0.0);

	for (int i = 0;i < 4;i += 1)
	{
		P[i].Set(Nod->BuildingNeighbours[i]->Pos.z - CenterZ,Nod->BuildingNeighbours[i]->Pos.x - CenterX);
	}

	float s;
	s = Det3(P[0],P[1],Z);
	if ((s * Det3(P[1],P[3],Z)) < 0)
	{
		return 0;
	}
	if ((s * Det3(P[3],P[2],Z)) < 0)
	{
		return 0;
	}
	if ((s * Det3(P[2],P[0],Z)) < 0)
	{
		return 0;
	}
	return 1;
}

void ReturnAngles(MapNode *Nod,float &min1,float &max1,float &min2,float &max2,int &count)
{
	if (OrgInRect(Nod))
	{
		count = 1;
		min1 = 0.0;
		max1 = Math::TwoPi;
		return;
	}

	float a[4];
	for (int i = 0;i < 4;i += 1)
	{
		a[i] = Atan2_360(Nod->BuildingNeighbours[i]->Pos.z - CenterZ,Nod->BuildingNeighbours[i]->Pos.x - CenterX);
	}

	int c[4] = {0,0,0,0};
	for (int i = 0;i < 4;i += 1)
	{
		if (a[i] <= Math::PiOver2)
		{
			c[0] += 1;
			continue;
		}
		if (a[i] <= Math::Pi)
		{
			c[1] += 1;
			continue;
		}
		if (a[i] <= Math::PiOver2 + Math::Pi)
		{
			c[2] += 1;
			continue;
		}
		c[3] += 1;
	}

	if ((c[0] > 0) && (c[3] > 0))
	{
		count = 2;

		min1 = Math::TwoPi * 2;
		max1 = Math::TwoPi;
		min2 = 0;
		max2 = -Math::TwoPi * 2;

		for (int i = 0;i < 4;i += 1)
		{
			if (a[i] <= Math::PiOver2)
			{
				max2 = Math::Max(max2,a[i]);
			}
			if (a[i] <= Math::PiOver2 + Math::Pi)
			{
				min1 = Math::Min(min1,a[i]);
			}
		}
	}
	else
	{
		count = 1;

		min1 = a[0];
		min1 = Math::Min(min1,a[1]);
		min1 = Math::Min(min1,a[2]);
		min1 = Math::Min(min1,a[3]);

		max1 = a[0];
		max1 = Math::Max(max1,a[1]);
		max1 = Math::Max(max1,a[2]);
		max1 = Math::Max(max1,a[3]);
	}
}

void MapNodeGraph::ComputeNeighbours(Vector3 Pos,Array<MapNode *> &Result)
{
	return ;
	Result.Clean();
	if (NodeCount <= 0)
	{
		return;
	}
	MapNode **TN = new MapNode*[NodeCount];
	for (int i = 0;i < NodeCount;i += 1)
	{
		TN[i] = &Nodes[i];
		TN[i]->TakenInNeighbourFind = 0;
	}

	CenterX = Pos.x;
	CenterZ = Pos.z;
	qsort(TN,NodeCount,sizeof(MapNode *),CompPoints);

	for (int i = 0;i < NodeCount;i += 1)
	{
		if (TN[i]->TakenInNeighbourFind != 0)
		{
			continue;
		}

		float min1,max1,min2,max2;
		int count;

		ReturnAngles(TN[i],min1,max1,min2,max2,count);

		for (int i = 0;i < count;i += 1)
		{

		}
	}


}
