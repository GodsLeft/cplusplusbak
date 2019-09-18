#include "line.h";
//����λ��ֻ��ʾ���֣�λ���ɱ�ĺ���ָ��
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
//�ƶ�����ʾһλ����
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
//	if(lastNum==num){	//������ֺ���һ�ε��õ�ʱ������һ��
//		showNum(num);
//		return;
//	}else{		//������ֲ�һ�����Ҿ����»�������
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
	tr.setTrM(position.X,position.Y);//����ƽ�ƾ���
	Matrix3x1 m;
	//���߶�����ܵ������˵�ƽ��x,y
	for(int i=0;i<6;i++){
		m.setAllElem2(sixQue[i]);
		sixQue[i]=(tr * m).getPoint(); //ƽ�Ƶ���position��λ�ã�position�����ɲ����޸�
	}
	//�����߶���Ķ˵�,��ƽ��֮��ĵ���
	line[0].setEnthPoint(sixQue[0],sixQue[3]);
	line[1].setEnthPoint(sixQue[3],sixQue[4]);
	line[2].setEnthPoint(sixQue[4],sixQue[5]);
	line[3].setEnthPoint(sixQue[5],sixQue[2]);
	line[4].setEnthPoint(sixQue[1],sixQue[2]);
	line[5].setEnthPoint(sixQue[0],sixQue[1]);
	line[6].setEnthPoint(sixQue[1],sixQue[4]);


}




//��һ���Ѿ�ȫ�������ڹ��캯�����ˣ���֪��Ϊʲô����д����

//Ĭ�ϵ�x=380,y=0   ������õĽ�����߶��ߣ���δ��ʾ���Ѿ��ƶ�����
void eightLight::setPosition(int x,int y){
	position.X=x;
	position.Y=y;
	Matrix3x3 tr;
	tr.setTrM(position.X,position.Y);//����ƽ�ƾ���
	Matrix3x1 m;
	//���߶�����ܵ������˵�ƽ��x,y
	for(int i=0;i<6;i++){
		m.setAllElem2(sixQue[i]);
		sixQue[i]=(tr * m).getPoint(); //ƽ�Ƶ���position��λ�ã�position�����ɲ����޸�
	}
	//�����߶���Ķ˵�,��ƽ��֮��ĵ���
	line[0].setEnthPoint(sixQue[0],sixQue[3]);
	line[1].setEnthPoint(sixQue[3],sixQue[4]);
	line[2].setEnthPoint(sixQue[4],sixQue[5]);
	line[3].setEnthPoint(sixQue[5],sixQue[2]);
	line[4].setEnthPoint(sixQue[1],sixQue[2]);
	line[5].setEnthPoint(sixQue[0],sixQue[1]);
	line[6].setEnthPoint(sixQue[1],sixQue[4]);
}