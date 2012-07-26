
#include "TankIncludes.h"
#include "utils\tinystr.h"
#include "utils\tinyxml.h"


LevelData::LevelData(void)
{
	loaded = 0;
	TerrainFileName = NULL;

	TerrainTexture = NULL;
	SkyModel = NULL;

	Tanks.Clean();
	Buildings.Clean();
	Props.Clean();
}

LevelData::~LevelData(void)
{

}

TeamData *LevelData::GetTeam(const char *Name)
{
	for (int i = 0;i < Teams.Length();i += 1)
	{
		if (strcmp(Teams[i]->TeamName,Name) == 0)
		{
			return Teams[i];
		}
	}
	return NULL;
}

void LevelData::LoadFromFile(char * FileName)
{
	if (loaded != 0)
	{
		return;
	}

	TiXmlDocument doc(FileName);
	if (!doc.LoadFile())
	{
		return;
	}

	TiXmlHandle hDoc(&doc);	
	TiXmlHandle hRoot(0); 
	
	TiXmlElement *pElem;	
	
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		return;
	}
	hRoot = TiXmlHandle(pElem);

	pElem = hRoot.Element();
	if (strcmp(pElem->Value(),"LevelData") != 0)
	{
		return;
	}
	for (TiXmlElement *sElem = pElem->FirstChildElement();sElem;sElem = sElem->NextSiblingElement())
	{
		if (strcmp(sElem->Value(),"TerrainFileName") == 0)
		{
			if (TerrainFileName == 0)
			{
				TerrainFileName = strdup(sElem->GetText());
			}
			continue;
		}
		if (strcmp(sElem->Value(),"TerrainTexture") == 0)
		{
			if (TerrainTexture == 0)
			{
				TerrainTexture = strdup(sElem->GetText());
			}
			continue;
		}
		if (strcmp(sElem->Value(),"MapWidthRatio") == 0)
		{
			sscanf(sElem->GetText(),"%f",&MapWidthRatio);
			continue;
		}
		if (strcmp(sElem->Value(),"MapHeightRatio") == 0)
		{
			sscanf(sElem->GetText(),"%f",&MapHeightRatio);
			continue;
		}
		if (strcmp(sElem->Value(),"MapVerticalRatio") == 0)
		{
			sscanf(sElem->GetText(),"%f",&MapVerticalRatio);
			continue;
		}
		if (strcmp(sElem->Value(),"SkyModel") == 0)
		{
			if (SkyModel == 0)
			{
				SkyModel = strdup(sElem->GetText());
			}
			continue;
		}
		if (strcmp(sElem->Value(),"Tank") == 0)
		{
			TankData *Tank = new TankData();
			Tanks.Push(Tank);
			Tank->Model = NULL;
			Tank->Name = NULL;
			Tank->Team = NULL;
			Tank->Scale.Set(1.0,1.0,1.0);
			for (TiXmlElement *tElem = sElem->FirstChildElement();tElem;tElem = tElem->NextSiblingElement())
			{
				if (strcmp(tElem->Value(),"Type") == 0)
				{
					if (strcmp(tElem->GetText(),"Player") == 0)
					{
						Tank->Type = tdtPlayer;
					}
					if (strcmp(tElem->GetText(),"AI") == 0)
					{
						Tank->Type = tdtAI;
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Team") == 0)
				{
					TeamData *Team = GetTeam(tElem->GetText());
					if (Team == NULL)
					{
						Team = new TeamData();
						Team->TeamID = Teams.Length() + 1;
						Team->TeamName = strdup(tElem->GetText());
						Teams.Push(Team);
					}
					Tank->Team = Team;
					continue;
				}
				if (strcmp(tElem->Value(),"Name") == 0)
				{
					if (Tank->Name == 0)
					{
						Tank->Name = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Model") == 0)
				{
					if (Tank->Model == 0)
					{
						Tank->Model = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"AI") == 0)
				{
					sscanf(tElem->GetText(),"%d",&Tank->AI);
					continue;
				}
				if (strcmp(tElem->Value(),"Pos") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Position.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Position.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Position.z);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Orient") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Orientation.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Orientation.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Orientation.z);
							continue;
						}
						if (strcmp(posElem->Value(),"W") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Orientation.w);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Scale") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Scale.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Scale.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Tank->Scale.z);
							continue;
						}
					}
					continue;
				}
			}
		}
		if (strcmp(sElem->Value(),"Building") == 0)
		{
			BuildingData *Building = new BuildingData();
			Buildings.Push(Building);
			Building->Model = NULL;
			Building->Name = NULL;
			Building->Team = NULL;
			Building->Scale.Set(1.0,1.0,1.0);
			for (TiXmlElement *tElem = sElem->FirstChildElement();tElem;tElem = tElem->NextSiblingElement())
			{
				if (strcmp(tElem->Value(),"Team") == 0)
				{
					TeamData *Team = GetTeam(tElem->GetText());
					if (Team == NULL)
					{
						Team = new TeamData();
						Team->TeamID = Teams.Length() + 1;
						Team->TeamName = strdup(tElem->GetText());
						Teams.Push(Team);
					}
					Building->Team = Team;
					continue;
				}
				if (strcmp(tElem->Value(),"Name") == 0)
				{
					if (Building->Name == 0)
					{
						Building->Name = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Model") == 0)
				{
					if (Building->Model == 0)
					{
						Building->Model = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"AI") == 0)
				{
					sscanf(tElem->GetText(),"%d",&Building->AI);
					continue;
				}

				if (strcmp(tElem->Value(),"Pos") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Position.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Position.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Position.z);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Orient") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Orientation.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Orientation.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Orientation.z);
							continue;
						}
						if (strcmp(posElem->Value(),"W") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Orientation.w);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Scale") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Scale.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Scale.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Building->Scale.z);
							continue;
						}
					}
					continue;
				}
			}
		}
		if (strcmp(sElem->Value(),"PropObject") == 0)
		{
			PropData *Prop = new PropData();
			Props.Push(Prop);
			Prop->Model = NULL;
			Prop->Name = NULL;
			Prop->Scale.Set(1.0,1.0,1.0);
			for (TiXmlElement *tElem = sElem->FirstChildElement();tElem;tElem = tElem->NextSiblingElement())
			{
				if (strcmp(tElem->Value(),"Name") == 0)
				{
					if (Prop->Name == 0)
					{
						Prop->Name = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Model") == 0)
				{
					if (Prop->Model == 0)
					{
						Prop->Model = strdup(tElem->GetText());
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Pos") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Position.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Position.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Position.z);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Orient") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Orientation.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Orientation.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Orientation.z);
							continue;
						}
						if (strcmp(posElem->Value(),"W") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Orientation.w);
							continue;
						}
					}
					continue;
				}
				if (strcmp(tElem->Value(),"Pos") == 0)
				{
					for (TiXmlElement *posElem = tElem->FirstChildElement();posElem;posElem = posElem->NextSiblingElement())
					{
						if (strcmp(posElem->Value(),"X") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Scale.x);
							continue;
						}
						if (strcmp(posElem->Value(),"Y") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Scale.y);
							continue;
						}
						if (strcmp(posElem->Value(),"Z") == 0)
						{
							sscanf(posElem->GetText(),"%f",&Prop->Scale.z);
							continue;
						}
					}
					continue;
				}
			}
		}
	}



	loaded = 1;
	return;

