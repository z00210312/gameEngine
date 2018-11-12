#include "TeamObj.h"

TeamObj::TeamObj()
{
	nil = nullptr;
}

TeamObj::~TeamObj()
{
	// NOTE: might cause crash
	delete[] *characterObj;
}

void TeamObj::initTeamObj(unsigned short _teamID, textureObj * _texObj, const char * _teamIconID, const char * _emptyCharacterIconID, unsigned short _MAX_CHARACTER_SIZE)
{
	TeamID = _teamID;
	MAX_CHARACTER_SIZE = _MAX_CHARACTER_SIZE;

	texObj = _texObj;
	TeamIconID = texObj->setPNGTextureID(_teamIconID);
	TeamIconSprite.setSprite(0.0f, 0.0f, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	EmptyCharacterIconID = texObj->setPNGTextureID(_emptyCharacterIconID);
	characterObj = new CharacterObj*[MAX_CHARACTER_SIZE];
	for( int i = 0; i < MAX_CHARACTER_SIZE; i++)
		characterObj[i] = nil;
}

void TeamObj::setTeamIconShift(float _posx, float _posy)
{
	TeamIconShiftx = _posx;
	TeamIconShifty = _posy;
}

void TeamObj::setTeamMember(unsigned short _index, CharacterObj * _characterPtr)
{
	if (_characterPtr == nullptr) {
		characterObj[_index] = nil;
	}
	else {
		characterObj[_index] = _characterPtr;
	}
}

short unsigned int TeamObj::getTeamID()
{
	return TeamID;
}

GLuint TeamObj::getTeamIconID()
{
	return TeamIconID;
}

spriteObj * TeamObj::getTeamIconSprite()
{
	return &TeamIconSprite;
}

CharacterObj* TeamObj::getTeamMember(int index)
{
	if (characterObj[index] != nil)
		return characterObj[index];
	return nil;
}

float TeamObj::getTeamIconShiftx()
{
	return TeamIconShiftx;
}

float TeamObj::getTeamIconShifty()
{
	return TeamIconShifty;
}

CharacterObj* TeamObj::getnullptr()
{
	return nil;
}

unsigned short TeamObj::getMAXCharacterSize()
{
	return MAX_CHARACTER_SIZE;
}
