#ifndef CTIMER_H
#define CTIMER_H

#include <windows.h>

class CTimer{
private:
	LONGLONG	m_CurrentTime,
				m_LastTime,
				m_NextTime,
				m_FrameTime,
				m_PerfCountFreq;

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