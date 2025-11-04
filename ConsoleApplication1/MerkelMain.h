#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "Candlestick.h"
/*tutor's work*/
class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();
    //student initialising vector<Candlestick> for part 1 task
    std::vector<Candlestick> graphDataObj;
private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    /*student initialising new item*/
    void statsTableAndGraphData();
    /*student initialising new item*/
    void drawStatsTable();
    /*student initialising new item*/
    void drawCandlestickGraph();
    /*student initialising new item*/
    void frequencyGraph();
    int getUserOption();
    /*student initialising new item*/
    std::string getUserCurrencyOption();
    void processUserOption(int userOption);
    /*student initialising new item*/
    std::string processUserCurrencyOption(std::string userCurrencyOption);
    /*student initialising new item*/
    bool processUserAskOrBidOption(std::string userCurrencyOption);
    /*student initialising new item*/
    void printCurrencyOptionMenu();
    /*student initialising new item*/
    void printBidsOrAsksOptionMenu();

    std::string currentTime;
    /*student initialising new item*/
    std::string currentTimeMinusOne;
    std::string nextTime;


    //OrderBook orderBook{"20200317.csv"};
    OrderBook orderBook{ "20200601.csv" };
    Wallet wallet;

};
