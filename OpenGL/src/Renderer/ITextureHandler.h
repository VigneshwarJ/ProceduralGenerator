#ifndef PG_ITEXTUREHANDLER_H
#define PG_ITEXTUREHANDLER_H

#include <string>

#include "../utilities/SmartTypePtr.h"



MAKE_SHARED(ITextureHandler);
class ITextureHandler
{
public:
	ITextureHandler();
	virtual ~ITextureHandler();

	virtual void bind(unsigned int  slot) = 0;
	virtual void unbind() = 0;
};

// namespace PG
#endif // PG_ITEXTUREHANDLER_H
