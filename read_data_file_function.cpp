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

//�f�[�^�ǂݎ��
std::vector<long double>read_data_file_func(unsigned long long int max_data_puls_one, std::string file_name) {

	//�z���`
	std::vector<long double> read_data_vector;

	//�����z�u�i�_�~�[�ݒ�j
	read_data_vector.push_back(0.0L);

	//�t�@�C������
	//��`
	std::fstream read_csv(file_name, std::ios::in);

	//�ǂݍ��ނ��߂̕������`
	std::string read_one;
	std::string read_two;

	//�����l
	long double read_ld;

	//���[�v
	while (std::getline(read_csv, read_one)) {

		//�������z��Ȃ�
		std::istringstream read_data_coma(read_one);

		//�R���}������
		while (std::getline(read_data_coma, read_two, ',')) {

			//�������long double �ɂ���
			read_ld = std::stold(read_two);

			//�f�[�^�ǂݎ��
			read_data_vector.push_back(read_ld);

		}

	}

	//����
	//�w�萔�ƃf�[�^��������Ȃ����͋����I������
	//��v�������͂��̔z������ɂ���
	if (max_data_puls_one == read_data_vector.size()) {

		//��v����̂ŏI���
		return (read_data_vector);
	}
	else {

		//��v���Ȃ��̂ŋ����I��
		std::cout << "error" << std::endl;
		exit(-1);

	}

}