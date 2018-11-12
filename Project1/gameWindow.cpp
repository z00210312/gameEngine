#include "gameWindow.h"
//#define WaitPullMode 0;

gameWindow::gameWindow(const char *title, int &width, int &height)
{
	_DefaultColorProgram = new GLSL();
	m_texObj = new textureObj();
	fontTex = new gameFont();


	// window variables
	m_title = title;
	m_width = width;
	m_height = height;
	
	// openGL variables
	init();
	glClearColor(0.5, 0.5f, 0.5, 1.0f);
	glfwPollEvents();
	glfwSwapBuffers(m_window);
	
	// game variables
	newState = loading;

	lastTime = 0.0;
	CurrentSpritesLocation_x = 0.0f;
	CurrentSpritesLocation_y = 0.0f;
	light_pos_z = -1.0f;

	testScaleValue = 1.0f;
	testDegree = 0.0f;

	// GLSL
	_DefaultColorProgram->setGLSL("Shader/newShader.vert", "Shader/newShader.frag", "Shader/newShader.attr");

	setMainScene();
	setCrusor();

	// finish loading 
	newState = mainScene;

	/////////////////
	// game variables
	/////////////////

	sideBorder = new SpriteBorder(m_texObj,"Shader/border_sprite2.png");
	smallBorder = new SpriteBorder(m_texObj,"Shader/border_sprite2.png");
	largeBorder = new SpriteBorder(m_texObj,"Shader/border_sprite2.png");
	sideBorder->setVertexValue		((float)-width / height, -1.0f, 0.8f, 1.0f);
	smallBorder->setVertexValue		((float)-width / height + 0.8f, -1.0f, 0.8f, 2.0f);
	largeBorder->setVertexValue		((float)width / height - 1.1f, -1.0f, 1.1f, 2.0f);

	

	newCharacter = new CharacterObj[4]();
	newCharacter[0].initCharacterObj(0, m_texObj, "Shader/characterName.png", "Shader/Idle__000.png", "Shader/BlankSpot.png", 8);
	newCharacter[0].getCharacterIconSprite()->setSpriteUV((float)0 / 3, (float)0 / 3, (float)3 / 3, (float)1 / 3);
	newCharacter[1].initCharacterObj(1, m_texObj, "Shader/characterName.png", "Shader/CharacterLeft_Standing.png", "Shader/BlankSpot.png", 8);
	newCharacter[1].getCharacterIconSprite()->setSpriteUV((float)0 / 3, (float)1 / 3, (float)3 / 3, (float)2 / 3);
	newCharacter[2].initCharacterObj(2, m_texObj, "Shader/characterName.png", "Shader/Idle__000.png", "Shader/BlankSpot.png", 8);
	newCharacter[2].getCharacterIconSprite()->setSpriteUV((float)0 / 3, (float)2 / 3, (float)3 / 3, (float)3 / 3);
	newCharacter[3].initCharacterObj(3, m_texObj, "Shader/characterName.png", "Shader/Idle__000.png", "Shader/BlankSpot.png", 8);
	newCharacter[3].getCharacterIconSprite()->setSpriteUV((float)0 / 3, (float)0 / 3, (float)3 / 3, (float)1 / 3);
	newCharacter[3].getCharacterIconSprite()->setSpriteColor(200,150,100,255);

	newTeam = new TeamObj[4]();
	newTeam[0].initTeamObj(0, m_texObj, "Shader/border_2.png", "Shader/border_0.png", 4);
	newTeam[0].getTeamIconSprite()->setSpriteColor(200, 150, 100, 255);
	newTeam[1].initTeamObj(1, m_texObj, "Shader/border_2.png", "Shader/border_0.png", 4);
	newTeam[1].getTeamIconSprite()->setSpriteColor(200, 250, 100, 255);
	newTeam[2].initTeamObj(2, m_texObj, "Shader/border_2.png", "Shader/border_0.png", 4);
	newTeam[2].getTeamIconSprite()->setSpriteColor(100, 150, 200, 255);
	newTeam[3].initTeamObj(3, m_texObj, "Shader/border_2.png", "Shader/border_0.png", 4);
	newTeam[3].getTeamIconSprite()->setSpriteColor(50, 150, 100, 255);

	teamMenu = new TeamMenu(m_texObj, "Shader/border_sprite1.png", "Shader/border_sprite2.png", 20, 4, 4);
	teamMenu->setPlaceHolder(m_width, m_height, 18);
	teamMenu->setCharactersPtr(4, newCharacter);
	teamMenu->setCharactersEntry();
	teamMenu->setTeamsPtr(4, newTeam);
	teamMenu->setTeamsEntry();

	newCharaMenu = new CharacterMenu(m_texObj, "Shader/border_2.png",9,5,5);
	newCharaMenu->setInventoryItemsEntry(m_width,m_height);
	newCharaMenu->setCharactersPtr(4, newCharacter);
	newCharaMenu->setPlaceHolder(m_width, m_height);

	itemCounter = 0;
}


