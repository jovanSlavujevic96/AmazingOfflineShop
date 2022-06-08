#include <iomanip>
#include <climits>
#include <cstdint>
#include <cmath>

#include "ProcessedOrders.h"

#define PROC_ORDERS_NUM_OF_COLS 6
#define DECIMAL_DIGITS 3 /* i.e. ".00" */
#define COLS_MIN_DISTANCE 5
#define PROD_NAME_MAX_LEN 20
#define PERCENT_MAX_LEN 6
#define PRICE_MAX_LEN 9
#define AMOUNT_MAX_LEN 9

/**
 * @brief Function which generates string with specified amount of spaces and vertial bar (optionally)
 *
 * @param[in] amount - amount of spaces
 * @param[in] veritcal_bar_postition - pointer to position of vertical bar within string (optional/nullable)
 * @return std::string - generated string
 */
static std::string generateWhiteSpaces(size_t amount, size_t* veritcal_bar_postition = nullptr);
/**
 * @brief Coutns number of digits within particular number
 *
 * @param[in] number - digit to be compared
 * @return size_t - number of digits
 */
static size_t count_digit(int number);

bool ProcessedOrder::operator==(const ProcessedOrder& other) const
{
    if (this->discountPercent != other.discountPercent)
    {
        return false;
    }
    else if (this->finalPrice != other.finalPrice)
    {
        return false;
    }
    else if (this->priceWoDiscount != other.priceWoDiscount)
    {
        return false;
    }
    else if (this->quantity != other.quantity)
    {
        return false;
    }
    else if (this->taxPercent != other.taxPercent)
    {
        return false;
    }
    return true;
}

ProcessedOrders::ProcessedOrders() :
    mTotal{0},
    mOrderNum{0}
{

}

/**
* Name            Tax   Disc.  U.price  Quant.  Price
* ---------------------------------------------------
* Fairy Dust	  8.80 	 0.00     4.99   3.00   14,97
* Helping Hand	 12.00 	30.00   699.99   1.00  489.99
* Freezing Coat  12.00 	15.00   124.99   1.00   87.49
* ---------------------------------------------------
* Total                                        592.45
**/
void ProcessedOrders::operator>>(std::ofstream& writer) noexcept(false)
{
    size_t whitespaces;
    size_t veritcal_bar_pos;
    std::string name;

    if (mProcessedOrders.empty())
    {
        throw std::runtime_error("Didn't processed any order yet.");
    }

    // set fixed decimal precision print
    writer << std::fixed << std::setprecision(2);

    // enter table header
    writer << "Order #" << mOrderNum << std::endl;
    writer << "------------------------------------------------------------------------------------" << std::endl;
    writer << "Name                  |     Tax  |   Disc.  |    U.price  |     Quant.  |      Price" << std::endl;
    writer << "------------------------------------------------------------------------------------" << std::endl;

    for (auto it = mProcessedOrders.cbegin(); it != mProcessedOrders.cend(); it++)
    {
        // assign name
        name = it->first;
        if (name.length() > PROD_NAME_MAX_LEN)
        {
            // if name has length bigger than 20 make it shorter
            // i.e. "Very Long Name Of Prodcut" => "Very Long Name Of..."
            name = name.substr(0, PROD_NAME_MAX_LEN - 3) + "...";
        }
        // append item name to discount
        writer << name;

        veritcal_bar_pos = PROD_NAME_MAX_LEN - name.length();
        whitespaces = veritcal_bar_pos + COLS_MIN_DISTANCE + PERCENT_MAX_LEN - count_digit((int)it->second.taxPercent) - DECIMAL_DIGITS;
        veritcal_bar_pos += 2;
        // append item tax percent
        writer << generateWhiteSpaces(whitespaces, &veritcal_bar_pos) << it->second.taxPercent;

        veritcal_bar_pos = 2;
        whitespaces = COLS_MIN_DISTANCE + PERCENT_MAX_LEN - count_digit((int)it->second.discountPercent) - DECIMAL_DIGITS;
        // append item discount percent
        writer << generateWhiteSpaces(whitespaces, &veritcal_bar_pos) << it->second.discountPercent;

        whitespaces = COLS_MIN_DISTANCE + PRICE_MAX_LEN - count_digit((int)it->second.priceWoDiscount) - DECIMAL_DIGITS;
        // append item price wo discount
        writer << generateWhiteSpaces(whitespaces, &veritcal_bar_pos) << it->second.priceWoDiscount;

        whitespaces = COLS_MIN_DISTANCE + AMOUNT_MAX_LEN - count_digit((int)it->second.quantity) - DECIMAL_DIGITS;
        // append item quantity
        writer << generateWhiteSpaces(whitespaces, &veritcal_bar_pos) << it->second.quantity;

        whitespaces = COLS_MIN_DISTANCE + PRICE_MAX_LEN - count_digit((int)it->second.finalPrice) - DECIMAL_DIGITS;
        // append item final price
        writer << generateWhiteSpaces(whitespaces, &veritcal_bar_pos) << it->second.finalPrice << std::endl;
    }

    writer << "------------------------------------------------------------------------------------" << std::endl;
    whitespaces = 70 + PRICE_MAX_LEN - count_digit(mTotal) - DECIMAL_DIGITS;
    // write total price
    writer << "Total" << generateWhiteSpaces(whitespaces) << mTotal;
}

