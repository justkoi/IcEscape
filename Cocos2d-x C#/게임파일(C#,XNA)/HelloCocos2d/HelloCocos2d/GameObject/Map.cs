using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;
using HelloCocos2d;

namespace HelloCocos2d.GameObject
{

    public class CMap
    {
        public int[,]	m_nBlockMap;


	    public void Init()
        {
            m_nBlockMap = new int[Define.D_BLOCKMAP_HEIGHT,Define.D_BLOCKMAP_WIDTH];
            //[Define.D_BLOCKMAP_HEIGHT][Define.D_BLOCKMAP_WIDTH]
            for(int i=0; i<Define.D_BLOCKMAP_HEIGHT; i++)
	        {
                for (int j = 0; j < Define.D_BLOCKMAP_WIDTH; j++)
		        {
			        m_nBlockMap[i,j] = 0;
		        }
	        }
        }
    }
}
