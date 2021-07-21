#include "utility.hpp"
#include <iostream>

utility::dec_float power(std::size_t i)
{
	return mp::pow(utility::dec_float(2), i);
}

utility::dec_float double_power(std::size_t i)
{
	return mp::pow(mp::pow(utility::dec_float(2), i), i);
}

int main()
{
	std::cout << std::scientific << std::setprecision(3);
	utility::func_t func[] = { power, double_power };
	std::cout << func[0](10) << std::endl;
	std::cout << func[1](10) << std::endl;
}