#include "InventoryItemObj.h"

InventoryItemObj::InventoryItemObj()
{
	CharacterID = -1;
	InventoryLoc = -1;
}

InventoryItemObj::~InventoryItemObj()
{
}

void InventoryItemObj::initItemObj(unsigned short _itemID, textureObj * _texObj, const char * _itemIconID)
{
	ItemID = _itemID;
	
	texObj = _texObj;
	ItemIconID = texObj->setPNGTextureID(_itemIconID);
	ItemIconSprite.setSprite(0.0f, 0.0f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	ItemIconShiftx = 0.0f;
	ItemIconShifty = 0.0f;
}

void InventoryItemObj::setItemIconShift(float _posx, float _posy)
{
	ItemIconShiftx = _posx;
	ItemIconShifty = _posy;
}

unsigned short InventoryItemObj::getItemID()
{
	return ItemID;
}

GLuint InventoryItemObj::getItemIconID()
{
	return ItemIconID;
}

spriteObj * InventoryItemObj::getItemIconSprite()
{
	return &ItemIconSprite;
}

float InventoryItemObj::getItemIconShiftx()
{
	return ItemIconShiftx;
}

float InventoryItemObj::getItemIconShifty()
{
	return ItemIconShifty;
}

void InventoryItemObj::setCharacterID(short _CharacterID)
{
	CharacterID = _CharacterID;
}

short InventoryItemObj::getCharacterID()
{
	return CharacterID;
}

void InventoryItemObj::setInventoryLoc(short _inventoryLoc)
{
	InventoryLoc = _inventoryLoc;
}

short InventoryItemObj::getInventoryLoc()
{
	return InventoryLoc;
}
