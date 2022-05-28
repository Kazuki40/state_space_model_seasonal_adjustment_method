//���d��`�p
#pragma once

//�p�b�P�[�W
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<istream>
#include<vector>
#include<string>

//���[�v
#define rep(i,n) for(i=0;i<n;i++)

void write_data_func(std::vector<std::vector<long double>>& result_data, std::string file_name) {

	//���[�v�p�ϐ���`
	unsigned long long int column, row;

	//�t�@�C�����`
	std::ofstream csv(file_name, std::ios::out);

	//�f�[�^��
	rep(row, result_data[0].size()) {

		//�f�[�^��
		rep(column, result_data.size()) {

			//��������
			//�L�������w��
			csv << std::scientific << result_data.at(column).at(row) << ",";

		}

		//���s
		csv << std::endl;

	}

	//�I���
	//�߂�l�͂Ȃ�
	return;

}