#ifndef PG_ISCENESETTINGS_H
#define PG_ISCENESETTINGS_H


#include "../utilities/SmartTypePtr.h"


MAKE_SHARED(ISceneSettings);
class ISceneSettings
{
public:
	ISceneSettings();
	virtual ~ISceneSettings();

	virtual void setViewMatrix(const glm::mat4 matrix) = 0;
	virtual void setProjectionMatrix(const glm::mat4 matrix) = 0;
	virtual void setModelMatrix(const glm::mat4 matrix) = 0;
	virtual void setJointMatrix(const glm::mat4 matrix) = 0;
};

#endif // PG_ISCENESETTINGS_H
