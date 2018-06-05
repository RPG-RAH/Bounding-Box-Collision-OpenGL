//Header Files
#include <iostream>
using namespace std;

#include "Shader.h"
#include "Shapes.h"
#include "Game.h"
#include "Camera.h"

//Future Version : send the Object in to the arguement and check Collision
//Main Program
int main()
{
	Game game("Bounding Box Algorithm - Game");
	game.gameLoop();
	return 0;
}

void update(GLFWwindow* window)
{
	static Cube c1 = {0,"crate.jpeg"},c2 = {0,"grid.jpeg"};
	static Shader s	= {"shader1"};
	static Camera camera = {window,vec3(0.0f,1.0f,5.0f)};

	camera.update();

	vec3 cubePos =vec3(0.0f,0.0f,0.0f);
	//Get Cube Box MIN and MAX Space in the World
	getMinMax(c1.minSet,c1.maxSet);
	//Input Handling with Collision Detection for Cube Only
	if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
	{
		camera.move(5.0f*0.01f*vec3(camera.look.x,0,camera.look.z));
		if(checkCollision(camera.position,cubePos,c1.minSet,c1.maxSet))
			camera.move(5.0f*0.01f*-vec3(camera.look.x,0,camera.look.z));
	}
	if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
	{
		camera.move(5.0f*0.01f*-vec3(camera.look.x,0,camera.look.z));
		if(checkCollision(camera.position,cubePos,c1.minSet,c1.maxSet))
			camera.move(5.0f*0.01f*vec3(camera.look.x,0,camera.look.z));
	}
	if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
	{
		camera.move(5.0f*0.01f*-vec3(camera.right.x,0,camera.right.z));
		if(checkCollision(camera.position,cubePos,c1.minSet,c1.maxSet))
			camera.move(5.0f*0.01f*vec3(camera.right.x,0,camera.right.z));
	}
	if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
	{
		camera.move(5.0f*0.01f*vec3(camera.right.x,0,camera.right.z));
		if(checkCollision(camera.position,cubePos,c1.minSet,c1.maxSet))
			camera.move(5.0f*0.01f*-vec3(camera.right.x,0,camera.right.z));
	}

	//Basic Cube Box Position in World
	mat4 model = translate(mat4(1.0f),cubePos);
	mat4 view  = camera.getViewMatrix();
	static mat4 projection = perspective(radians(45.0f),1.0f,0.1f,100.0f);
	s.setMVP(model,view,projection);
	s.useProgram();
	c1.draw(cubePos);
	cubePos=vec3(0.0f,-1.0f,0.0f);
	model = translate(mat4(1.0f),cubePos)*scale(mat4(1.0f),vec3(20.0f,1.0f,20.0f));
	s.setMVP(model,view,projection);
	s.useProgram();
	c2.draw(cubePos);
}

