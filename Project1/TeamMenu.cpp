#include "TeamMenu.h"

TeamMenu::TeamMenu(textureObj* _texObj, const char* _characterIcon, const char* _teamIcon, unsigned short _MAX_CHARACTER_SIZE, unsigned short _MAX_TEAM_SIZE, unsigned short _MAX_TEAM_MEMBER_SIZE)
{
	texObj = _texObj;
	MAX_CHARACTER_SIZE = _MAX_CHARACTER_SIZE;
	MAX_TEAM_SIZE = _MAX_TEAM_SIZE;
	MAX_TEAM_MEMBER_SIZE = _MAX_TEAM_MEMBER_SIZE;
	CharacterPlaceHolderTextureID = texObj->setPNGTextureID(_characterIcon);
	TeamPlaceHolderTextureID = texObj->setPNGTextureID(_teamIcon);

	CharacterPlaceHolder = new spriteObj[MAX_CHARACTER_SIZE];
	TeamPlaceHolder = new spriteObj[MAX_TEAM_SIZE*MAX_TEAM_MEMBER_SIZE + MAX_TEAM_SIZE];

	currPickIcon = -1;
}

TeamMenu::~TeamMenu()
{
	delete[] CharacterPlaceHolder;
	delete[] TeamPlaceHolder;
}

void TeamMenu::setPlaceHolder(int screenx, int screeny, int rowPerCol)
{
	float startX = (float)screenx / screeny - 1.0f;
	float startY = 0.9f;

	int rowCounter = 0;
	int colCounter = 0;

	float spriteDistance = 0.1f;

	for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		CharacterPlaceHolder[i].setSprite(startX + 0.3f*(colCounter), startY - spriteDistance * (1 + (i) % rowPerCol), 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
		CharacterPlaceHolder[i].spriteActivate();
		rowCounter++;
		if (rowCounter >= rowPerCol) {
			rowCounter = 0;
			if (colCounter == 0)
				colCounter = 1;
			else if (colCounter == 1)
				colCounter = 2;
			else if (colCounter == 2)
				colCounter = 0;
		}
	}

	startX = (float)-screenx / screeny + 0.9f;
	startY = 0.7f;

	int l = 0;
	for (int k = 0; k < MAX_TEAM_SIZE; k++) {
		TeamPlaceHolder[(MAX_TEAM_MEMBER_SIZE + 1) * k].setSprite(startX, startY - k * 0.3f + 0.1f, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
		for (int j = 0; j < MAX_TEAM_MEMBER_SIZE; j++) {
			TeamPlaceHolder[j + 1 + ((MAX_TEAM_MEMBER_SIZE + 1) * k)].setSprite(startX + (j % 2)*0.3f, startY - k * 0.3f - 0.1f*l, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
			TeamPlaceHolder[j + 1 + ((MAX_TEAM_MEMBER_SIZE + 1) * k)].spriteActivate();
			if ((j + 1) % MAX_TEAM_MEMBER_SIZE == 0)
				l++;
			if ((j + 1) % 2 == 0)
				l++;
		}
		l = 0;
	}
}

void TeamMenu::drawSprite(GLSL * _colorProgram)
{
	for (int i = 0; i < CharacterSize; i++) {
	//for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		_colorProgram->enable();
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharacterPlaceHolderTextureID);
		CharacterPlaceHolder[i].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	int MAX_TEAM_PLACEHOLDER = TeamSize * MAX_TEAM_MEMBER_SIZE + TeamSize;
	//int MAX_TEAM_PLACEHOLDER = MAX_TEAM_SIZE * MAX_TEAM_MEMBER_SIZE + MAX_TEAM_SIZE;
	for (int j = 0; j < MAX_TEAM_PLACEHOLDER; j++) {
		_colorProgram->enable();
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), TeamPlaceHolderTextureID);
		TeamPlaceHolder[j].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	for (int k = 0; k < CharacterSize; k++) {
		if (k != currPickIcon) {
			_colorProgram->enable();
			_colorProgram->setTranslateMatrix(CharactersPtr[k].getCharacterIconShiftx(), CharactersPtr[k].getCharacterIconShifty(), 0.0f);
			texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[k].getCharacterIconID());
			CharactersPtr[k].getCharacterIconSprite()->drawSprite();
			texObj->disable();
			_colorProgram->disable();
		}

		/*
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(CharactersPtr[k].getCharacterPictShiftx(), CharactersPtr[k].getCharacterPictShifty(), 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[k].getCharacterPictID());
		CharactersPtr[k].getCharacterPictSprite()->drawSprite();
		texObj->disable();
		_colorProgram->disable();
		*/
	}

	for (int l = 0; l < TeamSize; l++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(TeamsPtr[l].getTeamIconShiftx(), TeamsPtr[l].getTeamIconShifty(), 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), TeamsPtr[l].getTeamIconID());
		TeamsPtr[l].getTeamIconSprite()->drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	if (currPickIcon != -1) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(CharactersPtr[currPickIcon].getCharacterIconShiftx(), CharactersPtr[currPickIcon].getCharacterIconShifty(), 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[currPickIcon].getCharacterIconID());
		CharactersPtr[currPickIcon].getCharacterIconSprite()->drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}
}

