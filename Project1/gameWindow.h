#pragma once
#include "GLSL.h"
#include "textureObj.h"
#include "spriteObj.h"
#include "gameFont.h"
//#include "../add/include/GLEW/glew.h"
#include "../add/include/GLFW/glfw3.h"

#include "SpriteBorder.h"
#include "TeamMenu.h"
#include "CharacterMenu.h"

#define KEY_MAX 1024
#define MOUSE_BUTTON_MAX 32

class gameWindow
{
private:
	// also need to change characterMenu.h
	const static short int CHARACTER_MAX = 14;
	const double maxFPS = 40.0f;
	const double maxPeriod = 1.0 / maxFPS;
	double time, deltaTime, lastTime;

	const char *m_title;
	int m_width, m_height;
	GLFWwindow *m_window;

	bool m_key[KEY_MAX];
	bool m_mouseButton[MOUSE_BUTTON_MAX];
	float m_cursor_xpos;
	float m_cursor_ypos;

	float CurrentSpritesLocation_x;
	float CurrentSpritesLocation_y;

	GLSL* _DefaultColorProgram;
	textureObj* m_texObj;
	gameFont* fontTex;

	float testDegree;
	float testScaleValue;
	float light_pos_z;

	spriteObj crusorSprite;
	GLuint crusorTexture;

	spriteObj backgroundSprite;
	GLuint backgroundTexture;

	enum sceneState {mainScene, playScene, loading, /*inventoryScene, */characterMenuScene, teamMenuScene }newState;

	//////////////////////
	// game variables
	//////////////////////
	SpriteBorder* sideBorder;
	SpriteBorder* smallBorder;
	SpriteBorder* largeBorder;
	TeamMenu* teamMenu;
	CharacterObj* newCharacter;
	TeamObj* newTeam;

	InventoryItemObj newItem;
	InventoryItemObj newItem2;
	InventoryItemObj* newItemPtr;
	short int itemCounter;
	//InventoryStashObj newStash;
	CharacterMenu* newCharaMenu;
public:
	gameWindow(const char *title, int& width, int& height);
	~gameWindow();

	bool init();
	void initKeys();
	void initCallbacks();

	void gameLoop();
	void gameClear();
	void gameUpdate();
	inline bool gameClose() { return glfwWindowShouldClose(m_window); }

	bool isKeyPressed(unsigned int key) const;
	bool isMouseButtonPressed(unsigned int button) const;

	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
	static void resize_callback(GLFWwindow * window, int width, int height);

	void resetDrawProgram();
	void spriteCrusor();
	void spriteMainScene();
	void spriteInventory();

	void setCrusor();
	void setMainScene();
	void setInventory();
	void setCharacter();

	float getWindowMousePosx();
	float getWindowMousePosy();

	void testSceneKeyEvnts();
};