cleanup:;
	//cleanup in caz ca nu s-a incarcat
	loaded = 0;
	return;

/*

	{	
		pElem = hRoot.Element();
		

		for(pElem=hRoot.FirstChild().Element(); pElem;
  			pElem = pElem->NextSiblingElement())
 	    {
 	    	
			TiXmlElement *lElem;

			//for(lElem = (TiXmlElement*)pElem->FirstChild("TerrainFileName"); lElem;
			for(lElem = hRoot.FirstChild("TerrainFileName").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				const char *pKey = pElem->Value();
				const char *pText = pElem->GetText();

				strcpy(TerrainFileName, pText);
			}

			//for(lElem = (TiXmlElement *)pElem->FirstChild("TerrainTexture"); lElem;
			for(lElem = hRoot.FirstChild("TerrainTexture").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				const char *pKey = pElem->Value();
				const char *pText = pElem->GetText();

				strcpy(TerrainTexture, pText);
			}

			//for(lElem = (TiXmlElement *)pElem->FirstChild("MapWidthRatio"); lElem;
			for(lElem = hRoot.FirstChild("MapWidthRatio").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				const char *pKey = pElem->Value();
				const char *pText = pElem->GetText();

				sscanf(pText, "%d", MapWidthRatio);
			}

			//for(lElem = (TiXmlElement *)pElem->FirstChild("MapHeightRatio"); lElem;
			for(lElem = hRoot.FirstChild("MapHeightRatio").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				const char *pKey = pElem->Value();
				const char *pText = pElem->GetText();

				sscanf(pText, "%d", MapHeightRatio);
			}


			//for(lElem = (TiXmlElement *)pElem->FirstChild("SkyModel"); lElem;
			for(lElem = hRoot.FirstChild("SkyModel").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				const char *pKey = pElem->Value();
				const char *pText = pElem->GetText();

				strcpy(SkyModel, pText);
			}

			//for(lElem = (TiXmlElement *)pElem->FirstChild("Tank"); lElem;
			for(lElem = hRoot.FirstChild("Tank").Element(); lElem;
				lElem = lElem->NextSiblingElement())
			{
				TiXmlElement *current;
				TankData *tank = new TankData;

				for(current = (TiXmlElement *)lElem->FirstChild("Type"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();			
					if(strcmp(pText, "Player")) 
					{
						tank->Type = tdtPlayer;
					}
					if(strcmp(pText, "AI")) 
					{
						tank->Type = tdtAI;
					}
					
				}


				for(current = (TiXmlElement *)lElem->FirstChild("Team"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(tank->Team->TeamName, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Name"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(tank->Name, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Model"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(tank->Name, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("AI"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					sscanf(pText,"%d",&tank->AI);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Pos"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();
					
						sscanf(pText,"%d",&tank->Position.x);
					
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();
					
						sscanf(pText,"%d",&tank->Position.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText,"%d",&tank->Position.z);
					}
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Orient"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText,"%d",&tank->Orientation.x);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();
						
						sscanf(pText,"%d",&tank->Orientation.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText,"%d",&tank->Orientation.z);
					}
				}

				Tanks.Push(tank);
			}

			TanksNumber = Tanks.Length();

			//BUILDING STUFF GOES HERE

			for(lElem = (TiXmlElement *)pElem->FirstChild("Building"); lElem;
				lElem = lElem->NextSiblingElement())
			{
				TiXmlElement *current;
				BuildingData *building  = new BuildingData;

				for(current = (TiXmlElement *)lElem->FirstChild("Model"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(building->Model, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Team"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					sscanf(pText, "%d", building->TeamID);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Name"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(building->Name, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("AI"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					sscanf(pText, "%d", building->AI);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Pos"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Position.x);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Position.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Position.z);
					}
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Orient"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Orientation.x);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Orientation.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", building->Orientation.z);
					}
				}

				Buildings.Push(building);
			}

			BuildingsNumber = Buildings.Length();

			//OBJECT PROP GOES HERE!

			for(lElem = (TiXmlElement *)pElem->FirstChild("PropObject"); lElem;
				lElem = lElem->NextSiblingElement())
			{
				TiXmlElement *current;
				PropData *property = new PropData;

				for(current = (TiXmlElement *)lElem->FirstChild("Model"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(property->Model, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Name"); current;
				current = lElem->NextSiblingElement())
				{
					const char *pKey = pElem->Value();
					const char *pText = pElem->GetText();

					strcpy(property->Name, pText);
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Pos"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Position.x);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Position.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Position.z);
					}
				}

				for(current = (TiXmlElement *)lElem->FirstChild("Orient"); current;
				current = lElem->NextSiblingElement())
				{
					TiXmlElement *coord;

					for(coord = (TiXmlElement *)current->FirstChild("X"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Orientation.x);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Y"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Orientation.y);
					}

					for(coord = (TiXmlElement *)current->FirstChild("Z"); coord;
					coord = current->NextSiblingElement())
					{
						const char *pKey = pElem->Value();
						const char *pText = pElem->GetText();

						sscanf(pText, "%d", property->Orientation.z);
					}
				}

				Properties.Push(property);
			}

			PropsNumber = Properties.Length();
		}
	}*/
}


