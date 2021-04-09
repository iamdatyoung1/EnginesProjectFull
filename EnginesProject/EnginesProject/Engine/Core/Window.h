#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window
{
public:
	//Constructor 
	Window();
	//Destructor 
	~Window();
	//We are Creating the window with the name, widht and height of the window
	bool OnCreate(std::string name_, int width_, int height_);
	//Destroy Function
	void OnDestroy();
	//Get the width
	int GetWidth() const;
	//Get the Height
	int GetHeight() const;
	//Pointing the SDL window
	SDL_Window* GetWindow() const;

private:
	
	//Set PRe Atributes 
	void SetPreAttributes();
	//Set Post Attributes
	void SetPostAttributes();
	//Set Width
	int width;
	//Set Height
	int height;

	SDL_Window* window;
	//door way into our graphics card 
	SDL_GLContext context;

};
#endif
