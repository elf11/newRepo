
#ifndef CUBE__H
#define CUBE__H

#include "TankIncludes.h"

class CubeModel : public Model
{
public :
	CubeModel(ModelManager * Manager) : Model(Manager)
	{
	};
	~CubeModel(void);

	void initCube(void);
};

#endif
