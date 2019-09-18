#include "line.h"

#include <Windows.h>
#define bulletNum 15

double tPre,tNow,tCheck;
int num,frame,fps;
extern int Ellquesize; //用于记录椭圆的点，现在没用了
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
	gluOrtho2D(0.0, 480.0, 0.0, 320.0);//设置像素的个数？
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

//暂不使用
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
	if(tNow-tPre>=100){ //如果上次绘图与本次绘图时间相差0.1秒，就重绘.否则就什么也不做
		frame++;	    //如果进入就帧数加1
		if(tNow-tCheck>=1000){	//如果相差的时间超过1秒，就将帧数赋给fps，重新计算帧数
			fps =frame;
			printf("fps:%d\n",fps);//显示帧数
			frame = 0;
			tCheck = tNow;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,1.0,1.0);

		//wo.setCircle(MyPoint,10);
		wo.setPosition(MyPoint);//设置我的位置
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
     * 这里的x,y都是相对于绘制的窗口而言的，窗口的左上角为(0,0)，右下角为(250,250)
     * button==0 左键 button==2 右键 state==0 按下 state==1 抬起
     */
    cout<<"button="<<button<<"  state="<<state<<"  x="<<x<<"  y="<<y<<endl;
	//如果按键抬起并且
	if(state = 1 && !(p1.X == x && (320 - p1.Y) == y)){		//p2中一直保存着最后一次压入的值
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//初始化显示模式：单缓冲区，RGB模式
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello,OpenGL");
    init();


	//glutDisplayFunc(display);
	glutDisplayFunc(renderScene1);
	glutIdleFunc(renderScene1);//设置窗口刷新的回调函数,即程序空闲的时候做什么
	glutMouseFunc(displayMouse);//设置鼠标器按键回调函数

	glutKeyboardFunc(myKey);//设置键盘回调函数
	

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

	//glutMotionFunc(mymotion);//设置鼠标器移动回调函数?
    glutMainLoop();
	system("pause");
    return 0;
}