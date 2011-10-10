#include "TestLifecycle.h"

#include "../../Platform/Application.h"

#include "../../Graphics/GraphicsSystem.h"

#if defined(LINUX)
	#include "../../Graphics/Platform/Linux/LinuxRenderPlatform.h"
#elif defined(PANDORA)
	#include "../../Graphics/Platform/Pandora/PandoraRenderPlatform.h"
#elif defined(ANDROID)
	#include "../../Graphics/Platform/Android/AndroidRenderContext.h"
#elif defined(IOS)
	#include "../../Graphics/Platform/iOS/iOSRenderPlatform.h"
#endif

#include "../../Events/EventSystem.h"
#include "../../Input/InputSystem.h"
#include "../../Input/Keyboard.h"

#include "../../Graphics/Camera.h"
#include "../../Graphics/Mesh.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/Texture.h"
#include "../../Maths/Matrix4.h"

#include "../../Resources/Resource.h"
#include "../../Resources/ResourceBank.h"
#include "../../Resources/ResourceManager.h"

#include "MVPUniformUpdater.h"
#include "Texture0UniformUpdater.h"

#include <cstdio>
#include "../../Graphics/Renderer/GLES11/FixedFunctionGlVboRenderer.h"
#include "../../Graphics/State/GLES1/GLES1State.h"

using namespace GLESGAE;

namespace LifecycleTest
{
	Resources::Id TextureBank = Resources::INVALID;
	Resources::Type Texture = 0U;
	namespace Textures
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id MrSmileyFace = Resources::INVALID;
	}
	
	Resources::Id ShaderBank = Resources::INVALID;
	Resources::Type Shader = 1U;
	namespace Shaders
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SpriteShader = Resources::INVALID;
	}
	
	Resources::Id CameraBank = Resources::INVALID;
	Resources::Type Camera = 2U;
	namespace Cameras
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SceneCamera = Resources::INVALID;
	}
	
	Resources::Id MeshBank = Resources::INVALID;
	Resources::Type Mesh = 3U;
	namespace Meshes
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id MrSmileyFace = Resources::INVALID;
	}
	
	Resources::Id ShaderUniformUpdaterBank = Resources::INVALID;
	Resources::Type ShaderUniformUpdater = 4U;
	namespace ShaderUniformUpdaters
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id MVPUpdater = Resources::INVALID;
		Resources::Id TextureUpdater = Resources::INVALID;
	}
	
	Resources::Id IndexBufferBank = Resources::INVALID;
	Resources::Type IndexBuffer = 5U;
	namespace IndexBuffers
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SpriteIndexBuffer = Resources::INVALID;
	}
	
	Resources::Id VertexBufferBank = Resources::INVALID;
	Resources::Type VertexBuffer = 6U;
	namespace VertexBuffers
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SpriteVertexBuffer = Resources::INVALID;
	}
	
	Resources::Id MaterialBank = Resources::INVALID;
	Resources::Type Material = 7U;
	namespace Materials
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SpriteMaterial = Resources::INVALID;
	}
	
	Resources::Id TransformBank = Resources::INVALID;
	Resources::Type Transform = 8U;
	namespace Transforms
	{
		Resources::Group TestGroup = Resources::INVALID;
		Resources::Id SpriteTransform = Resources::INVALID;
	}
	
	namespace Controllers
	{
		Controller::Id Keyboard = 0U;
	}
}

// Good 'ol Helper Functions
void controlCamera(Resource<Camera>& camera, Controller::KeyboardController* const keyboard);
Mesh* makeSprite(Resource<Shader>& shader, Resource<Texture>& texture);
Shader* makeSpriteShader();

