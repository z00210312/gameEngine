#pragma once
#include <math.h>
#include <cstddef>
#include <iostream>
#include "Vertex.h"
#include "textureObj.h"
#include "GLSL.h"
class SpriteBorder
{
private:
	const static short BORDER_SIZE = 9;
	GLuint m_vboID;
	Vertex vertexData[9][4];
	GLubyte m_defaultColor[4];

	textureObj* texObj;
	GLuint borderTexID_1;

	void setSprite();
public:
	SpriteBorder(textureObj* _texObj, const char* _border);
	~SpriteBorder();
	
	void setVertexValue(float posx, float posy, float width, float height);
	void drawSprite(GLSL* _colorProgram);
};

