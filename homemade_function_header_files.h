#pragma once

//クラス用関数
#include"basic_statistics.h"
#include "importance_weight.h"

//データ読み取り関数
std::vector<long double> read_data_file_func(unsigned long long int, std::string);

//データ出力関数
void write_data_func(std::vector<std::vector<long double>>&, std::string);

//小さい値を足すよう
long double small_accumulation_func(long double, long double);

//浮動点小数比較用
bool comparison_long_double_value_function(long double*, long double*);

//分布形出力
void distribution_func(std::vector<std::vector<std::vector<long double>>>&, unsigned long long int, std::string, std::string, unsigned long long int);
