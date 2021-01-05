#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

//小方块的结构，包括小方块在x,y,z上的旋转角度，颜色数组下标，小方块的三维坐标。

struct rcube{
int xr;
int yr;
int zr;
int cl[6];
GLfloat x;
GLfloat y;
GLfloat z;
};
struct rcube rc[3][3][3];
struct rcube *temp[3][3];
//颜色数组
GLfloat color[6][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},
{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,1.0}};
int tempc[3][3][6];
//有关旋转的一些变量
GLfloat xRot = 10.0f;
GLfloat yRot = 10.0f;
int rotateType=0;
int rotateOK=0;
int rotateRate=50;
int rotate=0;
///////////////////////////////////////////////////////////////////////////////
//画小方块
void drawcube(int cl[6])
{   
glBegin(GL_QUADS);
//右面
glColor3fv(color[cl[0]]);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
glVertex3f(0.14f,0.14f,0.14f);
glVertex3f(0.14f,-0.14f,0.14f);

//左面
glColor3fv(color[cl[1]]);

glVertex3f(-0.14f,-0.14f,0.14f);
glVertex3f(-0.14f,0.14f,0.14f);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(-0.14f,-0.14f,-0.14f);
//前面
glColor3fv(color[cl[2]]);
glVertex3f(-0.14f,0.14f,0.14f);
glVertex3f(-0.14f,-0.14f,0.14f);
glVertex3f(0.14f,-0.14f,0.14f);
glVertex3f(0.14f,0.14f,0.14f);
//后面
glColor3fv(color[cl[3]]);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(-0.14f,-0.14f,-0.14f);

//上面

glColor3fv(color[cl[4]]);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(-0.14f,0.14f,0.14f);   
glVertex3f(0.14f,0.14f,0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
//下面
glColor3fv(color[cl[5]]);
glVertex3f(-0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,0.14f);
glVertex3f(-0.14f,-0.14f,0.14f);
glEnd();
glFlush();
}   
//窗口刷新时被调用。
void RenderScene(void)
{
int i,j,k;
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glRotatef(xRot, 1.0f, 0.0f, 0.0f);
glRotatef(yRot, 0.0f, 1.0f, 0.0f);
for(i=0;i<3;i++)

{

for(j=0;j<3;j++)
{
for(k=0;k<3;k++)

{
//魔方在这显示

glPushMatrix();     

glRotatef(rc[i][j][k].xr, 1.0f, 0.0f, 0.0f);

glRotatef(rc[i][j][k].zr, 0.0f, 0.0f, 1.0f);

glRotatef(rc[i][j][k].yr, 0.0f, 1.0f, 0.0f);   

glTranslatef(rc[i][j][k].x,rc[i][j][k].y,rc[i][j][k].z);               

drawcube(rc[i][j][k].cl);           

glPopMatrix();

}

}

}           

glPopMatrix();

glutSwapBuffers();

}

//初始化。

void SetupRC()

{

GLfloat x,y,z;

int i,j,k,l;

for(i=0,x=-0.3f;i<3;i++,x+=0.3f)

{

for(j=0,y=-0.3f;j<3;j++,y+=0.3f)

{

for(k=0,z=-0.3f;k<3;k++,z+=0.3f)

{

rc[i][j][k].x=x;rc[i][j][k].xr=0;

rc[i][j][k].y=y;rc[i][j][k].yr=0;

rc[i][j][k].z=z;rc[i][j][k].zr=0;                                     

for(l=0;l<6;l++)

{

rc[i][j][k].cl[l]=l;                         

}   

}

}

}

glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

glEnable(GL_DEPTH_TEST);

glEnable(GL_CULL_FACE);

}

//选择转动的那一组小方块。

void elect(int type)

{

int i,j; 

for(i=0;i<3;i++)

{

for(j=0;j<3;j++)

{

switch (type)

{

case 1:

temp[i][j]=&rc[0][i][j]; break;

case 2:

temp[i][j]=&rc[1][i][j]; break;

case 3:

temp[i][j]=&rc[2][i][j]; break;

case 4:

temp[i][j]=&rc[j][0][i]; break;

case 5:

temp[i][j]=&rc[j][1][i]; break;

case 6:

temp[i][j]=&rc[j][2][i]; break;

case 7:

temp[i][j]=&rc[i][j][0]; break;

case 8:

temp[i][j]=&rc[i][j][1]; break;

case 9:

temp[i][j]=&rc[i][j][2]; break;

}           

}

}   

}

//判断是否胜利。

int win(void)

{

int i,j,k,c,cl[6];

for(k=0;k<6;k++)

{

cl[k]=rc[0][0][0].cl[k];

}   

for(i=0;i<3;i++)

{

for(j=0;j<3;j++)

{

for(k=0;k<3;k++)

{

for(c=0;c<6;c++)

{

if(rc[i][j][k].cl[c]!=cl[c])

return 0;

}   

}   

}   

}

return 1;

}   

//转动小方块，实际上是交换颜色。

void shift(void)

{   

int i,j,k,c;

elect(rotateType);

for(i=0;i<3;i++)

{

for(j=0;j<3;j++)

{

(*temp[i][j]).xr=0;

(*temp[i][j]).yr=0;

(*temp[i][j]).zr=0;   

if(rotateType>0&&rotateType<=3)

{

c=(*temp[i][j]).cl[2];

(*temp[i][j]).cl[2]=(*temp[i][j]).cl[4];

(*temp[i][j]).cl[4]=(*temp[i][j]).cl[3];

(*temp[i][j]).cl[3]=(*temp[i][j]).cl[5];

(*temp[i][j]).cl[5]=c;

}

if(rotateType>3&&rotateType<=6)

{

c=(*temp[i][j]).cl[0];

(*temp[i][j]).cl[0]=(*temp[i][j]).cl[2];

(*temp[i][j]).cl[2]=(*temp[i][j]).cl[1];

(*temp[i][j]).cl[1]=(*temp[i][j]).cl[3];

(*temp[i][j]).cl[3]=c;

}

if(rotateType>6&&rotateType<=9)

{

c=(*temp[i][j]).cl[4];

(*temp[i][j]).cl[4]=(*temp[i][j]).cl[0];

(*temp[i][j]).cl[0]=(*temp[i][j]).cl[5];

(*temp[i][j]).cl[5]=(*temp[i][j]).cl[1];

(*temp[i][j]).cl[1]=c;

}

for(k=0;k<6;k++)

{

tempc[2-j][i][k]=(*temp[i][j]).cl[k];

}

}

}   

for(i=0;i<3;i++)

{

for(j=0;j<3;j++)

{

for(k=0;k<6;k++)

{

(*temp[i][j]).cl[k]=tempc[i][j][k];

}   

}

}

//如果完成将背景色设成黑色，否则设成灰色。

if(win()==1)

glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

else

glClearColor(0.5f, 0.5f, 0.5f, 1.0f );

}   

//转动魔方，也就是改变小方块在x,y,z上的旋转角度。

void turn (void)

{

int j,k;

elect(rotateType);

for(j=0;j<3;j++)

{

for(k=0;k<3;k++)

{           

if(rotateType>0&&rotateType<=3)

(*temp[j][k]).xr+=10;

if(rotateType>3&&rotateType<=6)

(*temp[j][k]).yr+=10;

if(rotateType>6&&rotateType<=9)

(*temp[j][k]).zr+=10;           

}

}

} 

//定时器回调函数，当魔方转动时产生动画。

void TimerFunc(int value)

{

rotate+=10;       

turn();

glutPostRedisplay();

if(rotate==90)

{

shift();

rotate=0;

rotateOK=0;       

rotateType=0;       

return;

}     

glutTimerFunc(rotateRate,TimerFunc,1);

}

//接收键盘输入。

void SpecialKeys(int key, int x, int y)

{

int temp=0;

switch (key)

{   

case GLUT_KEY_F1:

temp=1; break;

case GLUT_KEY_F2:

temp=2; break;

case GLUT_KEY_F3:

temp=3; break;                     

case GLUT_KEY_F4:

temp=4; break;

case GLUT_KEY_F5:

temp=5; break;

case GLUT_KEY_F6:

temp=6; break;

case GLUT_KEY_F7:

temp=7; break;

case GLUT_KEY_F8:

temp=8; break;

case GLUT_KEY_F9:

temp=9; break;                                                 

case GLUT_KEY_UP:

xRot -= 5.0f; break;

case GLUT_KEY_DOWN:

xRot += 5.0f; break;

case GLUT_KEY_LEFT:

yRot -= 5.0f; break;

case GLUT_KEY_RIGHT:

yRot += 5.0f; break;

}

if ( rotateOK==0 && temp!=0)

{

rotateType=temp;

rotateOK=1;

glutTimerFunc(rotateRate,TimerFunc,1);

}

else temp=0;

if(xRot > 356.0f) xRot = 0.0f;

if(xRot < -1.0f) xRot = 355.0f;

if(yRot > 356.0f) yRot = 0.0f;

if(yRot < -1.0f) yRot = 355.0f;

glutPostRedisplay();       

}

//当窗口改变尺寸时被调用。

void ChangeSize(int w, int h)

{

GLfloat nRange = 1.9f;

if(h == 0)

h = 1;

glViewport(0, 0, w, h);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

if (w <= h)

glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);

else

glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

glMatrixMode(GL_MODELVIEW);

glLoadIdentity();

}

//主函数。

int main(int argc, char* argv[])

{

glutInit(&argc, argv);

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutCreateWindow("GLUT Shapes");

glutReshapeFunc(ChangeSize);

glutSpecialFunc(SpecialKeys);

glutDisplayFunc(RenderScene);

SetupRC();

glutMainLoop();

return 0;
