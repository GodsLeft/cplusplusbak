#ifndef CTIMER_H
#define CTIMER_H

#include <windows.h>

class CTimer{
private:
	LONGLONG	m_CurrentTime,
				m_LastTime,
				m_NextTime,
				m_FrameTime,	//每游戏帧有多少机器周期？
				m_PerfCountFreq;//机器频率

	double		m_TimeElapsed,
				m_TimeScale;

	float		m_FPS;

public:
	CTimer();
	CTimer(float fps);

	void	Start();
	bool	ReadyForNextFrame();
	double	GetTimeElapsed(){return m_TimeElapsed;}
	double	TimeElapsed();
};

#endif