void TestLifecycle::onCreate()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	EventSystem* eventSystem(application->getEventSystem());
	
	if (false == graphicsSystem->initialise("GLESGAE Application Lifecycle Test", 800, 480, 16, false)) {
		//TODO: OH NOES! WE'VE DIEDED!
	}
	
	eventSystem->bindToWindow(graphicsSystem->getCurrentWindow());
	
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	mScreenTarget = currentContext->createRenderTarget(RenderTarget::TARGET_SCREEN, RenderTarget::OPTIONS_WITH_COLOUR);
	currentContext->setRenderer(Resource<Renderer>(new FixedFunctionGlVboRenderer));
}

void TestLifecycle::onStart()
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	InputSystem* inputSystem(application->getInputSystem());
	
	ResourceBank<Texture>& textureBank(resourceManager->createBank<Texture>(LifecycleTest::Texture));
	LifecycleTest::TextureBank = textureBank.getId();
	
	ResourceBank<Shader>& shaderBank(resourceManager->createBank<Shader>(LifecycleTest::Shader));
	LifecycleTest::ShaderBank = shaderBank.getId();
	
	ResourceBank<Camera>& cameraBank(resourceManager->createBank<Camera>(LifecycleTest::Camera));
	LifecycleTest::CameraBank = cameraBank.getId();
	
	ResourceBank<Mesh>& meshBank(resourceManager->createBank<Mesh>(LifecycleTest::Mesh));
	LifecycleTest::MeshBank = meshBank.getId();
	
	ResourceBank<Material>& materialBank(resourceManager->createBank<Material>(LifecycleTest::Material));
	LifecycleTest::MaterialBank = materialBank.getId();
	
	ResourceBank<VertexBuffer>& vertexBank(resourceManager->createBank<VertexBuffer>(LifecycleTest::VertexBuffer));
	LifecycleTest::VertexBufferBank = vertexBank.getId();
	
	ResourceBank<IndexBuffer>& indexBank(resourceManager->createBank<IndexBuffer>(LifecycleTest::IndexBuffer));
	LifecycleTest::IndexBufferBank = indexBank.getId();
	
	ResourceBank<Matrix4>& transformBank(resourceManager->createBank<Matrix4>(LifecycleTest::Transform));
	LifecycleTest::TransformBank = transformBank.getId();
	LifecycleTest::Transforms::TestGroup = transformBank.newGroup();
	Resource<Matrix4>& newTransform(transformBank.add(LifecycleTest::Transforms::TestGroup, LifecycleTest::Transform, new Matrix4));
	LifecycleTest::Transforms::SpriteTransform = newTransform.getId();
	
	// Create Groups for Mesh resources
	LifecycleTest::Materials::TestGroup = materialBank.newGroup();
	LifecycleTest::VertexBuffers::TestGroup = vertexBank.newGroup();
	LifecycleTest::IndexBuffers::TestGroup = indexBank.newGroup();
		
	// Create Texture resources
	LifecycleTest::Textures::TestGroup = textureBank.newGroup();
	Resource<Texture>& texture(textureBank.add(LifecycleTest::Textures::TestGroup, LifecycleTest::Texture, new Texture));
	LifecycleTest::Textures::MrSmileyFace = texture.getId();
	texture->loadBMP("Texture.bmp");
	
	// Create Shader resources
	LifecycleTest::Shaders::TestGroup = shaderBank.newGroup();
	Resource<Shader>& shader(shaderBank.add(LifecycleTest::Shaders::TestGroup, LifecycleTest::Shader, makeSpriteShader()));
	LifecycleTest::Shaders::SpriteShader = shader.getId();
	
	// Create Mesh resources
	LifecycleTest::Meshes::TestGroup = meshBank.newGroup();
	Resource<Mesh>& mesh(meshBank.add(LifecycleTest::Meshes::TestGroup, LifecycleTest::Mesh, makeSprite(shader, texture)));
	LifecycleTest::Meshes::MrSmileyFace = mesh.getId();
	
	// Create Camera resources
	LifecycleTest::Cameras::TestGroup = cameraBank.newGroup();
	Resource<Camera>& camera(cameraBank.add(LifecycleTest::Cameras::TestGroup, LifecycleTest::Camera, new Camera(Camera::CAMERA_3D)));
	LifecycleTest::Cameras::SceneCamera = camera.getId();
	
	camera->getTransformMatrix().setPosition(Vector3(0.0F, 0.0F, 5.0F));

	Controller::KeyboardController* myKeyboard(inputSystem->newKeyboard());
	LifecycleTest::Controllers::Keyboard = myKeyboard->getControllerId();
	
	// Setup Fixed Function settings
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	Resource<GLES1State> currentState(currentContext->getRenderState().recast<GLES1State>());
	currentState->setTexturingEnabled(true);
	currentState->setVertexPositionsEnabled(true);
}

