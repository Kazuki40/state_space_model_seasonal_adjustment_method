//���d��`�p
#pragma once

//�t�@�C��
#include "basic_statistics.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<numeric>

//�}�N��
#define rep(i,n) for(i=0;i<n;i++)


//�R���X�g���N�^
//�֐���`�p
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


//�f�R���g���N�^
basic_statistics::~basic_statistics() {
	//std::cout << "class_clear" << std::endl;
}


//���s�p�֐�
void basic_statistics::claculate_basic_statistics_func(std::vector<long double>target_vector) {

	//���ϒl�Z�o
	this->average_value = this->func_average(target_vector);

	//�s�Ε��U�Z�o
	this->unbaised_standard_deviation_value = this->func_unbaised_standard(target_vector);

	//�����l�Z�o
	this->median_value = this->func_median(target_vector);

	//�ŕp�l�Z�o
	this->mode_value = this->func_mode(target_vector);

	//�I���
	return;

}


//����
long double basic_statistics::func_average(std::vector<long double>& target_ave) {

	//���ϒl�Z�o�֐�
	//���a���o�����߂�,accumulate()�֐�
	//�������A�z��ŏ�
	//�������A�z��Ō�
	//��O�����A�����l���^
	//0.0L��long double �^
	this->temporary_variable = std::accumulate(target_ave.begin(), target_ave.end(), 0.0L) / (long double)target_ave.size();

	//�����F�߂�l����
	return (this->temporary_variable);

}


//�s�Ε��U
long double basic_statistics::func_unbaised_standard(std::vector<long double>target_unb) {

	//�s�Ε��U�v�Z�p�֐�
	//�l��傫���ς��邽�ߔz���`
	std::vector<long double>f_unbaised_standard(target_unb.size());

	//�l�𕽋ϒl�ň����ē�悷��
	rep(this->i, target_unb.size()) {

		//�l�������
		//�v����
		f_unbaised_standard[this->i] = std::powl((target_unb.at(i) - this->average_value), 2.0L);

	}

	//����ꂽ�l�𑫂��Ċ��邱�ƂŁA���U�i�W�{�j�����܂�
	this->temp_ans = this->func_average(f_unbaised_standard);

	//�l��,�W�{�Ȃ̂ŁA���U�l���������o�Ă���\��������
	//�s�Ε��U�Ɍv�Z������
	//�@n/(n-1) ����΂���
	//�s�ΕW���΍������߂������߃��[�g����
	this->temporary_variable = std::sqrtl(((long double)target_unb.size() / (long double)(target_unb.size() - 1LL)) * this->temp_ans);


	//�����������
	return (this->temporary_variable);

}


//�����l�Z�o
long double basic_statistics::func_median(std::vector<long double>target_median) {


	//���ϐ����`
	this->temporary_variable = 0.0L;


	//���Ԃ���ёւ�
	//�C���g���\�[�g
	std::sort(target_median.begin(), target_median.end());


	//������0�A���1
	//1,2,3,4,5,6,7,8,9,10=0
	//1,2,3,4,5,6,7,8,9 = 1
	this->even = target_median.size() % 2LL;
	//������𔻒肵���̂�

	//�������]��
	if (this->even == 0) {
		//2�Ŋ����
		//�����̕]��


		//10/2 = 5
		//�z���0�X�^�[�g
		//5��6�̊Ԃ������l
		// 1,2,3,4,5,6,7,8,9,10
		// 0,1,2,3,4,5,6,7,8,9
		// 4��5�Ȃ̂�
		//5��1�O���Ƃ悢
		this->temporary_variable = (target_median.at(target_median.size() / 2LL) + target_median.at((target_median.size() / 2LL) - 1)) / (long double)2.0L;

	}
	else if (this->even == 1) {
		//2�Ŋ���Ȃ�
		//��̕]��


		//9/2 = 4.5
		//�z���0�X�^�[�g
		// 1,2,3,4,5,6,7,8,9
		// 5�������l
		// 0,1,2,3,4,5,6,7,8
		//4�����΂���
		//(9-1)/2 = 4
		this->temporary_variable = target_median.at((target_median.size() - 1) / 2LL);

	}

	//�����������
	return this->temporary_variable;

}


//�ŕp�l�Z�o
long double basic_statistics::func_mode(std::vector<long double>target_mode) {

	//�����������邩���L������
	//map�z���u��
	std::map<long double, unsigned long long int>mode_map;
	std::map<long double, unsigned long long int>::iterator mode_map_ite;


	//map�ɒl�������
	rep(this->i, target_mode.size()) {

		//�]��
		//map�̑������ɒl�����邩TorF�ŕԂ�
		//T�̎���1
		if (mode_map.count(target_mode.at(this->i)) == 1) {

			//��������+1����
			mode_map[target_mode.at(this->i)]++;
		}
		else {

			//F�̎��A�l�����݂��Ă��Ȃ�����
			//emplace �ǉ�
			//�L�[�́Along double�^�A�l��1(Unsingned long long�^�j������
			mode_map.emplace(target_mode.at(this->i), 1ULL);
		}
	}

	//�z��̏����l���C�e���[�^�Őݒ�
	mode_map_ite = mode_map.begin();

	//�ő�l�̒l��⊮�p�ɒ�`
	this->temporary_ulli = 0ULL;

	//�ő�l��T��
	//.end()�́A�z��̍Ō�
	//���ꂽ�l��1���Ȃ̂ŁA!=�ł���
	while (mode_map_ite != mode_map.end())
	{
		//2�̒l���r���čő�l��Ԃ�
		this->temporary_ulli = std::max(temporary_ulli, mode_map_ite->second);

		//�l�𓮂���
		mode_map_ite++;

	}

	//�d������ő�l�̒l�̐��𐔂���
	this->temporary_partice = 0ULL;

	//�z��̍ŏ���ݒ�
	mode_map_ite = mode_map.begin();

	//���߂�l��ݒ�
	this->temporary_variable = 0.0L;

	//���[�v�ŒT��
	while (mode_map_ite != mode_map.end()) {

		//map�̍ő�l�ƍő�l����v���Ă��邩�H
		if (mode_map_ite->second == temporary_ulli) {

			//�l��ݐςł����
			this->temporary_variable += mode_map_ite->first;

			//�d���̌��𐔂���
			this->temporary_partice++;

		}

		//�C�e���[�^�̍X�V
		mode_map_ite++;

	}

	//���ϒl�̎Z�o
	this->temporary_variable /= (long double)this->temporary_partice;

	//����
	return this->temporary_variable;

}