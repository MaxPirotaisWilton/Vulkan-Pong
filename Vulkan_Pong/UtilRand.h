#pragma once

#include <random>
#include <chrono>

class UtilRand
{
private:
	inline static std::default_random_engine re;

public:
	static void setRESeed() {
		UtilRand::re.seed(std::chrono::system_clock::now().time_since_epoch().count());
	}

	static double randomDouble(double lower_bound, double upper_bound) {
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		double a_random_double = unif(UtilRand::re);
		return a_random_double;
	}
};

