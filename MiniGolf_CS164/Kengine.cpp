#include "Kengine.h"
#include "Shader.h"
#include "UserInput.h"
#include "CommonUtils.h"
#include "Camera.h"
#include "Projection.h"
#include "ArcballCamera.h"
#include "FreelookCamera.h"
#include "TopDown.h"
#include "LevelManager.h"
#include "Renderable.h"
#include "GameMenu.h"
#include "MenuContext.h"

#include <gl\glfw.h>

static Kengine *kengine = 0;

// Registers key presses with the input manager
void keyboard(unsigned char key, int x, int y)
{
	kengine->userInput->PressKey(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	kengine->userInput->ReleaseKey(key);
}

void keyboardSpecial(int key, int x, int y)
{
  kengine->userInput->PressSpecialKey(key);
}

void keyboardSpecialUp(int key, int x, int y)
{
  kengine->userInput->ReleaseSpecialKey(key);
}

void display()
{
	glViewport(0, 0, 640, 480);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  MenuContext *mc = kengine->userInput->Menu();

  if (mc == 0)
  {
    // Draw all 3D-placed objects
    kengine->shader->Enable();
	  glEnable(GL_DEPTH_TEST);
    // Send new values to the shaders
	  glUniform3fv(kengine->shader->eye, 1, (GLfloat*) kengine->c[kengine->activeCamera]->GetPosition());
	  glUniformMatrix4fv(kengine->shader->mat_camera, 1, GL_FALSE, (GLfloat*) kengine->c[kengine->activeCamera]->Matrix());
	  glUniformMatrix4fv(kengine->shader->mat_projection, 1, GL_FALSE, (GLfloat*) kengine->_projection->Matrix());

    kengine->_levelMgr->Render(kengine->c[kengine->activeCamera], kengine->shader);

    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,640,0,480,-5,5);
    glTranslatef(0.f, 460.f, 0.f);
    glScalef(1.f, -1.f, 1.f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    kengine->userInput->InGameHUD()->Render();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE);
    glEnable(GL_LIGHTING);
  }
  else
  {
    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,640,0,480,-5,5);
    glTranslatef(0.f, 460.f, 0.f);
    glScalef(1.f, -1.f, 1.f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    mc->Render();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE);
    glEnable(GL_LIGHTING);
  }
  // Time to draw the HUD!
  //glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void Tick(int value)
{
  double dt = 0.02;
	kengine->_projection->Tick();

	// Handle user input
	kengine->userInput->Tick(dt);
	if (kengine->userInput->IsKeyPressed('c'))
	{
		if (kengine->activeCamera == 0)
		{
			kengine->activeCamera = 1;
			std::cout << "Arcball" << std::endl;
		}
		else
		{
			kengine->activeCamera = 0;
		}
		kengine->userInput->BindCamera(kengine->c[kengine->activeCamera]);
		kengine->userInput->ReleaseKey('c');
	}
  /*
	else
	if (kengine->userInput->IsKeyPressed('v'))
	{
		if(kengine->activeCamera == 1 || kengine->activeCamera == 0)
		{
			kengine->activeCamera = 2;
			std::cout << "TopDown" << std::endl;
		}
		else
		{
			kengine->activeCamera = 0;
		}
		kengine->userInput->BindCamera(kengine->c[kengine->activeCamera]);
		kengine->userInput->ReleaseKey('v');
	}*/

	kengine->c[kengine->activeCamera]->Tick();

  kengine->_levelMgr->Tick(dt);

	glutPostRedisplay();
	glutTimerFunc(20, Tick, 0);
}

void Kengine::InitGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Use both!
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_AND_BACK);

	windowId = glutCreateWindow("Derp");
}

bool Kengine::Init(int argc, char** argv)
{
	if (argc < 2)
	{
		return false;
	}

	kengine = this;

	InitGlut(argc, argv);

	glewInit();

	// Initialize Shader
	shader = new Shader;
	if (!shader->Init("vert.glsl", "frag.glsl")) return false;
	shader->Enable();

	// Set the Renderable class to use the shader
  Renderable::UseShader(shader);

	c[1] = new FreelookCamera;
	c[1]->Init();
	c[0] = new ArcballCamera;
	c[0]->Init();
	c[2] = new TopDown;
	c[2]->Init();

	_projection = new Projection;
	_projection->Init();
	_projection->fovy(45.f);
	_projection->znear(0.1f);
	_projection->zfar(10000.f);
	_projection->screenWidth(640);
	_projection->screenHeight(480);

	userInput = new UserInput;
	userInput->BindCamera(c[0]);

  _levelMgr = new LevelManager;
  _levelMgr->Initialize(); // can't fail yet
  if (_levelMgr->LoadLevels() != 0x1)
  {
    return false;
  }
  _levelMgr->_uin = userInput;
  _levelMgr->PlayLevel(0);
  userInput->SetLevelManager(_levelMgr);

  _menu = new GameMenu;
  _menu->Initialize();
  _menu->SetLevelManager(_levelMgr);
  _menu->ActivateLevelManagerContext();

  userInput->SetLevelMenuContext(_menu->LevelContext());
  userInput->SetGameMenuContext(_menu->GameContext());

	InitCallbacks();

	return true;
}

void Kengine::InitCallbacks()
{
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(keyboardSpecial);
  glutSpecialUpFunc(keyboardSpecialUp);
	glutTimerFunc(20, Tick, 0);
}

void Kengine::Run()
{
	glutMainLoop();
}

void Kengine::DeInit()
{
	Delete(&userInput);
	Delete(&shader);
}
