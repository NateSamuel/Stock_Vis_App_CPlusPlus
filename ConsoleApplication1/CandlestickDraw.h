#pragma once
#include <vector>
#include <string>

class CandlestickDraw
{
public:
	CandlestickDraw();

	void getTableData(std::vector<std::string> times1, std::vector<double>open1, std::vector<double>maxAsk1,
		std::vector<double>minAsk1, std::vector<double>close1);

	void drawCandlestickGraph(std::vector<std::string> times1,
		std::vector<double>open1,
		std::vector<double>maxAsk1,
		std::vector<double>minAsk1,
		std::vector<double>close1);


};
