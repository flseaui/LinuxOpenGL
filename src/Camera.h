#ifndef CAMERA
#define CAMERA

class Camera
{
public:
	Camera(int width, int height);
	~Camera();
	void setDims(int width, int height);
	void translate(glm::vec3);
	glm::vec3 getPos();
	void setPos(glm::vec3);
	float getRotation();
	void rotate(float angle);
	void setRotation(float angle);
	glm::mat4 getProjection();
	glm::mat4 getView();
private:
	float width, height, rotation;
	glm::mat4 projection;
	glm::vec3 position;
};

#endif 