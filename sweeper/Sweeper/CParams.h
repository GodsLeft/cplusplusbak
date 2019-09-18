#ifndef CPARAMS_H
#define CPARAMS_H

#include <fstream>
#include <windows.h>

using namespace std;

class CParams{
public:
	static double dPi;
	static double dHalfPi;
	static double dTwoPi;

	static int	WindowWidth;
	static int	WindowHeight;

	static int	iFramesPerSecond;

	//神经网络
	static int	iNumInputs;
	static int	iNumHidden;
	static int	iNeuronsPerHiddenLayer;
	static int	iNumOutputs;

	static double	dActivationResponse;
	static double	dBias;

	static double dMaxTurnRate;	//限制扫雷车旋转速度
	static double dMaxSpeed;
	static int	  iSweeperScale;

	static int		iNumSweepers;
	static int		iNumMines;

	static int		iNumTicks;	//每一代生存的时间
	static double	dMineScale;

	//遗传算法参数
	static double	dCrossoverRate;
	static double	dMutationRate;

	static double	dMaxPerturbation;

	static int		iNumElite;			//上一代中的精英的个数（指定的）
	static int		iNumCopiesElite;	//要保存的上一代精英的个数

	CParams(){
		if(!LoadInParameters("params.ini")){
			MessageBox(NULL, "Cannot find ini file!", "Error", 0);
		}
	}
	
	bool LoadInParameters(char* szFileName);
};

#endif