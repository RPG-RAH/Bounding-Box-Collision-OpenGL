#include <string>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Mesh
	const GLfloat vertices[180] =		{
								//Back
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								-0.5f,-0.5f,-0.5f,0.0f,0.0f,
								 0.5f,-0.5f,-0.5f,1.0f,0.0f,
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								 0.5f,-0.5f,-0.5f,1.0f,0.0f,
								 0.5f, 0.5f,-0.5f,1.0f,1.0f,
								//Front
								-0.5f, 0.5f, 0.5f,0.0f,1.0f,
								-0.5f,-0.5f, 0.5f,0.0f,0.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								-0.5f, 0.5f, 0.5f,0.0f,1.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								 0.5f, 0.5f, 0.5f,1.0f,1.0f,
								//Left
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								-0.5f,-0.5f,-0.5f,0.0f,0.0f,
								-0.5f,-0.5f, 0.5f,1.0f,0.0f,
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								-0.5f,-0.5f, 0.5f,1.0f,0.0f,
								-0.5f, 0.5f, 0.5f,1.0f,1.0f,
								//Right
								 0.5f, 0.5f,-0.5f,0.0f,1.0f,
								 0.5f,-0.5f,-0.5f,0.0f,0.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								 0.5f, 0.5f,-0.5f,0.0f,1.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								 0.5f, 0.5f, 0.5f,1.0f,1.0f,
								//Top
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								 0.5f, 0.5f,-0.5f,0.0f,0.0f,
								 0.5f, 0.5f, 0.5f,1.0f,0.0f,
								-0.5f, 0.5f,-0.5f,0.0f,1.0f,
								 0.5f, 0.5f, 0.5f,1.0f,0.0f,
								-0.5f, 0.5f, 0.5f,1.0f,1.0f,
								//Bottom
								-0.5f,-0.5f,-0.5f,0.0f,1.0f,
								 0.5f,-0.5f,-0.5f,0.0f,0.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								-0.5f,-0.5f,-0.5f,0.0f,1.0f,
								 0.5f,-0.5f, 0.5f,1.0f,0.0f,
								-0.5f,-0.5f, 0.5f,1.0f,1.0f						   							};
//Classes
class Cube
{
	int loc;
	vec3 cubePos;
	GLuint vbo,vao,texId;
	GLint imageWidth,imageHeight,components;
	unsigned char* data;
	bool useTex;
	
	public :
		 vec3 minSet,maxSet; //Bounding Box Collision
		 Cube(int,string="");
		~Cube();
		 void draw(vec3);
		 bool loadTexture(string);
};


Cube::Cube(int loc,string textureLoc)
{
	this->loc = loc;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(loc,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),NULL);
	glVertexAttribPointer(loc+1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(loc);
	glEnableVertexAttribArray(loc+1);

	glBindVertexArray(0);
	useTex = loadTexture(textureLoc);
}

bool Cube::loadTexture(string filename)
{
	data = stbi_load(filename.c_str(),&imageWidth,&imageHeight,&components,STBI_rgb_alpha);
	if(data==NULL)
	{
		cout<<"Texture Error!!"<<endl;
		return false;
	}
	glGenTextures(1,&texId);
	glBindTexture(GL_TEXTURE_2D,texId);
	glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}

void Cube::draw(vec3 cubePos)
{
	this->cubePos = cubePos;
	if(useTex) glBindTexture(GL_TEXTURE_2D,texId);
	glBindVertexArray(vao);	
	glDrawArrays(GL_TRIANGLES,0,sizeof(vertices)/sizeof(3*vertices[0]));
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D,0);
}

Cube::~Cube()
{
	glDeleteTextures(1,&texId);
	glDisableVertexAttribArray(loc);
	glDisableVertexAttribArray(loc+1);
	glDeleteVertexArrays(1,&vao);
	glEnableVertexAttribArray(loc);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&vbo);
}

