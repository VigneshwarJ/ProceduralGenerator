#ifndef PG_IBufferObject_H
#define PG_IBufferObject_H

#include "../utilities/SmartTypePtr.h"


MAKE_SHARED(IBufferObject);
class IBufferObject
{
public:
	IBufferObject();
	virtual ~IBufferObject();
};

#endif // PG_IBufferObject_H
