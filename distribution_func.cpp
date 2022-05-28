#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<ostream>
#include<istream>
#include<sstream>

//�}�N��
//���[�v
#define rep(i,n) for(i=0;i<n;i++)

//�f�[�^�C���t, �t�@�C�����i�O�j�C�t�@�C�����i��j,�Ώۓ�
void distribution_func(std::vector<std::vector<std::vector<long double>>>& data_ans, unsigned long long int ans_now_day, std::string front, std::string back, unsigned long long int target_day) {

	//���z�`�o�͗p
	//������������
	std::stringstream distribution_day_name;

	//�����𕶎���ɕϊ�
	distribution_day_name << ans_now_day;
	std::string str = distribution_day_name.str();

	//�L������t�@�C�������`
	std::string file_name;

	//������̑����Z
	file_name = front + str + back;

	//�t�@�C���̎w��
	std::ofstream distribution_csv(file_name, std::ios::out);

	//���[�v�p�ϐ���`
	unsigned long long int des_j, des_i;

	//���z�`�o��
	rep(des_j, data_ans.at(0).size()) {
		rep(des_i, data_ans.size()) {
			distribution_csv << data_ans.at(des_i).at(des_j).at(target_day) << ",";
		}
		distribution_csv << std::endl;
	}


	return;
}