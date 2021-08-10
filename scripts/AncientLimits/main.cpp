#include "utility.hpp"

#include <iostream>
#include <tuple>

utility::dec_float kumawakamaru(std::size_t level)
{
	static const utility::dec_float constant = -0.025;
	return -8 * (1 - mp::exp(constant * level));
}

utility::dec_float vaagur(std::size_t level)
{
	static const utility::dec_float constant = -0.026;
	return -75 * (1 - mp::exp(constant * level));
}

utility::dec_float atman(std::size_t level)
{
	static const utility::dec_float constant = -0.013;
	return 75 * (1 - mp::exp(constant * level));
}

utility::dec_float chronos(std::size_t level)
{
	static const utility::dec_float constant = -0.034;
	return 30 * (1 - mp::exp(constant * level));
}

utility::dec_float dogcog(std::size_t level)
{
	static const utility::dec_float constant = -0.01;
	return -99.99999999 * (1 - mp::exp(constant * level));
}

utility::dec_float dora(std::size_t level)
{
	static const utility::dec_float constant = -0.002;
	return 9900 * (1 - mp::exp(constant * level));
}

utility::dec_float bubos(std::size_t level)
{
	static const utility::dec_float constant = -0.002;
	return -5 * (1 - mp::exp(constant * level));
}

int main() 
{
	std::tuple<char const*, int> ancients[] = {
		{"Chronos", 1101},
		{"Vaagur", 1440},
		{"Kumawakamaru", 1498},
		{"Atman", 2880},
		{"Dogcog", 3743},
		{"Bubos",18715},
		{"Dora", 18715}
	};
	std::size_t rest = std::size(ancients);
	std::cout << std::scientific << std::setprecision(3);
	std::cerr << std::scientific << std::setprecision(3) << std::boolalpha;
	for (auto [name, level] : ancients)
	{
		std::cout << name << "|" << level << "|" << mp::pow(utility::dec_float(2), level) << std::endl;
	}
}