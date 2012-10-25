#include "QSceneDisplay.h"

QSceneDisplay::QSceneDisplay(QWidget *parent)
	: QGLWidget(parent)
{
	xangle=yangle=0.0;
	scale=1.0;
	eye[0]=eye[1]=eye[2]=0.0;
	eye[3]=1.0;
	scene=NULL;

	//plane[0]=-width();
	//plane[1]=width();
	//plane[2]=-height();
	//plane[3]=height();
}


QSceneDisplay::~QSceneDisplay()
{

}

void QSceneDisplay::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(1.0,1.0,1.0,1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void QSceneDisplay::paintGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };//��������ɫ
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//���������ɫ
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//���淴˼����ɫ
	GLfloat light_position[] = { 9999.0, 9999.0, 9999.0, 0.0 };//��Դλ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);//���û�����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//�����������
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//���þ��淴���
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//���ù�Դλ��
	glEnable(GL_LIGHTING);//�򿪹���
	glEnable(GL_LIGHT0);//��0�Ź�Դ
	glEnable(GL_DEPTH_TEST);//����Ȳ���

	glDepthFunc(GL_LEQUAL);							// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// ������ϸ��͸������

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	//double aspect=(double)width()/height();

	//emit SetCamera(eye,scale,aspect);
	SetCamera();
	DrawCoodinates();


	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glTranslatef(0,0,-5);
	//glRotated(xangle,1.0,0.0,0.0);
	//glRotated(yangle,0.0,1.0,0.0);

	emit DrawScene();
}

void QSceneDisplay::resizeGL( int width,int height )
{
	if (height==0)
		height=1;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect=GLfloat(width)/height;
	//if (aspect<1) 
	//	glOrtho (-100.0, 100.0, -100 / aspect, 100.0 / aspect, 1.0, -1.0);
	//else 
	//	glOrtho (-100.0 * aspect, 100.0 * aspect, -100.0, 100.0, 1.0, -1.0);
	plane[0]=-width;
	plane[1]=width;
	plane[2]=-height;
	plane[3]=height;
	if (aspect<1)
	{
		plane[2]/=aspect;
		plane[3]/=aspect;
	}
	else
	{
		plane[0]*=aspect;
		plane[1]*=aspect;
	}
	glOrtho(plane[0],plane[1],plane[2],plane[3],1.0,100);
	//glFrustum(-x,+x,-1.0,+1.0,4.0,100.0);
	//gluPerspective(45,x,1.0,10000.0);
	//glOrtho(-x,x,-1.0,1.0,4.0,100);
	glMatrixMode(GL_MODELVIEW);
}

void QSceneDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    double dx=double(lbtnDown.x()-point.x())/width();
    double dy=double(lbtnDown.y()-point.y())/height();
	eye[0]+=dx;
	eye[1]+=dy;
	//xangle -= 180 * dy;
	//yangle -= 180 * dx;
    this->updateGL();
    lbtnDown=point;
}

void QSceneDisplay::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        lbtnDown=event->pos();
}

void QSceneDisplay::wheelEvent(QWheelEvent *event)
{

}

void QSceneDisplay::DrawCoodinates()
{
	glTranslatef(0,0,-6);
	glBegin(GL_LINES);
	glColor3b(0,0,255);
	glVertex3f(0,-5000,0);
	glVertex3f(0,5000,0);
	glColor3b(0,255,0);
	glVertex3f(-5000,0,0);
	glVertex3f(5000,0,0);
	glColor3b(255,0,0);
	glVertex3f(0,0,-5000);
	glVertex3f(0,0,5000);
	glEnd();
}

void QSceneDisplay::SetDisProperty( point center, float r )
{
	//zFar=zNear+2*r;
	//eye[2]=4*r;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x=GLfloat(width())/height();
	gluPerspective(50.0*scale,x,1,2*r+1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],0.0,1.0,0.0);
}

void QSceneDisplay::SetDisScene( Scene* scene )
{
	this->scene=scene;
	eye[0]=scene->bsphere.center[0];
	eye[1]=scene->bsphere.center[1];
	eye[2]=scene->bsphere.center[2]+scene->bsphere.r;
	updateGL();
}

void QSceneDisplay::SetCamera()
{
	if(scene==NULL)
		return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double diam=2*scene->bsphere.r;
	double tmp=abs(scene->bsphere.center[0]);
	plane[0]=-(tmp+diam);
	plane[1]=-plane[0];
	tmp=abs(scene->bsphere.center[1]);
	plane[2]=-(tmp+diam);
	plane[3]=-plane[2];
	//plane[0]=scene->bsphere.center[0]-diam;
	//plane[1]=scene->bsphere.center[0]+diam;
	//plane[2]=scene->bsphere.center[1]-diam;
	//plane[3]=scene->bsphere.center[1]+diam;
	double aspect=(double)width()/height();
	if (aspect<1)
	{
		plane[2]/=aspect;
		plane[3]/=aspect;
	}
	else
	{
		plane[0]*=aspect;
		plane[1]*=aspect;
	}
	//double z=abs(scene->bsphere.center[3]);
	/*glOrtho(plane[0],plane[1],plane[2],plane[3],z+10,-z-10);*/
	glOrtho(plane[0],plane[1],plane[2],plane[3],-10000,10000);
	//gluLookAt(eye.x,eye.y,eye.z,)
	//glOrtho(-10000,10000,-10000,10000,-10000,10000);
	gluLookAt(eye[0],eye[1],eye[2],scene->bsphere.center[0],scene->bsphere.center[1],scene->bsphere.center[2],0,1,0);
	//gluLookAt(scene->bsphere.center[0],scene->bsphere.center[1],scene->bsphere.center[2]+10,scene->bsphere.center[0],scene->bsphere.center[1],scene->bsphere.center[2],0,1,0);
	//glRotated(xangle,scene->bsphere.center[0],0.0,0.0);
	//glRotated(yangle,0.0,scene->bsphere.center[1],0.0);
	//gluLookAt(0,0,5,0,0,-1,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}