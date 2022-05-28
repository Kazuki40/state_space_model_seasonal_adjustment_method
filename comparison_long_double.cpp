//重複宣言を消す
#pragma once

//パッケージを提案
#include<iostream>
#include<algorithm>

//関数を生成
//比較用関数
bool comparison_long_double_value_function(long double* one_value, long double* two_value) {

	//計算用イプシロン
	long double ep = (std::numeric_limits<long double>::epsilon());

	//比較
	//A<=B
	//0<B-A,0=B-A

	//B-A
	long double evaluation_value = *two_value - *one_value;

	//比較
	//0!=ep
	//ep:計算機イプシロン×1or最大値

	//B-A が0より大きい時は真
	//B-Aの絶対値がepより小さい時は真
	//それ以外は偽
	bool ans_comparison = (std::abs(evaluation_value)<=ep? true:(evaluation_value>=0? true :false));

	//答えを返す
	return ans_comparison;

}