/* 
In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
*/

#include "UsefulFunctions.h"

enum UKCoin
{ // 8 types of coin
    coin_1p,
    coin_2p,
    coin_5p,
    coin_10p,
    coin_20p,
    coin_50p,
    coin_1P,
    coin_2P
};

class CoinPouch
{
public:
    int m_total{0};
    int m_num_1p{0};
    int m_num_2p{0};
    int m_num_5p{0};
    int m_num_10p{0};
    int m_num_20p{0};
    int m_num_50p{0};
    int m_num_1P{0};
    int m_num_2P{0};

    CoinPouch() = default;

    CoinPouch(std::initializer_list<UKCoin> list)
    {
        for (auto coin : list)
            *this += coin;
        calcTotal();
    }

    void operator+=(UKCoin coin)
    {
        switch (coin)
        {
        case coin_1p:
            m_num_1p += 1;
            break;
        case coin_2p:
            m_num_2p += 1;
            break;
        case coin_5p:
            m_num_5p += 1;
            break;
        case coin_10p:
            m_num_10p += 1;
            break;
        case coin_20p:
            m_num_20p += 1;
            break;
        case coin_50p:
            m_num_50p += 1;
            break;
        case coin_1P:
            m_num_1P += 1;
            break;
        case coin_2P:
            m_num_2P += 1;
            break;

        default:
            break;
        }
        calcTotal();
    }
    void calcTotal()
    {
        m_total =
            1 * m_num_1p +
            2 * m_num_2p +
            5 * m_num_5p +
            10 * m_num_10p +
            20 * m_num_20p +
            50 * m_num_50p +
            100 * m_num_1P +
            200 * m_num_2P;
    }
    int getPence()
    {
        return m_total;
    }

    void checkCoinOverflow()
    {
        if (m_num_1p > 200)
        {
            m_num_1p = 0;
            m_num_2p += 1;
        }
        if (m_num_2p > 100)
        {
            m_num_2p = 0;
            m_num_5p += 1;
        }
        if (m_num_5p > 40)
        {
            m_num_5p = 0;
            m_num_10p += 1;
        }
        if (m_num_10p > 20)
        {
            m_num_10p = 0;
            m_num_20p += 1;
        }
        if (m_num_20p > 10)
        {
            m_num_20p = 0;
            m_num_50p += 1;
        }
        if (m_num_50p > 4)
        {
            m_num_50p = 0;
            m_num_1P += 1;
        }
        if (m_num_1P > 2)
        {
            m_num_1P = 0;
            m_num_2P += 1;
        }
        if (m_num_2P > 1)
        {
            // m_num_2P = 0;
            // m_num_1p += 1;
        }
        calcTotal();
    }

    void checkPouchOverflow()
    {
        // Check if there are more than 200p worth inside the pouch.
        if (m_total > 200)
        {
        }
        else
            return;
    }
};

void operator+=(UKCoin &coin_out, int num)
{
    // UKCoin has integer values 0 to 7 for each of its coin values coin_1p to coin_2P.
    int new_coin_num{static_cast<int>(coin_out) + num};
    // Over or underflow new_coin_num to be within the range ([0,7])
    new_coin_num %= 8;
    if (new_coin_num < 0)
        new_coin_num += 8;
    coin_out = static_cast<UKCoin>(new_coin_num);
}
void operator-=(UKCoin &coin_out, int num)
{
    coin_out += -num;
}
UKCoin operator++(UKCoin &coin_out)
{
    coin_out += 1;
    return coin_out;
}
UKCoin operator--(UKCoin &coin_out)
{
    coin_out -= 1;
    return coin_out;
}

void operator++(std::vector<UKCoin> &coin_list)
{
    uf::assertMsg(coin_list.size() > 0, "List empty");
    bool coin_overflow{false};
    if (coin_list[0] == coin_2P)
        coin_overflow = true;
    coin_list[0] += 1;
    int j{0};
    while (coin_overflow)
    {
        if (j == (coin_list.size() - 1))
        {
            coin_list.push_back(coin_1p);
            coin_overflow = false;
        }
        else
        {
            if (coin_list[j + 1] != coin_2P)
                coin_overflow = false;
            coin_list[j + 1] += 1;
        }
        ++j;
    }
}

int countPence(std::vector<UKCoin> coin_list)
{
    int coin_total{0};
    for (auto elem : coin_list)
    {
        switch (elem)
        {
        case coin_1p:
            coin_total += 1;
            break;
        case coin_2p:
            coin_total += 2;
            break;
        case coin_5p:
            coin_total += 5;
            break;
        case coin_10p:
            coin_total += 10;
            break;
        case coin_20p:
            coin_total += 20;
            break;
        case coin_50p:
            coin_total += 50;
            break;
        case coin_1P:
            coin_total += 100;
            break;
        case coin_2P:
            coin_total += 200;
            break;

        default:
            break;
        }
    }
    return coin_total;
}

int main()
{
    CoinPouch pouch;
    int combinations{0};
    while (pouch.m_num_2P < 2)
    {
        if (pouch.m_total < 200)
            pouch.m_num_1p += 200 - pouch.m_total;
        int coin_idx{0};
        while (pouch.m_total > 200)
        {
            switch (coin_idx++)
            {
            case 0:
                pouch.m_num_1p = 201;
                break;
            case 1:
                pouch.m_num_2p = 101;
                break;
            case 2:
                pouch.m_num_5p = 41;
                break;
            case 3:
                pouch.m_num_10p = 21;
                break;
            case 4:
                pouch.m_num_20p = 11;
                break;
            case 5:
                pouch.m_num_50p = 5;
                break;
            case 6:
                pouch.m_num_1P = 3;
                break;
            case 7:
                pouch.m_num_2P = 2;
                std::cout << combinations;
                return 0;
            default:
                break;
            }
            pouch.checkCoinOverflow();
        }
        pouch.checkCoinOverflow();

        if (pouch.getPence() == 200)
        {
            ++combinations;
            pouch.m_num_1p += 1;
            pouch.checkCoinOverflow();
        }

        if (pouch.m_num_2P == 2)
            std::cout << "";
    }
    return 0;
}