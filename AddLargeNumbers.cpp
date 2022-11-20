// Program to add very large numbers

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

// Function headers
string AddNums(const string& num1, const string& num2);
int ParseDigit(const char digit);
string ConvertDigitsToNum(const vector<int>& vDigits);


int ParseDigit(const char digit)
{
	if(digit < '0' || digit > '9')
		throw std::invalid_argument("Expect only digits 0-9");

	return static_cast<int>(digit - '0');
}


string ConvertDigitsToNum(const vector<int>& vDigits)
{
	string num;

	for(const int digit : vDigits)
		num += '0' + digit;

	std::reverse(num.begin(), num.end());

	return num;
}


string AddNums(const string& num1, const string& num2)
{
	vector<int> viNum1;
	vector<int>	viNum2;
	for(auto it=num1.crbegin(); it != num1.crend(); it++)
		viNum1.emplace_back(ParseDigit(*it));

	for(auto it=num2.crbegin(); it != num2.crend(); it++)
		viNum2.emplace_back(ParseDigit(*it));

	size_t uNumOfDigits = std::max(viNum1.size(), viNum2.size());
	vector<int> viSum;
	viSum.reserve(uNumOfDigits+1);
	int iCarryOver(0);

	auto GetDigit = [](const vector<int>& vNumbers, const size_t idx)
	{
		return idx < vNumbers.size() ? vNumbers[idx] : 0;
	};
	
	for(size_t idx = 0; idx < uNumOfDigits; idx++)
	{
		int iSumOfDigits = GetDigit(viNum1,idx) + GetDigit(viNum2,idx) + iCarryOver;
		iCarryOver = iSumOfDigits/10;
		viSum.emplace_back(iSumOfDigits%10);
	}

	if(iCarryOver != 0)
		viSum.emplace_back(iCarryOver);

	return ConvertDigitsToNum(viSum);
}


int main()
{
	cout << "Enter number 1: " << endl;
	string num1, num2;
	cin >> num1;
	cout << "Enter number 2: " << endl;
	cin >> num2;

	try {
		string sum = AddNums(num1, num2);
		cout << "The sum is: " << sum << endl;
	}
	catch(const std::invalid_argument& ia)
	{
		std::cerr << "Found invalid input number: " << ia.what() << endl;
	}

	return 0;
}
