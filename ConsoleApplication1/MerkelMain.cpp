#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Candlestick.h"
#include <cmath>

MerkelMain::MerkelMain()
{

}
/*tutor's work*/
void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    //student's work*/
    currentTimeMinusOne = orderBook.getEarliestTimeMinusOne();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);

    }
}

/*tutor's work*/
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;
    //student's work
    // 7 create statistic tables and graphs
    std::cout << "7: Print stats tables and graphs " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}
/*tutor's work*/
void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}
/*tutor's work*/
void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
}
/*tutor's work*/
void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }
}
/*tutor's work*/
void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }
    }
}
/*tutor's work*/
void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
/*tutor's work*/
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }

    }
    //new assignment
    currentTimeMinusOne = currentTime;
    currentTime = orderBook.getNextTime(currentTime);

}

/*new function by student which builds the data required to calculate the tables and graphs / charts, and then calls them as separate functions.*/
void MerkelMain::statsTableAndGraphData()
{

    std::string currencyInput;
    std::string chosenCurrency;
    std::string AskOrBidInput;
    bool chosenAskOrBid;

    //changing currencies
    printCurrencyOptionMenu();
    currencyInput = getUserCurrencyOption();
    chosenCurrency = processUserCurrencyOption(currencyInput);
    //changing ask or bid
    printBidsOrAsksOptionMenu();
    AskOrBidInput = getUserCurrencyOption();
    chosenAskOrBid = processUserAskOrBidOption(AskOrBidInput);

    //getting current, previous and next times for the candlestick class vector object that is to be made
    std::vector<std::string> graphTimeSlots;
    std::vector<std::string> graphTimeSlotsForOpen;

    nextTime = orderBook.getNextTime(currentTime);

    graphTimeSlots.push_back(currentTime);
    graphTimeSlotsForOpen.push_back(currentTimeMinusOne);
    graphTimeSlotsForOpen.push_back(currentTime);

    for (int i = 0; i < 6; ++i)
    {
        graphTimeSlots.push_back(nextTime);
        graphTimeSlotsForOpen.push_back(nextTime);
        nextTime = orderBook.getNextTime(nextTime);
    }
    graphTimeSlots.push_back(nextTime);

    //initialising vectors that will be placed in candlestick class vector object
    std::vector<double>maxAskVector;
    std::vector<double>minAskVector;
    std::vector<double>openVector;
    std::vector<double>closeVector;
    std::vector<int>highFrequencyVector;
    std::vector<int>lowFrequencyVector;

    //getting the data through iteration for these vectors and pushing them back
    for (int i = 0; i < 8; i++)
    {
        std::vector<OrderBookEntry> entries;
        std::vector<OrderBookEntry> entriesOpen;
        if (chosenAskOrBid == true)
        {
            entries = orderBook.getOrders(OrderBookType::ask,chosenCurrency, graphTimeSlots[i]);
            entriesOpen = orderBook.getOrders(OrderBookType::ask, chosenCurrency, graphTimeSlotsForOpen[i]);
        }
        if (chosenAskOrBid == false)
        {
            entries = orderBook.getOrders(OrderBookType::bid, chosenCurrency, graphTimeSlots[i]);
            entriesOpen = orderBook.getOrders(OrderBookType::bid, chosenCurrency, graphTimeSlotsForOpen[i]);
        }
        maxAskVector.push_back(OrderBook::getHighPrice(entries));
        minAskVector.push_back(OrderBook::getLowPrice(entries));
        closeVector.push_back(OrderBook::getClosePrice(entries));
        openVector.push_back(OrderBook::getOpenPrice(entriesOpen));
        highFrequencyVector.push_back(OrderBook::getPriceHighFrequency(entries));
        lowFrequencyVector.push_back(OrderBook::getPriceLowFrequency(entries));

        //then iterating over the vectors and pushing them to the Candlestick class object 'graphDataObj'
        graphDataObj.push_back(Candlestick{ graphTimeSlots[i],
                                        openVector[i],
                                        maxAskVector[i],
                                        minAskVector[i],
                                        closeVector[i],
                                        highFrequencyVector[i],
                                        lowFrequencyVector[i] });

    }
    //calling the table / graph functions

    drawStatsTable();
    drawCandlestickGraph();
    frequencyGraph();
    //clearing timeslots and graphDataObj ready for any changes the user makes
    graphTimeSlots.clear();
    graphTimeSlotsForOpen.clear();
    graphDataObj.clear();
}
/*new function by student to print a statistical table for part 1 of the assignment*/
void MerkelMain::drawStatsTable()
{
    //printing out column headers
    std::cout << std::setw(26) << "Date/Time"
        << "|" << std::setw(15) << "Open"
        << "|" << std::setw(15) << "High"
        << "|" << std::setw(15) << "Low"
        << "|" << std::setw(15) << "Close"
        << std::endl;
    std::cout << std::setfill('-') << std::setw(90) << "-" << std::endl;
    std::cout << std::setfill(' ');
    //iterating through graphDataObj to print out statistical table
    for (int i = 0; i < 8; ++i)
    {
        std::cout << std::setw(26) << graphDataObj[i].times
        << "|" << std::setw(15) << std::setprecision(6) << graphDataObj[i].open
        << "|" << std::setw(15) << std::setprecision(6) << graphDataObj[i].maxAsk
        << "|" << std::setw(15) << std::setprecision(6) << graphDataObj[i].minAsk
        << "|" << std::setw(15) << std::setprecision(6) << graphDataObj[i].close
        << std::endl << std::endl;
    }
}
/*new function by student to print a candlestick graph for part 2 of the assignment*/
void MerkelMain::drawCandlestickGraph()
{
    double maxBin = 0;
    double minBin = graphDataObj[0].minAsk;
    double binIncr;
    double nextPriceIncr;
    //creating the correct increments for the y axis
    std::vector<double> priceIncrVec;
    for (int g = 0; g < 8; ++g)
    {
        if (graphDataObj[g].maxAsk > maxBin)
        {
            maxBin = graphDataObj[g].maxAsk;
        }

        if (graphDataObj[g].minAsk < minBin)
        {
            minBin = graphDataObj[g].minAsk;
        }
    }
    binIncr = (maxBin - minBin) / 30;
    nextPriceIncr = maxBin + binIncr;
    priceIncrVec.push_back(nextPriceIncr);

    for (int h = 0; h < 32; ++h)
    {
        nextPriceIncr = nextPriceIncr - binIncr;
        priceIncrVec.push_back(nextPriceIncr);
    }
    //printing out title and key
    std::cout << std::endl << std::setw(75) << "Candlestick Graph " << std::endl << std::endl;
    std::cout << std::setw(14) << " Key " << std::endl;
    std::cout << std::setfill('-') << std::setw(14) << "-" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setw(14) << " [+] = Open" << std::endl;
    std::cout << std::setw(14) << " [-] = Close" << std::endl << std::endl;

    //iterating over each priceIncrVec and graphDataObj to create a set of 8 candlesticks
    for (int i = 0; i < 32; ++i)
    {

        std::cout << std::setw(14) << priceIncrVec[i] << " | ";

        for (int j = 0; j < 8; ++j)
        {
            if (priceIncrVec[i] > graphDataObj[j].open && priceIncrVec[i + 1] <= graphDataObj[j].open )
            {
                std::cout << std::setw(13) << " [+] ";
            }
            else if (priceIncrVec[i] > graphDataObj[j].close && priceIncrVec[i + 1] <= graphDataObj[j].close)
            {
                std::cout << std::setw(13) << " [-] ";
            }

            else if (priceIncrVec[i + 1] < graphDataObj[j].maxAsk && priceIncrVec[i] >= graphDataObj[j].maxAsk)
            {
                std::cout << std::setw(13) << " -*- ";
            }
            else if (priceIncrVec[i] > graphDataObj[j].minAsk && priceIncrVec[i + 1] <= graphDataObj[j].minAsk)
            {
                std::cout << std::setw(13) << " -*- ";
            }
            else if (priceIncrVec[i] < graphDataObj[j].close && priceIncrVec[i] >= graphDataObj[j].open)
            {
                std::cout << std::setw(13) << " | | ";
            }
            else if (priceIncrVec[i] < graphDataObj[j].open && priceIncrVec[i] >= graphDataObj[j].close)
            {
                std::cout << std::setw(13) << " | | ";
            }
            else if (priceIncrVec[i] < graphDataObj[j].maxAsk && priceIncrVec[i] >= graphDataObj[j].minAsk)
            {
                std::cout << std::setw(13) << "  |  ";
            }
            else std::cout << std::setw(13) << "     ";
        }
        std::cout << std::endl;
    }
    //printing the data for the x axis
    std::cout << std::setfill('-') << std::setw(140) << "-" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setw(21) << "  ";
    for (int i = 0; i < 8; i++)
    {
        graphDataObj[i].times.erase(0, 11);
        graphDataObj[i].times.erase(graphDataObj[i].times.end() - 7, graphDataObj[i].times.end());
        std::cout << std::setw(10) << graphDataObj[i].times << " | ";
    }
    std::cout << std::endl;
}
/*new function by student to print a frequency graph / chart for part 3 of the assignment*/
void MerkelMain::frequencyGraph()
{
    double maxBin = graphDataObj[0].highFreq;
    double minBin = graphDataObj[0].lowFreq;
    double binIncr;
    double nextFreqIncr;
    //creating the correct increments for the y axis
    std::vector<double> freqIncrVec;
    for (int g = 0; g < 8; ++g)
    {
        if (graphDataObj[g].highFreq > maxBin)
        {
            maxBin = graphDataObj[g].highFreq;
        }

        if (graphDataObj[g].lowFreq > minBin)
        {
            minBin = graphDataObj[g].lowFreq;
        }
    }

    if (maxBin > minBin)
    {
        binIncr = maxBin / 15;
    }
    else binIncr = minBin / 15;

    nextFreqIncr = maxBin + binIncr;
    freqIncrVec.push_back(nextFreqIncr);
    //printing out title
    std::cout << std::endl << std::setw(100) << " Frequency Graph/Chart Of Positive vs Negative Requests In Comparison To Average Price Within Each Time Period " << std::endl << std::endl;

    for (int h = 0; h < 16; ++h)
    {
        nextFreqIncr = nextFreqIncr - binIncr;
        freqIncrVec.push_back(nextFreqIncr);
    }

    for (int i = 0; i < 16; ++i)
    {
        std::cout << std::setw(20) << floor(freqIncrVec[i]) << " | ";
        for (int j = 0; j < 8; ++j)
        {

            if (graphDataObj[j].highFreq <= freqIncrVec[i] && graphDataObj[j].highFreq > freqIncrVec[i + 1])
            {
                std::cout << std::setw(13) << " ----- ";
            }
            else if (graphDataObj[j].highFreq > freqIncrVec[i])
            {
                std::cout << std::setw(13) << " |-+-| ";
            }
            else std::cout << std::setw(13) << "       ";
        }
        std::cout << std::endl;
    }

    std::cout << std::setw(20) << " Average (At Close) " << std::setfill('-') << std::setw(140) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (int h = 16; h < 32; ++h)
    {
        nextFreqIncr = nextFreqIncr - binIncr;
        freqIncrVec.push_back(nextFreqIncr);
    }

    for (int i = 16; i < 32; ++i)
    {
        std::cout << std::setw(20) << floor(freqIncrVec[i]) << " | ";
        for (int j = 0; j < 8; ++j)
        {

            if (-(graphDataObj[j].lowFreq) <= freqIncrVec[i] && -(graphDataObj[j].lowFreq) > freqIncrVec[i + 1])
            {
                std::cout << std::setw(13) << " ----- ";
            }
            else if (-(graphDataObj[j].lowFreq) < freqIncrVec[i])
            {
                std::cout << std::setw(13) << " |---| ";
            }
            else std::cout << std::setw(13) << "       ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    //printing the data for the x axis
    std::cout << std::setfill('-') << std::setw(140) << "-" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setw(26) << "  ";
    for (int i = 0; i < 8; i++)
    {
        std::cout << std::setw(10) << graphDataObj[i].times << " | ";
    }
    std::cout << std::endl;
}
/*tutor's work*/
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-7" << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        // 
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

/*new function by student*/
std::string MerkelMain::getUserCurrencyOption()
{
    std::string line;
    std::getline(std::cin, line);
    std::cout << "You chose: " << line << std::endl;
    return line;
}
/*tutor's work*/
void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-7" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    if (userOption == 7)
    {
        statsTableAndGraphData();
    }
}
/*new function returning string by student to choose the currency for the graph*/
std::string MerkelMain::processUserCurrencyOption(std::string userCurrencyOption)
{
    std::string chosenOption;

    if (userCurrencyOption == "a")
    {
        std::cout << "You have chosen ETH/BTC" << std::endl;
        chosenOption = "ETH/BTC";
    }
    if (userCurrencyOption == "b")
    {
        std::cout << "You have chosen DOGE/BTC" << std::endl;
        chosenOption = "DOGE/BTC";
    }
    if (userCurrencyOption == "c")
    {
        std::cout << "You have chosen BTC/USDT" << std::endl;
        chosenOption = "BTC/USDT";
    }
    if (userCurrencyOption == "d")
    {
        std::cout << "You have chosen ETH/USDT" << std::endl;
        chosenOption = "ETH/USDT";
    }
    if (userCurrencyOption == "e")
    {
        std::cout << "You have chosen DOGE/USDT" << std::endl;
        chosenOption = "DOGE/USDT";
    }
    return chosenOption;
}
/*new function return boolean by student to choose ask or bid when building the graph*/
bool MerkelMain::processUserAskOrBidOption(std::string userCurrencyOption)
{
    if (userCurrencyOption == "f")
    {
        std::cout << "You have chosen ask" << std::endl;
        return true;
    }
    if (userCurrencyOption == "g")
    {
        std::cout << "You have chosen bid" << std::endl;
        return false;
    }
}
/*new function by student to print a currency menu when building the graph data*/
void MerkelMain::printCurrencyOptionMenu()
{
    std::cout << "type a-e for specific currency data within table." << std::endl;

    std::cout << "a: ETH / BTC " << std::endl;

    std::cout << "b: DOGE / BTC" << std::endl;

    std::cout << "c: BTC / USDT " << std::endl;

    std::cout << "d: ETH / USDT " << std::endl;

    std::cout << "e: DOGE / USDT " << std::endl;
}
/*new function by student to print a bid or ask menu when building the graph data*/
void MerkelMain::printBidsOrAsksOptionMenu()
{
    std::cout << "type f for ask version or g for bid version within the table." << std::endl;

    std::cout << "f: ask " << std::endl;

    std::cout << "g: bid " << std::endl;
}