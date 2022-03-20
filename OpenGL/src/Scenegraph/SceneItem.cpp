#include "SceneItem.h"
#include "material/IShaderMaterial.h"
#include <iostream>

SceneItem::SceneItem()
	: mWorldTransform(glm::mat4(1))
	, mLocaltransform(glm::mat4(1))
	, mStaticJoint(glm::mat4(1))
	, mWorldJoint(glm::mat4(1))
	, mAbsoluteRotation(glm::mat4(1))
	, mHasCustomMaterial(false)
{
}

SceneItem::~SceneItem()
{
}

void SceneItem::setScale(const float x,
	const float y)
{
	mLocaltransform = glm::scale(mLocaltransform, glm::vec3(x,
		y, y));
}

void SceneItem::setScale(const glm::vec3& vector)
{
	mLocaltransform = glm::scale(mLocaltransform, vector);
}

void SceneItem::setRotation(const glm::quat& rotation)
{
	mLocaltransform *= glm::toMat4(rotation);
}

void SceneItem::setTranslation(const glm::vec3& vector)
{
	mLocaltransform = glm::translate(mLocaltransform, vector);
}

void SceneItem::setRotation(float angle,
	const glm::vec3& direction)
{
	mLocaltransform = glm::rotate(mLocaltransform, angle,
		direction);
}

void SceneItem::setAbsoluteRotation(float angle, const glm::vec3& direction)
{

	mAbsoluteRotation = glm::rotate(glm::mat4(1.0), angle,
		direction);
}

void SceneItem::setLocalTransform(glm::mat4 matrix)
{
	mLocaltransform = matrix;
}

void SceneItem::setWorldTransform(glm::mat4 matrix)
{
	mWorldTransform = matrix;
}

void SceneItem::addChild(SceneItemSharedPtr child)
{
	mChildren.push_back(child);
}

std::vector<SceneItemSharedPtr>& SceneItem::getChildren()
{
	return mChildren;
}

glm::mat4 SceneItem::getTransform()
{
	return  mWorldTransform * mLocaltransform;
}

glm::mat4 SceneItem::getJointMatrix(int animIndex, float deltaTime)
{
	return mWorldJoint * mStaticJoint;
}

const glm::mat4& SceneItem::getWorldTransform()
{
	return mWorldTransform;
}

std::string SceneItem::getID() const
{
	return mID;
}

void SceneItem::setID(const std::string& iD)
{
	mID = iD;
}

void SceneItem::setCustomMaterial(IShaderMaterialSharedPtr value)
{
	mCustomMaterial = value;
	mHasCustomMaterial = true;
}

bool SceneItem::hasCustomMaterial() const
{
	return mHasCustomMaterial;
}

IShaderMaterialSharedPtr SceneItem::getCustomMaterial() const
{
	return mCustomMaterial;
}

void SceneItem::setWorldJoint(const glm::mat4 worldJoint)
{
	mWorldJoint = worldJoint;
}

glm::mat4 SceneItem::getWorldJoint() const
{
	return mWorldJoint;
}

