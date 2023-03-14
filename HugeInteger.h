#pragma once //compile once
#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <exception>

/* SHAKIR ALAM 400397108*/

class HugeInteger {
private:
    //private member num which stores the HugeInteger
    std::vector<int> num;
    //bool private member stores '-' sign
    bool minus;
    //negative operations
    HugeInteger negadd(const HugeInteger& val1, const HugeInteger& val2);
    HugeInteger negsubtract(const HugeInteger& value1, const HugeInteger& value2);
    int negcompare(const HugeInteger& h);


public:
    // Required methods
    HugeInteger() {
    num = {}; minus = true;}
    HugeInteger(const std::string& val);
    HugeInteger(int n);
    HugeInteger add(const HugeInteger& h);
    HugeInteger subtract(const HugeInteger& h);
    HugeInteger multiply(const HugeInteger& h);
    int compareTo(const HugeInteger& h);
    std::string toString();


};

#endif /* HUGEINTEGER_H_ */