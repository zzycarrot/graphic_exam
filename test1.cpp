// 提示：在合适的地方修改或添加代码
#include "geomodeling.h"
#include "test1.h"

#include <cstdio>
#include <math.h>
#include <ctime>
#define max_x 20
#define max_y 10
#define max_z 20
#define pi 3.1415926
#define eps 5*1e-4
#define  debug printf
float key_x = 0;
float key_y = 0;
int face = 0;
// extern float eye[] , eobj[];
void drawCuboid(float length, float width, float height, float color[3] ,int white) {


    glColor3f(color[0], color[1], color[2]); // 设置颜色
    glPushMatrix();
    glScalef(length, height, width); // 缩放到指定大小
    glutSolidCube(1.0); // 绘制实心立方体
    glPopMatrix();
    
// 绘制边框
    glColor3f(1.0 * white, 1.0 * white, 1.0 * white); // 设置边框颜色
    glLineWidth(2.0); // 设置边框线宽
    glPushMatrix();
    glScalef(length, height, width); // 缩放到指定大小
    glutWireCube(1.0); // 绘制线框立方体
    glPopMatrix();

}
float chair_x=0;
float chair_y=0;
float lastchair_x=0;
float lastchair_y=0;
int right = 0;
//bed
void draw_bed(void)
{

    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

    /********** begin your code below*************/        

    float headboardColor[3] = {0.0f, 0.54f, 0.5f};
    float bedBodyColor[3] = {1.0f, 0.54f, 0.5f};

    // 绘制床头
    glPushMatrix();
    glTranslatef(0.0f, 3.0f - 10, -20 +0.5); // 平移到床头位置，床头高度为 6/2 = 3.0f，宽度中心在 z=-7.5f

    drawCuboid(12.0f, 1.0f, 6.0f, headboardColor , 1);
    glPopMatrix();

    // 绘制床身
    glPushMatrix();
    glTranslatef(0.0f, 0.75f - 10, 0+7-20+1.0 +1.5 ); // 平移到床身位置，床身高度为 1.5/2 = 0.75f

    drawCuboid(12.0f, 14.0f, 1.5f, bedBodyColor , 1);// 14 to 15
    glPopMatrix();


    /***********end your code here****************/
}
void drawLamp() {
    GLUquadric* quad = gluNewQuadric();

    // 绘制灯柱
    glPushMatrix();
   glTranslatef(0,1.2,0); // 平移到台灯位置

    glColor3f(0.0f, 0.0f, 0.0f); // 灯柱颜色为黑色
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // 旋转使圆柱垂直
    gluCylinder(quad, 0.5f, 0.2f, 4.0f, 40, 40); // 绘制圆柱形灯柱
    glPopMatrix();

    // 绘制灯罩
    glPushMatrix();
    glTranslatef(0, 4.0f, -0.f); // 平移到灯罩位置
    glColor3f(1.0f, 0.0f, 1.0f); // 灯罩颜色为紫色
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // 旋转
    glutSolidCone(1.5f, 2.0f, 16, 16); // 绘制灯罩
    glPopMatrix();

    gluDeleteQuadric(quad);
}
//台灯+床头柜
void draw_taideng(void)
{
    GLUquadric *obj;
    obj = gluNewQuadric();
    glColor3f(1, 0, 1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
    glMaterialfv(GL_FRONT, GL_SHININESS, matBlack);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    if(Light2)
        glMaterialfv(GL_FRONT, GL_EMISSION, matBrown);

    /********** begin your code below*************/        
   // drawLamp();
    glPushMatrix();
    glTranslatef(1.5+6.5, 1.5f -10, 1.5f - 20); // 平移到床头柜位置
    float tableColor[3] = {1.0f, 0.6f, 0.3f};
    glColor3f(tableColor[0], tableColor[1], tableColor[2]);

    glPointSize(5.0);
    glColor3f(0.f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(-0.5, 0, 1.5); // 左侧把手
    glVertex3f(0.5f, 0, 1.5f); // 右侧把手
    glEnd();

    // 绘制柜体
    // glTranslatef(6.5f, 1.5f , -0.75f); // 平移到床头柜位置
    drawCuboid(3.0f, 3.0f, 3.0f, tableColor,0);

    //drawBedsideTable();
    drawLamp();

    glPopMatrix();

    /***********end your code here****************/

    gluDeleteQuadric(obj);
}
void draw_tvdesk(void)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);    
    

    //TV desk
    /********** begin your code below*************/        



    glColor3f(1,0.6,0.3); // 设置颜色
    glPushMatrix();
        glTranslatef(20-1.8, -10+ 6.2, -4.2-5); // 平移到柜子位置
        //glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,8.4); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
    glPopMatrix();

    glPushMatrix();

        glTranslatef(20-1.8, -10+ 6.2 -3.6 -0.2, -4.2-5); // 平移到柜子位置
        //glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,8.4); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
    glPopMatrix();
    glPushMatrix();

        glTranslatef(20-1.8,-10 +6.2 -1.8,-4.2-5); // 平移到柜子位置
        glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,3.6); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
        glPopMatrix();

    glPopMatrix();
    glPushMatrix();

        glTranslatef(20-1.8,-10 +6.2 -1.8,-4.2-5+4.2-0.2); // 平移到柜子位置
        glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,3.6); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(20-1.8,-10 +6.2 -1.8,-4.2-5-4.2+0.2); // 平移到柜子位置
        glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,3.6); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
        glPopMatrix();

    glPopMatrix();
    glPushMatrix();

        glTranslatef(20-1.8,-10 +1.2,-4.2-5+4.2-0.2); // 平移到柜子位置
        glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,2.4); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(20-1.8,-10 +1.2,-4.2-5-4.2+0.2); // 平移到柜子位置
        glRotatef(90, 1, 0, 0); // 旋转
        glScalef(3.6,0.4,2.4); // 缩放到指定大小
        glutSolidCube(1.0); // 绘制实心立方体
        glPopMatrix();

    glPopMatrix();
    /***********end your code here****************/

}
void draw_seat(void)
{
    debug("chair x : %f, y : %f\n", chair_x, chair_y);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    GLUquadric *obj;
    obj = gluNewQuadric();
    glPushMatrix();
    glTranslatef(chair_x, 0, chair_y);
    /********** begin your code below*************/      
    GLfloat x_sz;
    GLfloat y_sz;
    GLfloat z_sz;  
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.3);
        x_sz = 3.0;
        y_sz = 0.5;
        z_sz = 3.0;
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1 * (max_y - y_sz / 2.0 - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glScalef(x_sz, y_sz, z_sz);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(-1.0, 0.0, -1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(1.0, 0.0, -1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();
    glPopMatrix();
    /***********end your code here****************/
    gluDeleteQuadric(obj);
    lastchair_x = chair_x;
    lastchair_y = chair_y;
}
void draw_seat2(void)
{

    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    GLUquadric *obj;
    obj = gluNewQuadric();

    /********** begin your code below*************/
    glPushMatrix();
    glTranslatef(chair_x, 0, chair_y);
    GLfloat x_sz;
    GLfloat y_sz;
    GLfloat z_sz;
    glPushMatrix();
    glTranslatef(0.5,0,0);
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.3);
        x_sz = 3.0;
        y_sz = 0.5;
        z_sz = 3.0;
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1 * (max_y - y_sz / 2.0 - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glScalef(x_sz, y_sz, z_sz);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(-1.0, 0.0, -1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(1.0, 0.0, -1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.6f, 0.3f);
        glTranslatef((max_x - x_sz / 2.0 - 6.0), -1.0 * (max_y - 2.5), -1.0 * (6.0 + z_sz / 2.0));
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(obj, 0.2, 0.2, 2.5, 10, 10);
    glPopMatrix();
glPopMatrix();
    glPopMatrix();
    /***********end your code here****************/
    gluDeleteQuadric(obj);
    lastchair_x = chair_x;
    lastchair_y = chair_y;
}
void drawCabinet() {
    float cabinetColor[3] = {1.0f, 0.6f, 0.3f};
    glColor3f(cabinetColor[0], cabinetColor[1], cabinetColor[2]);

    // 绘制柜体
    glPushMatrix();
    //glTranslatef(-2.0f, 7.0f, -7.0f); // 平移到柜子位置
    drawCuboid(4.0f, 6.0f, 14.0f, cabinetColor,0);
    glPopMatrix();



    // 绘制柜门缝线
    glPushMatrix();
    glTranslatef(0, 0, -1.5); // 平移到柜子位置
    drawCuboid(4.0f, 3.0f, 14.0f, cabinetColor,0);
    glPopMatrix();

    // 绘制柜门把手
    glPushMatrix();
    glTranslatef(2.1f, 0, -0.6); // 平移到柜门把手位置
    glScalef(0.2f, 2, 0.2);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidCube(1.0); // 绘制左侧把手
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1f, 0, 0.6); // 平移到柜门把手位置
    glScalef(0.2f, 2, 0.2);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidCube(1.0); // 绘制右侧把手
    glPopMatrix();
}
//closet
void draw_closet(void)
{
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

    /********** begin your code below*************/
    glPushMatrix();
    glTranslatef(2-20, 7-10, 3-20); // 平移到柜子位置
    drawCabinet();
    glPopMatrix();

    /***********end your code here****************/
}
void draw_clock()
{
    GLUquadric *obj;
    obj = gluNewQuadric();

    glColor3f(1, 0.6, 0.3);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    //========begin========
    float inr = 3, outr = 3.5;
    float x0 = 0, y0 = 4, z0 = -19.9;

    glPushMatrix();
    glTranslatef(0, 4, -19.9);
    glColor3f(1, 0.6, 0.3);
    gluDisk(obj, inr, outr, 20, 4);
    glColor3f(0.25, 0.25, 0.25);
    gluDisk(obj, 0, inr, 20, 4);
    glPopMatrix();

    glColor3f(1, 1, 1);
    for(int i = 0; i < 60; i++) {
        switch (i%5) {
            case 0:
                glLineWidth(4);
                glBegin(GL_LINE_LOOP);
                glVertex3f(x0 + 2 * cos(i * 6 * pi / 180), y0 + 2 * sin(i * 6 * pi / 180), z0 + eps);
                glVertex3f(x0 + 3 * cos(i * 6 * pi / 180), y0 + 3 * sin(i * 6 * pi / 180), z0 + eps);
                glEnd();
                break;
            default:
                glLineWidth(2);
                glBegin(GL_LINE_LOOP);
                glVertex3f(x0 + 2.5 * cos(i * 6 * pi / 180), y0 + 2.5 * sin(i * 6 * pi / 180), z0 + eps);
                glVertex3f(x0 + 3 * cos(i * 6 * pi / 180), y0 + 3 * sin(i * 6 * pi / 180), z0 + eps);
                glEnd();
                break;
        }
    }
    time_t timep;
    struct tm *p;

    time(&timep);
    p = localtime(&timep);

    int h,m,s;
    h = p->tm_hour;
    h%=12;
    m = p->tm_min;
    m%=60;
    s = p->tm_sec;
    s%=60;
    // seconds
    glBegin(GL_LINE_LOOP);
    glLineWidth(3);
    glVertex3f(x0, y0, z0 + eps);
    glVertex3f(x0 + 0.7 * inr * sin(s * 6 * pi / 180), y0 + 0.7 * inr * cos(s * 6 * pi / 180), z0 + eps);
    glEnd();
    // minutes
    glBegin(GL_LINE_LOOP);
    glLineWidth(3);
    glVertex3f(x0, y0, z0 + eps);
    glVertex3f(x0 + 0.6 * inr * sin(m  * pi / 30), y0 + 0.6 * inr * cos(m  * pi / 30), z0 + eps);
    glEnd();

    // hours
    glBegin(GL_LINE_LOOP);
    glLineWidth(3);
    glVertex3f(x0, y0, z0 + eps);
    glVertex3f(x0 + 0.5 * inr* sin(h* pi / 6), y0 + inr * 0.5 * cos(h * pi / 6), z0 + eps);
    glEnd();


    //=========end=========
    gluDeleteQuadric(obj);
}
float last_x=0;
float last_y=0;
float last_z=0;
extern int dir;
bool checkboundingbox(float x, float y) {
    bool flag = true;
    //wall
    if(x-1.5<=-20 || x+1.5>=20 || y-1.5<=-20 || y+1.5>=0) {
        flag = false;
    }
    //bed
    if(x>-6.1&&x<6.9) {
        if(y<-2.1) {
            flag= false;
        }
    }
    //closet
    if(x<-14.1) {
        if(y<-12.1)flag = false;
    }
    //dresser
    if(x<10.1&&x>6.9) {
        if(y<-15.1)flag = false;
    }
    //tvdesk
    if(y<-4.1&&y>-14.9) {
        if(x>15.1)flag=false;
    }
    //chair;
    if(x>10.1+chair_x&&x<14.9+chair_x) {
        if(y<-5.1+chair_y&&y>-9.9+chair_y) {
            // flag = false;
            switch (dir){
                case 0:
                    chair_y -= 1;
                    break;
                case 1:
                    chair_y += 1;
                    break;
                case 2:
                    chair_x -= 1;
                    break;
                case 3:
                    chair_x += 1;
                    break;
            }
        }
    }
    return flag;
}

int lasr_face=0;
float walktime = 100;
int count = 0;
int iswalk = 0;
bool canLay=0;
bool doBed = false;
int chair = 0;
void checklaybed(float x,float y) {
    right = 0;
    chair = 0;
    if(abs(x - (-7)) <eps ) {
        if( abs(y - (-9)) < eps|| abs(y - (-10)) < eps|| abs(y - (-11)) < eps|| abs(y - (-12)) < eps) {
            // debug("can lay on bed\n");
            canLay = 1;
            right = 0;
        }

    }else
    if(abs(x - (7)) <eps ) {
        if( abs(y - (-9)) < eps|| abs(y - (-10)) < eps|| abs(y - (-11)) < eps|| abs(y - (-12)) < eps) {
            // debug("can lay on bed\n");
            canLay = 1;
            right = 1;
        }

    }
    else {
        if(abs(x +chair_x- (10)) <eps ) {
            if( abs(y +chair_y- (-8)) < eps || abs(y +chair_y- (-7)) < eps) {
                // debug("can lay on chair\n");
                canLay = 1;
                chair = 1;

            }
        }else {
            canLay = 0;
            chair = 0;
        }

    }
}
extern int state;
enum {
    WALK,BED,CHAIR,TVON,TVOFF
};
int bedcount = 0;
void timer333(int value) {
    glutPostRedisplay();           // 标记当前窗口需要重新绘制


}
int seat=1;
int beddone = 0;
int f=1;
void draw_people()
{
    if(chair==1) {
        seat=0;
        draw_seat2();
    }
    // printf("isflag : %d\n", iswalk);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
    glMaterialfv(GL_FRONT, GL_SHININESS, matBlack);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    if(Light2)
        glMaterialfv(GL_FRONT, GL_EMISSION, matBrown);

    /**********************start your code below**********************/
    float x,y,z;
    x=key_x-10;
    y=-8.3;
    z=key_y-18;
    if(!checkboundingbox(x,z)) {
        key_x=last_x;
        key_y=last_z;
        glutPostRedisplay();
        return;
    }
    // debug("canLay : %d\n", canLay);
    checklaybed(x,z);
    //bounding box

    //
    glPushMatrix();

    glTranslated(key_x,0,key_y);
    glTranslatef(-10,-8.3,-18);

    glRotatef(90*(abs(lasr_face - face)),0,1,0);

    // debug("STATE : %d\n", state);
    if(state == BED) {
        beddone = 0;
        if(right&&!chair) {
            glRotatef(180,0,1,0);
        }
        glRotatef(90*abs(face - 3),0,1,0);
        face = 3;
        {
            // debug("state : %d\n", state);
            if(bedcount<0) {

                f=1;
                bedcount = 0;
            }
            // debug("bedcount : %d\n", bedcount);
            // debug("inswitch\n");
            // bedcount = 1;
            switch (bedcount) {
                case 0:{

                    //left leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,1,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0,0,0);
                        glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    //right leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);

                        glTranslatef(-0.5,1,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(-0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    glPushMatrix();

                    {
                        glColor3f(0,0,0+0.25);
                        glTranslatef(0.5,-0.25-2+0.7,0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glutTimerFunc(2*333, timer333, 0);
                    // debug("outswitch\n");
                    break;
                }
                case 1:{
                    //left leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,1,0);
                        glTranslatef(0,0,-0.5);//
                        glRotatef(90,1,0,0);
                        glRotatef(-30,1,0,0);//
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0,0,0);
                        glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    //right leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);

                        glTranslatef(-0.5,1,0);
                        glTranslatef(0,0,-0.5);//
                        glRotatef(90,1,0,0);
                        glRotatef(-30,1,0,0);//
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(-0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    glPushMatrix();

                    {
                        glColor3f(0,0,0+0.25);
                        glTranslatef(0.5,-0.25-2+0.7,0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glutTimerFunc(2*333, timer333, 0);
                    break;
                }
                case 2:{
                    //left leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,1,0);
                        glTranslatef(0,-0.2,-0.75);//
                        glRotatef(90,1,0,0);
                        glRotatef(-60,1,0,0);//
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0,0,0);
                        glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    //right leg and foot
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);

                        glTranslatef(-0.5,1,0);
                        glTranslatef(0,-0.2,-0.75);//
                        glRotatef(90,1,0,0);
                        glRotatef(-60,1,0,0);//
                        glScalef(0.8,0.6,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glPushMatrix();
                    {
                        glColor3f(0.7,0.5,0.5);
                        glTranslatef(-0.5,-1+0.5,0);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,0.5,2);
                        glutSolidCube(1);
                    }
                    glPopMatrix();

                    glPushMatrix();

                    {
                        glColor3f(0,0,0+0.25);
                        glTranslatef(0.5,-0.25-2+0.7,0.25);
                        glRotatef(90,1,0,0);
                        glScalef(0.5,1,0.5);
                        glutSolidCube(1);
                    }
                    glPopMatrix();
                    glutTimerFunc(2*333, timer333, 0);
                    break;
                }
                default:
                    // debug("default\n");
                break;
            }
            bedcount +=f;
            if(bedcount<0) {
                beddone = -1;
                // state = WALK;
            }
        }

    }
    // glTranslatef(0,0,-5);
    glPushMatrix();

    int cnt = count;

    if(state == WALK)
    if(iswalk==1) {
        count ++;
            count%=3;
        switch (cnt){

            case 0:
            {
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0.5,1,0);
                glRotatef(90,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0,0,0);
                glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();

                //right leg and foot
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);

                glTranslatef(-0.5,1,0);
                glRotatef(90,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(-0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();

                glColor3f(0,0,0+0.25);
                glTranslatef(0.5,-0.25-2+0.7,0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();
                //left arm and hand
                glPushMatrix();
                glColor3f(0,0,1);
                glTranslatef(1.25,3.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,1);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0,0,1);
                glTranslatef(1.25,2.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.4,0.5,1);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3ub(239,228,176);
                glTranslatef(1.25,2,0+eps);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,0.5);
                glutSolidCube(1);
                glPopMatrix();

                //right arm and hand
                glPushMatrix();
                glColor3f(0,0,1);
                glTranslatef(-1.25,3.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,1);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0,0,1);
                glTranslatef(-1.25,2.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.4,0.5,1);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3ub(239,228,176);
                glTranslatef(-1.25,2,0+eps);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,0.5);
                glutSolidCube(1);
                glPopMatrix();
                break;
            }
            //step 2:
            case 1: {
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0.5,1,0);
                glRotatef(90,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                //TODO : 腿动画播片
                glColor3f(0,0,0);
                glTranslatef(0,0.1,0.5);//
                glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();

                //right leg and foot
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);

                glTranslatef(-0.5,1,0);
                glTranslated(0,0,0.3);
                glRotatef(90,1,0,0);
                glRotated(-15,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0,0.1,0.5);//
                glTranslatef(-0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();

                glColor3f(0,0,0+0.25);

                glTranslatef(0.5,-0.25-2+0.7,0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();

                //left arm and hand
                glPushMatrix();
                    glColor3f(0,0,1);

                    glTranslatef(1.25,3.5,0);
                    glRotatef(90,1,0,0);
                    glRotatef(-10,1,0,0);
                    glScalef(0.5,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,1);
                glTranslatef(0,0,0.5);//
                    glTranslatef(1.25,2.5,0);
                    glRotatef(90,1,0,0);

                glRotatef(-30,1,0,0);
                    glScalef(0.4,0.5,1);
                    glutSolidCube(1);
                    glPopMatrix();
                glPushMatrix();
                    glColor3ub(239,228,176);
                glTranslatef(0,0,0.8);//

                    glTranslatef(1.25,2,0+eps);
                    glRotatef(90,1,0,0);
                glRotatef(-30,1,0,0);
                    glScalef(0.5,0.5,0.5);
                    glutSolidCube(1);
                glPopMatrix();

                //right arm and hand
                glPushMatrix();
                    glColor3f(0,0,1);
                    glTranslatef(-1.25,3.5,0);
                    glRotatef(90,1,0,0);
                    glRotatef(10,1,0,0);
                    glScalef(0.5,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,1);

                glTranslatef(0,0,-0.05);
                    glTranslatef(-1.25,2.5,0);
                    glRotatef(90,1,0,0);

                    glScalef(0.4,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3ub(239,228,176);
                glTranslatef(0,0,-0.05);
                    glTranslatef(-1.25,2,0+eps);
                    glRotatef(90,1,0,0);

                    glScalef(0.5,0.5,0.5);
                    glutSolidCube(1);
                glPopMatrix();
                break;
            }
            case 2:
            {
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0.5,1,0);
                glTranslated(0,0,0.3);
                glRotatef(90,1,0,0);
                glRotated(-15,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(0,0.1,0.5);//
                glTranslatef(0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();
                glColor3f(0,0,0);

                glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();

                //right leg and foot
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);

                glTranslatef(-0.5,1,0);
                glRotatef(90,1,0,0);
                glScalef(0.8,0.6,2);
                glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                glColor3f(0.7,0.5,0.5);
                glTranslatef(-0.5,-1+0.5,0);
                glRotatef(90,1,0,0);
                glScalef(0.5,0.5,2);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();

                glColor3f(0,0,0+0.25);
                glTranslatef(0,0.1,0.5);//
                glTranslatef(0.5,-0.25-2+0.7,0.25);
                glRotatef(90,1,0,0);
                glScalef(0.5,1,0.5);
                glutSolidCube(1);
                glPopMatrix();
                //left arm and hand
                glPushMatrix();
                    glColor3f(0,0,1);

                    glTranslatef(1.25,3.5,0);
                    glRotatef(90,1,0,0);
                    glRotatef(10,1,0,0);
                    glScalef(0.5,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,1);
                    glTranslatef(0,0,-0.05);
                    glTranslatef(1.25,2.5,0);
                    glRotatef(90,1,0,0);
                    glScalef(0.4,0.5,1);
                    glutSolidCube(1);
                    glPopMatrix();
                glPushMatrix();
                    glColor3ub(239,228,176);
                    glTranslatef(0,0,-0.05);
                    glTranslatef(1.25,2,0+eps);
                    glRotatef(90,1,0,0);
                    glScalef(0.5,0.5,0.5);
                    glutSolidCube(1);
                glPopMatrix();

                //right arm and hand
                glPushMatrix();
                    glColor3f(0,0,1);
                    glTranslatef(-1.25,3.5,0);
                    glRotatef(90,1,0,0);
                    glRotatef(-10,1,0,0);
                    glScalef(0.5,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,1);
                    glTranslatef(0,0,0.5);//
                    glTranslatef(-1.25,2.5,0);
                    glRotatef(90,1,0,0);
                    glRotatef(-30,1,0,0);
                    glScalef(0.4,0.5,1);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glColor3ub(239,228,176);
                    glTranslatef(0,0,0.8);//
                    glTranslatef(-1.25,2,0+eps);
                    glRotatef(90,1,0,0);
                    glRotatef(-30,1,0,0);
                    glScalef(0.5,0.5,0.5);
                    glutSolidCube(1);
                glPopMatrix();
                break;
            }

        };
        iswalk = 0;
    }
    else {
        {
            glPushMatrix();
            glColor3f(0.7,0.5,0.5);
            glTranslatef(0.5,1,0);
            glRotatef(90,1,0,0);
            glScalef(0.8,0.6,2);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.7,0.5,0.5);
            glTranslatef(0.5,-1+0.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,2);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,0);
            glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
            glRotatef(90,1,0,0);
            glScalef(0.5,1,0.5);
            glutSolidCube(1);
            glPopMatrix();

            //right leg and foot
            glPushMatrix();
            glColor3f(0.7,0.5,0.5);

            glTranslatef(-0.5,1,0);
            glRotatef(90,1,0,0);
            glScalef(0.8,0.6,2);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.7,0.5,0.5);
            glTranslatef(-0.5,-1+0.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,2);
            glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();

            glColor3f(0,0,0+0.25);
            glTranslatef(0.5,-0.25-2+0.7,0.25);
            glRotatef(90,1,0,0);
            glScalef(0.5,1,0.5);
            glutSolidCube(1);
            glPopMatrix();

        }
        if(state!=BED){
            //left arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();

            //right arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(-1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();
        }
    }

    if(state == BED) {
        glPushMatrix();
        // debug("bedcount : %d\n", bedcount);
        if(f==1)
        switch (bedcount) {
            case 1:
                glTranslatef(0,0,0);
                break;
            case 2:
                glTranslatef(0,0,-1.25);
                break;
            case 3:
                glTranslatef(0,-0.6,-1.75);//
                break;
            default:
                break;
        }
        else {

            switch (bedcount) {
                case 0:
                    glTranslatef(0,-0.2,-1);
                    // state = WALK;
                    // debug("set walk\n");
                break;
                case 1:
                    glTranslatef(0,-0.67,-2);
                break;
                case 2:
                    glTranslatef(0,-3,-3);//
                break;
                default:
                    break;
            }
        }
    }
    if(state == BED) {
        {
            //left arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();

            //right arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(-1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();
        }
    }
    //body
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(0,3,0);
        glRotatef(90,1,0,0);
        glScalef(2,0.6,2);
        glutSolidCube(1);
    glPopMatrix();


    //neck
    glPushMatrix();
        glColor3ub(239,228,176);
        glTranslatef(0,0.3+3+1,0);
        // glRotatef(90,1,0,0);
        glScalef(0.7,0.6,0.4);
        glutSolidCube(1);
    glPopMatrix();

    //head
    glTranslatef(0,5.4,0);
        glScalef(0.8,1,0.7);
        glColor3ub(239,228,176);
        glutSolidSphere(1,100,100);
    glPopMatrix();
    // if(f==-1)
    //eyes
    if(state!=BED) {
        glTranslatef(0,5.4,0);
        glColor3f(0,0,0);
        glPointSize(4);
        glBegin(GL_POINTS);
            glVertex3f(0.3,0.3,0.62);
            glVertex3f(-0.3,0.3,0.62);
            glVertex3f(0,-2,0.4);
            glVertex3f(0,-3,0.4);
            glColor3f(1,0,0);
            glVertex3f(0,-0.5,0.6);
        glEnd();
    }


    if(state == BED) {
        glPopMatrix();
    }
    glPopMatrix();
    // //mouth
    // glTranslatef(0,5.4,0);
    //
    //     glPointSize(4);
    //     glBegin(GL_POINTS);
    //
    //     glEnd();
    // glPopMatrix();

    glPopMatrix();
    last_x = key_x;
    last_z = key_y;
    if(bedcount == 0&& f==-1 &&state==BED)state = WALK;
    /***********************end your code here************************/
}
void draw_people2() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
    glMaterialfv(GL_FRONT, GL_SHININESS, matBlack);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
    if(Light2)
        glMaterialfv(GL_FRONT, GL_EMISSION, matBrown);

    /**********************start your code below**********************/
    glPushMatrix();
    {

    }
    {
    glPushMatrix();
        glTranslatef(-2,-8,-10);

        glRotatef(90,0,0,1);
        glRotatef(-90,1,0,0);
        glRotatef(90,0,1,0);

    // glTranslatef(0,0,-5);
    glPushMatrix();

    //left leg and foot
    glPushMatrix();
    glColor3f(0.7,0.5,0.5);
    glTranslatef(0.5,1,0);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.6,2);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.7,0.5,0.5);
    glTranslatef(0.5,-1+0.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,2);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
    glRotatef(90,1,0,0);
    glScalef(0.5,1,0.5);
    glutSolidCube(1);
    glPopMatrix();

    //right leg and foot
    glPushMatrix();
    glColor3f(0.7,0.5,0.5);
    glTranslatef(-0.5,1,0);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.6,2);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.7,0.5,0.5);
    glTranslatef(-0.5,-1+0.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,2);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,0+0.25);
    glTranslatef(0.5,-0.25-2+0.7,0.25);
    glRotatef(90,1,0,0);
    glScalef(0.5,1,0.5);
    glutSolidCube(1);
    glPopMatrix();

    //body
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0,3,0);
    glRotatef(90,1,0,0);
    glScalef(2,0.6,2);
    glutSolidCube(1);
    glPopMatrix();

    //left arm and hand
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(1.25,3.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(1.25,2.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.4,0.5,1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3ub(239,228,176);
    glTranslatef(1.25,2,0+eps);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,0.5);
    glutSolidCube(1);
    glPopMatrix();

    //right arm and hand
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-1.25,3.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-1.25,2.5,0);
    glRotatef(90,1,0,0);
    glScalef(0.4,0.5,1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3ub(239,228,176);
    glTranslatef(-1.25,2,0+eps);
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,0.5);
    glutSolidCube(1);
    glPopMatrix();
    //neck
    glPushMatrix();
    glColor3ub(239,228,176);
    glTranslatef(0,0.3+3+1,0);
    // glRotatef(90,1,0,0);
    glScalef(0.7,0.6,0.4);
    glutSolidCube(1);
    glPopMatrix();

    //head
    glTranslatef(0,5.4,0);
    glScalef(0.8,1,0.7);
    glColor3ub(239,228,176);
    glutSolidSphere(1,100,100);
    glPopMatrix();
    //eyes
    glTranslatef(0,5.4,0);
    glColor3f(0,0,0);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0.3,0.3,0.62);
    glVertex3f(-0.3,0.3,0.62);
    glVertex3f(0,-2,0.4);
    glVertex3f(0,-3,0.4);
    glColor3f(1,0,0);
    glVertex3f(0,-0.5,0.6);
    glEnd();
    glPopMatrix();
    // //mouth
    // glTranslatef(0,5.4,0);
    //
    //     glPointSize(4);
    //     glBegin(GL_POINTS);
    //
    //     glEnd();
    // glPopMatrix();

    glPopMatrix();
}
    glPopMatrix();
    beddone = 1;

    /***********************end your code here************************/
}
int chairface = 1;
void draw_people3() {

    //
    glPushMatrix();

    glTranslated(key_x,0,key_y);
    glTranslatef(-10,-8.0,-18);
    glTranslatef(4.5,0.4,0);
    glRotatef(90*(abs(lasr_face - face)),0,1,0);
    glRotatef(2*90,0,1,0);
    glPushMatrix();
    {
        glColor3f(0.7,0.5,0.5);
        glTranslatef(0.5,1,0);
        glTranslatef(0,-0.2,-0.75);//
        glRotatef(90,1,0,0);
        glRotatef(-90,1,0,0);//
        glScalef(0.8,0.6,2);
        glutSolidCube(1);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0.7,0.5,0.5);
        glTranslatef(0.5,-1+0.5,0);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,2);
        glutSolidCube(1);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0,0,0);
        glTranslatef(-0.5,-0.25-2+0.7,0+0.25);
        glRotatef(90,1,0,0);
        glScalef(0.5,1,0.5);
        glutSolidCube(1);
    }
    glPopMatrix();

    //right leg and foot
    glPushMatrix();
    {
        glColor3f(0.7,0.5,0.5);

        glTranslatef(-0.5,1,0);
        glTranslatef(0,-0.2,-0.75);//
        glRotatef(90,1,0,0);
        glRotatef(-90,1,0,0);//
        glScalef(0.8,0.6,2);
        glutSolidCube(1);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0.7,0.5,0.5);
        glTranslatef(-0.5,-1+0.5,0);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,2);
        glutSolidCube(1);
    }
    glPopMatrix();

    glPushMatrix();

    {
        glColor3f(0,0,0+0.25);
        glTranslatef(0.5,-0.25-2+0.7,0.25);
        glRotatef(90,1,0,0);
        glScalef(0.5,1,0.5);
        glutSolidCube(1);
    }
    glPopMatrix();
    // glutTimerFunc(2*333, timer333, 0);

    glPushMatrix();
    glTranslatef(0,-0.85,-1.5);
        glPushMatrix();
    glTranslatef(0,4.7,4);
        glRotatef(-102,1,0,0);

        {
            //left arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();

            //right arm and hand
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,3.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0,0,1);
            glTranslatef(-1.25,2.5,0);
            glRotatef(90,1,0,0);
            glScalef(0.4,0.5,1);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3ub(239,228,176);
            glTranslatef(-1.25,2,0+eps);
            glRotatef(90,1,0,0);
            glScalef(0.5,0.5,0.5);
            glutSolidCube(1);
            glPopMatrix();
        }
    glPopMatrix();
    //body
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(0,3,0);
        glRotatef(90,1,0,0);
        glScalef(2,0.6,2);
        glutSolidCube(1);
    glPopMatrix();


    //neck
    glPushMatrix();
        glColor3ub(239,228,176);
        glTranslatef(0,0.3+3+1,0);
        // glRotatef(90,1,0,0);
        glScalef(0.7,0.6,0.4);
        glutSolidCube(1);
    glPopMatrix();

    //head
    glTranslatef(0,5.4,0);
        glScalef(0.8,1,0.7);
        glColor3ub(239,228,176);
        glutSolidSphere(1,100,100);
    glPopMatrix();
    // if(f==-1)
    //eyes
    if(state!=BED) {
        glTranslatef(0,5.4,0);
        glColor3f(0,0,0);
        glPointSize(4);
        glBegin(GL_POINTS);
            glVertex3f(0.3,0.3,0.62);
            glVertex3f(-0.3,0.3,0.62);
            glVertex3f(0,-2,0.4);
            glVertex3f(0,-3,0.4);
            glColor3f(1,0,0);
            glVertex3f(0,-0.5,0.6);
        glEnd();
    }


    if(state == BED) {
        glPopMatrix();
    }
    glPopMatrix();
    // //mouth
    // glTranslatef(0,5.4,0);
    //
    //     glPointSize(4);
    //     glBegin(GL_POINTS);
    //
    //     glEnd();
    // glPopMatrix();

    glPopMatrix();
    beddone = 1;
    // eye[3] = { 5,-5, 0};

    glutPostRedisplay();
}
int imageWidth, imageHeight;
unsigned char* imageData;

void testcode1()
{
    draw_tvdesk();
    if(seat)
        draw_seat();
    else {
        draw_seat2();
    }
    draw_bed();
    draw_closet();
    draw_taideng();
    draw_clock();
    if(bedcount<3)draw_people();
    else {
        if(!chair)
            draw_people2();
        else {
            draw_people3();
        }

    }

}

void testanimation()
{
    /****here,add glut callback events for animation*/




    /*********************end***********************/
    return;
}