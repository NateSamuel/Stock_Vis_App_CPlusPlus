#include "CandlestickDraw.h"
#include "Candlestick.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

CandlestickDraw::CandlestickDraw()
{

}
void CandlestickDraw::getTableData(std::vector<std::string>times1,
	std::vector<double>open1,
	std::vector<double>maxAsk1,
	std::vector<double>minAsk1,
	std::vector<double>close1)
{

	std::cout << "candlestick stat table is working " << std::endl;
	std::cout << std::setw(26) << "Date/Time"
		<< "|" << std::setw(15) << "Open"
		<< "|" << std::setw(15) << "High"
		<< "|" << std::setw(15) << "Low"
		<< "|" << std::setw(15) << "Close"
		<< std::endl;
	std::cout << std::setfill('-') << std::setw(90) << "-" << std::endl;
	std::cout << std::setfill(' ');
	for (int i = 0; i < 5; ++i)
	{
		std::cout << std::setw(26) << times1[i]
			<< "|" << std::setw(15) << std::setprecision(6) << open1[i]
			<< "|" << std::setw(15) << std::setprecision(6) << maxAsk1[i]
			<< "|" << std::setw(15) << std::setprecision(6) << minAsk1[i]
			<< "|" << std::setw(15) << std::setprecision(6) << close1[i]
			<< std::endl << std::endl;
	}
}
void CandlestickDraw::drawCandlestickGraph(std::vector<std::string> times1,
	std::vector<double>open1,
	std::vector<double>maxAsk1,
	std::vector<double>minAsk1,
	std::vector<double>close1)
{
	double maxBin = 0;
	double minBin = minAsk1[0];
	double binIncr;
	double nextPriceIncr;

	std::vector<double> priceIncrVec;
	for (int g = 0; g < 5; ++g)
	{
		if (maxAsk1[g] > maxBin)
		{
			maxBin = maxAsk1[g];
		}

		if (minAsk1[g] < minBin)
		{
			minBin = minAsk1[g];
		}
	}
	binIncr = (maxBin - minBin) / 20;
	nextPriceIncr = maxBin;
	priceIncrVec.push_back(nextPriceIncr);

	for (int h = 0; h < 21; ++h)
	{
		nextPriceIncr = nextPriceIncr - binIncr;
		priceIncrVec.push_back(nextPriceIncr);
	}

	for (int i = 0; i < 21; ++i)
	{

		std::cout << priceIncrVec[i] << " | ";
		for (int j = 0; j < 5; ++j)
		{
			if (priceIncrVec[i] > open1[j] && priceIncrVec[i + 1] < open1[j])
			{
				std::cout << " --- ";
			}
			if (priceIncrVec[i] > maxAsk1[j] && priceIncrVec[i + 1] < maxAsk1[j])
			{
				std::cout << " -*- ";
			}
			if (priceIncrVec[i] > minAsk1[j] && priceIncrVec[i + 1] < minAsk1[j])
			{
				std::cout << " -*- ";
			}
			if (priceIncrVec[i] > close1[j] && priceIncrVec[i + 1] < close1[j])
			{
				std::cout << " --- ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::setw(26) << " | " << std::endl;
	std::cout << std::setw(13);
	for (int i = 0; i < 5; i++)
	{
		times1[i].erase(0, 11);
		times1[i].erase(times1[i].end() - 7, times1[i].end());
		std::cout << std::setw(13) << times1[i] << " | ";
	}
	std::cout << std::endl;
}