void TestLifecycle::onResume()
{
}

bool TestLifecycle::onLoop()
{
	Application* application(Application::getInstance());
	EventSystem* eventSystem(application->getEventSystem());
	InputSystem* inputSystem(application->getInputSystem());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	Resource<RenderState> currentState(currentContext->getRenderState());
	
	ResourceManager* resourceManager(application->getResourceManager());
	
	ResourceBank<Camera>& cameraBank(resourceManager->getBank<Camera>(LifecycleTest::CameraBank, LifecycleTest::Camera));
	Resource<Camera>& camera(cameraBank.get(LifecycleTest::Cameras::TestGroup, LifecycleTest::Cameras::SceneCamera));
	
	ResourceBank<Mesh>& meshBank(resourceManager->getBank<Mesh>(LifecycleTest::MeshBank, LifecycleTest::Mesh));
	Resource<Mesh>& mesh(meshBank.get(LifecycleTest::Meshes::TestGroup, LifecycleTest::Meshes::MrSmileyFace));
	
	ResourceBank<Matrix4>& transformBank(resourceManager->getBank<Matrix4>(LifecycleTest::TransformBank, LifecycleTest::Transform));
	Resource<Matrix4>& transform(transformBank.get(LifecycleTest::Transforms::TestGroup, LifecycleTest::Transforms::SpriteTransform));
	
	Controller::KeyboardController* myKeyboard(inputSystem->getKeyboard(LifecycleTest::Controllers::Keyboard));
	
	controlCamera(camera, myKeyboard);

	eventSystem->update();
	inputSystem->update();
	
	mScreenTarget->bind();
	currentState->setCamera(camera);
	currentContext->drawMesh(mesh, transform);
	currentContext->refresh();
	mScreenTarget->unbind();
	
	return !(myKeyboard->getKey(Controller::KEY_ESCAPE));
}

void TestLifecycle::onPause()
{
}

void TestLifecycle::onStop()
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	
	resourceManager->removeBank<Mesh>(LifecycleTest::MeshBank, LifecycleTest::Mesh);
	resourceManager->removeBank<Texture>(LifecycleTest::TextureBank, LifecycleTest::Texture);
	resourceManager->removeBank<Shader>(LifecycleTest::ShaderBank, LifecycleTest::Shader);
	resourceManager->removeBank<Camera>(LifecycleTest::CameraBank, LifecycleTest::Camera);
	
	resourceManager->removeBank<VertexBuffer>(LifecycleTest::VertexBufferBank, LifecycleTest::VertexBuffer);
	resourceManager->removeBank<IndexBuffer>(LifecycleTest::IndexBufferBank, LifecycleTest::IndexBuffer);
	resourceManager->removeBank<Matrix4>(LifecycleTest::TransformBank, LifecycleTest::Transform);
	resourceManager->removeBank<Material>(LifecycleTest::MaterialBank, LifecycleTest::Material);
}

void TestLifecycle::onDestroy()
{
}

