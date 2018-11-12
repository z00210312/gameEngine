#pragma once
#include "CharacterObj.h"
#include "InventoryStashObj.h"
class CharacterMenu
{
private:
	unsigned short MAX_INVENTORY_ITEM_SIZE;
	unsigned short MAX_ROW;
	unsigned short MAX_COL;
	unsigned short MAX_CHARACTER_SIZE;
	const static unsigned short MAX_CHARACTER_EQUIPMENT_SIZE = 8;

	textureObj* texObj;

	spriteObj* CharacterPlaceHolder;
	spriteObj* CharacterEquipmentPlaceHolder;
	GLuint CharacterPlaceHolderTextureID;

	InventoryStashObj newIntStash;

	CharacterObj* CharactersPtr;
	unsigned short CharacterSize;

	short currPickIcon;
	short prevPickLoct;

	short currCharacter;
public:
	CharacterMenu(textureObj* _texObj, const char* _characterPlaceHolderTextureID, unsigned short _MAX_ROW, unsigned short  _MAX_COL, unsigned short _MAX_CHARACTER_SIZE);
	~CharacterMenu();

	void setPlaceHolder(int _width, int _height);
	
	unsigned short getMaxInventorySize();
	bool addItem(InventoryItemObj* _newItemPtr);
	bool delItem(int index);
	InventoryItemObj* getItem(int index);
	void drawSprite(GLSL* _colorProgram);

	void setInventoryItemsEntry(int _width, int _height);
	void setCharactersEntry(int _width, int _height);

	void setCharactersPtr(unsigned short _size, CharacterObj* _CharactersPtr);

	void moveItemIcon(int index, float _posx, float _posy);

	bool isStillHoldItem(float _posx, float _posy);
	void pickUpItem(float _posx, float _posy);
	void releaseItem(float _posx, float _posy);

	void changeCurrCharacter(int index);

	int isCharacterPlaceHolderCollision(float _posx, float _posy);

	int isCharacterInventoryItemsCollision(float _posx, float _posy);
	int isCharacterEquipmentPlaceHolderCollision(float _posx, float _posy);
};

