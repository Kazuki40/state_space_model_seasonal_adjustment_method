//miyazaki
#pragma once

//�p�b�P�[�W
#include<iostream>
#include<cmath>

//����֐���`
#include"homemade_function_header_files.h"

//���œK���A���S���Y���������炱�����肷��@��
//#define optimisation false

//hyper parameter

//����p�����[�^�̐ݒ�
//�n�C�p�[�p�����[�^�i�������z�j�̐ݒ�
//x_0
#define inital_sd 4.0L
#define sd_random_inital std::powl(10.0L,inital_sd)
#define sd_random_inital_week std::powl(10.0L,(inital_sd))

//�V�[�^
#define trend_a_e std::powl(10.0L,2)
#define trend_b_e std::powl(10.0L,4)
#define trend_week_e std::powl(10.0L,3)
#define observation_e std::powl(10.0L,4)

//���ȑg�D����ԋ�ԃ��f���̗p 

//�n�C�p�[�p�����[�^�̐ݒ�(������)�̕W���΍�

//���œK���A���S���Y���������炱�����肷��@��

//�֐��ݒ�
long double main_function(long double, long double, long double, long double, long double, long double);

//���C��
//���s�t�@�C��
int main() {

	main_function(sd_random_inital, sd_random_inital_week, trend_a_e, trend_b_e, trend_week_e, observation_e);

	std::cout << "�����@�Ȃɂ����������" << std::endl;
	long int somthing_num;
	std::cin >> somthing_num;

	return 0;
}
