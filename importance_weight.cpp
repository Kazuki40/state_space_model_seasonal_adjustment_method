//多重定義
#pragma once

//ファイルインクルード
#include "importance_weight.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<numeric>


//マクロ
#define rep(i, n) for (i = 0; i < n; i++)


//コンストラクタ
//初期値の定義
importance_weight::importance_weight() {
	this->loop_func_value = 0ULL;
	this->loglikelihood = 0.0L;
	this->likelihood = 0.0L;
	this->temp = 0.0L;
}

//デコンストラクタ
importance_weight::~importance_weight() {
	//std::cout << "e" << std::endl;
}

//重みの正規化
std::vector<long double>importance_weight::importance_weight_func(std::vector<long double>& data_set) {
	
	//仮フォルダ指定
	std::vector<long double>use_data = data_set;

	//ソート
	std::sort(use_data.begin(), use_data.end());
	
	//総和の計算
	//対数の和を取るための関数accumulate関数
	//引数は、第1：開始場所、第2：終了場所、第3：初期値、初期値の型が答えなので0.0L(0のlong double 型）
	this->likelihood = std::accumulate(data_set.begin(), data_set.end(), 0.0L);

	//対数尤度の計算
	this->loglikelihood = std::logl(this->likelihood);

	//答え用の配列定義
	std::vector<long double> importance_weight_result;
	importance_weight_result.resize(data_set.size());

	//重み
	rep(this->loop_func_value, data_set.size()) {

		//正規化
		importance_weight_result.at(this->loop_func_value) = data_set.at(this->loop_func_value) / this->likelihood;

	}

	//答え
	return importance_weight_result;

}


//実効サンプルサイズ
long double importance_weight::effective_sample_size_func(std::vector<long double>& data) {

	//仮フォルダ指定
	std::vector<long double>use_data = data;

	//尤度を2乗する
	rep(this->loop_func_value, data.size())use_data.at(this->loop_func_value) = std::powl(data.at(this->loop_func_value), 2.0L);

	//ソート
	std::sort(use_data.begin(),use_data.end());

	//実効サンプルサイズの式に入れる
	//分母が2乗和なので
	temp = 1.0L / std::accumulate(use_data.begin(), use_data.end(), 0.0L);

	//答え
	return(temp);

}
