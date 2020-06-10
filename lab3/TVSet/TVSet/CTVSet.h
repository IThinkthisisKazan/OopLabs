#pragma once
#include <string>
#include <map>

class CTVSet
{
public:
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	int GetChannel() const;
	bool IsTurnedOn() const;
	void SelectPreviousChannel();

private:
	bool m_isOn = false;
	int m_currChannel = 1;
	int m_prevChannel = 0;
	static const int m_minChannel = 1;
	static const int m_maxChannel = 99;
};

