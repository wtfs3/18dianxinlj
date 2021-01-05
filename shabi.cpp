#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

//С����Ľṹ������С������x,y,z�ϵ���ת�Ƕȣ���ɫ�����±꣬С�������ά���ꡣ

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
//��ɫ����
GLfloat color[6][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},
{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,1.0}};
int tempc[3][3][6];
//�й���ת��һЩ����
GLfloat xRot = 10.0f;
GLfloat yRot = 10.0f;
int rotateType=0;
int rotateOK=0;
int rotateRate=50;
int rotate=0;
///////////////////////////////////////////////////////////////////////////////
//��С����
void drawcube(int cl[6])
{   
glBegin(GL_QUADS);
//����
glColor3fv(color[cl[0]]);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
glVertex3f(0.14f,0.14f,0.14f);
glVertex3f(0.14f,-0.14f,0.14f);

//����
glColor3fv(color[cl[1]]);

glVertex3f(-0.14f,-0.14f,0.14f);
glVertex3f(-0.14f,0.14f,0.14f);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(-0.14f,-0.14f,-0.14f);
//ǰ��
glColor3fv(color[cl[2]]);
glVertex3f(-0.14f,0.14f,0.14f);
glVertex3f(-0.14f,-0.14f,0.14f);
glVertex3f(0.14f,-0.14f,0.14f);
glVertex3f(0.14f,0.14f,0.14f);
//����
glColor3fv(color[cl[3]]);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(-0.14f,-0.14f,-0.14f);

//����

glColor3fv(color[cl[4]]);
glVertex3f(-0.14f,0.14f,-0.14f);
glVertex3f(-0.14f,0.14f,0.14f);   
glVertex3f(0.14f,0.14f,0.14f);
glVertex3f(0.14f,0.14f,-0.14f);
//����
glColor3fv(color[cl[5]]);
glVertex3f(-0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,-0.14f);
glVertex3f(0.14f,-0.14f,0.14f);
glVertex3f(-0.14f,-0.14f,0.14f);
glEnd();
glFlush();
}   
//����ˢ��ʱ�����á�
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
//ħ��������ʾ

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

//��ʼ����

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

//ѡ��ת������һ��С���顣

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

//�ж��Ƿ�ʤ����

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

//ת��С���飬ʵ�����ǽ�����ɫ��

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

//�����ɽ�����ɫ��ɺ�ɫ��������ɻ�ɫ��

if(win()==1)

glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

else

glClearColor(0.5f, 0.5f, 0.5f, 1.0f );

}   

//ת��ħ����Ҳ���Ǹı�С������x,y,z�ϵ���ת�Ƕȡ�

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

//��ʱ���ص���������ħ��ת��ʱ����������

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

//���ռ������롣

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

//�����ڸı�ߴ�ʱ�����á�

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

//��������

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
