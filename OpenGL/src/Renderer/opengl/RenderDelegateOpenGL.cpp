#include "RenderDelegateOpenGL.h"


#include "../../Scenegraph/geometry/PolygonalGeometry.h"
#include "../../Scenegraph/material/DiffuseMaterial.h"
#include "../../Scenegraph/material/TextureMaterial.h"
#include "RenderableHandlerOpenGL.h"
#include "BufferObjectOpenGL.h"



RenderDelegateOpenGL::RenderDelegateOpenGL()
	: mRenderer(RendererOpenGL())
	, mSceneSettings(SceneSettingsOpenGL())
{
}

RenderDelegateOpenGL::~RenderDelegateOpenGL()
{
}

void RenderDelegateOpenGL::setViewMatrix(const glm::mat4& matrix)
{
	mSceneSettings.setViewMatrix(matrix);
}

void RenderDelegateOpenGL::setProjectionMatrix(const glm::mat4& matrix)
{
	mSceneSettings.setProjectionMatrix(matrix);
}

void RenderDelegateOpenGL::initialize()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mRenderer.initialize();
}

void RenderDelegateOpenGL::commitScene(SceneItemSharedPtr scene)
{
	sceneGraphTraversal(scene, PG_COMMIT);
}


void RenderDelegateOpenGL::render(SceneItemSharedPtr scene, int animIndex, float deltatime)
{

	mDeltaTime = deltatime;
	mIndex = animIndex;




	glClearColor(0.20f, 0.20f, 0.20f, 0.20f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderHandlerOpenGLSharedPtr shader_handler =
		std::dynamic_pointer_cast<ShaderHandlerOpenGL>(
			mRenderer.getShaderHandler(PG_DEFAULT_SHADER));



	sceneGraphTraversal(scene, PG_RENDER);
}

void RenderDelegateOpenGL::sceneGraphTraversal(SceneItemSharedPtr node,
	TraversalState state)
{
	if (node == nullptr)
	{
		return;
	}



	PolygonalGeometrySharedPtr mesh;

	mesh = std::dynamic_pointer_cast<PolygonalGeometry>(node);

	if (mesh)
	{
		if (state == PG_COMMIT)
		{
			RenderableHandlerOpenGLSharedPtr mesh_handler =
				std::dynamic_pointer_cast<RenderableHandlerOpenGL>(
					mRenderer.generatePolygonalGeometryHandler(
						mesh->getVertices(),
						mesh->getIndices(),
						mesh->getNumberOfVertices(),
						mesh->getNumberOfIndices(),
						mRenderer.getNativePrimitiveType(
							mesh->getPrimitiveType())));
			mesh->setRenderableHandler(mesh_handler);

			IMaterialSharedPtr mesh_material = mesh->getMaterial();

			DiffuseMaterialSharedPtr diffuse_material =
				std::dynamic_pointer_cast<DiffuseMaterial>(
					mesh_material);

			if (diffuse_material)
			{
				// TODO: If the diffuse material is
				// refactored, we can remove this binding
				// and unbinding of the mesh before
				// commiting resources of the diffuse
				// material to the renderer
				mesh_handler->bind();
				diffuse_material->setColorPerVertexHandler(
					mRenderer.generateBufferObject(
						diffuse_material->getColorPerVertex(),
						diffuse_material->getNumberOfVertices()));
				mesh_handler->unbind();
			}

			TextureMaterialSharedPtr texture_material
				= std::dynamic_pointer_cast<TextureMaterial>(
					mesh_material);

			if (texture_material)
			{
				texture_material->setTextureHandler(
					mRenderer.generateTextureHandler(
						texture_material->getTexturePath()));
			}

			if (mesh_material)
			{
				mesh_material->setShader(
					mRenderer.getShaderHandler(
						mesh_material->getShaderProgramType()));
			}
		}
		else if (state == PG_RENDER)
		{
			RenderableHandlerOpenGLSharedPtr mesh_handler =
				std::dynamic_pointer_cast<RenderableHandlerOpenGL>(
					mesh->getRenderableHandler());

			ShaderHandlerOpenGLSharedPtr shader_handler =
				std::dynamic_pointer_cast<ShaderHandlerOpenGL>(
					mRenderer.getShaderHandler(
						mesh->getMaterial()->getShaderProgramType()));
			mSceneSettings.setShaderHandler(shader_handler);

			mSceneSettings.setModelMatrix(mesh->getTransform());
			mSceneSettings.setJointMatrix(mesh->getJointMatrix(mIndex, mDeltaTime));
			mesh_handler->bind();
			mesh->getMaterial()->bind();
			mSceneSettings.applyProjectionMatrix();
			mSceneSettings.applyViewMatrix();
			mSceneSettings.applyModelMatrix();
			mSceneSettings.applyJointMatrix();

			mesh_handler->render();
			mesh->getMaterial()->unbind();
			mesh_handler->unbind();

		}
	}

	size_t total = node->getChildren().size();
	for (size_t i = 0; i < total; ++i)
	{
		SceneItemSharedPtr child_node = node->getChildren()[i];
		child_node->setWorldTransform(node->getTransform());
		child_node->setWorldJoint(node->getJointMatrix(mIndex, mDeltaTime));
		sceneGraphTraversal(child_node, state);
	}
}
