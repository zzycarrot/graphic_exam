#include<fstream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include<vector>
#include <iostream>
#include <stdlib.h>
//#include "pngimage.h"
#include "test1.h"
#include "geomodeling.h"
#define  debug printf
// #include<opencv2/core/core.hpp>
// #include<opencv2/highgui/highgui.hpp>
// #include<opencv2/imgproc/imgproc.hpp>

using namespace std;
extern float key_x,key_y;
extern int face;
extern bool tv_open;
int windowWidth = 600;   // 窗口宽度
int windowHeight = 350;  // 窗口高度
// extern bool tv_open;
int WinWidth,WinHeight;
static unsigned int texName;
unsigned char checkImage[64][64][4];
static int checkImageHeight = 64, checkImageWidth = 64;
// static float eye[3] = { 0,0,20 }, eobj[3] = { 0,0,0 };
float eye[3] = { 0,0,20 }, eobj[3] = { 0,0,0 };
int watch =0;
// static float eye[3] = { 5,-5, 0}, eobj[3] = { 13,-2,-8 };



void timer(int value);

struct FILEHEADER{
    char dummy1[18];
    int width;
    int height;
    char dummy2[28];
};

struct Vertex3D{
    double x;
    double y;
    double z;
    Vertex3D(double _x=0, double _y=0, double _z=0)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Circle{
    Vertex3D vt;
    double r;
    Circle()
    {
        r = 0;
    }
};

vector <Vertex3D> g_upVt;
vector <Vertex3D> g_downVt;
vector <Vertex3D> g_sideVt;
Circle g_downCircle, g_upCircle;
vector <Circle> g_arrCircle;
void changeeye() {
    // debug("watch:%d\n",watch);
    if(watch==1) {
        eye[0] = 5;
        eye[1] = -5;
        eye[2] = 0;
        eobj[0] = 13;
        eobj[1] = -2;
        eobj[2] = -8;
        tv_open = 1;
    }else {
        eye[0] = 0;
        eye[1] = 0;
        eye[2] = 20;
        eobj[0] = 0;
        eobj[1] = 0;
        eobj[2] = 0;
        tv_open = 0;
    }


}
//产生纹理
void makeCheckImages(void)
{
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            if (c == 255)
            {
                checkImage[i][j][0] = (GLubyte)180;
                checkImage[i][j][1] = (GLubyte)180;
                checkImage[i][j][2] = (GLubyte)180;
                checkImage[i][j][3] = (GLubyte)255;
            }
            else
            {
                checkImage[i][j][0] = (GLubyte)c;
                checkImage[i][j][1] = (GLubyte)c;
                checkImage[i][j][2] = (GLubyte)c;
                checkImage[i][j][3] = (GLubyte)255;
            }
        }
    }
}

void setLight0(bool Light0)
{
    Light0 = 0;

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        GLfloat light1_position[] = { -20.0, 2.0, 1.0, 1.0 };
        GLfloat spot_direction[] = { -10.0, -1.0, 0.0 };
    if(watch) {
        // GLfloat light1_position[] = { 15.0, 0.0, 0, 1.0 };
        // GLfloat spot_direction[] = { 17.0, 2.0, -20.0 };
        light_position[0]=15.0;
        light_position[1]=0.0;
        light_position[2]=0.0;
        light_position[3]=1.0;
        spot_direction[0]=17.0;
        spot_direction[1]=2.0;
        spot_direction[2]=-20.0;
    }else {
        // GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
        // GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
        light_position[0]=-2.0;
        light_position[1]=2.0;
        light_position[2]=1.0;
        light_position[3]=1.0;
        spot_direction[0]=-1.0;
        spot_direction[1]=-1.0;
        spot_direction[2]=0.0;
    }


    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_LIGHT1);
}

struct BGR {
    unsigned char b;
    unsigned char g;
    unsigned char r;
    BGR(unsigned char _b=0, unsigned char _g=0, unsigned char _r=0){
        b = _b;
        g = _g;
        r = _r;
    }
    bool operator==(BGR x){
        if (b==x.b && g==x.g && r==x.r)
            return true;
        else
            return false;
    }
};
GLuint textureId;
int loadBmp(char *fileName)
{
    FILEHEADER imgHead;
    BGR pixel;
    fstream imgFile;

    imgFile.open(fileName, ios::in|ios::binary);

    if(!imgFile)
    {
        cerr<<"File opening or creating error!"<<endl;
        return 0;
    }

    imgFile.read((char *)(&imgHead), sizeof(FILEHEADER));
    cout << "Image size:" << imgHead.width << "*" << imgHead.height << endl;
    if(imgHead.width%4!=0) return 0;
    for(int i=0; i<(imgHead.width*imgHead.height); i++)
    {
        /*图像的位数通常是8位，2^8 = 256种，0-255刚好是256种颜色*/
        imgFile.read((char *)(&pixel), sizeof(BGR));
        if (pixel == BGR(0, 0, 255)){
            //Red对应底部那条线
            g_downVt.push_back(Vertex3D(i%imgHead.width, i/imgHead.width, 0));
        }
        else if (pixel == BGR(0, 255, 0)){
            //Green对应角顶点的两个pixel
            g_upVt.push_back(Vertex3D(i%imgHead.width, i/imgHead.width, 0));
        }
        else if (pixel == BGR(255, 0, 0)){
            //Blue在对应边缘
            g_sideVt.push_back(Vertex3D(i%imgHead.width, i/imgHead.width, 0));
        }

    }
    imgFile.close();
    return 1;
}





