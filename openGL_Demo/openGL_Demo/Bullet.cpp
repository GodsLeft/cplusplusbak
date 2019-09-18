#include "line.h"

Bullet::Bullet(int radius){
	bp.X=rand()%480;
	bp.Y=rand()%320;
	vx=rand()%40-20;
	vy=rand()%40-20;
	circ.setCircle(bp,radius);
	circ.circleMid();
}

//Bullet::Bullet(int ){}

void Bullet::setV(float velx,float vely){
	vx=velx;
	vy=vely;
}

float Bullet::getVx(){
	return vx;
}

float Bullet::getVy(){
	return vy;
}

void Bullet::bulletdraw(){
	//circ.setCircle(bp,20);
	circ.setPosition(bp);
	circ.circleMid();
}
//移动并进行边缘检测
void Bullet::BorderDet(){
	//如果获得帧率的话就可以有精确的速度控制
	if(vx<0){
		bp.X-=1;
	}else{
		bp.X+=1;
	}
	if(vy<0){
		bp.Y-=1;
	}else{
		bp.Y+=1;
	}
	//int R=circ.getRadius();
	if((bp.X<=0 && vx<0)||(bp.X>=480 && vx>0)){
		vx=-vx;
	}
	if((bp.Y<=0 && vy<0)||(bp.Y>=320 && vy>0)){
		vy=-vy;
	}
}
Point Bullet::getPosition(){
	Point temp;
	temp.X=bp.X;
	temp.Y=bp.Y;
	return temp;
}

Circle Bullet::getCirc(){
	return circ;
}