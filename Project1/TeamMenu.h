#pragma once
#include "CharacterObj.h"
#include "TeamObj.h"
class TeamMenu
{
private:
	unsigned short MAX_CHARACTER_SIZE;
	unsigned short MAX_TEAM_SIZE;
	unsigned short MAX_TEAM_MEMBER_SIZE;

	textureObj* texObj;

	spriteObj* CharacterPlaceHolder;
	spriteObj* TeamPlaceHolder;
	GLuint CharacterPlaceHolderTextureID;
	GLuint TeamPlaceHolderTextureID;

	CharacterObj* CharactersPtr;
	unsigned short CharacterSize;
	TeamObj* TeamsPtr;
	unsigned short TeamSize;
	short currPickIcon;
	short prevPickLoct;
public:
	TeamMenu(textureObj* _texObj, const char* _characterIcon, const char* _teamIcon, unsigned short _MAX_CHARACTER_SIZE, unsigned short _MAX_TEAM_SIZE, unsigned short _MAX_TEAM_MEMBER_SIZE);
	~TeamMenu();

	void setPlaceHolder(int screenx, int screeny, int rowPerCol);
	void drawSprite(GLSL* _colorProgram);

	void setCharactersPtr(unsigned short _size, CharacterObj* _CharactersPtr);
	void setCharactersEntry();
	void setTeamsPtr(unsigned short _size, TeamObj* _TeamPtr);
	void setTeamsEntry();

	void moveCharacterIcon(int index, float _posx, float _posy);

	void pickUpCharacter(float _posx, float _posy);
	bool isHoldCharacter(float _posx, float _posy);
	void releaseCharacter(float _posx, float _posy);

	int isCharactersEntryCollision(float _posx, float _posy);
	int isTeamEntryCollision(float _posx, float _posy);
};

