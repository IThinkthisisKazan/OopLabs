#include "CTVSet.h"
#include <iostream>

using namespace std;


void CTVSet::TurnOn() 
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}


bool CTVSet::SelectChannel(int channel)
{
	if (!m_isOn)
	{
		return false;
	}
	if ((channel >= m_minChannel && channel <= m_maxChannel))
	{
		m_prevChannel = m_currChannel;
		m_currChannel = channel;
		return true;
	}
	return false;
}


int CTVSet::GetChannel() const 
{
	if(m_isOn)
	{
		return m_currChannel;
	}
	return 0;
}

bool CTVSet::IsTurnedOn() const 
{
	return m_isOn;
}

void CTVSet::SelectPreviousChannel() 
{
	if (m_isOn && m_prevChannel != 0)
	{
		swap(m_currChannel , m_prevChannel);
	}
}