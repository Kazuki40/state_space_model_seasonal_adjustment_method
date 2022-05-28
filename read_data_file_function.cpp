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

//データ読み取り
std::vector<long double>read_data_file_func(unsigned long long int max_data_puls_one, std::string file_name) {

	//配列定義
	std::vector<long double> read_data_vector;

	//初期配置（ダミー設定）
	read_data_vector.push_back(0.0L);

	//ファイル入力
	//定義
	std::fstream read_csv(file_name, std::ios::in);

	//読み込むための文字列定義
	std::string read_one;
	std::string read_two;

	//入れる値
	long double read_ld;

	//ループ
	while (std::getline(read_csv, read_one)) {

		//多次元配列など
		std::istringstream read_data_coma(read_one);

		//コンマを消す
		while (std::getline(read_data_coma, read_two, ',')) {

			//文字列をlong double にする
			read_ld = std::stold(read_two);

			//データ読み取り
			read_data_vector.push_back(read_ld);

		}

	}

	//判別
	//指定数とデータ数が合わない時は強制終了する
	//一致した時はこの配列を解にする
	if (max_data_puls_one == read_data_vector.size()) {

		//一致するので終わり
		return (read_data_vector);
	}
	else {

		//一致しないので強制終了
		std::cout << "error" << std::endl;
		exit(-1);

	}

}