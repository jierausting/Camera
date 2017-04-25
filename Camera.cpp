#include <stdlib.h>
#include <stdio.h>
#include <GL/glu.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<time.h>
#include<iostream>
using namespace std;

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
    ptop(1.0f),pbottom(-1.0f),pnear(0.01f),pfar(2),
    cameraPosX(0),cameraPosY(0),cameraPosZ(0),
    cameraFrontX(0),cameraFrontY(0),cameraFrontZ(-1),
    cameraRightX(1.0f),cameraRightY(0),cameraRightZ(0),
    cameraUpX(0),cameraUpY(1.0f),cameraUpZ(0)
    {} ;

    void moveForward(GLfloat const distance);
    void moveBack(GLfloat const distance);
    void moveRight(GLfloat const distance);
    void moveLeft(GLfloat const distance);
    void rotate(GLfloat const pitch,GLfloat const yaw);

    float getCamPosX() {
        return cameraPosX;
    }
    float getCamPosY() {
        return cameraPosY;
    }
    float getCamPosZ() {
        return cameraPosZ;
    }
    float getCamFrontX() {
        return cameraFrontX;
    }
    float getCamFrontY() {
        return cameraFrontY;
    }
    float getCamFrontZ() {
        return cameraFrontZ;
    }
    float getCamUpX() {
        return cameraUpX;
    }
    float getCamUpY() {
        return cameraUpY;
    }
    float getCamUpZ() {
        return cameraUpZ;
    }

private:
    GLfloat pleft,pright,ptop,pbottom,pnear,pfar;
    GLfloat cameraPosX,cameraPosY,cameraPosZ;
    GLfloat cameraFrontX,cameraFrontY,cameraFrontZ;
    GLfloat cameraRightX,cameraRightY,cameraRightZ;
    GLfloat cameraUpX,cameraUpY,cameraUpZ;
};
void Camera::moveForward(GLfloat const distance) {
    cameraPosX += cameraFrontX*distance;
    cameraPosY += cameraFrontY*distance;
    cameraPosZ += cameraFrontZ*distance;

    gluLookAt(cameraPosX,cameraPosY,cameraPosZ,
              cameraPosX+cameraFrontX,cameraPosY+cameraFrontY,cameraPosZ+cameraFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);

    cout << "PosX : " << cameraPosX << "PosY : " << cameraPosY << "PosZ : " <<cameraPosZ << endl;
}

void Camera::moveBack(GLfloat const distance) {
    cameraPosX -= cameraFrontX*distance;
    cameraPosY -= cameraFrontY*distance;
    cameraPosZ -= cameraFrontZ*distance;


    gluLookAt(cameraPosX,cameraPosY,cameraPosZ,
              cameraPosX+cameraFrontX,cameraPosY+cameraFrontY,cameraPosZ+cameraFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);

    cout << "PosX : " << cameraPosX << "PosY : " << cameraPosY << "PosZ : " <<cameraPosZ << endl;
}

void Camera::moveRight(GLfloat const distance) {
    cameraPosX += cameraRightX*distance;
    cameraPosY += cameraRightY*distance;
    cameraPosZ += cameraRightZ*distance;


    gluLookAt(cameraPosX,cameraPosY,cameraPosZ,
              cameraPosX+cameraFrontX,cameraPosY+cameraFrontY,cameraPosZ+cameraFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);

    cout << "PosX : " << cameraPosX << "PosY : " << cameraPosY << "PosZ : " <<cameraPosZ << endl;
}

void Camera::moveLeft(GLfloat const distance) {
    cameraPosX -= cameraRightX*distance;
    cameraPosY -= cameraRightY*distance;
    cameraPosZ -= cameraRightZ*distance;


    gluLookAt(cameraPosX,cameraPosY,cameraPosZ,
              cameraPosX+cameraFrontX,cameraPosY+cameraFrontY,cameraPosZ+cameraFrontZ,
              cameraUpX,cameraUpY,cameraUpZ);

    cout << "PosX : " << cameraPosX << "PosY : " << cameraPosY << "PosZ : " <<cameraPosZ << endl;
}

