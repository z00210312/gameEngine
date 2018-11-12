#include "SpriteBorder.h"



SpriteBorder::SpriteBorder(textureObj* _texObj, const char* _border)
{
	texObj = _texObj;
	borderTexID_1 = texObj->setPNGTextureID(_border);
	m_defaultColor[0] = 255;
	m_defaultColor[1] = 255;
	m_defaultColor[2] = 255;
	m_defaultColor[3] = 255;
	setSprite();
}


SpriteBorder::~SpriteBorder()
{
	glDeleteBuffers(1, &m_vboID);
	m_vboID = 0;
}

void SpriteBorder::setSprite()
{
	if (m_vboID == 0) {
		glGenBuffers(1, &m_vboID);
	}
}

void SpriteBorder::setVertexValue(float posx, float posy, float width, float height)
{
	///////////
	// X O O //
	// O O O //
	// O O O //
	///////////

	//Top-left
	vertexData[0][0].position.x = posx;
	vertexData[0][0].position.y = posy + height;
	vertexData[0][0].uv.u = (float)0 / 3;
	vertexData[0][0].uv.v = (float)0 / 3;
	vertexData[0][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[0][1].position.x = posx + 0.1f;
	vertexData[0][1].position.y = posy + height;
	vertexData[0][1].uv.u = (float)1 / 3;
	vertexData[0][1].uv.v = (float)0 / 3;
	vertexData[0][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[0][2].position.x = posx + 0.1f;
	vertexData[0][2].position.y = posy + height - 0.1f;
	vertexData[0][2].uv.u = (float)1 / 3;
	vertexData[0][2].uv.v = (float)1 / 3;
	vertexData[0][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[0][3].position.x = posx;
	vertexData[0][3].position.y = posy + height - 0.1f;
	vertexData[0][3].uv.u = (float)0 / 3;
	vertexData[0][3].uv.v = (float)1 / 3;
	vertexData[0][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O X O //
	// O O O //
	// O O O //
	///////////

	//Top-left
	vertexData[1][0].position.x = posx + 0.1f;
	vertexData[1][0].position.y = posy + height;
	vertexData[1][0].uv.u = (float)1 / 3;
	vertexData[1][0].uv.v = (float)0 / 3;
	vertexData[1][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[1][1].position.x = posx + width - 0.1f;
	vertexData[1][1].position.y = posy + height;
	vertexData[1][1].uv.u = (float)2 / 3;
	vertexData[1][1].uv.v = (float)0 / 3;
	vertexData[1][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[1][2].position.x = posx + width - 0.1f;
	vertexData[1][2].position.y = posy + height - 0.1f;
	vertexData[1][2].uv.u = (float)2 / 3;
	vertexData[1][2].uv.v = (float)1 / 3;
	vertexData[1][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[1][3].position.x = posx + 0.1f;
	vertexData[1][3].position.y = posy + height - 0.1f;
	vertexData[1][3].uv.u = (float)1 / 3;
	vertexData[1][3].uv.v = (float)1 / 3;
	vertexData[1][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O X //
	// O O O //
	// O O O //
	///////////

	//Top-left
	vertexData[2][0].position.x = posx + width - 0.1f;
	vertexData[2][0].position.y = posy + height;
	vertexData[2][0].uv.u = (float)2 / 3;
	vertexData[2][0].uv.v = (float)0 / 3;
	vertexData[2][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[2][1].position.x = posx + width;
	vertexData[2][1].position.y = posy + height;
	vertexData[2][1].uv.u = (float)3 / 3;
	vertexData[2][1].uv.v = (float)0 / 3;
	vertexData[2][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[2][2].position.x = posx + width;
	vertexData[2][2].position.y = posy + height - 0.1f;
	vertexData[2][2].uv.u = (float)3 / 3;
	vertexData[2][2].uv.v = (float)1 / 3;
	vertexData[2][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[2][3].position.x = posx + width - 0.1f;
	vertexData[2][3].position.y = posy + height - 0.1f;
	vertexData[2][3].uv.u = (float)2 / 3;
	vertexData[2][3].uv.v = (float)1 / 3;
	vertexData[2][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// X O O //
	// O O O //
	///////////

	//Top-left
	vertexData[3][0].position.x = posx;
	vertexData[3][0].position.y = posy + height - 0.1f;
	vertexData[3][0].uv.u = (float)0 / 3;
	vertexData[3][0].uv.v = (float)1 / 3;
	vertexData[3][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[3][1].position.x = posx + 0.1f;
	vertexData[3][1].position.y = posy + height - 0.1f;
	vertexData[3][1].uv.u = (float)1 / 3;
	vertexData[3][1].uv.v = (float)1 / 3;
	vertexData[3][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[3][2].position.x = posx + 0.1f;
	vertexData[3][2].position.y = posy + 0.1f;
	vertexData[3][2].uv.u = (float)1 / 3;
	vertexData[3][2].uv.v = (float)2 / 3;
	vertexData[3][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[3][3].position.x = posx;
	vertexData[3][3].position.y = posy + 0.1f;
	vertexData[3][3].uv.u = (float)0 / 3;
	vertexData[3][3].uv.v = (float)2 / 3;
	vertexData[3][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// O X O //
	// O O O //
	///////////

	//Top-left
	vertexData[4][0].position.x = posx + 0.1f;
	vertexData[4][0].position.y = posy + height - 0.1f;
	vertexData[4][0].uv.u = (float)1 / 3;
	vertexData[4][0].uv.v = (float)1 / 3;
	vertexData[4][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[4][1].position.x = posx + width - 0.1f;
	vertexData[4][1].position.y = posy + height - 0.1f;
	vertexData[4][1].uv.u = (float)2 / 3;
	vertexData[4][1].uv.v = (float)1 / 3;
	vertexData[4][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[4][2].position.x = posx + width - 0.1f;
	vertexData[4][2].position.y = posy + 0.1f;
	vertexData[4][2].uv.u = (float)2 / 3;
	vertexData[4][2].uv.v = (float)2 / 3;
	vertexData[4][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[4][3].position.x = posx + 0.1f;
	vertexData[4][3].position.y = posy + 0.1f;
	vertexData[4][3].uv.u = (float)1 / 3;
	vertexData[4][3].uv.v = (float)2 / 3;
	vertexData[4][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// O O X //
	// O O O //
	///////////

	//Top-left
	vertexData[5][0].position.x = posx + width - 0.1f;
	vertexData[5][0].position.y = posy + height - 0.1f;
	vertexData[5][0].uv.u = (float)2 / 3;
	vertexData[5][0].uv.v = (float)1 / 3;
	vertexData[5][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[5][1].position.x = posx + width;
	vertexData[5][1].position.y = posy + height - 0.1f;
	vertexData[5][1].uv.u = (float)3 / 3;
	vertexData[5][1].uv.v = (float)1 / 3;
	vertexData[5][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[5][2].position.x = posx + width;
	vertexData[5][2].position.y = posy + 0.1f;
	vertexData[5][2].uv.u = (float)3 / 3;
	vertexData[5][2].uv.v = (float)2 / 3;
	vertexData[5][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[5][3].position.x = posx + width - 0.1f;
	vertexData[5][3].position.y = posy + 0.1f;
	vertexData[5][3].uv.u = (float)2 / 3;
	vertexData[5][3].uv.v = (float)2 / 3;
	vertexData[5][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// O O O //
	// X O O //
	///////////

	//Top-left
	vertexData[6][0].position.x = posx;
	vertexData[6][0].position.y = posy + 0.1f;
	vertexData[6][0].uv.u = (float)0 / 3;
	vertexData[6][0].uv.v = (float)2 / 3;
	vertexData[6][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[6][1].position.x = posx + 0.1f;
	vertexData[6][1].position.y = posy + 0.1f;
	vertexData[6][1].uv.u = (float)1 / 3;
	vertexData[6][1].uv.v = (float)2 / 3;
	vertexData[6][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[6][2].position.x = posx + 0.1f;
	vertexData[6][2].position.y = posy;
	vertexData[6][2].uv.u = (float)1 / 3;
	vertexData[6][2].uv.v = (float)3 / 3;
	vertexData[6][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[6][3].position.x = posx;
	vertexData[6][3].position.y = posy;
	vertexData[6][3].uv.u = (float)0 / 3;
	vertexData[6][3].uv.v = (float)3 / 3;
	vertexData[6][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// O O O //
	// O X O //
	///////////

	//Top-left
	vertexData[7][0].position.x = posx + 0.1f;
	vertexData[7][0].position.y = posy + 0.1f;
	vertexData[7][0].uv.u = (float)1 / 3;
	vertexData[7][0].uv.v = (float)2 / 3;
	vertexData[7][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[7][1].position.x = posx + width - 0.1f;
	vertexData[7][1].position.y = posy + 0.1f;
	vertexData[7][1].uv.u = (float)2 / 3;
	vertexData[7][1].uv.v = (float)2 / 3;
	vertexData[7][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[7][2].position.x = posx + width - 0.1f;
	vertexData[7][2].position.y = posy;
	vertexData[7][2].uv.u = (float)2 / 3;
	vertexData[7][2].uv.v = (float)3 / 3;
	vertexData[7][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[7][3].position.x = posx + 0.1f;
	vertexData[7][3].position.y = posy;
	vertexData[7][3].uv.u = (float)1 / 3;
	vertexData[7][3].uv.v = (float)3 / 3;
	vertexData[7][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	///////////
	// O O O //
	// O O O //
	// O O X //
	///////////

	//Top-left
	vertexData[8][0].position.x = posx + width - 0.1f;
	vertexData[8][0].position.y = posy + 0.1f;
	vertexData[8][0].uv.u = (float)2 / 3;
	vertexData[8][0].uv.v = (float)2 / 3;
	vertexData[8][0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Top-right
	vertexData[8][1].position.x = posx + width;
	vertexData[8][1].position.y = posy + 0.1f;
	vertexData[8][1].uv.u = (float)3 / 3;
	vertexData[8][1].uv.v = (float)2 / 3;
	vertexData[8][1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-right
	vertexData[8][2].position.x = posx + width;
	vertexData[8][2].position.y = posy;
	vertexData[8][2].uv.u = (float)3 / 3;
	vertexData[8][2].uv.v = (float)3 / 3;
	vertexData[8][2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	//Bottom-left
	vertexData[8][3].position.x = posx + width - 0.1f;
	vertexData[8][3].position.y = posy;
	vertexData[8][3].uv.u = (float)2 / 3;
	vertexData[8][3].uv.v = (float)3 / 3;
	vertexData[8][3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };
}

void SpriteBorder::drawSprite(GLSL* _colorProgram)
{

	_colorProgram->enable();
	texObj->enable(_colorProgram->getUniformLocation("sampler_1"), borderTexID_1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_QUADS, 0, 4 * BORDER_SIZE);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	texObj->disable();
	_colorProgram->disable();

}
