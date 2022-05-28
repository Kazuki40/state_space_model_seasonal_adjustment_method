#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<numeric>

class importance_weight
{
private:
	unsigned long long int loop_func_value;
	long double temp;

public:
	importance_weight();
	~importance_weight();
	std::vector<long double> importance_weight_func(std::vector<long double>&);
	long double loglikelihood;
	long double likelihood;
	long double effective_sample_size_func(std::vector<long double>&);
};