void TeamMenu::setCharactersPtr(unsigned short _size, CharacterObj* _CharactersPtr)
{
	CharactersPtr = _CharactersPtr;
	CharacterSize = _size;
}

void TeamMenu::setCharactersEntry()
{
	int j = 0;
	for (int i = 0; i + j< CharacterSize; i++) {
		//if(CharactersPtr[i])
		CharactersPtr[i].setCharacterIconShift(CharacterPlaceHolder[i].getVexPosx(), CharacterPlaceHolder[i].getVexPosy());
		//CharactersPtr[i].setCharacterPictShift((float)_width/ _height - CharactersPtr[i].getCharacterPictSprite()->getVexWidth() - 0.7f,1.0f - CharactersPtr[i].getCharacterPictSprite()->getVexHeight() - 0.1f);
	}
}

void TeamMenu::setTeamsPtr(unsigned short _size, TeamObj * _TeamPtr)
{
	TeamsPtr = _TeamPtr;
	TeamSize = _size;
}

void TeamMenu::setTeamsEntry()
{
	for (int i = 0; i < TeamSize; i++) {
		TeamsPtr[i].setTeamIconShift(TeamPlaceHolder[i*(MAX_TEAM_MEMBER_SIZE + 1)].getVexPosx(), TeamPlaceHolder[i*(MAX_TEAM_MEMBER_SIZE + 1)].getVexPosy());
		for (int j = 0; j < MAX_TEAM_MEMBER_SIZE; j++) {
			if (TeamsPtr[i].getTeamMember(j)) {
				TeamsPtr[i].getTeamMember(j)->setCharacterIconShift(TeamPlaceHolder[i * (MAX_TEAM_MEMBER_SIZE + 1) + j + 1].getVexPosx(), TeamPlaceHolder[i * (MAX_TEAM_MEMBER_SIZE + 1) + j + 1].getVexPosy());
			}
		}
	}
}

void TeamMenu::moveCharacterIcon(int index, float _posx, float _posy)
{
	CharactersPtr[index].setCharacterIconShift(_posx, _posy);
}

void TeamMenu::pickUpCharacter(float _posx, float _posy)
{
	currPickIcon = -1;
	prevPickLoct = -1;
	for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		if (CharacterPlaceHolder[i].isCollision(_posx, _posy, 0.0f, 0.0f)) {
			prevPickLoct = i;
			break;
		}
	}
	if (prevPickLoct == -1) {
		prevPickLoct = isTeamEntryCollision(_posx, _posy);
		if (prevPickLoct != -1) {
			prevPickLoct += MAX_CHARACTER_SIZE;
		}
	}
	currPickIcon = isCharactersEntryCollision(_posx, _posy);
}

bool TeamMenu::isHoldCharacter(float _posx, float _posy)
{
	if (currPickIcon != -1) {
		moveCharacterIcon(currPickIcon, _posx - CharacterPlaceHolder[currPickIcon].getVexWidth()/2, _posy - CharacterPlaceHolder[currPickIcon].getVexHeight() / 2);
		return true;
	}
	return false;
}

