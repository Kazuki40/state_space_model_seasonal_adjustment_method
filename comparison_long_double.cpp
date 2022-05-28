//�d���錾������
#pragma once

//�p�b�P�[�W����
#include<iostream>
#include<algorithm>

//�֐��𐶐�
//��r�p�֐�
bool comparison_long_double_value_function(long double* one_value, long double* two_value) {

	//�v�Z�p�C�v�V����
	long double ep = (std::numeric_limits<long double>::epsilon());

	//��r
	//A<=B
	//0<B-A,0=B-A

	//B-A
	long double evaluation_value = *two_value - *one_value;

	//��r
	//0!=ep
	//ep:�v�Z�@�C�v�V�����~1or�ő�l

	//B-A ��0���傫�����͐^
	//B-A�̐�Βl��ep��菬�������͐^
	//����ȊO�͋U
	bool ans_comparison = (std::abs(evaluation_value)<=ep? true:(evaluation_value>=0? true :false));

	//������Ԃ�
	return ans_comparison;

}