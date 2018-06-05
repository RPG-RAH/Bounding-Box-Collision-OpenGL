#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game
{
	GLFWwindow* window;
	string Title,errorMessage;
	int width,height;
	bool call_start,call_update;
	public :
		 GLFWwindow* getWindow() {return window;}
		 Game(string Title,int=500,int=500,bool=false);
		~Game() {glfwTerminate();}
		 GLFWmonitor* getScreenDetails();
		 void gameLoop();
};
//User Defined Functions 
void start() __attribute__((weak));
void update(GLFWwindow*) __attribute__((weak));

//Class Function Definition
Game::Game(string Title,int width,int height,bool isFullscreen)
{
	this->width  = width,this->height = height;
	this->Title  = Title;
	this->errorMessage = "";
	this->call_start = this->call_update = true;
	if(!glfwInit())
	{
		this->errorMessage = "GLFW is not Initialized";
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	if(!(this->window=glfwCreateWindow(this->width,this->height,Title.c_str(),isFullscreen?getScreenDetails():NULL,NULL)))
	{
		this->errorMessage = "Game Window not Initialized";
		return;
	}
	glfwMakeContextCurrent(window);
	glewExperimental=GL_TRUE;
	if(glewInit()!=GLEW_OK)
	{
		this->errorMessage = "Game Window not Initialized";
		return;
	}
}

GLFWmonitor* Game::getScreenDetails()
{ 
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* v = glfwGetVideoMode(monitor);
	if(v!=NULL)
	{
		this->width  = v->width;
		this->height = v->height;
		return monitor;
	}
	return NULL;
}

void Game::gameLoop()
{
	if(errorMessage=="")
	{
		if(call_start)
		{
			if(start) start();
			else{ 	cerr<<"Warning!! : Define Function void start() "<<endl;
				call_start = false;}
		}
		while(!glfwWindowShouldClose(window))
		{
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f,0.0f,0.0f,0.0f);
			if(call_update)
			{
				if(update) update(window);
				else 
				{	cerr<<"Warning!! : Define Function void update() "<<endl;
					call_update = false;}
			}
			glfwPollEvents();
			glEnable(GL_DEPTH_TEST);
			glfwSwapBuffers(window);
		}
	}
}
