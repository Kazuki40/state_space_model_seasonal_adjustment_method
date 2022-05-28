//miyazaki
#pragma once

//パッケージ
#include<iostream>
#include<cmath>

//自作関数定義
#include"homemade_function_header_files.h"

//↓最適化アルゴリズム書いたらここ推定する　↓
//#define optimisation false

//hyper parameter

//仮定パラメータの設定
//ハイパーパラメータ（初期分布）の設定
//x_0
#define inital_sd 4.0L
#define sd_random_inital std::powl(10.0L,inital_sd)
#define sd_random_inital_week std::powl(10.0L,(inital_sd))

//シータ
#define trend_a_e std::powl(10.0L,2)
#define trend_b_e std::powl(10.0L,4)
#define trend_week_e std::powl(10.0L,3)
#define observation_e std::powl(10.0L,4)

//自己組織化状態空間モデルの用 

//ハイパーパラメータの設定(乱数項)の標準偏差

//↑最適化アルゴリズム書いたらここ推定する　↑

//関数設定
long double main_function(long double, long double, long double, long double, long double, long double);

//メイン
//実行ファイル
int main() {

	main_function(sd_random_inital, sd_random_inital_week, trend_a_e, trend_b_e, trend_week_e, observation_e);

	std::cout << "おわり　なにか数字を入力" << std::endl;
	long int somthing_num;
	std::cin >> somthing_num;

	return 0;
}