void TeamMenu::releaseCharacter(float _posx, float _posy)
{


	// currently hold an character
	if (currPickIcon != -1) {

		// preproceduress
		int teamCollisionResult = isTeamEntryCollision(_posx, _posy);
		int characterCollisionResult = isCharactersEntryCollision(_posx, _posy);

		int teamA = teamCollisionResult / (MAX_TEAM_MEMBER_SIZE + 1);
		int memberA = (teamCollisionResult % (MAX_TEAM_MEMBER_SIZE + 1)) - 1;

		int teamB = (prevPickLoct - MAX_CHARACTER_SIZE) / (MAX_TEAM_MEMBER_SIZE + 1);
		int memberB = ((prevPickLoct - MAX_CHARACTER_SIZE) % (MAX_TEAM_MEMBER_SIZE + 1)) - 1;

		if (teamA >= TeamSize) {
			CharactersPtr[currPickIcon].setCharacterIconShift(CharacterPlaceHolder[currPickIcon].getVexPosx(), CharacterPlaceHolder[currPickIcon].getVexPosy());
			CharactersPtr[currPickIcon].setTeamID(-1);
			if (prevPickLoct > MAX_CHARACTER_SIZE) {
				TeamsPtr[teamB].setTeamMember(memberB, nullptr);
			}
			return;
		}

		CharacterObj* _ptrA = TeamsPtr[teamA].getTeamMember(memberA);
		CharacterObj* _ptrB;

		if (prevPickLoct - MAX_CHARACTER_SIZE >= 0) {
			_ptrB = TeamsPtr[teamB].getTeamMember(memberB);
		}
		else {
			_ptrB = nullptr;
		}

		// remove member from team
		if (_ptrA)
			TeamsPtr[teamA].setTeamMember(memberA, TeamsPtr[teamA].getnullptr()); // still
		if (_ptrB)
			TeamsPtr[teamB].setTeamMember(memberB, TeamsPtr[teamB].getnullptr()); // pickedUp



		/////// start here //////////////
		/////////////////////////////////

		// if not release at team sprites
		if (teamCollisionResult == -1) {
			CharactersPtr[currPickIcon].setCharacterIconShift(CharacterPlaceHolder[currPickIcon].getVexPosx(), CharacterPlaceHolder[currPickIcon].getVexPosy());
			CharactersPtr[currPickIcon].setTeamID(-1);
		}
		// if release at team sprites
		else {
			// if the team sprite does not have an character
			if (_ptrA == TeamsPtr[teamA].getnullptr()) {
				TeamsPtr[teamA].setTeamMember(memberA,&CharactersPtr[currPickIcon]);
				CharactersPtr[currPickIcon].setCharacterIconShift(TeamPlaceHolder[teamCollisionResult].getVexPosx(), TeamPlaceHolder[teamCollisionResult].getVexPosy());
				CharactersPtr[currPickIcon].setTeamID(teamA);
			}
			// if the team sprite has an character
			else {
				// if it is picked from team member list
				if (prevPickLoct > MAX_CHARACTER_SIZE) {
					TeamsPtr[teamA].setTeamMember(memberA, _ptrB);
					CharactersPtr[_ptrB->getCharacterID()].setCharacterIconShift(TeamPlaceHolder[teamA * (MAX_TEAM_MEMBER_SIZE + 1) + memberA + 1].getVexPosx(), TeamPlaceHolder[teamA * (MAX_TEAM_MEMBER_SIZE + 1) + memberA + 1].getVexPosy());
					CharactersPtr[_ptrB->getCharacterID()].setTeamID(teamA);

					TeamsPtr[teamB].setTeamMember(memberB, _ptrA);
					CharactersPtr[_ptrA->getCharacterID()].setCharacterIconShift(TeamPlaceHolder[teamB * (MAX_TEAM_MEMBER_SIZE + 1) + memberB + 1].getVexPosx(), TeamPlaceHolder[teamB * (MAX_TEAM_MEMBER_SIZE + 1) + memberB + 1].getVexPosy());
					CharactersPtr[_ptrA->getCharacterID()].setTeamID(teamB);
				}
				// if it is picked from character list
				else {
					// NOTE: currPickIcon == prevPickLoct
					TeamsPtr[teamA].setTeamMember(memberA, &CharactersPtr[currPickIcon]);
					CharactersPtr[prevPickLoct].setCharacterIconShift(TeamPlaceHolder[teamA * (MAX_TEAM_MEMBER_SIZE + 1) + memberA + 1].getVexPosx(), TeamPlaceHolder[teamA * (MAX_TEAM_MEMBER_SIZE + 1) + memberA + 1].getVexPosy());
					CharactersPtr[prevPickLoct].setTeamID(teamA);

					CharactersPtr[_ptrA->getCharacterID()].setCharacterIconShift(CharacterPlaceHolder[_ptrA->getCharacterID()].getVexPosx(), CharacterPlaceHolder[_ptrA->getCharacterID()].getVexPosy());
					CharactersPtr[_ptrA->getCharacterID()].setTeamID(-1);
				}
			}
		}
		/////// end here //////////////
		/////////////////////////////////
	}
	currPickIcon = -1;
	prevPickLoct = -1;
}

int TeamMenu::isCharactersEntryCollision(float _posx, float _posy)
{
	for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		if (CharactersPtr[i].getCharacterIconSprite()->isCollision(_posx - CharactersPtr[i].getCharacterIconShiftx(), _posy - CharactersPtr[i].getCharacterIconShifty(), 0.0f, 0.0f)) {
			return i;
		}
	}
	return -1;
}

int TeamMenu::isTeamEntryCollision(float _posx, float _posy)
{
	for (int i = 0; i < MAX_TEAM_SIZE * (MAX_TEAM_MEMBER_SIZE + 1); i++) {
		if (i % (MAX_TEAM_MEMBER_SIZE + 1) != 0) {
			if (TeamPlaceHolder[i].isCollision(_posx, _posy, 0.0f, 0.0f)) {
				return i;
			}
		}
	}
	return -1;
}