#include "line.h"
int collisionNum=0;
int collisionDet(Bullet *bullet,Circle *wo){
	//if(bullet==NULL)return 0;
	float bx=0,by=0,rb;
	float wx=0,wy=0,rw;
	rb=(*bullet).getCirc().getRadius();
	rw=(*wo).getRadius();
	bx=(*bullet).getPosition().X;
	by=(*bullet).getPosition().Y;
	wx=(*wo).getPosition().X;
	wy=(*wo).getPosition().Y;
	/*if( (((wx-rw)<(bx+rb))&&((bx+rb)<(wx+rw)) || ((wx-rw)<(bx-rb))&&((bx-rb)<(wx+rw))) && (((wy-rw)<(by+rb))&&((by+rb)<(wy+rw)) || ((wy-rw)<(by-rb))&&((by-rb)<(wy+rw))) ){
		collisionNum++;
		(*bullet).setV(-(*bullet).getVx(),-(*bullet).getVy());

		printf("CollisionNum:%d",collisionNum);
	}*/



	//Ê¹ÓÃ°ë¾¶¼ì²âÅö×²
	if((bx-wx)*(bx-wx)+(by-wy)*(by-wy)<(rb+rw)*(rb+rw)){
		collisionNum++;
		(*bullet).setV(-(*bullet).getVx(),-(*bullet).getVy());

		printf("CollisionNum:%d\n",collisionNum);
	}
	return 1;//collisionNum;

}
int collisionDet1(Bullet *bullet,Circle *wo){
	if(bullet==NULL)return 0;
	float bx=0,by=0,rb;
	float wx=0,wy=0,rw;
	rb=(*bullet).getCirc().getRadius();
	rw=(*wo).getRadius();
	bx=(*bullet).getPosition().X;
	by=(*bullet).getPosition().Y;
	wx=(*wo).getPosition().X;
	wy=(*wo).getPosition().Y;
	
	//Ê¹ÓÃ°ë¾¶¼ì²âÅö×²
	/*if((bx-wx)*(bx-wx)+(by-wy)*(by-wy)<(rb+rw)*(rb+rw)){
		collisionNum++;
		(*bullet).setV(-(*bullet).getVx(),-(*bullet).getVy());

		printf("CollisionNum:%d\n",collisionNum);
	}
	return 1;*///collisionNum;


	if((bx-wx)*(bx-wx)+(by-wy)*(by-wy)<(rb+rw)*(rb+rw)){
		if(rb<rw){
			collisionNum++;
			(*wo).setRadius(rw+rb);
			delete(bullet);
			bullet=NULL;
			return 1;
		}
		(*bullet).setV(-(*bullet).getVx(),-(*bullet).getVy());
		collisionNum++;
		//(*bullet).setV(-(*bullet).getVx(),-(*bullet).getVy());

		printf("CollisionNum:%d\n",collisionNum);
	}
	return 1;//collisionNum;
}