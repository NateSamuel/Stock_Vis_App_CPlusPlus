#include "Candlestick.h"

#include <string>
/* New Class by student */
Candlestick::Candlestick(std::string _times,
						 double _open,
						 double _maxAsk,
						 double _minAsk,
						 double _close,
						 int _highFreq,
						 int _lowFreq)
	: times(_times),
	open(_open),
	maxAsk(_maxAsk),
	minAsk(_minAsk),
	close(_close),
	highFreq(_highFreq),
	lowFreq(_lowFreq)
{
	
}

