#include "Window.h"

Window::Window() : window (nullptr), context(nullptr)
{
	//You can either set the nullptr in the contructor or on top 
	//window = nullptr;
	//context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	//checking if window would open by leaving a comment if it doesnt work
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
	}
	// no reason to add "this" but its there anyways
	this->width = width_;
	this->height = height_;
	//ask prof
	SetPreAttributes();
	// convert string name into a charstar by putting it into a certain way ( c_str())
	window = SDL_CreateWindow(name_.c_str(),
		//These to functions are macros for the window to be launched in the middle of the screen
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);
	//if the window was not created properly then return false 
	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		return false;
	}
	//ask prof 
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	//GLEW will be used for any opengl call
	//we call glew init which instilizes glew libary, glew libary return a enum.
	//if enum doesnt return a vaule then somethung went wrong
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	 }
	//Objects are rendered there z vaule will be taking into account
	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, width, height);

	return true;

	
}

void Window::OnDestroy()
{
	//Always Destroy all functions that are getting pointed to, then set window to nullptr.
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	//Core PROFILE
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//Major Version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	//Minor Version 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	//Setting BufferSize to 32
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}