#pragma once

//�N���X�p�֐�
#include"basic_statistics.h"
#include "importance_weight.h"

//�f�[�^�ǂݎ��֐�
std::vector<long double> read_data_file_func(unsigned long long int, std::string);

//�f�[�^�o�͊֐�
void write_data_func(std::vector<std::vector<long double>>&, std::string);

//�������l�𑫂��悤
long double small_accumulation_func(long double, long double);

//�����_������r�p
bool comparison_long_double_value_function(long double*, long double*);

//���z�`�o��
void distribution_func(std::vector<std::vector<std::vector<long double>>>&, unsigned long long int, std::string, std::string, unsigned long long int);
