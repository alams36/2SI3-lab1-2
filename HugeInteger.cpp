#ifndef HUGEINTEGER_H_
#include "HugeInteger.h"
#endif
using namespace std;

/* SHAKIR ALAM 400397108 alams36@mcmaster.ca */

HugeInteger::HugeInteger(const string& val) {
	//variable storing negative 
	int negative = 1;
	this->minus = true;
	//assign number_size to size of string
	int number_size = val.size();
	//bool storing negative check
	bool is_negative = (val[0] == '-' && number_size > 1);

	//check for minus sign
	if (is_negative && '1' <= val[1] && '9' >= val[1]) {
		this->minus = false;
		//check if size is greater than one and first value is between 1-9
	}
	else if (number_size > 1 && '1' <= val[0] && '9' >= val[0]) {
		negative = 0;
		//if number is 0
	}
	else if (number_size == 1 && ('0' <= val[0])) {
		negative = 0;
	}
	else {
		//throw as invalid
		throw invalid_argument("Error: invalid number.");
	}

	//iterate through each non-zero element in string
	for (int i = val.size() - 1; i >= negative; i--) {
		//if not in range [0-9]
		if (!('0' <= val[i] && '9' >= val[i])) {
			//throw as invalid byebye
			throw invalid_argument("Error: invalid character.");
		}
		//store int tmp in num
		int tmp = val[i] - '0';
		num.push_back(tmp);
	}
}

