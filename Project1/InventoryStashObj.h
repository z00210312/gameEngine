#pragma once
#include "CharacterObj.h"
#include "InventoryItemObj.h"
class InventoryStashObj
{
private:
	unsigned short MAX_ROW;
	unsigned short MAX_COL;
	unsigned short MAX_INVENTORY_ITEM_SIZE;
	unsigned short InventoryID;

	textureObj* texObj;

	// inventory variables
	spriteObj* InventoryListItemSprite;
	float InventoryListItemShiftx;
	float InventoryListItemShifty;

	// item variables
	GLuint EmptyItemIconID;
	InventoryItemObj** itemObj;
	InventoryItemObj* nil;
public:
	InventoryStashObj();
	~InventoryStashObj();

	void initInventoryStashObj(unsigned short _inventoryID, textureObj* _texObj, const char* _emptyItemIconID, unsigned short _MAX_ROW, unsigned short _MAX_COL);
	void setInventoryListItem(int index, InventoryItemObj* _ptr);
	void setInventoryListItemShift(float _posx, float _posy);

	unsigned short getInventoryStashID();
	spriteObj* getInventoryListItemSprite(int index);
	float getInventoryListItemShiftx();
	float getInventoryListItemShifty();
	GLuint getEmptyItemIconID();

	InventoryItemObj* getInventoryListItem(int index);
};

