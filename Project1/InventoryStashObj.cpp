#include "InventoryStashObj.h"

InventoryStashObj::InventoryStashObj()
{
	nil = nullptr;
}

InventoryStashObj::~InventoryStashObj()
{
	delete[] InventoryListItemSprite;
	// NOTE: it might cause crash
	delete[] *itemObj;
}

void InventoryStashObj::initInventoryStashObj(unsigned short _inventoryID, textureObj * _texObj, const char * _emptyItemIconID, unsigned short _MAX_ROW, unsigned short _MAX_COL)
{
	InventoryID = _inventoryID;
	MAX_ROW = _MAX_ROW;
	MAX_COL = _MAX_COL;
	MAX_INVENTORY_ITEM_SIZE = MAX_ROW * MAX_COL;
	texObj = _texObj;
	EmptyItemIconID = texObj->setPNGTextureID(_emptyItemIconID);

	InventoryListItemSprite = new spriteObj[MAX_INVENTORY_ITEM_SIZE];
	itemObj = new InventoryItemObj*[MAX_INVENTORY_ITEM_SIZE];
	float temp_x = 0.0f;
	float temp_y = 0.0f;
	for (int colIndex = 0; colIndex < MAX_COL; colIndex++) {
		for (int rowIndex = 0; rowIndex < MAX_ROW; rowIndex++) {
			InventoryListItemSprite[colIndex*MAX_ROW + rowIndex].setSprite(temp_x, temp_y, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
			itemObj[colIndex*MAX_ROW + rowIndex] = nil;
			temp_x += 0.1f;
		}
		temp_x = 0.0f;
		temp_y -= 0.1f;
	}

	InventoryListItemShiftx = 0.0f;
	InventoryListItemShifty = 0.0f;
}

void InventoryStashObj::setInventoryListItem(int index, InventoryItemObj* _ptr)
{
	if (_ptr)
		itemObj[index] = _ptr;
	else
		itemObj[index] = nil;
}

void InventoryStashObj::setInventoryListItemShift(float _posx, float _posy)
{
	InventoryListItemShiftx = _posx;
	InventoryListItemShifty = _posy;
}

unsigned short InventoryStashObj::getInventoryStashID()
{
	return InventoryID;
}

spriteObj * InventoryStashObj::getInventoryListItemSprite(int index)
{
	return &InventoryListItemSprite[index];
}

float InventoryStashObj::getInventoryListItemShiftx()
{
	return InventoryListItemShiftx;
}

float InventoryStashObj::getInventoryListItemShifty()
{
	return InventoryListItemShifty;
}

GLuint InventoryStashObj::getEmptyItemIconID()
{
	return EmptyItemIconID;
}

InventoryItemObj * InventoryStashObj::getInventoryListItem(int index)
{
	return itemObj[index];
}
