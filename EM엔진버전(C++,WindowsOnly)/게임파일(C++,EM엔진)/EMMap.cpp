#include "stdafx.h"

void CEMMap::Init()
{
	for(int i=0; i<D_BLOCKMAP_HEIGHT; i++)
	{
		for(int j=0; j<D_BLOCKMAP_WIDTH; j++)
		{
			m_nBlockMap[i][j] = 0;
		}
	}
}