#include "line.h";
//不管位置只显示数字，位置由别的函数指定
void eightLight::showNum(int num){
	switch(num){
	case 0:
		line[0].lineBres();
		line[1].lineBres();
		line[2].lineBres();
		line[3].lineBres();
		line[4].lineBres();
		line[5].lineBres();
		break;
	case 1:
		line[1].lineBres();
		line[2].lineBres();
		break;
	case 2:
		line[3].lineBres();
		line[2].lineBres();
		line[6].lineBres();
		line[5].lineBres();
		line[0].lineBres();
		break;
	case 3:
		line[3].lineBres();
		line[2].lineBres();
		line[6].lineBres();
		line[1].lineBres();
		line[0].lineBres();
		break;
	case 4:
		line[4].lineBres();
		line[6].lineBres();
		line[1].lineBres();
		line[2].lineBres();
		break;
	case 5:
		line[3].lineBres();
		line[4].lineBres();
		line[6].lineBres();
		line[1].lineBres();
		line[0].lineBres();
		break;
	case 6:
		line[3].lineBres();
		line[4].lineBres();
		line[6].lineBres();
		line[1].lineBres();
		line[0].lineBres();
		line[5].lineBres();
		break;
	case 7:
		line[3].lineBres();
		line[2].lineBres();
		line[1].lineBres();
		break;
	case 8:
		line[0].lineBres();
		line[1].lineBres();
		line[2].lineBres();
		line[3].lineBres();
		line[4].lineBres();
		line[5].lineBres();
		line[6].lineBres();
		break;
	case 9:
		line[0].lineBres();
		line[1].lineBres();
		line[2].lineBres();
		line[3].lineBres();
		line[4].lineBres();
		line[6].lineBres();
		break;
	}
	glFlush();
}
//移动并显示一位数字
//void eightLight::posNum(Point vec,int num){
//	Matrix3x3 tr;
//	tr.setTrM(vec.X,vec.Y);
//	Matrix3x1 m;
//	for(int i=0;i<6;i++){
//		m.setAllElem2(sixQue[i]);
//		sixQue[i]=(tr * m).getPoint();
//	}
//	showNum(num);
//}

//void eightLight::showMoreNum(int num){
//	/*static int lastNum=0;
//	static Point lastPos;
//	int rem;*/
//	showNum(8);
//	if(lastNum==num){	//如果数字和上一次调用的时候数字一样
//		showNum(num);
//		return;
//	}else{		//如果数字不一样，我就重新绘制数字
//		lastNum=num;
//		lastPos=position;
//		showNum(num);
//	}
//}

eightLight::eightLight(int x,int y){
	Point sixQue[6];
	Point P;
	P.X=2;P.Y=2;
	sixQue[0]=P;
	P.X=2;P.Y=10;
	sixQue[1]=P;
	P.X=2;P.Y=18;
	sixQue[2]=P;
	P.X=10;P.Y=2;
	sixQue[3]=P;
	P.X=10;P.Y=10;
	sixQue[4]=P;
	P.X=10;P.Y=18;
	sixQue[5]=P;
	
	//setPosition(380,0);

	position.X=x;
	position.Y=y;
	Matrix3x3 tr;
	tr.setTrM(position.X,position.Y);//构造平移矩阵
	Matrix3x1 m;
	//将七段数码管的六个端点平移x,y
	for(int i=0;i<6;i++){
		m.setAllElem2(sixQue[i]);
		sixQue[i]=(tr * m).getPoint(); //平移到了position的位置，position可以由参数修改
	}
	//设置线对象的端点,是平移之后的的线
	line[0].setEnthPoint(sixQue[0],sixQue[3]);
	line[1].setEnthPoint(sixQue[3],sixQue[4]);
	line[2].setEnthPoint(sixQue[4],sixQue[5]);
	line[3].setEnthPoint(sixQue[5],sixQue[2]);
	line[4].setEnthPoint(sixQue[1],sixQue[2]);
	line[5].setEnthPoint(sixQue[0],sixQue[1]);
	line[6].setEnthPoint(sixQue[1],sixQue[4]);


}




//这一段已经全部包含在构造函数中了，不知道为什么单独写不行

//默认的x=380,y=0   最后设置的结果是七段线，但未显示，已经移动过了
void eightLight::setPosition(int x,int y){
	position.X=x;
	position.Y=y;
	Matrix3x3 tr;
	tr.setTrM(position.X,position.Y);//构造平移矩阵
	Matrix3x1 m;
	//将七段数码管的六个端点平移x,y
	for(int i=0;i<6;i++){
		m.setAllElem2(sixQue[i]);
		sixQue[i]=(tr * m).getPoint(); //平移到了position的位置，position可以由参数修改
	}
	//设置线对象的端点,是平移之后的的线
	line[0].setEnthPoint(sixQue[0],sixQue[3]);
	line[1].setEnthPoint(sixQue[3],sixQue[4]);
	line[2].setEnthPoint(sixQue[4],sixQue[5]);
	line[3].setEnthPoint(sixQue[5],sixQue[2]);
	line[4].setEnthPoint(sixQue[1],sixQue[2]);
	line[5].setEnthPoint(sixQue[0],sixQue[1]);
	line[6].setEnthPoint(sixQue[1],sixQue[4]);
}