/*pitch can adapt up and down , yaw adapt left and right*/
void Camera::rotate(GLfloat const pitch, GLfloat const yaw) {
    float angleOfPitch = pitch/480;
    float angleOfYaw = yaw/640;
    float a,b,c;

    /*rotate around Up Vector*/
    float cosPitch = cos(angleOfPitch);
    float sinPitch = sin(angleOfPitch);
    float minusCosPitch = -1*cosPitch;
    float minusSinPitch = -1*sinPitch;
    float cosYaw = cos(angleOfYaw);
    float sinYaw = sin(angleOfYaw);
    float minusCosYaw = -1*cosYaw;
    float minusSinYaw = -1*sinYaw;
    float X;
    float Y;
    float Z;

    a = cameraUpX;
    b = cameraUpY;
    c = cameraUpZ;

    X = cameraFrontX;
    Y = cameraFrontY;
    Z = cameraFrontZ;
    cameraFrontX = (a*a+(1-a*a)*cosYaw)*X + (a*b*(1-cosYaw)+c*sinYaw)*Y+(a*c*(1-cosYaw)-b*sinYaw)*Z;
    cameraFrontY = (a*b*(1-cosYaw)-c*sinYaw)*X+(b*b+(1-b*b)*cosYaw)*Y+(b*c*(1-cosYaw)+a*sinYaw)*Z;
    cameraFrontZ = (a*c*(1-cosYaw)+b*sinYaw)*X+(b*c*(1-cosYaw)-a*sinYaw)*Y+(c*c+(1-c*c)*cosYaw)*Z;

    X = cameraRightX;
    Y = cameraRightY;
    Z = cameraRightZ;
    cameraRightX = (a*a+(1-a*a)*cosYaw)*X + (a*b*(1-cosYaw)+c*sinYaw)*Y+(a*c*(1-cosYaw)-b*sinYaw)*Z;
    cameraRightY = (a*b*(1-cosYaw)-c*sinYaw)*X+(b*b+(1-b*b)*cosYaw)*Y+(b*c*(1-cosYaw)+a*sinYaw)*Z;
    cameraRightZ = (a*c*(1-cosYaw)+b*sinYaw)*X+(b*c*(1-cosYaw)-a*sinYaw)*Y+(c*c+(1-c*c)*cosYaw)*Z;

    a = cameraRightX;
    b = cameraRightY;
    c = cameraRightZ;

    X = cameraFrontX;
    Y = cameraFrontY;
    Z = cameraFrontZ;
    cameraFrontX = (a*a+(1-a*a)*cosPitch)*X + (a*b*(1-cosPitch)+c*sinPitch)*Y+(a*c*(1-cosPitch)-b*sinPitch)*Z;
    cameraFrontY = (a*b*(1-cosPitch)-c*sinPitch)*X+(b*b+(1-b*b)*cosPitch)*Y+(b*c*(1-cosPitch)+a*sinPitch)*Z;
    cameraFrontZ = (a*c*(1-cosPitch)+b*sinPitch)*X+(b*c*(1-cosPitch)-a*sinPitch)*Y+(c*c+(1-c*c)*cosPitch)*Z;

    X = cameraUpX;
    Y = cameraUpY;
    Z = cameraUpZ;
    cameraUpX = (a*a+(1-a*a)*cosPitch)*X + (a*b*(1-cosPitch)+c*sinPitch)*Y+(a*c*(1-cosPitch)-b*sinPitch)*Z;
    cameraUpY = (a*b*(1-cosPitch)-c*sinPitch)*X+(b*b+(1-b*b)*cosPitch)*Y+(b*c*(1-cosPitch)+a*sinPitch)*Z;
    cameraUpZ = (a*c*(1-cosPitch)+b*sinPitch)*X+(b*c*(1-cosPitch)-a*sinPitch)*Y+(c*c+(1-c*c)*cosPitch)*Z;
}
int main(void)
{
    Camera* cam = new Camera();

    double* lastCursorX =(double*)malloc(sizeof(double));
    double* lastCursorY =(double*)malloc(sizeof(double));
    double* currentCursorX =(double*)malloc(sizeof(double));
    double* currentCursorY =(double*)malloc(sizeof(double));
    double tempX;
    double tempY;
    bool IsFirstFrame = true;

    GLFWwindow* window;

    bool lookAtIsSetted = false;

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
        lookAtIsSetted = false;

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

        glFrustum(-ratio*0.5,ratio*0.5,0.5f,-0.5f,0.5f,0.8f);
        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            cam->moveForward(0.001f);
            lookAtIsSetted = true;
        } else if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            cam->moveBack(0.001f);
            lookAtIsSetted = true;
        } else if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            cam->moveLeft(0.001f);
            lookAtIsSetted = true;
        } else if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            cam->moveRight(0.001f);
            lookAtIsSetted = true;
        }
        if (IsFirstFrame) {
            IsFirstFrame = false;
            glfwGetCursorPos(window,lastCursorX,lastCursorY);
        }
        glfwGetCursorPos(window,currentCursorX,currentCursorY);
        cam->rotate(*lastCursorY-*currentCursorY,*currentCursorX-*lastCursorX);
        *lastCursorX = *currentCursorX;
        *lastCursorY = *currentCursorY;


        if (!lookAtIsSetted) {
            gluLookAt(cam->getCamPosX(),cam->getCamPosY(),cam->getCamPosZ(),
                      cam->getCamPosX()+cam->getCamFrontX(),cam->getCamPosY()+cam->getCamFrontY(),cam->getCamPosZ()+cam->getCamFrontZ(),
                      cam->getCamUpX(),cam->getCamUpY(),cam->getCamUpZ());
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glTranslatef(-0.5f,0.5f,0.8f);
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


