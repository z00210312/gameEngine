#pragma once
#include "spriteObj.h"
#include "textureObj.h"
class InventoryItemObj
{
private:
	unsigned short ItemID;

	textureObj* texObj;

	// item variables
	GLuint ItemIconID;
	spriteObj ItemIconSprite;
	float ItemIconShiftx;
	float ItemIconShifty;

	short CharacterID;
	short InventoryLoc;
public:
	InventoryItemObj();
	~InventoryItemObj();

	void initItemObj(unsigned short _itemID, textureObj* _texObj, const char* _itemIconID);

	void setItemIconShift(float _posx, float _posy);

	unsigned short getItemID();
	GLuint getItemIconID();
	spriteObj* getItemIconSprite();
	float getItemIconShiftx();
	float getItemIconShifty();

	void setCharacterID(short _CharacterID);
	short getCharacterID();
	void setInventoryLoc(short _inventoryLoc);
	short getInventoryLoc();
};