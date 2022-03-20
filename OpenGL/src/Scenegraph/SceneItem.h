#ifndef PG_SCENEITEM_H
#define PG_SCENEITEM_H

#include <vector>


#include "../utilities/SmartTypePtr.h"
#include "Vertex.h"
#include <string>


MAKE_SHARED(IShaderMaterial);
MAKE_SHARED(SceneItem);
class SceneItem
{
public:
	SceneItem();
	virtual ~SceneItem();

	void setTranslation(const glm::vec3& vector);

	void setScale(const float x,
		const float y);
	void setScale(const glm::vec3& vector);

	void setRotation(const glm::quat& rotation);
	void setRotation(float angle,
		const glm::vec3& direction);
	void setAbsoluteRotation(float angle,
		const glm::vec3& direction);

	void setLocalTransform(glm::mat4 matrix);
	void setWorldTransform(glm::mat4 matrix);

	void addChild(SceneItemSharedPtr child);

	std::vector<SceneItemSharedPtr>& getChildren();
	glm::mat4 getTransform();
	glm::mat4 getJointMatrix(int animIndex, float deltTime);
	const glm::mat4& getWorldTransform();

	std::string getID() const;
	void setID(const std::string& iD);

	void setCustomMaterial(IShaderMaterialSharedPtr value);
	bool hasCustomMaterial() const;
	IShaderMaterialSharedPtr getCustomMaterial() const;


	void setWorldJoint(const glm::mat4 worldJoint);

	glm::mat4 getWorldJoint() const;

	void setStaticJoint(const glm::mat4& staticJoint);

protected:
	glm::mat4 mWorldTransform;
	glm::mat4 mWorldJoint;
	glm::mat4 mStaticJoint;
	glm::mat4 mLocaltransform;
	glm::mat4 mAbsoluteRotation;


private:
	std::string mID;
	std::vector<SceneItemSharedPtr> mChildren;
	bool mHasCustomMaterial;
	IShaderMaterialSharedPtr mCustomMaterial;
};

inline void SceneItem::setStaticJoint(const glm::mat4& staticJoint)
{
	mStaticJoint = staticJoint;
}

// namespace PG
#endif // PG_SCENEITEM_H
