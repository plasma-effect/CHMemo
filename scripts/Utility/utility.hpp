#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>

#include <utility>

namespace mp = boost::multiprecision;

namespace utility
{
	using dec_float = mp::cpp_dec_float_100;
	
	using func_t = dec_float(*)(std::size_t);
}