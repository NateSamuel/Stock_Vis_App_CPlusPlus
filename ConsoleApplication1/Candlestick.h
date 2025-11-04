#pragma once

#include <string>
/* student new class */
class Candlestick
{
public:
	Candlestick(std::string _times,
				double _open,
				double _maxAsk,
				double _minAsk,
				double _close,
				int _highFreq,
				int _lowFreq);

	std::string times;
	double open;
	double maxAsk;
	double minAsk;
	double close;
	int highFreq;
	int lowFreq;

};

