#pragma once
#include "textureObj.h"
#include "spriteObj.h"
#include "GLSL.h"
#include "InventoryItemObj.h"
class CharacterObj
{
private:
	unsigned short MAX_CHARACTER_INVENTORY_SIZE;
	unsigned short CharacterID;

	textureObj* texObj;

	// character varaibles
	GLuint CharacterIconID;
	spriteObj CharacterIconSprite;
	float CharacterIconShiftx;
	float CharacterIconShifty;

	GLuint CharacterPictID;
	spriteObj CharacterPictSprite;
	float CharacterPictShiftx;
	float CharacterPictShifty;

	// item variables
	GLuint EmptyItemIconID;
	InventoryItemObj** CharacterEquipments_Item;
	InventoryItemObj* nil;

	// team variables
	short teamID;
public:
	CharacterObj();
	~CharacterObj();

	void initCharacterObj(unsigned short _characterID, textureObj* _texObj, const char* _characterIconID, const char* _characterPictID, const char* _emptyItemIconID, unsigned short _MAX_INVENTORY_SIZE);

	void setCharacterIconShift(float _posx, float _posy);
	void setCharacterPictShift(float _posx, float _posy);

	unsigned short getCharacterID();
	GLuint getCharacterIconID();
	spriteObj* getCharacterIconSprite();
	float getCharacterIconShiftx();
	float getCharacterIconShifty();

	GLuint getCharacterPictID();
	spriteObj* getCharacterPictSprite();
	float getCharacterPictShiftx();
	float getCharacterPictShifty();

	void setCharacterEquipmentItem(int _index, InventoryItemObj* _ptr);
	InventoryItemObj* getCharacterEquipmentItem(int _index);

	void setTeamID(short _teamID);
	short getTeamID();
};

