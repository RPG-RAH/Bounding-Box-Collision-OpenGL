#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
using namespace std;


class Shader
{
	private	:
			GLuint vs,fs,program;
			string vertexShaderData;
			string fragmentShaderData;
			string readShaderFile(string);
			fstream file;
	public	:
			 Shader(string);
			~Shader();
			 void setMVP(mat4,mat4,mat4);
			 void useProgram() {glUseProgram(program);}
			 void checkError(GLuint,GLenum);
};

Shader::Shader(string fileLocation)
{
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	vertexShaderData   = readShaderFile(fileLocation+".vs");
	fragmentShaderData = readShaderFile(fileLocation+".fs");
	const GLchar* vertexText   = vertexShaderData.c_str();
	const GLchar* fragmentText = fragmentShaderData.c_str();
	glShaderSource(vs,1,&vertexText,NULL);
	glShaderSource(fs,1,&fragmentText,NULL);
	glCompileShader(vs);
	checkError(vs,GL_COMPILE_STATUS);
	glCompileShader(fs);
	checkError(fs,GL_COMPILE_STATUS);
	program = glCreateProgram();
	glAttachShader(program,vs);
	glAttachShader(program,fs);
	glLinkProgram(program);
	checkError(program,GL_LINK_STATUS);
}

string Shader::readShaderFile(string fileName)
{
	string line;
	ostringstream s;
	file.open(fileName);
	while(!file.eof())
	{
		getline(file,line);
		s<<line<<endl;
	}
	file.close();
	return s.str();
}

void Shader::checkError(GLuint id,GLenum flag)
{
	int result;
	GLchar infoLog[1024];
	if(vs==id||fs==id) glGetShaderiv(id,flag,&result);
	else glGetProgramiv(id,flag,&result);
	if(!result)
	{
		if(vs==id||fs==id)
		{
			glGetShaderInfoLog(id,sizeof(infoLog),NULL,infoLog);
			cout<<"Shader : "<<infoLog<<endl;
		}
		else
		{
			glGetProgramInfoLog(id,sizeof(infoLog),NULL,infoLog);
			cout<<"Program : "<<infoLog<<endl;			
		}
	}
}

void Shader::setMVP(mat4 model,mat4 view,mat4 projection)
{
	glUniformMatrix4fv(glGetUniformLocation(program,"model"),1,GL_FALSE,&model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program,"view"),1,GL_FALSE,&view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program,"projection"),1,GL_FALSE,&projection[0][0]);
}

Shader::~Shader()
{
	glDetachShader(program,vs);
	glDetachShader(program,fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}
