#include "CharacterObj.h"

CharacterObj::CharacterObj()
{
	nil = nullptr;
	teamID = -1;
}

CharacterObj::~CharacterObj()
{
}

void CharacterObj::initCharacterObj(unsigned short _characterID, textureObj * _texObj, const char * _characterIconID, const char * _characterPictID, const char * _emptyItemIconID, unsigned short _MAX_INVENTORY_SIZE)
{
	CharacterID = _characterID;
	MAX_CHARACTER_INVENTORY_SIZE = _MAX_INVENTORY_SIZE;

	texObj = _texObj;
	CharacterIconID = texObj->setPNGTextureID(_characterIconID);
	CharacterIconSprite.setSprite(0.0f, 0.0f, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterIconShiftx = 0.0f;
	CharacterIconShifty = 0.0f;

	CharacterPictID = texObj->setPNGTextureID(_characterPictID);
	float _width;
	float _height;
	_width = (float)texObj->getTexWidth() / texObj->getTexHeight();
	_height = 1.0f;
	while (_width > 0.4f) {
		_width /= 2;
		_height /= 2;
	}
	CharacterPictSprite.setSprite(0.0f, 0.0f, _width, _height, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterPictShiftx = 0.0f;
	CharacterPictShifty = 0.0f;

	EmptyItemIconID = texObj->setPNGTextureID(_emptyItemIconID);

	CharacterEquipments_Item = new InventoryItemObj*[MAX_CHARACTER_INVENTORY_SIZE];
	for (int i = 0; i < MAX_CHARACTER_INVENTORY_SIZE; i++)
		CharacterEquipments_Item[i] = nil;
}

void CharacterObj::setCharacterIconShift(float _posx, float _posy)
{
	CharacterIconShiftx = _posx;
	CharacterIconShifty = _posy;
}

void CharacterObj::setCharacterPictShift(float _posx, float _posy)
{
	CharacterPictShiftx = _posx;
	CharacterPictShifty = _posy;
}

unsigned short CharacterObj::getCharacterID()
{
	return CharacterID;
}

GLuint CharacterObj::getCharacterIconID()
{
	return CharacterIconID;
}

spriteObj* CharacterObj::getCharacterIconSprite()
{
	return &CharacterIconSprite;
}

float CharacterObj::getCharacterIconShiftx()
{
	return CharacterIconShiftx;
}

float CharacterObj::getCharacterIconShifty()
{
	return CharacterIconShifty;
}

GLuint CharacterObj::getCharacterPictID()
{
	return CharacterPictID;
}

spriteObj* CharacterObj::getCharacterPictSprite()
{
	return &CharacterPictSprite;
}

float CharacterObj::getCharacterPictShiftx()
{
	return CharacterPictShiftx;
}

float CharacterObj::getCharacterPictShifty()
{
	return CharacterPictShifty;
}

void CharacterObj::setCharacterEquipmentItem(int _index, InventoryItemObj * _ptr)
{
	CharacterEquipments_Item[_index] = _ptr;
}

InventoryItemObj* CharacterObj::getCharacterEquipmentItem(int _index)
{
	return CharacterEquipments_Item[_index];
}

void CharacterObj::setTeamID(short _teamID)
{
	teamID = _teamID;
}


short CharacterObj::getTeamID()
{
	return teamID;
}