void ProcessedOrders::processOrder(const Orders* initialOrders, const  Items* items, const  Discounts* discounts) noexcept(false)
{
    std::map<uint64_t, Order>::const_iterator orderBegin;
    std::map<uint64_t, Order>::const_iterator orderEnd;
    const Item* currentItem;
    const Discount* currentDiscount;
    ProcessedOrder* procOrder;

    if (!initialOrders || !items)
    {
        throw std::runtime_error("orders & items can't be NULL.");
    }

    mProcessedOrders.clear();
    mTotal = 0;

    orderBegin = initialOrders->getOrdersBegin();
    orderEnd = initialOrders->getOrdersEnd();

    for (auto it = orderBegin; it != orderEnd; it++)
    {
        // get current item
        currentItem = items->getItem(it->first);
        if (!currentItem)
        {
            throw std::runtime_error("can't find order within items.");
        }

        // get discount
        currentDiscount = (discounts) ? discounts->getDiscount(it->first) : nullptr;

        // insert map element with key
        procOrder = &mProcessedOrders.insert(std::make_pair(currentItem->name, ProcessedOrder())).first->second;

        // get tax percentage from current item
        procOrder->taxPercent = currentItem->taxPercent;

        // get discount percentage from discounts
        procOrder->discountPercent = (currentDiscount) ? currentDiscount->discountPercent : 0;

        // get quantity from current order
        procOrder->quantity = it->second.quantity;

        // calculate price without discount
        // PRICE WO DISCOUNT = PRICE WO TAX * (1 + TAX PERCENT / 100) * QUANTITY
        procOrder->priceWoDiscount = currentItem->priceWoTax * (1.0f + currentItem->taxPercent/100) * procOrder->quantity;

        // calculate final price
        // TOTAL PRICE = PRICE WO DISCOUNT * (1 - DISCOUNT PERCENT / 100)
        procOrder->finalPrice = procOrder->priceWoDiscount * (1.0f - procOrder->discountPercent / 100);

        mTotal += procOrder->finalPrice;
    }
    mOrderNum = initialOrders->getOrderNum();
}

static std::string generateWhiteSpaces(size_t amount, size_t* veritcal_bar_postition)
{
    std::string ret = "";
    for (size_t i = 0; i < amount; i++)
    {
        if (veritcal_bar_postition && i == *veritcal_bar_postition)
        {
            ret += "|";
            continue;
        }
        ret += " ";
    }
    return ret;
}

static size_t count_digit(int number)
{
    if (number)
    {
        return size_t(log10(number) + 1);
    }
    return 1;
}
