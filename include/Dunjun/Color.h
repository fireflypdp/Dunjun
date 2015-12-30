#ifndef DUNJUN_COLOR_H
#define DUNJUN_COLOR_H

#include <Dunjun/Types.h>

namespace Dunjun
{
	union Color
	{
		u08 rgba[4];
		struct
		{
			u08 r, g, b, a;
		};
	};
}

#endif//DUNJUN_COLOR_H
