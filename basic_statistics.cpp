//多重定義用
#pragma once

//ファイル
#include "basic_statistics.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<numeric>

//マクロ
#define rep(i,n) for(i=0;i<n;i++)


//コンストラクタ
//関数定義用
basic_statistics::basic_statistics() {
	//std::cout << "class_teigi" << std::endl;
	this->average_value = 0.0L;
	this->unbaised_standard_deviation_value = 0.0L;
	this->mode_value = 0.0L;
	this->median_value = 0.0L;
	this->i = 0LL;
	this->temporary_variable = 0.0L;
	this->even = 0;
	this->temp_ans = 0.0L;
	this->temporary_ulli = 0LL;
	this->temporary_partice = 0LL;
}


//デコントラクタ
basic_statistics::~basic_statistics() {
	//std::cout << "class_clear" << std::endl;
}


//実行用関数
void basic_statistics::claculate_basic_statistics_func(std::vector<long double>target_vector) {

	//平均値算出
	this->average_value = this->func_average(target_vector);

	//不偏分散算出
	this->unbaised_standard_deviation_value = this->func_unbaised_standard(target_vector);

	//中央値算出
	this->median_value = this->func_median(target_vector);

	//最頻値算出
	this->mode_value = this->func_mode(target_vector);

	//終わり
	return;

}


//平均
long double basic_statistics::func_average(std::vector<long double>& target_ave) {

	//平均値算出関数
	//総和を出すために,accumulate()関数
	//第一引数、配列最初
	//第二引数、配列最後
	//第三引数、初期値かつ型
	//0.0Lはlong double 型
	this->temporary_variable = std::accumulate(target_ave.begin(), target_ave.end(), 0.0L) / (long double)target_ave.size();

	//答え：戻り値が解
	return (this->temporary_variable);

}


//不偏分散
long double basic_statistics::func_unbaised_standard(std::vector<long double>target_unb) {

	//不偏分散計算用関数
	//値を大きく変えるため配列定義
	std::vector<long double>f_unbaised_standard(target_unb.size());

	//値を平均値で引いて二乗する
	rep(this->i, target_unb.size()) {

		//値をいれる
		//要件等
		f_unbaised_standard[this->i] = std::powl((target_unb.at(i) - this->average_value), 2.0L);

	}

	//得られた値を足して割ることで、分散（標本）が求まる
	this->temp_ans = this->func_average(f_unbaised_standard);

	//値は,標本なので、分散値が小さく出ている可能性がある
	//不偏分散に計算し直す
	//　n/(n-1) すればいい
	//不偏標準偏差が求めたいためルートする
	this->temporary_variable = std::sqrtl(((long double)target_unb.size() / (long double)(target_unb.size() - 1LL)) * this->temp_ans);


	//答えをいれる
	return (this->temporary_variable);

}


//中央値算出
long double basic_statistics::func_median(std::vector<long double>target_median) {


	//仮変数を定義
	this->temporary_variable = 0.0L;


	//順番を並び替え
	//イントロソート
	std::sort(target_median.begin(), target_median.end());


	//偶数＝0、奇数＝1
	//1,2,3,4,5,6,7,8,9,10=0
	//1,2,3,4,5,6,7,8,9 = 1
	this->even = target_median.size() % 2LL;
	//奇数偶数を判定したので

	//奇数偶数を評価
	if (this->even == 0) {
		//2で割れる
		//偶数の評価


		//10/2 = 5
		//配列は0スタート
		//5と6の間が中央値
		// 1,2,3,4,5,6,7,8,9,10
		// 0,1,2,3,4,5,6,7,8,9
		// 4と5なので
		//5と1つ前取るとよい
		this->temporary_variable = (target_median.at(target_median.size() / 2LL) + target_median.at((target_median.size() / 2LL) - 1)) / (long double)2.0L;

	}
	else if (this->even == 1) {
		//2で割れない
		//奇数の評価


		//9/2 = 4.5
		//配列は0スタート
		// 1,2,3,4,5,6,7,8,9
		// 5が中央値
		// 0,1,2,3,4,5,6,7,8
		//4を取ればいい
		//(9-1)/2 = 4
		this->temporary_variable = target_median.at((target_median.size() - 1) / 2LL);

	}

	//答えをいれる
	return this->temporary_variable;

}


//最頻値算出
long double basic_statistics::func_mode(std::vector<long double>target_mode) {

	//同じ数があるかを記入する
	//map配列を置く
	std::map<long double, unsigned long long int>mode_map;
	std::map<long double, unsigned long long int>::iterator mode_map_ite;


	//mapに値をいれる
	rep(this->i, target_mode.size()) {

		//評価
		//mapの第一引数に値があるかTorFで返す
		//Tの時は1
		if (mode_map.count(target_mode.at(this->i)) == 1) {

			//第二引数に+1する
			mode_map[target_mode.at(this->i)]++;
		}
		else {

			//Fの時、値が存在していないため
			//emplace 追加
			//キーは、long double型、値は1(Unsingned long long型）を入れる
			mode_map.emplace(target_mode.at(this->i), 1ULL);
		}
	}

	//配列の初期値をイテレータで設定
	mode_map_ite = mode_map.begin();

	//最大値の値を補完用に定義
	this->temporary_ulli = 0ULL;

	//最大値を探す
	//.end()は、配列の最後
	//入れた値の1つ後ろなので、!=でいい
	while (mode_map_ite != mode_map.end())
	{
		//2つの値を比較して最大値を返す
		this->temporary_ulli = std::max(temporary_ulli, mode_map_ite->second);

		//値を動かす
		mode_map_ite++;

	}

	//重複する最大値の値の数を数える
	this->temporary_partice = 0ULL;

	//配列の最初を設定
	mode_map_ite = mode_map.begin();

	//求める値を設定
	this->temporary_variable = 0.0L;

	//ループで探索
	while (mode_map_ite != mode_map.end()) {

		//mapの最大値と最大値が一致しているか？
		if (mode_map_ite->second == temporary_ulli) {

			//値を累積でいれる
			this->temporary_variable += mode_map_ite->first;

			//重複の個数を数える
			this->temporary_partice++;

		}

		//イテレータの更新
		mode_map_ite++;

	}

	//平均値の算出
	this->temporary_variable /= (long double)this->temporary_partice;

	//答え
	return this->temporary_variable;

}