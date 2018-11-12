#include "CharacterMenu.h"

CharacterMenu::CharacterMenu(textureObj* _texObj, const char* _characterPlaceHolderTextureID, unsigned short _MAX_ROW, unsigned short  _MAX_COL, unsigned short _MAX_CHARACTER_SIZE)
{
	texObj = _texObj;
	CharacterPlaceHolderTextureID = texObj->setPNGTextureID(_characterPlaceHolderTextureID);
	MAX_ROW = _MAX_ROW;
	MAX_COL = _MAX_COL;
	MAX_INVENTORY_ITEM_SIZE = MAX_ROW * MAX_COL;
	MAX_CHARACTER_SIZE = _MAX_CHARACTER_SIZE;
	newIntStash.initInventoryStashObj(0, texObj, "Shader/BlankSpot.png", MAX_ROW, MAX_COL);

	currPickIcon = -1;
	prevPickLoct = -1;

	currCharacter = 0;
}

CharacterMenu::~CharacterMenu()
{
	delete[] CharacterPlaceHolder;
}

void CharacterMenu::setPlaceHolder(int _width, int _height)
{
	CharacterPlaceHolder = new spriteObj[MAX_CHARACTER_SIZE];
	for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		CharacterPlaceHolder[i].setSprite((float)-_width / _height + 0.9f, 0.8f - 0.1f*i, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	}

	CharacterEquipmentPlaceHolder = new spriteObj[MAX_CHARACTER_EQUIPMENT_SIZE];
	CharacterEquipmentPlaceHolder[0].setSprite((float)_width / _height - 0.4f, 0.8f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[1].setSprite((float)_width / _height - 0.3f, 0.8f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[2].setSprite((float)_width / _height - 0.2f, 0.8f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[3].setSprite((float)_width / _height - 0.4f, 0.7f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[4].setSprite((float)_width / _height - 0.3f, 0.7f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[5].setSprite((float)_width / _height - 0.2f, 0.7f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[6].setSprite((float)_width / _height - 0.4f, 0.6f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	CharacterEquipmentPlaceHolder[7].setSprite((float)_width / _height - 0.3f, 0.6f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
}

unsigned short CharacterMenu::getMaxInventorySize()
{
	return MAX_INVENTORY_ITEM_SIZE;
}

bool CharacterMenu::addItem(InventoryItemObj * _newItemPtr)
{
	if (_newItemPtr->getInventoryLoc() != -1)
		return false;
	for (int i = 0; i < MAX_INVENTORY_ITEM_SIZE; i++) {
		if (!newIntStash.getInventoryListItem(i)) { // if there is no item
			newIntStash.setInventoryListItem(i, _newItemPtr);
			float _posx = newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(i)->getVexPosx();
			float _posy = newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(i)->getVexPosy();
			_newItemPtr->setItemIconShift(_posx, _posy);
			_newItemPtr->setInventoryLoc(i);
			return true;
		}
	}
	return false;
}

InventoryItemObj* CharacterMenu::getItem(int index)
{
	return newIntStash.getInventoryListItem(index);
}

bool CharacterMenu::delItem(int index)
{
	if (newIntStash.getInventoryListItem(index)) {
		newIntStash.getInventoryListItem(index)->setInventoryLoc(-1);
		newIntStash.setInventoryListItem(index, nullptr);
	}
	return false;
}

void CharacterMenu::drawSprite(GLSL * _colorProgram)
{
	// draw empty character sprites
	for (int i = 0; i < CharacterSize; i++) {
	//for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		_colorProgram->enable();
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharacterPlaceHolderTextureID);
		CharacterPlaceHolder[i].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	// draw character equipments
	for (int i = 0; i < MAX_CHARACTER_EQUIPMENT_SIZE; i++) {
		_colorProgram->enable();
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharacterPlaceHolderTextureID);
		CharacterEquipmentPlaceHolder[i].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	// draw empty inventory sprites
	for (int i = 0; i < MAX_INVENTORY_ITEM_SIZE; i++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(newIntStash.getInventoryListItemShiftx(), newIntStash.getInventoryListItemShifty(),0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), newIntStash.getEmptyItemIconID());
		newIntStash.getInventoryListItemSprite(i)->drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	// draw items
	for (int i = 0; i < MAX_INVENTORY_ITEM_SIZE; i++) {
		if (newIntStash.getInventoryListItem(i)) {
			_colorProgram->enable();
			_colorProgram->setTranslateMatrix(newIntStash.getInventoryListItem(i)->getItemIconShiftx(), newIntStash.getInventoryListItem(i)->getItemIconShifty(), 0.0f);
			texObj->enable(_colorProgram->getUniformLocation("sampler_1"), newIntStash.getInventoryListItem(i)->getItemIconID());
			newIntStash.getInventoryListItem(i)->getItemIconSprite()->drawSprite();
			texObj->disable();
			_colorProgram->disable();
		}
	}

	// draw equipment items
	for (int i = 0; i < MAX_CHARACTER_EQUIPMENT_SIZE; i++) {
		if (CharactersPtr[currCharacter].getCharacterEquipmentItem(i)) {
			_colorProgram->enable();
			_colorProgram->setTranslateMatrix(CharactersPtr[currCharacter].getCharacterEquipmentItem(i)->getItemIconShiftx(), CharactersPtr[currCharacter].getCharacterEquipmentItem(i)->getItemIconShifty(), 0.0f);
			texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[currCharacter].getCharacterEquipmentItem(i)->getItemIconID());
			CharactersPtr[currCharacter].getCharacterEquipmentItem(i)->getItemIconSprite()->drawSprite();
			texObj->disable();
			_colorProgram->disable();
		}
	}

	// draw character icons
	for (int k = 0; k < CharacterSize; k++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(CharactersPtr[k].getCharacterIconShiftx(), CharactersPtr[k].getCharacterIconShifty(), 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[k].getCharacterIconID());
		CharactersPtr[k].getCharacterIconSprite()->drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}

	// draw character picts
	_colorProgram->enable();
	_colorProgram->setTranslateMatrix(CharactersPtr[currCharacter].getCharacterPictShiftx(), CharactersPtr[currCharacter].getCharacterPictShifty(), 0.0f);
	texObj->enable(_colorProgram->getUniformLocation("sampler_1"), CharactersPtr[currCharacter].getCharacterPictID());
	CharactersPtr[currCharacter].getCharacterPictSprite()->drawSprite();
	texObj->disable();
	_colorProgram->disable();
}

void CharacterMenu::setInventoryItemsEntry(int _width, int _height)
{
	newIntStash.setInventoryListItemShift((float)_width / _height - 0.1f*(MAX_ROW + 1), -1.0f + 0.1f*(MAX_COL));
}

void CharacterMenu::setCharactersEntry(int _width, int _height)
{
	for (int i = 0; i < CharacterSize; i++) {
		CharactersPtr[i].setCharacterIconShift(CharacterPlaceHolder[i].getVexPosx(), CharacterPlaceHolder[i].getVexPosy());
		CharactersPtr[i].setCharacterPictShift((float)_width/ _height - CharactersPtr[i].getCharacterPictSprite()->getVexWidth() - 0.7f,1.0f - CharactersPtr[i].getCharacterPictSprite()->getVexHeight() - 0.1f);
	}
}

void CharacterMenu::setCharactersPtr(unsigned short _size, CharacterObj * _CharactersPtr)
{
	CharactersPtr = _CharactersPtr;
	CharacterSize = _size;
}

void CharacterMenu::moveItemIcon(int index, float _posx, float _posy)
{
	float _spritex;
	float _spritey;
	if (index < MAX_INVENTORY_ITEM_SIZE) {
		_spritex = _posx - ( newIntStash.getInventoryListItemSprite(index)->getVexWidth()) / 2;
		_spritey = _posy - ( newIntStash.getInventoryListItemSprite(index)->getVexHeight()) / 2;
		newIntStash.getInventoryListItem(index)->setItemIconShift(_spritex, _spritey);
	}
	else {
		_spritex = _posx - CharactersPtr[currCharacter].getCharacterEquipmentItem(index - MAX_INVENTORY_ITEM_SIZE)->getItemIconSprite()->getVexWidth()/2;
		_spritey = _posy - CharactersPtr[currCharacter].getCharacterEquipmentItem(index - MAX_INVENTORY_ITEM_SIZE)->getItemIconSprite()->getVexHeight()/2;
		CharactersPtr[currCharacter].getCharacterEquipmentItem(index - MAX_INVENTORY_ITEM_SIZE)->setItemIconShift(_spritex, _spritey);
	}
}

bool CharacterMenu::isStillHoldItem(float _posx, float _posy)
{
	if (currPickIcon != -1) {
		moveItemIcon(currPickIcon, _posx, _posy);
		return true;
	}
	return false;
}

void CharacterMenu::pickUpItem(float _posx, float _posy)
{
	// check inventory
	prevPickLoct = isCharacterInventoryItemsCollision(_posx, _posy);
	
	// check equipment
	if (prevPickLoct == -1) {
		prevPickLoct = isCharacterEquipmentPlaceHolderCollision(_posx, _posy);
		if (prevPickLoct != -1)
			prevPickLoct += MAX_INVENTORY_ITEM_SIZE;
	}

	// if no hit, return
	if (prevPickLoct == -1)
		return;

	// get ItemObj index
	if (prevPickLoct < MAX_INVENTORY_ITEM_SIZE) {
		if(newIntStash.getInventoryListItem(prevPickLoct))
			currPickIcon = prevPickLoct;
	}
	else {
		if(CharactersPtr[currCharacter].getCharacterEquipmentItem(prevPickLoct - MAX_INVENTORY_ITEM_SIZE))
			currPickIcon = prevPickLoct;
	}


	/*
	if (prevPickLoct != -1 && newIntStash.getInventoryListItem(prevPickLoct)) {
		currPickIcon = prevPickLoct;
		//std::cout << "PickUpItem" << std::endl;
	}
	else {
		currPickIcon = -1;
	}
	*/
}

void CharacterMenu::releaseItem(float _posx, float _posy)
{
	if (currPickIcon != -1) {

		int currItemSprite = isCharacterInventoryItemsCollision(_posx, _posy);
		InventoryItemObj* _LoctPtr = nullptr;
		InventoryItemObj* _HoldPtr = nullptr;

		// set the Location ItemObj pointer
		if (currItemSprite == -1) {
			currItemSprite = isCharacterEquipmentPlaceHolderCollision(_posx, _posy);
			if (currItemSprite != -1) {
				_LoctPtr = CharactersPtr[currCharacter].getCharacterEquipmentItem(currItemSprite);
				currItemSprite += MAX_INVENTORY_ITEM_SIZE;
			}
		}
		else {
			_LoctPtr = newIntStash.getInventoryListItem(currItemSprite);
		}

		// set the Hold ItemObj pointer
		if (currPickIcon != -1) {
			if (currPickIcon < MAX_INVENTORY_ITEM_SIZE)
				_HoldPtr = newIntStash.getInventoryListItem(currPickIcon);
			else
				_HoldPtr = CharactersPtr[currCharacter].getCharacterEquipmentItem(currPickIcon - MAX_INVENTORY_ITEM_SIZE);
		}

		// change value
		if (currItemSprite != -1) {
			// released at same place
			if (currPickIcon == currItemSprite) {
				if (currItemSprite < MAX_INVENTORY_ITEM_SIZE)
					_HoldPtr->setItemIconShift(newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosx(), newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosy());
				else
					_HoldPtr->setItemIconShift(CharacterEquipmentPlaceHolder[currItemSprite - MAX_INVENTORY_ITEM_SIZE].getVexPosx(), CharacterEquipmentPlaceHolder[currItemSprite - MAX_INVENTORY_ITEM_SIZE].getVexPosy());
			}
			// released on top of item
			else if (_LoctPtr) {
				// set location ItemObj
				if (currItemSprite < MAX_INVENTORY_ITEM_SIZE) {
					newIntStash.setInventoryListItem(currItemSprite, _HoldPtr);
					_HoldPtr->setItemIconShift(newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosx(), newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosy());
					_HoldPtr->setInventoryLoc(currItemSprite);
					_HoldPtr->setCharacterID(-1);
				}
				else {
					CharactersPtr[currCharacter].setCharacterEquipmentItem(currItemSprite- MAX_INVENTORY_ITEM_SIZE, _HoldPtr);
					_HoldPtr->setItemIconShift(CharacterEquipmentPlaceHolder[currItemSprite- MAX_INVENTORY_ITEM_SIZE].getVexPosx(), CharacterEquipmentPlaceHolder[currItemSprite - MAX_INVENTORY_ITEM_SIZE].getVexPosy());
					_HoldPtr->setInventoryLoc(-1);
					_HoldPtr->setCharacterID(currCharacter);
				}

				// set hold ItemObj
				if (currPickIcon < MAX_INVENTORY_ITEM_SIZE) {
					newIntStash.setInventoryListItem(currPickIcon, _LoctPtr);
					_LoctPtr->setItemIconShift(newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(currPickIcon)->getVexPosx(), newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(currPickIcon)->getVexPosy());
					_LoctPtr->setInventoryLoc(currPickIcon);
					_LoctPtr->setCharacterID(-1);
				}
				else {
					CharactersPtr[currCharacter].setCharacterEquipmentItem(currPickIcon - MAX_INVENTORY_ITEM_SIZE, _LoctPtr);
					_LoctPtr->setItemIconShift(CharacterEquipmentPlaceHolder[currPickIcon - MAX_INVENTORY_ITEM_SIZE].getVexPosx(), CharacterEquipmentPlaceHolder[currPickIcon - MAX_INVENTORY_ITEM_SIZE].getVexPosy());
					_HoldPtr->setInventoryLoc(-1);
					_HoldPtr->setCharacterID(currCharacter);
				}
			}
			// released on empty spot
			else {
				if (currItemSprite < MAX_INVENTORY_ITEM_SIZE) {
					newIntStash.setInventoryListItem(currItemSprite, _HoldPtr);
					_HoldPtr->setItemIconShift(newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosx(), newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(currItemSprite)->getVexPosy());
					_HoldPtr->setInventoryLoc(currItemSprite);
					_HoldPtr->setCharacterID(-1);
				}
				else {
					CharactersPtr[currCharacter].setCharacterEquipmentItem(currItemSprite - MAX_INVENTORY_ITEM_SIZE, _HoldPtr);
					_HoldPtr->setItemIconShift(CharacterEquipmentPlaceHolder[currItemSprite - MAX_INVENTORY_ITEM_SIZE].getVexPosx(), CharacterEquipmentPlaceHolder[currItemSprite - MAX_INVENTORY_ITEM_SIZE].getVexPosy());
					_HoldPtr->setInventoryLoc(-1);
					_HoldPtr->setCharacterID(currCharacter);
				}

				if(currPickIcon < MAX_INVENTORY_ITEM_SIZE)
					newIntStash.setInventoryListItem(currPickIcon, nullptr);
				else
					CharactersPtr[currCharacter].setCharacterEquipmentItem(currPickIcon - MAX_INVENTORY_ITEM_SIZE, nullptr);
			}
		}
		// released on invalid location
		else {
			if (currPickIcon < MAX_INVENTORY_ITEM_SIZE)
				_HoldPtr->setItemIconShift(newIntStash.getInventoryListItemShiftx() + newIntStash.getInventoryListItemSprite(currPickIcon)->getVexPosx(), newIntStash.getInventoryListItemShifty() + newIntStash.getInventoryListItemSprite(currPickIcon)->getVexPosy());
			else
				_HoldPtr->setItemIconShift(CharacterEquipmentPlaceHolder[currPickIcon - MAX_INVENTORY_ITEM_SIZE].getVexPosx(), CharacterEquipmentPlaceHolder[currPickIcon - MAX_INVENTORY_ITEM_SIZE].getVexPosy());
		}
	}
	currPickIcon = -1;
	prevPickLoct = -1;
}

void CharacterMenu::changeCurrCharacter(int index)
{
	if (index > CharacterSize)
		return;
	currCharacter = index;
}

int CharacterMenu::isCharacterPlaceHolderCollision(float _posx, float _posy)
{
	int returnValue = -1;
	for (int i = 0; i < MAX_CHARACTER_SIZE; i++) {
		if (CharacterPlaceHolder[i].isCollision(_posx, _posy, 0.0f, 0.0f)) {
			returnValue = i;
			break;
		}
	}
	if (returnValue >= CharacterSize)
		returnValue = -1;
	return returnValue;
}

int CharacterMenu::isCharacterInventoryItemsCollision(float _posx, float _posy)
{
	float _spritex;
	float _spritey;
	for (int i = 0; i < MAX_INVENTORY_ITEM_SIZE; i++) {
		_spritex = -newIntStash.getInventoryListItemShiftx() + _posx;
		_spritey = -newIntStash.getInventoryListItemShifty() + _posy;
		if (newIntStash.getInventoryListItemSprite(i)->isCollision(_spritex, _spritey, 0.0f, 0.0f)) {
			//std::cout << "isCharacterInventoryItemsCollision" << std::endl;
			return i;
		}
	}
	return -1;
}

int CharacterMenu::isCharacterEquipmentPlaceHolderCollision(float _posx, float _posy)
{
	for (int i = 0; i < MAX_CHARACTER_EQUIPMENT_SIZE; i++) {
		if (CharacterEquipmentPlaceHolder[i].isCollision(_posx, _posy, 0.0f, 0.0f))
			return i;
	}
	return -1;
}
