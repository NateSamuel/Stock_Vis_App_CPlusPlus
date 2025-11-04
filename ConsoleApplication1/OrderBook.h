#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
/*tutor's work*/
class OrderBook
{
public:
    /** construct, reading a csv data file */
    OrderBook(std::string filename);
    /** return vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();
    /** return vector of all known timestamps in the dataset*/
    std::vector<std::string> getKnownTimestamps();
    /** return vector of Orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
        std::string product,
        std::string timestamp);

    /** returns the earliest time in the orderbook*/
    std::string getEarliestTime();
    std::string getEarliestTimeMinusOne();
    /** returns the next time after the
     * sent time in the orderbook
     * If there is no next timestamp, wraps around to the start
     * */
    std::string getNextTime(std::string timestamp);
    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    /*student's work*/
    static double getOpenPrice(std::vector<OrderBookEntry>& orders);
    static double getClosePrice(std::vector<OrderBookEntry>& orders);
    static int getPriceHighFrequency(std::vector<OrderBookEntry>& orders);
    static int getPriceLowFrequency(std::vector<OrderBookEntry>& orders);

private:
    std::vector<OrderBookEntry> orders;


};