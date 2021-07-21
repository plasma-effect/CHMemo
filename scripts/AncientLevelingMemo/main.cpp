#include "utility.hpp"

#include <fstream>
#include <unordered_map>

#include <boost/range/irange.hpp>

using utility::dec_float;

dec_float juggernaut(dec_float level)
{
	return mp::pow(level, 2.5) * 2 / 5 + mp::pow(level, 1.5) / 2 + mp::pow(level, 0.5) / 8;
}

dec_float next_juggernaut(dec_float level)
{
	return juggernaut(level * 10) - juggernaut(level);
}

dec_float normal(dec_float level)
{
	dec_float lev = level;
	return lev * (lev + 1) / 2;
}

dec_float next_normal(dec_float level)
{
	return normal(level * 10) - normal(level);
}

void print(std::size_t chorgorloth)
{
	dec_float outsider = mp::pow(dec_float(0.95), chorgorloth);
	std::fstream fst("ancients/c" + std::to_string(chorgorloth) + ".md", std::ios_base::out | std::ios_base::trunc);
	std::unordered_map<std::size_t, char const*> remove = {
		{271, "Chronos"},
		{355, "Vaagur"},
		{369, "Kumawakamaru"},
		{709, "Atman"},
		{922, "Dogcog"},
		{4606, "Dora & Bubos"},
		{213, "Sniperino"},
		{436, "Kleptos"}
	};
	dec_float sum = 0;
	std::size_t exponential_level = 1;
	dec_float juggernaut_level = 1;
	dec_float juggernaut_next = 10;
	dec_float normal_level = 1;
	dec_float normal_next = 10;
	std::size_t active_exponential = 13;
	std::size_t active_juggernaut = 2;
	std::size_t active_normal = 8;

	std::string last_removed = "";
	fst << std::scientific << std::setprecision(3);
	fst << "# Chorgorloth == 0" << std::endl << std::endl;
	fst << "- [0000 to 0099](#Under-100)" << std::endl;
#define SETW2(i) std::setw(2) << std::setfill('0') << i << std::flush
	for (auto i : boost::irange(1, 20))
	{
		fst << "- [" << SETW2(i) << "00 to " << SETW2(i) << "99](#" << SETW2(i) << "XX)" << std::endl;
	}
	fst << std::endl << "## Under-100" << std::endl << std::endl;
	fst << "|Hero Souls|Exponential|Last Removed|Juggernaut|Accelerate|" << std::endl;
	fst << "----|----|----|----|----" << std::endl;
	std::size_t rank = 1;
	while (true)
	{
		dec_float n = 0;
		dec_float nexp = active_exponential * mp::pow(dec_float(2), exponential_level + 1) * outsider;
		dec_float njug = active_juggernaut * next_juggernaut(juggernaut_level) * outsider;
		dec_float nnor = active_normal * next_normal(normal_level) * outsider;
		if (njug < nexp && njug < nnor)
		{
			n = njug;
			juggernaut_level += juggernaut_next;
			juggernaut_next *= 10;
		}
		else if (nnor < nexp)
		{
			n = nnor;
			normal_level += normal_next;
			normal_next *= 10;
		}
		else
		{
			n = njug;
			++exponential_level;
			if (remove.count(exponential_level))
			{
				--active_exponential;
				last_removed = remove.at(exponential_level);
				if (active_exponential == 5)
				{
					--active_exponential;
				}
			}
		}
		sum += n;
		if (sum + n >= mp::pow(utility::dec_float(10), 100 * rank))
		{
			if (rank == 20)
			{
				return;
			}
			fst << std::endl << "## " << SETW2(rank) << "XX" << std::endl << std::endl;
			fst << "|Hero Souls|Exponential|Last Removed|Juggernaut|Accelerate|" << std::endl;
			fst << "----|----|----|----|----" << std::endl;
			++rank;
		}
		fst << sum + n << "|" << exponential_level << "|" << last_removed << "|" << juggernaut_level << "|" << normal_level << std::endl;
	}
}

int main()
{
	for (auto i : boost::irange(151))
	{
		print(i);
	}
}