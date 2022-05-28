//多重定義用
#pragma once

//パッケージ
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<istream>
#include<vector>
#include<string>

//ループ
#define rep(i,n) for(i=0;i<n;i++)

void write_data_func(std::vector<std::vector<long double>>& result_data, std::string file_name) {

	//ループ用変数定義
	unsigned long long int column, row;

	//ファイルを定義
	std::ofstream csv(file_name, std::ios::out);

	//データ↓
	rep(row, result_data[0].size()) {

		//データ→
		rep(column, result_data.size()) {

			//書き込み
			//有効数字指定
			csv << std::scientific << result_data.at(column).at(row) << ",";

		}

		//改行
		csv << std::endl;

	}

	//終わり
	//戻り値はなし
	return;

}