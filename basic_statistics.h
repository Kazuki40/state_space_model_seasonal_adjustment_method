#pragma once
#include<vector>

class basic_statistics
{
protected:
	long double func_average(std::vector<long double>&);
	long double func_unbaised_standard(std::vector<long double>);
	long double func_mode(std::vector<long double>);
	long double func_median(std::vector<long double>);

private:

	long double temporary_variable;
	long double temp_ans;
	unsigned long long int temporary_ulli;
	unsigned long long int temporary_partice;
	unsigned long long int i;
	unsigned short int even;
public:
	basic_statistics();
	~basic_statistics();
	void claculate_basic_statistics_func(std::vector<long double>);
	long double average_value;
	long double unbaised_standard_deviation_value;
	long double mode_value;
	long double median_value;
};

