#ifndef PG_IRENDERABLEHANDLER_H
#define PG_IRENDERABLEHANDLER_H

#include "../utilities/SmartTypePtr.h"


MAKE_SHARED(IRenderableHandler);
class IRenderableHandler
{
public:
	IRenderableHandler();
	virtual ~IRenderableHandler();
};

// namespace PG
#endif // PG_IRENDERABLEHANDLER_H