gameWindow::~gameWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();

	delete _DefaultColorProgram;
	delete m_texObj;
	delete fontTex;
	delete sideBorder;
	delete smallBorder;
	delete largeBorder;
	delete[] newCharacter;
}

bool gameWindow::init()
{
	if (!glfwInit()) {
		std::cout << "GLFW error" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!m_window) {
		std::cout << "window error" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, 100, 100);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW error" << std::endl;
		return false;
	}

	initKeys();
	initCallbacks();

	return true;
}

void gameWindow::initKeys()
{
	for (bool i : m_key)
		i = false;
	for (bool j : m_mouseButton)
		j = false;
}

void gameWindow::initCallbacks()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
}

void gameWindow::gameLoop()
{
	
	while (!gameClose()) {
		time = glfwGetTime();
		deltaTime = time - lastTime;
		if (deltaTime >= maxPeriod) {
			lastTime = time;
			gameClear();
			gameUpdate();
		}
	}
}

void gameWindow::gameClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gameWindow::gameUpdate()
{
	glfwPollEvents();

	resetDrawProgram();
	switch (newState) {
	case mainScene:
		spriteMainScene();
		break;
	case playScene:
		break;
	case characterMenuScene:
		sideBorder->drawSprite(_DefaultColorProgram);
		smallBorder->drawSprite(_DefaultColorProgram);
		largeBorder->drawSprite(_DefaultColorProgram);
		newCharaMenu->setCharactersEntry(m_width,m_height);
		newCharaMenu->drawSprite(_DefaultColorProgram);
		if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			newCharaMenu->isStillHoldItem(getWindowMousePosx(), getWindowMousePosy());
		break;
	case teamMenuScene:
		sideBorder->drawSprite(_DefaultColorProgram);
		smallBorder->drawSprite(_DefaultColorProgram);
		largeBorder->drawSprite(_DefaultColorProgram);
		teamMenu->setCharactersEntry();
		teamMenu->setTeamsEntry();
		if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			teamMenu->isHoldCharacter(getWindowMousePosx(), getWindowMousePosy());
		teamMenu->drawSprite(_DefaultColorProgram);
		break;
	default:
		break;
	}
	spriteCrusor();
	glfwSwapBuffers(m_window);
}

bool gameWindow::isKeyPressed(unsigned int key) const
{
	if (key>KEY_MAX)
		return false;
	return m_key[key];
}

bool gameWindow::isMouseButtonPressed(unsigned int button) const
{
	if (button>MOUSE_BUTTON_MAX)
		return false;
	return m_mouseButton[button];
}

void gameWindow::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	switch (win->newState) {
	case playScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = mainScene;
		break;
	case characterMenuScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = playScene;
		else if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
			win->newItemPtr = new InventoryItemObj();
			win->newItemPtr->initItemObj(win->itemCounter++, win->m_texObj, "Shader/BlankSpot_0.png");
			win->newCharaMenu->addItem(win->newItemPtr);
		}
		else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
			win->newItemPtr = new InventoryItemObj();
			win->newItemPtr->initItemObj(win->itemCounter++, win->m_texObj, "Shader/border_sprite2.png");
			win->newCharaMenu->addItem(win->newItemPtr);
		}
		else if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS) {
			for (int i = 0; i < win->newCharaMenu->getMaxInventorySize(); i++) {
				InventoryItemObj* _objPtr = win->newCharaMenu->getItem(i);
				if (_objPtr != nullptr) {
					win->newCharaMenu->delItem(i);
					delete _objPtr;
				}

			}
		}
		break;
	case teamMenuScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = playScene;
		break;
	default:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}

	win->m_key[key] = action != GLFW_RELEASE;
	/*
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		win->newSlots.currCharacter = 1;
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		win->newSlots.currCharacter = 0;
	*/
}

void gameWindow::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);

	switch (win->newState) {
	case mainScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->newState = playScene;
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	case playScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->newState = characterMenuScene;
			}
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
				win->newState = teamMenuScene;
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = mainScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {

			}
		}
		break;
	case loading:
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			win->CurrentSpritesLocation_x = 0.0f;
			win->CurrentSpritesLocation_y = 0.0f;
			win->newState = mainScene;
		}
		break;
	case characterMenuScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->newCharaMenu->pickUpItem(win->getWindowMousePosx(), win->getWindowMousePosy());
				int changeCharaInt = win->newCharaMenu->isCharacterPlaceHolderCollision(win->getWindowMousePosx(), win->getWindowMousePosy());
				if(changeCharaInt != -1)
					win->newCharaMenu->changeCurrCharacter(changeCharaInt);
				//win->newCharaMenu->isCharacterPlaceHolderCollision(win->getWindowMousePosx(), win->getWindowMousePosy());
				//win->newCharaMenu->isCharacterInventoryItemsCollision(win->getWindowMousePosx(), win->getWindowMousePosy());
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = playScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->newCharaMenu->releaseItem(win->getWindowMousePosx(), win->getWindowMousePosy());
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	case teamMenuScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->teamMenu->pickUpCharacter(win->getWindowMousePosx(), win->getWindowMousePosy());
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = playScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->teamMenu->releaseCharacter(win->getWindowMousePosx(), win->getWindowMousePosy());
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	default:
		break;
	}
	win->m_mouseButton[button] = action != GLFW_RELEASE;
}

