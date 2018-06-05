#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
class Camera
{
	public :
		vec3 position,target,up;
		vec3 look,right,WORLD_UP;
		float pitchr,yawr;
		GLFWwindow* window;
		void move(vec3);
		 Camera(GLFWwindow*,vec3=vec3(0.0f,0.0f,0.0f),float=3.14f,float=0.0f);
		~Camera() {}
		 mat4 getViewMatrix() {return lookAt(position,target,up);}
		 void rotate(float yaw,float pitch);
		 void update();
		 void updateVectors();
};

Camera::Camera(GLFWwindow* window,vec3 position,float yaw,float pitch)
{
	this->window = window;
	this->pitchr = pitch , this->yawr = yaw;
	this->position = position;
	right 	 = vec3(0.0f,0.0f,0.0f);
	target   = vec3(0.0f,0.0f,-1.0f);
	up = WORLD_UP = vec3(0.0f,1.0f,0.0f);
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window,500/2,500/2);
}

void Camera::rotate(float yaw,float pitch)
{
	yawr	+= radians(yaw);
	pitchr	+= radians(pitch);
	pitchr  = clamp(pitchr,-3.14f/2.0f+0.1f,3.14f/2.0f-0.1f);
	updateVectors();
}

void Camera::updateVectors()
{
	look.x	= cosf(pitchr)*sinf(yawr);
	look.y	= sinf(pitchr);
	look.z	= cosf(pitchr)*cosf(yawr);
	look	= normalize(look);
	right	= normalize(cross(look,WORLD_UP));
	up	= normalize(cross(right,look));
	target	= position+look;
}

void Camera::move(vec3 offset)
{
	position += offset;
	updateVectors();
}

void Camera::update()
{
	double mouseX,mouseY;
	glfwGetCursorPos(window,&mouseX,&mouseY);
	glfwSetCursorPos(window,500/2,500/2);
	rotate(((float)(500/2)-mouseX)*0.05f,((float)(500/2)-mouseY)*0.05f);
}


//----------------------------------------------------------------------------------------------------------
//Code For Checking Collision
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)
//Bounding Box Algorithm
//Note Min and Max Set are in each Cube(Object) Class 
//(returns enclosing Box min(back(-z) or left(-x) or bottom(-y) face set) and max(front(z) or right(x) face or top(y) face set))
//Pre-Condition - the Object must be Stored in vertice[] array of type GLfloat(further checkImplementation)
//Input Output vec3 min and max
void getMinMax(vec3 &minSet,vec3 &maxSet)
{
	const int numFloatsPerLine = 5;	//Can be Changed Accordingly
	if((sizeof(vertices)/sizeof(vertices[0]))>=3 &&(sizeof(vertices)/sizeof(vertices[0]))%numFloatsPerLine==0)	
	//If atleast 1 triangle is formed and only triangles are formed by vertices, we construct Bounding Box
	{
		//Looking at vertices Set above, its ditributed as Follows
		//pos.x,pos.y,pos.z , tex.x,tex.y   
		//-> 1st three denotes position of vertices in triangle making up mesh and rest denoted texture Coordinates
		int numIteration = (sizeof(vertices)/sizeof(vertices[0])) / numFloatsPerLine;
		float min_x=vertices[0],min_y=vertices[1],min_z=vertices[2];
		float max_x=vertices[0],max_y=vertices[1],max_z=vertices[2];
		for(int i=0;i<numIteration;i++)
		{
			min_x = MIN(min_x,vertices[i+numFloatsPerLine]);
			min_y = MIN(min_y,vertices[i*numFloatsPerLine+1]);
			min_z = MIN(min_z,vertices[i*numFloatsPerLine+2]);
			max_x = MAX(max_x,vertices[i*numFloatsPerLine]);
			max_y = MAX(max_y,vertices[i*numFloatsPerLine+1]);
			max_z = MAX(max_z,vertices[i*numFloatsPerLine+2]);
		}
		minSet = vec3(min_x,min_y,min_z);
		maxSet = vec3(max_x,max_y,max_z);
	}
}

bool checkCollision(vec3 playerPos,vec3 objectPos,vec3 objectMinSet,vec3 objectMaxSet)
{
	vec3 worldRestrictionMin,worldRestrictionMax;
	worldRestrictionMin = objectPos+objectMinSet;
	worldRestrictionMax = objectPos+objectMaxSet;
	if(worldRestrictionMin.x<=playerPos.x && playerPos.x<=worldRestrictionMax.x)
			if(worldRestrictionMin.z<=playerPos.z && playerPos.z<=worldRestrictionMax.z)
				return true;
}
//--------------------------------------------------------------------------------------------------------------

