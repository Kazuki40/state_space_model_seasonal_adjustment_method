#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<ostream>
#include<istream>
#include<sstream>

//マクロ
//ループ
#define rep(i,n) for(i=0;i<n;i++)

//データ，日付, ファイル名（前），ファイル名（後）,対象日
void distribution_func(std::vector<std::vector<std::vector<long double>>>& data_ans, unsigned long long int ans_now_day, std::string front, std::string back, unsigned long long int target_day) {

	//分布形出力用
	//数字→文字列
	std::stringstream distribution_day_name;

	//数字を文字列に変換
	distribution_day_name << ans_now_day;
	std::string str = distribution_day_name.str();

	//記入するファイル名を定義
	std::string file_name;

	//文字列の足し算
	file_name = front + str + back;

	//ファイルの指定
	std::ofstream distribution_csv(file_name, std::ios::out);

	//ループ用変数定義
	unsigned long long int des_j, des_i;

	//分布形出力
	rep(des_j, data_ans.at(0).size()) {
		rep(des_i, data_ans.size()) {
			distribution_csv << data_ans.at(des_i).at(des_j).at(target_day) << ",";
		}
		distribution_csv << std::endl;
	}


	return;
}