#pragma once

class IWindow;
class Scene;
class IInputManager;

class Director
{
public:
	static Director* getInstance();
	void init();

	IWindow* getWindow();
	IInputManager* getInputManager();
	void setWindow(IWindow* window);

	void mainLoop(float delta);

	IWindow* createDefaultWindow();

	void runWithScene(Scene* scene);
	Scene* getRunningScene();

private:
	Director();
private:
	IWindow* mWindow;

	Scene* mCurrentScene;
};