HugeInteger::HugeInteger(int n) {
	//check if n is less than or equal to 0
	if (n <= 0) {
		throw invalid_argument("Error: number is not greater than zero.");
	}
	this->minus = ((rand() % 2) == 0); //generate random bool for whether num is + or -
	//loop n times for each digit
	for (int i = 0; i < n; i++) {
		//if last digit, create a random digit between 1-9
		if (i == n - 1) {
			HugeInteger::num.push_back(rand() % 9 + 1);
		}
		else {
			//create a digit between 0-9
			HugeInteger::num.push_back(rand() % 10);
		}
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	HugeInteger summation;
	//check minus
	switch (this->minus) {
		//is negative
	case true: {
		//check if added object is negative
		switch (h.minus) {
			//both are negative
		case true: {
			//add absval of nums
			summation = this->negadd(*this, h);
			summation.minus = true;
			//end case
			break;
		}
				 //added object is postive
		case false: {
			//if num2 > num1
			if (negcompare(h) > 0) {
				summation = this->negsubtract(*this, h);
				summation.minus = true;
			}
			//if num2 < num1
			else if (negcompare(h) < 0) {
				summation = this->negsubtract(h, *this);
				summation.minus = false;
			}
			//case for both equal
			else {
				summation.num.push_back(0);
				summation.minus = true;
			}
			break;
		}
		}
		break;
	}
			 //num is positive
	case false: {
		//check if added num is negative
		switch (h.minus) {
		case true: {
			//iif num2 > num1
			if (negcompare(h) > 0) {
				summation = this->negsubtract(*this, h);
				summation.minus = false;
			}
			//if num 2 < num1
			else if (negcompare(h) < 0) {
				summation = this->negsubtract(h, *this);
				summation.minus = true;
			}
			//case for if they are equal
			else {
				summation.num.push_back(0);
				summation.minus = true;
			}
			break;
		}
				 //added num is positive
		case false: {
			//no minus sign
			summation = this->negadd(h, *this);
			summation.minus = false;
			break;
		}
		}
		break;
	}
	}
	if (summation.num[0] == 0 && summation.num.size() == 1 && !summation.minus) {
		summation.minus = true;
	}

	return summation;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	HugeInteger difference;
	//first num negative
	switch (this->minus) {
	case true: {
		//and second num negative
		switch (h.minus) {
		case true: {
			//if absval of num1 >  absval of num2
			if (negcompare(h) > 0) {
				//get negative difference
				difference = this->negsubtract(*this, h);
				difference.minus = true;
			}
			//if absval num1 < absval num2
			else if (negcompare(h) < 0) {
				//get negative difference
				difference = this->negsubtract(h, *this);
				difference.minus = false;
			}
			//if equal
			else {
				//no difference
				difference.num.push_back(0);
				difference.minus = true;
			}
			break;
		}
				 //num2 is positive
		case false: {
			//get negative sum
			difference = this->negadd(*this, h);
			difference.minus = true;
			break;
		}
		}
		break;
	}
			 //num1 positive
	case false: {
		//and second num negative
		switch (h.minus) {
		case true: {
			//get sum
			difference = this->negadd(*this, h);
			difference.minus = false;
			break;
		}
				 //second num is pos
		case false: {
			//num1 > num2
			if (negcompare(h) > 0) {
				//find difference
				difference = this->negsubtract(*this, h);
				difference.minus = false;
			}
			//num1 < num2
			else if (negcompare(h) < 0) {
				//find difference
				difference = this->negsubtract(h, *this);
				difference.minus = true;
			}
			//case for equal
			else {
				//no difference
				difference.num.push_back(0);
				difference.minus = true;
			}
			break;
		}
		}
		break;
	}
	}
	//size of difference
	int total_sub_size = difference.num.size();
	//if difference is 0, minus is true
	if (difference.num[0] == 0 && !difference.minus && total_sub_size == 1) {
		difference.minus = true;
	}
	return difference;
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	HugeInteger product;
	//store size of each num
	int numbers_amount = (this->num.size());
	int h_numbers_amount = (h.num.size());
	if (this->num[numbers_amount - 1] == 0 || h.num[h_numbers_amount - 1] == 0) {
		product.num.push_back(0);
		product.minus = true;
		return product;
	}
	//init for multiplication
	int count = 0;
	int tmp2 = 0;
	int adjust = 0;
	int numbers_size = this->num.size();
	int h_numbers_size = h.num.size();
	//loop through digits of first HugeInteger
	for (unsigned int i = 0; i < numbers_size; i++) {
		//creates temporary hugeint
		HugeInteger tmp;
		adjust = 0;
		for (int k = 0; k < count; k++) {
			tmp.num.push_back(0);
		}
		//loops through digits of second HugeInteger
		for (unsigned int j = 0; j < h_numbers_size; j++) {
			//calculate each product
			int mult = h.num[j] * this->num[i] + adjust;
			adjust = mult / 10;
			tmp2 = mult % 10;
			tmp.num.push_back(tmp2);
			//account for carry
			if (j == h_numbers_size - 1 && adjust != 0) {
				tmp.num.push_back(adjust);
			}
		}
		//add product
		product = product.add(tmp);
		count++;
	}
	//sign from hugeint signs
	product.minus = ((this->minus && h.minus) || (!this->minus && !h.minus));
	//if product 0 and pos, set minus true
	if (product.num[0] == 0 && !product.minus && product.num.size() == 1) {
		product.minus = true;
	}
	return product;
}

int HugeInteger::compareTo(const HugeInteger& h) {
	//handles case of negative
	if (minus && h.minus) {
		if (this->num.size() < h.num.size()) {
			return -1;
		}
		if (this->num.size() > h.num.size()) {
			return 1;
		}
		for (unsigned int i = 1; i <= this->num.size(); i++) {
			if (this->num[this->num.size() - i] < h.num[h.num.size() - i]) {
				return -1;
			}
			else if (this->num[this->num.size() - i] > h.num[h.num.size() - i]) {
				return 1;
			}
		}
	}
	//handles case of positive
	if (!minus && !h.minus) {
		if (this->num.size() > h.num.size()) {
			return -1;
		}
		if (this->num.size() < h.num.size()) {
			return 1;
		}
		for (unsigned int i = 1; i <= this->num.size(); i++) {
			if (this->num[this->num.size() - i] > h.num[h.num.size() - i]) {
				return -1;
			}
			if (this->num[this->num.size() - i] < h.num[h.num.size() - i]) {
				return 1;
			}
		}
	}
	//num1 negative num 2 positive
	if (minus && !h.minus) {
		return 1;
	}
	//num 2 neg, num 1 pos
	if (!minus && h.minus) {
		return -1;
	}
	//same number case
	return 0;
}

HugeInteger HugeInteger::negadd(const HugeInteger& val1, const HugeInteger& val2) {
	//init carry as 0
	int carry = 0;
	HugeInteger ans;
	//check which input is larger, store in bool
	bool bigger = (val1.num.size() >= val2.num.size());
	int larger = bigger ? val1.num.size() : val2.num.size();
	int smaller = bigger ? val2.num.size() : val1.num.size();
	int i = 0;
	int j = 0;
	/*
	variable storing biggerint:
	0 - val1 is bigger
	1 - val2 is bigger
	*/
	int result = bigger ? 0 : 1;
	//loop through each digit of inputs to length of smaller
	for (i = 0; i < smaller; i++) {
		int tmp = val1.num[i] + val2.num[i] + carry;
		carry = tmp / 10;
		tmp = tmp % 10;
		ans.num.push_back(tmp);
	}
	//loop through remaining inputs
	for (j = smaller; j < larger; j++) {
		//add carry and current digit
		int tmp = ((result == 0) ? val1.num[j] : val2.num[j]) + carry;
		//divide tmp by 10, store in carry, add ans to object
		carry = tmp / 10;
		tmp = tmp % 10;
		ans.num.push_back(tmp);
	}
	//if carry remains, add it
	if (carry != 0) {
		ans.num.push_back(carry);
	}
	return ans;
}

HugeInteger HugeInteger::negsubtract(const HugeInteger& val1, const HugeInteger& val2) {
	//stores the BORROW
	int sub = 0;
	//init difference to hold result of subtraction
	HugeInteger difference;
	int num1_size = val1.num.size();
	int num2_size = val2.num.size();
	//loop through val2
	for (unsigned int k = 0; k < val2.num.size(); k++) {
		//if val1 - borrow less than val2 
		if ((val1.num[k] - sub) < val2.num[k]) {
			//get result and put in vector
			difference.num.push_back((val1.num[k] - sub) + 10 - val2.num[k]);
			//check val1 zero update borrow
			if (val1.num[k + 1] == 0 && num1_size > k + 1) {
				sub = -9;
			}
			else {
				sub = 1;
			}
		}
		else {
			//get result and put in vector
			difference.num.push_back((val1.num[k] - sub) - val2.num[k]);
			//check if val1 is 0, check borrow is -9
			if (val1.num[k] == 0 && sub == -9) {
				//check val1 zero update borrow
				if (val1.num[k + 1] == 0 && num1_size > k + 1) {
					sub = -9;
				}
				else {
					sub = 1;
				}
			}
			else {
				sub = 0;
			}
		}
	}
	bool is_zero;
	//iterate num1 after num2 
	for (unsigned int j = num2_size; j < num1_size; j++) {
		//subtract borrow from val1  
		difference.num.push_back(val1.num[j] - sub);
		//check if 0 and borrow is -9
		if (val1.num[j] == 0 && sub == -9) {
			if (val1.num[j + 1] == 0 && num1_size > j + 1) {
				sub = -9;
			}
			else if (val1.num[j + 1] != 0 && num1_size > j + 1) {
				sub = 1;
			}
		}
		else {
			sub = 0;
		}
	}
	int total_sub_size = difference.num.size();
	int count = total_sub_size - 1;
	while (count != 0 && difference.num[count] == 0) {
		difference.num.pop_back();
		count--;
	}
	return difference;
}

int HugeInteger::negcompare(const HugeInteger& h) {
	int num_size = num.size();
	int h_size = h.num.size();
	//if not equal return -1 if first num is smaller otherwise return 1
	if (num_size != h_size) {
		return num_size < h_size ? -1 : 1;
	}
	//if equal size, check digits left -> right
	for (int i = num_size - 1; i >= 0; i--) {
		//if num1 smaller than num2 -1
		if (num[i] != h.num[i]) {
			return num[i] < h.num[i] ? -1 : 1;
		}
	}
	//integers are equal
	return 0;
}

string HugeInteger::toString() {
	//init final string 
	string final = "";
	//retrive the size of HugeInteger
	int number_amount = num.size();
	//if negative add '-' to string
	if (!this->minus) {
		final = '-';
	}
	//iterate through HugeInteger from right -> left
	for (unsigned int i = 1; i <= number_amount; i++) {
		//convert to char and append
		final += (this->num[number_amount - i] + '0');
	}
	return final;
}