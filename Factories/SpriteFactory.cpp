#include "SpriteFactory.h"

#include "../Graphics/Material.h"
#include "../Graphics/Shader.h"
#include "../Utils/Sprite.h"

using namespace GLESGAE;

SpriteFactory::SpriteFactory(Texture* const texture)
: mMaterial(new Material())
{
	mMaterial->setShader(makeSpriteShader());
	mMaterial->addTexture(texture);
}

void SpriteFactory::setShader(Shader* const shader)
{
	mMaterial->setShader(shader);
}

Sprite* SpriteFactory::create(const Vector2& size, const unsigned int u, const unsigned int v, const unsigned int s, const unsigned int t)
{
	const unsigned int texWidth(mMaterial->getTexture(0U)->getWidth());
	const unsigned int texHeight(mMaterial->getTexture(0U)->getHeight());
		
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

	return new Sprite(mMaterial, size, texU, texV, texS, texT);
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