void gameWindow::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	win->m_cursor_xpos = (float)xpos;
	win->m_cursor_ypos = (float)ypos;
}

void gameWindow::resize_callback(GLFWwindow * window, int width, int height)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	glViewport(0, 0, width, height);
	win->m_width = width;
	win->m_height = height;
}

void gameWindow::resetDrawProgram()
{
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setOrthoMatrix((float)-m_width / m_height, (float)m_width / m_height, -1.0f, 1.0f, -3.0f, 3.0f);
	_DefaultColorProgram->setScaleMatrix(glm::vec3(testScaleValue, testScaleValue, testScaleValue));
	_DefaultColorProgram->setRotateMatrix(0.0f, 0.0f, 0.0f, 1.0f);
	//m_colorProgram.setColorAndEffect(1.0f, 1.0f, 1.0f, 1.0f, 0.0000001f, 0.0000001f, light_pos_z);
	_DefaultColorProgram->setColorAndEffect(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, 0.0f);
	_DefaultColorProgram->setTranslateMatrix(0.0f, 0.0f, 0.0f);
	_DefaultColorProgram->disable();
}

void gameWindow::spriteCrusor()
{
	////////// crusor //////////
	////////////////////////////

	//resetDrawProgram();
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setTranslateMatrix(-0.5f*(2.0f * crusorSprite.getVexPosx() + crusorSprite.getVexWidth()) + getWindowMousePosx(), -0.5f*(2.0f * crusorSprite.getVexPosy() + crusorSprite.getVexHeight()) + getWindowMousePosy(), 0.0f);
	//m_colorProgram.setColorAndEffect(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, light_pos_z);
	_DefaultColorProgram->setColorAndEffect(0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);

	m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), crusorTexture);
	crusorSprite.drawSprite();
	m_texObj->disable();

	_DefaultColorProgram->disable();

	////////////////////////////
	/////////// end ////////////
}

void gameWindow::spriteMainScene()
{
	//resetDrawProgram();
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setTranslateMatrix((float)-m_width / m_height - (float)std::fmod(time, 8.0f) / 2, -1.0f, 0.0f);

	m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), backgroundTexture);
	backgroundSprite.drawSprite();
	m_texObj->disable();
	_DefaultColorProgram->disable();
}

void gameWindow::setCrusor()
{
	crusorSprite.setSprite(0.0f, 0.0f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	crusorTexture = m_texObj->setPNGTextureID("Shader/CharacterLeft_Standing.png");
}

void gameWindow::setMainScene()
{
	backgroundTexture = m_texObj->setPNGTextureID("Shader/sky/Daylight Box_0.png");
	backgroundSprite.setSprite(0.0f, 0.0f, 4.0f * 2.0f * (float)m_width / m_height / testScaleValue, 2.0f * (float)m_height / m_height / testScaleValue, 0.0f, 0.0f, 3.0f, 1.0f);
}

float gameWindow::getWindowMousePosx()
{
	return (1.0f / testScaleValue) * ((m_cursor_xpos - (m_width / 2.0f)) / m_width) * 2.0f * m_width / m_height;
}

float gameWindow::getWindowMousePosy()
{
	return (1.0f / testScaleValue) * ((-m_cursor_ypos + (m_height / 2.0f)) / m_height) * 2.0f * m_height / m_height;
}

void gameWindow::testSceneKeyEvnts()
{
	if (isKeyPressed(GLFW_KEY_A)) {
	}
	if (isKeyPressed(GLFW_KEY_D)) {
	}
	if (isKeyPressed(GLFW_KEY_W)) {
	}
	if (isKeyPressed(GLFW_KEY_S)) {
	}

	if (isKeyPressed(GLFW_KEY_PERIOD)) {
		//std::cout << testDegree << std::endl;
		testDegree += 0.1f;
	}

	if (isKeyPressed(GLFW_KEY_COMMA)) {
		//std::cout << testDegree << std::endl;
		testDegree -= 0.1f;
	}

	if (isKeyPressed(GLFW_KEY_R)) {
		testDegree = 0.0f;
		light_pos_z = 1.0f;
		CurrentSpritesLocation_x = 0.0f;
		CurrentSpritesLocation_y = 0.0f;
	}

	if (isKeyPressed(GLFW_KEY_F)) {
	}

	if (isKeyPressed(GLFW_KEY_Z)) {
		light_pos_z++;
	}

	if (isKeyPressed(GLFW_KEY_C)) {
		light_pos_z--;
	}

	if (isKeyPressed(GLFW_KEY_X)) {
	}
}