#ifndef PG_ISHADERMATERIAL_H
#define PG_ISHADERMATERIAL_H

#include "IMaterial.h"


MAKE_SHARED(IShaderMaterial);
class IShaderMaterial : public IMaterial
{
public:
	IShaderMaterial();
	virtual ~IShaderMaterial();
};

#endif // PG_ISHADERMATERIAL_H
