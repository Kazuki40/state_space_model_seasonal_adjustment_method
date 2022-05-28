//���d��`
#pragma once

//�t�@�C���C���N���[�h
#include "importance_weight.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<numeric>


//�}�N��
#define rep(i, n) for (i = 0; i < n; i++)


//�R���X�g���N�^
//�����l�̒�`
importance_weight::importance_weight() {
	this->loop_func_value = 0ULL;
	this->loglikelihood = 0.0L;
	this->likelihood = 0.0L;
	this->temp = 0.0L;
}

//�f�R���X�g���N�^
importance_weight::~importance_weight() {
	//std::cout << "e" << std::endl;
}

//�d�݂̐��K��
std::vector<long double>importance_weight::importance_weight_func(std::vector<long double>& data_set) {
	
	//���t�H���_�w��
	std::vector<long double>use_data = data_set;

	//�\�[�g
	std::sort(use_data.begin(), use_data.end());
	
	//���a�̌v�Z
	//�ΐ��̘a����邽�߂̊֐�accumulate�֐�
	//�����́A��1�F�J�n�ꏊ�A��2�F�I���ꏊ�A��3�F�����l�A�����l�̌^�������Ȃ̂�0.0L(0��long double �^�j
	this->likelihood = std::accumulate(data_set.begin(), data_set.end(), 0.0L);

	//�ΐ��ޓx�̌v�Z
	this->loglikelihood = std::logl(this->likelihood);

	//�����p�̔z���`
	std::vector<long double> importance_weight_result;
	importance_weight_result.resize(data_set.size());

	//�d��
	rep(this->loop_func_value, data_set.size()) {

		//���K��
		importance_weight_result.at(this->loop_func_value) = data_set.at(this->loop_func_value) / this->likelihood;

	}

	//����
	return importance_weight_result;

}


//�����T���v���T�C�Y
long double importance_weight::effective_sample_size_func(std::vector<long double>& data) {

	//���t�H���_�w��
	std::vector<long double>use_data = data;

	//�ޓx��2�悷��
	rep(this->loop_func_value, data.size())use_data.at(this->loop_func_value) = std::powl(data.at(this->loop_func_value), 2.0L);

	//�\�[�g
	std::sort(use_data.begin(),use_data.end());

	//�����T���v���T�C�Y�̎��ɓ����
	//���ꂪ2��a�Ȃ̂�
	temp = 1.0L / std::accumulate(use_data.begin(), use_data.end(), 0.0L);

	//����
	return(temp);

}