Mesh* makeSprite(Resource<Shader>& shader, Resource<Texture>& texture)
{
	float vertexData[32] = {// Position - 16 floats
					-1.0F, 1.0F, 0.0F, 1.0F,
					1.0F, 1.0F, 0.0F, 1.0F,
					1.0F, -1.0F, 0.0F, 1.0F,
					-1.0F, -1.0F, 0.0F, 1.0F,
					// Tex Coords - 8 floats
					1.0F, 1.0F, 	// top right
					0.0F, 1.0F, 	// top left
					0.0F, 0.0F, 	// bottom left
					1.0F, 0.0F};	// bottom right

	unsigned int vertexSize = 25 * sizeof(float);

	unsigned char indexData[6] = { 0, 1, 2, 2, 3, 0 };
	unsigned int indexSize = 6 * sizeof(unsigned char);

	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());
	ResourceBank<Material>& materialBank(resourceManager->getBank<Material>(LifecycleTest::MaterialBank, LifecycleTest::Material));
	ResourceBank<VertexBuffer>& vertexBank(resourceManager->getBank<VertexBuffer>(LifecycleTest::VertexBufferBank, LifecycleTest::VertexBuffer));
	ResourceBank<IndexBuffer>& indexBank(resourceManager->getBank<IndexBuffer>(LifecycleTest::IndexBufferBank, LifecycleTest::IndexBuffer));

	Resource<VertexBuffer>& newVertexBuffer(vertexBank.add(LifecycleTest::VertexBuffers::TestGroup, LifecycleTest::VertexBuffer, new VertexBuffer(reinterpret_cast<unsigned char*>(&vertexData), vertexSize)));
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_POSITION_4F, 4U);
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_TEXTURE_2F, 4U);
	
	Resource<IndexBuffer>& newIndexBuffer(indexBank.add(LifecycleTest::IndexBuffers::TestGroup, LifecycleTest::IndexBuffer, new IndexBuffer(reinterpret_cast<unsigned char*>(&indexData), indexSize, IndexBuffer::INDEX_UNSIGNED_BYTE, IndexBuffer::FORMAT_TRIANGLES)));
	
	Resource<Material>& newMaterial(materialBank.add(LifecycleTest::Materials::TestGroup, LifecycleTest::Material, new Material));
	newMaterial->setShader(shader);
	newMaterial->addTexture(texture);

	return new Mesh(newVertexBuffer, newIndexBuffer, newMaterial);
}

void controlCamera(Resource<Camera>& camera, Controller::KeyboardController* const keyboard)
{
	Vector3 newPosition;
	camera->getTransformMatrix().getPosition(&newPosition);
	if (true == keyboard->getKey(Controller::KEY_ARROW_DOWN))
		newPosition.z() -= 0.01F;
	
	if (true == keyboard->getKey(Controller::KEY_ARROW_UP))
		newPosition.z() += 0.01F;
	
	if (true == keyboard->getKey(Controller::KEY_ARROW_LEFT))
		newPosition.x() -= 0.01F;
	
	if (true == keyboard->getKey(Controller::KEY_ARROW_RIGHT))
		newPosition.x() += 0.01F;
	camera->getTransformMatrix().setPosition(newPosition);
	
	camera->update();
}

#if defined(GLX)
	#include "../../Graphics/Context/Linux/GLee.h"
#endif

Shader* makeSpriteShader()
{
	std::string vShader =
		"attribute vec4 a_position;								\n"
		"attribute vec2 a_texCoord0;							\n"
		"varying vec2 v_texCoord0;								\n"
		"uniform mat4 u_mvp;									\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position =  u_mvp * a_position;					\n"
		"	v_texCoord0 = a_texCoord0;							\n"
		"}														\n";

	std::string fShader =
		#ifdef GLES2
		"precision mediump float;								\n"
		#endif
		"varying vec2 v_texCoord0;								\n"
		"uniform sampler2D s_texture0;							\n"
		"void main()											\n"
		"{														\n"
		"	gl_FragColor = texture2D(s_texture0, v_texCoord0);	\n"
		"	gl_FragColor.a = 1.0;								\n"
		"}														\n";

	#ifndef GLES1
		Shader* newShader(new Shader());
		newShader->createFromSource(vShader, fShader);

		return newShader;
	#else
		return 0;
	#endif
}

