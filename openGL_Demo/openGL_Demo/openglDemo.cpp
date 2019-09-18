#include "line.h"

#include <Windows.h>
#define bulletNum 15

double tPre,tNow,tCheck;
int num,frame,fps;
extern int Ellquesize; //���ڼ�¼��Բ�ĵ㣬����û����
extern int collisionNum;
Point MyPoint={240,12};
Circle wo;

Bullet *bullet[bulletNum];

eightLight *light[5];

Point p1,p2;
queue<Point> points;
queue<Point> Ellque;
void init(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 480.0, 0.0, 320.0);//�������صĸ�����
}

void eightshow(int num){
	int remd=0;
	int i=0;
	while(num>0){
		remd=num%10;
		(*light[i]).showNum(remd);
		i++;
		num=int(num/10);
	}
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
}

//�ݲ�ʹ��
void renderScene(void){
	//display();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);

	//wo.setCircle(MyPoint,10);
	wo.circleMid();
	
	for(int i=0;i<bulletNum;i++){
		(*(bullet[i])).BorderDet();
		collisionDet(bullet[i],&wo);
		(*(bullet[i])).bulletdraw();
	}
	eightshow(collisionNum);
	glFlush();
}
void renderScene1(void){
	tNow=GetTickCount();
	if(tNow-tPre>=100){ //����ϴλ�ͼ�뱾�λ�ͼʱ�����0.1�룬���ػ�.�����ʲôҲ����
		frame++;	    //��������֡����1
		if(tNow-tCheck>=1000){	//�������ʱ�䳬��1�룬�ͽ�֡������fps�����¼���֡��
			fps =frame;
			printf("fps:%d\n",fps);//��ʾ֡��
			frame = 0;
			tCheck = tNow;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,1.0,1.0);

		//wo.setCircle(MyPoint,10);
		wo.setPosition(MyPoint);//�����ҵ�λ��
		wo.circleMid();
		

		for(int i=0;i<bulletNum;i++){
			if(bullet[i]==NULL)continue;
			(*(bullet[i])).BorderDet();
			collisionDet(bullet[i],&wo);
			(*(bullet[i])).bulletdraw();
		}
		eightshow(collisionNum);
		glFlush();

		tPre=GetTickCount();
	}
}


void displayMouse(int button, int state, int x, int y)
{
    /*
     * �����x,y��������ڻ��ƵĴ��ڶ��Եģ����ڵ����Ͻ�Ϊ(0,0)�����½�Ϊ(250,250)
     * button==0 ��� button==2 �Ҽ� state==0 ���� state==1 ̧��
     */
    cout<<"button="<<button<<"  state="<<state<<"  x="<<x<<"  y="<<y<<endl;
	//�������̧����
	if(state = 1 && !(p1.X == x && (320 - p1.Y) == y)){		//p2��һֱ���������һ��ѹ���ֵ
		p1.X=x;
		p1.Y=320-y;
		points.push(p1);
	}
	while(points.size() >= 2){
		p1=points.front();
		points.pop();
		p2=points.front();
		points.pop();
		lineBres_lk(p1.X,p1.Y,p2.X,p2.Y);
		glFlush();
	}
}



void myKey(unsigned char key,int x,int y){
	switch(key){
	case 'd':
		if(MyPoint.X<480){
			MyPoint.X+=5;
			//printf("d\n");
		}
		break;
	case 'a':
		if(MyPoint.Y>0){
			MyPoint.X-=5;
			//printf("a\n");
		}
		break;
	case 'w':
		if(MyPoint.Y<320){
			MyPoint.Y+=5;
		}
		break;
	case 's':
		if(MyPoint.Y>0){
			MyPoint.Y-=5;
		}
		break;
	}
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//��ʼ����ʾģʽ������������RGBģʽ
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello,OpenGL");
    init();


	//glutDisplayFunc(display);
	glutDisplayFunc(renderScene1);
	glutIdleFunc(renderScene1);//���ô���ˢ�µĻص�����,��������е�ʱ����ʲô
	glutMouseFunc(displayMouse);//��������������ص�����

	glutKeyboardFunc(myKey);//���ü��̻ص�����
	

	for(int i=0;i<bulletNum;i++){
		bullet[i] = new Bullet(rand()%10+2);
		(*bullet[i]).bulletdraw();
	}
	glFlush();

	wo.setCircle(MyPoint,10);
	int po=462;
	for(int i=0;i<5;i++){
		light[i]=new eightLight(po-12*i,0);
	}

	//glutMotionFunc(mymotion);//����������ƶ��ص�����?
    glutMainLoop();
	system("pause");
    return 0;
}