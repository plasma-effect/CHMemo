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
	std::tuple<char const*, utility::func_t, utility::dec_float, bool> ancients[] = {
		{"Kumawakamaru", kumawakamaru, -8, false},
		{"Vaagur", vaagur, -75, false},
		{"Atman", atman, 75, false},
		{"Chronos", chronos, 30, false},
		{"Dogcog", dogcog, -99.99999999, false},
		{"Dora", dora, 9900, false},
		{"Bubos", bubos, -5, false}
	};
	std::size_t rest = std::size(ancients);
	std::cout << std::scientific << std::setprecision(3);
	std::cerr << std::scientific << std::setprecision(3) << std::boolalpha;
	for (std::size_t level = 2;;++level)
	{
		for (auto& [name, func, limit, flag] : ancients)
		{
			if (flag)
			{
				continue;
			}
			auto effect = func(level);
			if (mp::abs(effect - limit) < mp::abs(limit) * 0.0001)
			{
				flag = true;
				--rest;
				std::cout << name << "(level: " << level << ", effect: " << effect << ", cost: " << mp::pow(utility::dec_float(2), level) << ")" << std::endl;
				if (rest == 0)
				{
					return 0;
				}
			}
		}
	}
}