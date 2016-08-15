#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Scene.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);

    void GetMonitorResolution();

	static int GetWindowWidth();
	static int GetWindowHeight();

    // Game Scenes
    Scene *scene;

private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
};

#endif