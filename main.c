#include <stdlib.h>
#include <stdio.h>
#include <GL/glu.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<time.h>

//���ô���ص�
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
//���ù���ESC���Ļص�
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

class Camera {
public:
    Camera() :pleft(-1.34f),pright(1.34f),
    ptop(1.0f),pbottom(-1.0f),pnear(0.2f),pfar(2),
    cameraFrontX(0),cameraFrontY(0),cameraFrontZ(-1),
    cameraRightX(1.0f),cameraRightY(0),cameraRightZ(0),
    cameraUpX(0),cameraUpY(1.0f),cameraUpZ(0)
    {} ;

    void moveFoward(GLfloat const distance);
    void moveBack(GLfloat const distance);
    void moveRight(GLfloat const distance);
    void moveLeft(GLfloat const distance);
    void rotate(GLfloat const pitch,GLfloat const yaw);

private:
    GLfloat pleft,pright,ptop,pbottom,pnear,pfar;
    GLfloat cameraPosX,cameraPosY,cameraPosZ;
    GLfloat cameraFrontX,cameraFrontY,cameraFrontZ;
    GLfloat cameraRightX,cameraRightY,cameraRightZ;
    GLfloat cameraUpX,cameraUpY,cameraUpZ;
};
void Camera::moveFoward(GLfloat const distance) {
    cameraPosX += cameraFrontX*distance;
    cameraPosY += cameraFrontY*distance;
    cameraPosZ += cameraFrontZ*distance;

    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);

    gluLookAt(cameraPosX,cameraPosY,CameraPosZ,
              cameraPosX+camerFrontX,cameraPosY+camerFrontY,cameraPosZ+camerFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);
}

void Camera::moveBack(GLfloat const distance) {
    cameraPosX -= cameraFrontX*distance;
    cameraPosY -= cameraFrontY*distance;
    cameraPosZ -= cameraFrontZ*distance;

    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);

    gluLookAt(cameraPosX,cameraPosY,CameraPosZ,
              cameraPosX+camerFrontX,cameraPosY+camerFrontY,cameraPosZ+camerFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);


}

void Camera::moveRight(GLfloat const distance) {
    cameraPosX += cameraRightX*distance;
    cameraPosY += cameraRightY*distance;
    cameraPosZ += cameraRightZ*distance;

    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);

    gluLookAt(cameraPosX,cameraPosY,CameraPosZ,
              cameraPosX+camerFrontX,cameraPosY+camerFrontY,cameraPosZ+camerFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);


}

void Camera::moveLeft(GLfloat const distance) {
    cameraPosX -= cameraRightX*distance;
    cameraPosY -= cameraRightY*distance;
    cameraPosZ -= cameraRightZ*distance;

    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);

    gluLookAt(cameraPosX,cameraPosY,CameraPosZ,
              cameraPosX+camerFrontX,cameraPosY+camerFrontY,cameraPosZ+camerFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);
}
int main(void)
{
    Camera cam = new Camera();

    GLFWwindow* window;


    glfwSetErrorCallback(error_callback);

    /* ��ʼ��GLFW�� */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    /*�������ں������� */
    window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* ������ǰ������*/
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
     /* ��ʼ��Ⱦ�׶� */
        float ratio;
        int width,height;

        /* ��ȡ����֡�Ĵ�С*/
        glfwGetFramebufferSize(window,&width,&height);
        ratio = width/(float) height;

        /*�����ӿڲ���֮ǰ����ɫ�������*/
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT);

        /*���þ���ģʽΪͶ��ģʽ�������Ӿ���*/
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

//        glOrtho(-ratio,ratio,-1.0f,1.0f,0.08f,0.25f);
        glFrustum(-ratio,ratio,1.0f,-1.0f,0.2f,2.0f);
        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            cam.moveForward(0.1f);
        } else if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            cam.moveBack(0.1f);
        } else if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            cam.moveLeft(0.1f);
        } else if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            cam.moveRight(0.1f);
        }


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glTranslatef(-0.5f,0.5f,1.5f);
//        glDisable(GL_DEPTH_TEST);
//        glRotatef(45.f,0.f,1.f,0.f);
//        glRotatef(60.f,1.f,0.f,0.f);
//        glRotatef(i,1.f,1.f,0.f);
//        glScaled(sin(glfwGetTime()),sin(glfwGetTime()),sin(glfwGetTime()));
//        glTranslatef((float)0.05f*i,0.0f,0.0f);
    /* ��ѭ�� */
        glBegin(GL_QUADS);
        glColor3f(255.f/255.f,0.f/255.f,0.f/255.f);
        glVertex3f(0.55f,-0.55f,-1.45f);
        glVertex3f(0.55f,-0.45f,-1.45f);
        glVertex3f(0.55f,-0.45f,-1.55f);
        glVertex3f(0.55f,-0.55f,-1.55f);


        glColor3f(0.f/255.f,255.f/255.f,0.f/255.f);
        glVertex3f(0.45f,-0.55f,-1.45f);
        glVertex3f(0.45f,-0.45f,-1.45f);
        glVertex3f(0.45f,-0.45f,-1.55f);
        glVertex3f(0.45f,-0.55f,-1.55f);


        glColor3f(0.f/255.f,0.f/255.f,255.f/255.f);
        glVertex3f(0.55f,-0.45f,-1.45f);
        glVertex3f(0.45f,-0.45f,-1.45f);
        glVertex3f(0.45f,-0.45f,-1.55f);
        glVertex3f(0.55f,-0.45f,-1.55f);

        glColor3f(0.f/255.f,255.f/255.f,255.f/255.f);
        glVertex3f(0.55f,-0.55f,-1.45f);
        glVertex3f(0.45f,-0.55f,-1.45f);
        glVertex3f(0.45f,-0.55f,-1.55f);
        glVertex3f(0.55f,-0.55f,-1.55f);

        /*Purple*/
        glColor3f(255.f/255.f,0.f/255.f,255.f/255.f);
        glVertex3f(0.55f,-0.55f,-1.45f);
        glVertex3f(0.55f,-0.45f,-1.45f);
        glVertex3f(0.45f,-0.45f,-1.45f);
        glVertex3f(0.45f,-0.55f,-1.45f);

        /*Yellow*/
        glColor3f(255.f/255.f,255.f/255.f,0.f/255.f);
        glVertex3f(0.55f,-0.55f,-1.55f);
        glVertex3f(0.55f,-0.45f,-1.55f);
        glVertex3f(0.45f,-0.45f,-1.55f);
        glVertex3f(0.45f,-0.55f,-1.55f);
        glEnd();


                /*����������*/
//        glfwSwapBuffers(window);
//
//        /*�����¼�*/
//        glfwPollEvents();

        //        glTranslatef(0.1f,0.1f,0.1f);
        glfwSwapBuffers(window);

        /*�����¼�*/
        glfwPollEvents();


    }
    /*�رմ��ڲ�ֹͣʹ��GLFW�Ŀ�*/
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


