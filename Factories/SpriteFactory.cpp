#include "SpriteFactory.h"

#include "../Maths/Matrix4.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Shader.h"

#include "../Resources/ResourceManager.h"
#include "../Platform/Application.h"

using namespace GLESGAE;

Resources::Locator SpriteFactory::create(const Vector2& scale, const unsigned int u, const unsigned int v, const unsigned int s, const unsigned int t)
{
	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());

	Resource<Shader> shader;
	
	if (Resources::INVALID != mSettings.shader.bank) { // Shader bank isn't strictly necessary for Fixed Function, so we can safely ignore this.
		ResourceBank<Shader>& shaderBank(resourceManager->getBank<Shader>(mSettings.shader.bank, Resources::Shader));
		shader = (shaderBank.add(mSettings.shader.group, Resources::Shader, makeSpriteShader()));
	}
		
	const unsigned int texWidth(mTexture->getWidth());
	const unsigned int texHeight(mTexture->getHeight());
		
	// (0,0) is bottom left, we want it top left so that pixel co-ords match from a graphics editor.
	float texU(static_cast<float>(u) / texWidth);
	float texV(static_cast<float>(texHeight - v) / texHeight);
	float texS(static_cast<float>(s) / texWidth);
	float texT(static_cast<float>(texHeight - t) / texHeight);

	const float texelOffsetWidth(0.00125F);
	const float texelOffsetHeight(0.00125F);

	if (u > 0U)
		texU += texelOffsetWidth;
	if (v > 0U)
		texV += texelOffsetHeight;
	if (s < texWidth)
		texS += texelOffsetWidth;
	if (t < texHeight)
		texT += texelOffsetHeight;

	ResourceBank<Mesh>& meshBank(resourceManager->getBank<Mesh>(mSettings.mesh.bank, Resources::Mesh));
	Resource<Mesh>& mesh(meshBank.add(mSettings.mesh.group, Resources::Mesh, makeSprite(scale, shader, texU, texV, texS, texT)));
	
	Resources::Locator locator(mSettings.mesh);
	locator.resource = mesh.getId();
	
	return locator;
}

Mesh* SpriteFactory::makeSprite(const Vector2& scale, const Resource<Shader>& shader, const float u, const float v, const float s, const float t)
{
	float vertexData[32] = {// Position - 16 floats
					-1.0F * scale.x(), 1.0F * scale.y(), 0.0F, 1.0F,
					1.0F * scale.x(), 1.0F * scale.y(), 0.0F, 1.0F,
					1.0F * scale.x(), -1.0F * scale.y(), 0.0F, 1.0F,
					-1.0F * scale.x(), -1.0F * scale.y(), 0.0F, 1.0F,
					// Tex Coords - 8 floats
					u, v, 	// bottom left
					s, v, 	// top left
					s, t, 	// top right
					u, t};	// bottom right

	unsigned int vertexSize = 25 * sizeof(float);

	unsigned char indexData[6] = { 0, 1, 2, 2, 3, 0 };
	unsigned int indexSize = 6 * sizeof(unsigned char);

	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());
	ResourceBank<Material>& materialBank(resourceManager->getBank<Material>(mSettings.material.bank, Resources::Material));
	ResourceBank<VertexBuffer>& vertexBank(resourceManager->getBank<VertexBuffer>(mSettings.vertex.bank, Resources::VertexBuffer));
	ResourceBank<IndexBuffer>& indexBank(resourceManager->getBank<IndexBuffer>(mSettings.index.bank, Resources::IndexBuffer));

	Resource<VertexBuffer>& newVertexBuffer(vertexBank.add(mSettings.vertex.group, Resources::VertexBuffer, new VertexBuffer(reinterpret_cast<unsigned char*>(&vertexData), vertexSize)));
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_POSITION_4F, 4U);
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_TEXTURE_2F, 4U);
	
	Resource<IndexBuffer>& newIndexBuffer(indexBank.add(mSettings.index.group, Resources::IndexBuffer, new IndexBuffer(reinterpret_cast<unsigned char*>(&indexData), indexSize, IndexBuffer::FORMAT_UNSIGNED_BYTE)));
	
	Resource<Material>& newMaterial(materialBank.add(mSettings.material.group, Resources::Material, new Material));
	newMaterial->setShader(shader);
	newMaterial->addTexture(mTexture);

	return new Mesh(newVertexBuffer, newIndexBuffer, newMaterial);
}

/// Helper function to generate a shader if need be.
Shader* SpriteFactory::makeSpriteShader()
{
	std::string vShader =
		"attribute vec4 a_position;								\n"
		"attribute vec2 a_texCoord0;							\n"
		"varying vec2 v_texCoord0;								\n"
		"uniform mat4 u_mvp;									\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = u_mvp * a_position;					\n"
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

