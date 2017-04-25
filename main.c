#include <stdlib.h>
#include <stdio.h>
#include <GL/glu.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<time.h>

//设置错误回调
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
//设置关于ESC键的回调
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

    /* 初始化GLFW库 */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    /*创建窗口和上下文 */
    window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* 创建当前上下文*/
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
     /* 开始渲染阶段 */
        float ratio;
        int width,height;

        /* 获取缓存帧的大小*/
        glfwGetFramebufferSize(window,&width,&height);
        ratio = width/(float) height;

        /*创建视口并将之前的颜色缓存清除*/
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT);

        /*设置矩阵模式为投射模式并设置视景体*/
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
    /* 主循环 */
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


                /*交换缓存区*/
//        glfwSwapBuffers(window);
//
//        /*处理事件*/
//        glfwPollEvents();

        //        glTranslatef(0.1f,0.1f,0.1f);
        glfwSwapBuffers(window);

        /*处理事件*/
        glfwPollEvents();


    }
    /*关闭窗口并停止使用GLFW的库*/
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


