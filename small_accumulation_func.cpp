//多重定義
#pragma once

//ライブラリ
#include<iostream>
#include<cmath>
#include<algorithm>

//小さい値同士の和
long double small_accumulation_func(long double one_value, long double two_value) {

	//変数定義
	long double ans;
	long double max_val;
	long double min_val;
	long double one_val_temp;
	long double two_val_temp;

	//変数を対数化
	one_val_temp = std::logl(one_value);
	two_val_temp = std::logl(two_value);

	// log(0)=-inf の判定
	if ((std::isinf(one_val_temp) == true) || (std::isinf(two_val_temp) == true)) {

		//ほぼ0の演算
		ans = one_value + two_value;

	}
	else
	{

		//大・小の判定
		max_val = std::max(one_val_temp, two_val_temp);
		min_val = std::min(one_val_temp, two_val_temp);

		//a+b=exp(ln(a))+exp(ln(b))を展開
		//exp(ln(exp(ln(a)-ln(b))+1)+ln(b))
		ans = std::expl(max_val + std::log1pl(std::expl(min_val - max_val)));

	}

	//答え
	return ans;

}