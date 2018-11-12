#pragma once
#include "CharacterObj.h"
class TeamObj
{
private:
	unsigned short MAX_CHARACTER_SIZE;
	unsigned short TeamID;

	textureObj* texObj;

	// team variables
	GLuint TeamIconID;
	spriteObj TeamIconSprite;
	float TeamIconShiftx;
	float TeamIconShifty;

	// character variables
	GLuint EmptyCharacterIconID;
	CharacterObj** characterObj;
	CharacterObj* nil;
public:
	TeamObj();
	~TeamObj();

	void initTeamObj(unsigned short _teamID, textureObj* _texObj, const char* _teamIconID, const char* _emptyCharacterIconID, unsigned short _MAX_CHARACTER_SIZE);

	void setTeamIconShift(float _posx, float _posy);
	void setTeamMember(unsigned short _index, CharacterObj * _characterPtr);

	unsigned short getTeamID();
	GLuint getTeamIconID();
	spriteObj* getTeamIconSprite();
	CharacterObj* getTeamMember(int index);
	float getTeamIconShiftx();
	float getTeamIconShifty();
	CharacterObj* getnullptr();

	unsigned short getMAXCharacterSize();
};