void display(void) // Here's Where We Do All The Drawing
{
    // changeeye();
    // TODO:
    // Place light source here
    setLight0(Light0);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//texture
    // TODO:
    // Draw walls and objects here




    draw_wall();
    draw_window();
    draw_light();
    draw_tv();

    testcode1();
// gluLookAt(eye[0], eye[1], eye[2], eobj[0], eobj[1], eobj[2], 0.0, 1.0, 0.0);
    /*draw_tvdesk();
    draw_seat();
    draw_bed();
    draw_closet();
    draw_taideng();
   */

    glutSwapBuffers();

}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
    if (h == 0) h = 1;
    WinWidth = w;
    WinHeight = h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

    gluLookAt(eye[0], eye[1], eye[2], eobj[0], eobj[1], eobj[2], 0.0, 1.0, 0.0);

}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    //texture mapping
    makeCheckImages();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}
//将窗口信息保存为图片
void saveImage() {
    // 设置OpenGL视口和投影矩阵
    int saveWidth, saveHeight;

    saveWidth = windowWidth;
    saveHeight = windowHeight;

    glViewport(0, 0, saveWidth, saveHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 创建OpenCV Mat对象并读取窗口像素数据
    // cv::Mat image(saveHeight, saveWidth, CV_8UC3);
    // glReadPixels(0, 0, saveWidth, saveHeight, GL_BGR, GL_UNSIGNED_BYTE, image.data);
    //
    // // 翻转图像（因为OpenGL坐标和图片坐标的差异）
    // cv::flip(image, image, 0);
    //
    // // 保存图像
    // cv::imwrite("../img_step1/test.png", image);
}
enum {
    WALK,BED,CHAIR,TVON,TVOFF
};
int state = WALK;
extern int iswalk;
extern bool canLay;
int dir = 0;
void SpecialKeys(int key, int x, int y)
{
    switch (state) {
        case WALK:

            if(key == GLUT_KEY_UP ) {
                dir = 0;
                debug("key : up\n");
                iswalk = 1;
                key_y += -1;
                face = 2;
                glutPostRedisplay(); // 刷新窗口
                // iswalk = 0;
            }
            if(key == GLUT_KEY_DOWN){
                dir = 1;
                debug("key : down\n");
                iswalk = 1;
                key_y -= -1;
                face = 0;
                glutPostRedisplay(); // 刷新窗口
                // iswalk = 0;
            }
            if(key == GLUT_KEY_LEFT) {
                dir = 2;
                debug("key : left\n");
                iswalk = 1;
                key_x += -1;
                face = 3;
                glutPostRedisplay(); // 刷新窗口
                // iswalk = 0;
            }
            if(key == GLUT_KEY_RIGHT) {
                dir = 3;
                debug("key : right\n");
                iswalk = 1;
                key_x -= -1;
                face = 1;
                glutPostRedisplay(); // 刷新窗口
                // iswalk = 0;
            }
            // iswalk = 0;
            break;
        default:
            break;
    }


}
extern int beddone,f;
extern int bedcount;
extern int chair;

void processNormalKeys(unsigned char key, int x, int y) {
    debug("key:%c\n",key);
    if (key=='f' || key == 'F' ) {
        if(canLay) {
            // debug("lay on bed\n");
            state = BED;
            glutPostRedisplay();
        }
        if(beddone==1) {
            f=-1;
            beddone=0;
            // debug("main bedcouunt:%d\n",bedcount);
            bedcount--;
        }
        if(beddone==-1) {
            // state= WALK;
        }
    }
    if(key =='g'|| key == 'G') {
        // debug("chair :%d\n",chair);
        if(chair == 1) {
            if(watch==0) {
                watch = 1;
                changeeye();
                int witdh = glutGet(GLUT_WINDOW_WIDTH);
                int height = glutGet(GLUT_WINDOW_HEIGHT);
                reshape(witdh,height);
            }
            else {
                watch = 0;
                changeeye();
                int witdh = glutGet(GLUT_WINDOW_WIDTH);
                int height = glutGet(GLUT_WINDOW_HEIGHT);
                reshape(witdh,height);
            }
        }
        else {
            watch = 0;
        }
    }
    if(key=='d'|| key == 'D') {
        if(watch==1) {
            watch = 1;
            // changeeye();
        }
        else {
            watch = 0;
            // changeeye();
        }
    }
}
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}
void pic() {
    // 假设已经加载了图片数据并获得了宽度、高度和像素数据
    unsigned char* imageData; // 假设这里是图片像素数据
    int imageWidth, imageHeight; // 图片宽度和高度

    // 步骤 2：创建纹理对象
    GLuint textureId;
    glGenTextures(1, &textureId);

    // 步骤 3：绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, textureId);

    // 步骤 4：将图片数据传输到纹理对象
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 渲染图片
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
    glEnd();

    // 解绑纹理对象
    glBindTexture(GL_TEXTURE_2D, 0);
}
int main(int argc, char** argv)
{
    int width = 600, height = 350;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Add furnitures");

    init();
    loadBmp("C:\\Users\\ez_zz\\Desktop\\Lessons\\graphic_exam\\d60c2099763d4e03998c31537e2f94da.bmp");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialKeys);//设置特殊键位的回调函数
    glutKeyboardFunc(processNormalKeys);//设置键盘回调函数
    glutTimerFunc(10, timer, 0); // 100毫秒后调用timer函数
    testanimation();

    glutCloseFunc(saveImage);// 设置窗口关闭的回调函数

    glutMainLoop(); //glutMainLoopEvent()

    // system("pause");
    return 0;
}
