#include "Sprite.h"
#include <GL\glew.h>
#include <iostream>

Sprite::Sprite()
{
	vboID = 0;
	vaoID = 0;
}

Sprite::~Sprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
	if (vaoID != 0)
		glDeleteVertexArrays(1, &vaoID);
}

void Sprite::init(float width, float height)
{
	this->width = width;
	this->height = height;
	if(vaoID == 0)
		glGenVertexArrays(1, &vaoID);
	if(vboID == 0)
		glGenBuffers(1, &vboID);
	setUpSpriteDimensions(width, height);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Sprite::setTextureID(unsigned int textureID)
{
	this->textureID = textureID;
}

unsigned int Sprite::getTextureID() const noexcept
{
	return textureID;
}

glm::vec2 Sprite::getDimensions() const
{
	return glm::vec2(width, height);
}

void Sprite::setDimension(const glm::vec2& newDimension)
{
	setUpSpriteDimensions(newDimension.x, newDimension.y);
}

void Sprite::setDimension(float width, float height)
{
	setUpSpriteDimensions(width, height);
}

void Sprite::setUpSpriteDimensions(float width, float height)
{
	float vertexData[24];
	vertexData[0] = width * 0.5f;
	vertexData[1] = height * 0.5f;

	vertexData[2] = 1.0f;
	vertexData[3] = 1.0f;

	vertexData[4] = -width * 0.5f;
	vertexData[5] = height * 0.5f;

	vertexData[6] = 0.0f;
	vertexData[7] = 1.0f;

	vertexData[8] = -width * 0.5f;
	vertexData[9] = -height * 0.5f;

	vertexData[10] = 0.0f;
	vertexData[11] = 0.0f;

	vertexData[12] = -width * 0.5f;
	vertexData[13] = -height * 0.5f;

	vertexData[14] = 0.0f;
	vertexData[15] = 0.0f;

	vertexData[16] = width * 0.5f;
	vertexData[17] = -height * 0.5f;

	vertexData[18] = 1.0f;
	vertexData[19] = 0;

	vertexData[20] = width * 0.5f;
	vertexData[21] = height * 0.5f;

	vertexData[22] = 1.0f;
	vertexData[23] = 1.0f;

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
