#pragma once

//�p�b�P�[�W
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<istream>
#include<vector>
#include<random>
#include<cmath>
#include<string>
#include<algorithm>
#include<numeric>
#include<chrono>


//����֐���`
#include"homemade_function_header_files.h"

//�}�N��
//���[�v
#define rep(i,n) for(i=0;i<n;i++)

//�~����
#define pi() std::acos(-1.0L)

//�ύX����l
//���O�Ɍ��߂���́�

//��ԕϐ��̎���
#define max_state_dimension 8

//���莞�̓��ɂ�
#define max_day 730

//�Œ胉�O�����̓�
#define max_lag_day 30

//���q��
//1�ȉ��͌v�Z�o���Ȃ�
#define max_particle 10000
//50000-10000-100000 �܂�

//�t�@�C����
//�f�[�^�t�@�C��
#define data_read_file "input/newly_confirmed_cases_daily.csv"

//�t�B���^���z�̏o�̓t�H���_
#define data_filter_file "output/ans_filter5.csv"

//�ŏI�̉��̏o�̓t�H���_
#define data_weite_file "output/ans_smoothing5.csv"

//���z�`�o�̓t�@�C��
#define distribution_file_name_front "output/distribution_"
#define distribution_file_name_back "_5.csv"

#define distribution_output true
//���O�Ɍ��߂���́�

//���C��
//���s�t�@�C��
long double main_function(long double sd_random_inital, long double sd_random_inital_week, long double trend_a_e, long double  trend_b_e, long double trend_week_e, long double observation_e) {

	//���s���ԋL�^
	//�Q�l�Fttp://vivi.dyndns.org/tech/cpp/timeMeasurement.html
	auto start_time_main = std::chrono::system_clock::now();

	//������

	//�ϐ���`�i�v�����j
	unsigned long long int loop_i, loop_j, loop_k, calculating_now_day_t, now_particle, state_variables_being_calculayed, move_day;
	long double temporary_value, obsevation_ome, sum_of_likelihood_importance_weight, resumpling_value, accumulation_value, effective_sample_size;


	//�����l���܂߂�����
	//�s�ϒl
	//�R���p�C�����萔
	//�ő�l+1��
	constexpr unsigned long long int max_day_puls_initial = 1 + max_day;

	//�ő�l+���O�ő�l
	constexpr unsigned long long int max_day_puls_initial_puls_lag = max_day_puls_initial + max_lag_day;

	//���O�ő�l+1��
	constexpr unsigned long long int max_lag_day_puls_initial = max_lag_day + 1;

	//��ԕϐ���4�{�i���ϒl�A�s�Ε��U�A�����l�A�ŕp�l�p�j
	constexpr unsigned long long int max_output_data_column = max_state_dimension * 4;

	//�n�����T���v�����O�p�̍X�V��
	constexpr long double  update_step_value = (long double)1.0L / max_particle;

	//�f�[�^�ǂݎ�� 
	//�t�@�C���ǂݎ��
	//�ϑ��ϐ�
	std::vector<long double>data_observation_varuable_y_vector;
	data_observation_varuable_y_vector.resize(max_day_puls_initial);

	//�֐���`���
	data_observation_varuable_y_vector = read_data_file_func(data_observation_varuable_y_vector.size(), data_read_file);


	//�ŏI��ԕϐ��̒�`
	std::vector<std::vector<long double>>result_state_value;
	result_state_value.resize(max_output_data_column);
	rep(loop_i, max_output_data_column)result_state_value.at(loop_i).resize(max_day_puls_initial_puls_lag);

	//��ԕϐ��̒�`
	std::vector<std::vector<std::vector<long double>>>now_state_value_xt(max_state_dimension, std::vector < std::vector < long double>>(max_particle, std::vector<long double>(max_lag_day_puls_initial, 0.0L)));

	//��ԍX�V�p���ϐ��̒�`
	std::vector<std::vector<std::vector<long double>>>update_sampling(max_state_dimension, std::vector < std::vector < long double>>(max_particle, std::vector<long double>(max_lag_day_puls_initial, 0.0L)));

	//��Ԍv�Z�p���x�N�g��
	std::vector<long double> update_bacis_variable(max_particle);

	//smpling-Importance-resmpling
	//�d�݂̒�`
	std::vector<long double>weight_observation_state;
	weight_observation_state.resize(max_particle);
	rep(loop_i, max_particle)weight_observation_state.at(loop_i) = 0.0L;

	//�d�݂̔ԍ��p
	std::vector<unsigned long long int> weight_numkber;
	weight_numkber.resize(max_particle);

	//�����`�N���X�̕\��
	class basic_statistics vector_answer_output;
	class importance_weight partice_importance_weight_answer;


	//���f���ύX���E�ύX����l

	//�����̒�`
	//�����_��(���S�����_��)
	//std::random_device random_device_seed_initial;

	//���������̃V�[�h�l 0
	//std::mt19937_64 seed_value(random_device_seed_initial());
	std::mt19937_64 seed_value(0);

	//�����̒�`
	//�����p�����[�^

	std::normal_distribution<>random_inital_state(0.0L, sd_random_inital);
	std::normal_distribution<>random_inital_state_week(0.0L, sd_random_inital_week);

	//�n�C�p�[�p�����[�^�̐���
	std::normal_distribution<>random_trend_a(0.0L, trend_a_e);
	std::normal_distribution<>random_trend_b(0.0L, trend_b_e);
	std::normal_distribution<>random_week(0.0L, trend_week_e);
	//�n�C�p�[�n�C�p�[�p�����[�^


	//���T���v�����O
	// �n�����T���v�����O
	// 0.0�ȏ�1.0�����̒l�𓙊m���Ŕ���������
	std::uniform_real_distribution<>random_system_sampling(0.0L, ((long double)1.0L / max_particle));


	//�����I��


	//�v�Z�J�n

	//��������
	//��ԁi�n�C�p�[�p�����[�^�j
	//now_day=0�̒l

	//x_0
	rep(loop_i, 2)rep(loop_j, max_particle)now_state_value_xt.at(loop_i).at(loop_j).at(0) = std::abs(random_inital_state(seed_value));

	for (loop_i = 2; loop_i < 8; loop_i++)rep(loop_j, max_particle)now_state_value_xt.at(loop_i).at(loop_j).at(0) = random_inital_state_week(seed_value);

	//���ȑg�D����ԋ�ԃ��f���̎��ɕK�v


	//�ޓx�v�Z�p
	sum_of_likelihood_importance_weight = 0.0L;

	//1������
	//��ԋ�ԃ��f���̐���J�n
	for (calculating_now_day_t = 1; calculating_now_day_t < max_day_puls_initial; calculating_now_day_t++) {


		//���z�`�o�͔���
		//�f�[�^�C���t, �t�@�C�����i�O�j�C�t�@�C�����i��j,�Ώۓ�
		if (distribution_output == true) {
			distribution_func(now_state_value_xt, calculating_now_day_t, distribution_file_name_front, distribution_file_name_back, max_lag_day);
		}

		//��ԃ��f���X�V�X�e�b�v
		//���Ԃ�A�ύX���Ȃ��Ă��g���ł���Ǝv��
		rep(state_variables_being_calculayed, max_state_dimension) {

			//�L�^�p
			rep(now_particle, max_particle) {


				//�k��A���S���Y��

				//���ϒl�E���U�E�ŕp�l�𒲂ׂ邽�߂ɓ����
				//now_state_value_xt�̈����́A�ϐ��A���q�A���t
				//���t��max_lag_day_puls_initall�Œ�`���Ă���
				//�ŏI���̒l��-1�Ȃ̂ŁAmax_lag_day
				//�O�̎��_�ōŏI���̒l�͍X�V�ɂ���ď�����̂ŁA���̗��q�𓚂��ɂ��邽�߁A�x�N�g����
				update_bacis_variable.at(now_particle) = now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(max_lag_day);

				//�l���X���C�h
				for (move_day = max_lag_day; move_day > 0; move_day--) {

					//max��max-1�A...3��2�A2��1�A1��0�Œl����������l�ɋL�q
					now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(move_day) = now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(move_day - 1);

				}

				//���ꂩ��v�Z���鍀�ڂ�0�ɂ���
				now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(0) = 0.0L;

			}

			//�N���X�Ŋ�{���v�ʂ��v�Z
			vector_answer_output.claculate_basic_statistics_func(update_bacis_variable);


			//�L��

			//�����ł͒l��-1����
			// 2���ڂ�1���ڂ̋L�^�����邩��
			// �ŏI��(5���Ƃ���Ɓj��4�ɓ����
			// �ő�l��max_day_puls_ititail-2
			//�l���
			//���ϒl
			result_state_value.at(state_variables_being_calculayed).at(calculating_now_day_t - 1) = vector_answer_output.average_value;

			//�s�Ε��U
			result_state_value.at(state_variables_being_calculayed + max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.unbaised_standard_deviation_value;

			//�����l
			result_state_value.at(state_variables_being_calculayed + 2 * max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.median_value;

			//�ŕp�l
			result_state_value.at(state_variables_being_calculayed + 3 * max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.mode_value;

		}



		////�d�݂̘a
		//weight_sum = 0.0L;

		//����
		//����
		//�z��ȊO�̓v���C�x�[�g�ϐ�
		//���ɒu���ϐ���private�Œ�`���邱�Ƃł��ꂼ��Ŋ��p
		//�X���b�h�ʁX�Ōʂ̕ϐ��I�Ȋ���
		rep(now_particle, max_particle) {

			//���f���̕ύX

			//��ԋ�ԃ��f���̃R�[�h��ύX�������͂������牺��ύX
			//��ԋ�ԃ��f��
			//��ԍX�V
			//�V�X�e�����f��

			//P(x_t|x_t-1)

			//�p�����[�^�[�X�V
			//�ύX�K�v

			//�p�����[�^�̐ݒ�

			//�����ϓ�����
			//6�̂���5���ړ�
			for (loop_i = 7; loop_i > 2; loop_i--) {
				now_state_value_xt.at(loop_i).at(now_particle).at(0) = now_state_value_xt.at(loop_i - 1).at(now_particle).at(1);
			}

			//1�T�Ԃ̘a��const.
			//t1+t2+t3+t4+t5+t6+t7=0
			//t1=-(t2+t3+t4+t5+t6+t7)
			temporary_value = 0.0L;
			rep(loop_i, 6) {
				temporary_value += now_state_value_xt.at(2 + loop_i).at(now_particle).at(1);
			}

			//�g�����h a
			now_state_value_xt.at(0).at(now_particle).at(0) = now_state_value_xt.at(0).at(now_particle).at(1) + random_trend_a(seed_value);
			//�g�����h b
			now_state_value_xt.at(1).at(now_particle).at(0) = now_state_value_xt.at(0).at(now_particle).at(1) + now_state_value_xt.at(1).at(now_particle).at(1) + random_trend_b(seed_value);

			//��������t�������ϓ�����
			now_state_value_xt.at(2).at(now_particle).at(0) = -temporary_value + random_week(seed_value);




			//�ϑ����f��


			//P(y_t|x_t)


			//�ޓx
			//���p
			//���͑ΐ��ޓx
			temporary_value = 0.0L;

			//�ϑ����f���̌덷
			obsevation_ome = observation_e;

			//���p
			temporary_value = now_state_value_xt.at(1).at(now_particle).at(0) + now_state_value_xt.at(2).at(now_particle).at(0);

			//�ޓx
			weight_observation_state.at(now_particle) = ((long double)1.0L / ((std::sqrtl(2 * pi() * std::powl(obsevation_ome, 2.0L))))) * std::expl(-((std::powl((data_observation_varuable_y_vector[calculating_now_day_t] - temporary_value), 2.0L)) / (2 * std::powl(obsevation_ome, 2.0L))));

			//���f���̕ύX



		}


		//�d�݌v�Z
		//�d�݃N���X
		//���K��
		weight_observation_state = partice_importance_weight_answer.importance_weight_func(weight_observation_state);

		//�ΐ��ޓx�̘a
		sum_of_likelihood_importance_weight += std::logl(partice_importance_weight_answer.likelihood);


		//���s�T���v���T�C�Y
		effective_sample_size = partice_importance_weight_answer.effective_sample_size_func(weight_observation_state);

		//���T���v�����O
		//�t�B���^�����O
		//A��B���ׂ�
		//A�͌n���T���v�����O�ɂ��擾�̏d���i0����1�͈̔́j
		//�a�͑Ώۂ̖ޓx�̐��K���ς݁i0����1�͈̔́j

		//A��B���ׂ�
		//A>B�̎�,B��1���₷
		//A<=B�̎�,���̎���B�̒l���̗p����
		//A��1���₷
		//A��1�𒴂���܂ŌJ��Ԃ��i1/N�j�������邩��

		//n=0����n�߂�
		//������������l���z(0,1/N)
		//�������邽��0�X�^�[�g�ł͂Ȃ��i���ҁj

		//N=N�̎�
		//��������+1���1�͈̔͂𒴂���͂�
		//�����N-1�܂łł�߂�


		//������
		loop_k = 0;
		loop_i = 0;

		//�`
		//��������
		resumpling_value = random_system_sampling(seed_value);

		//B
		//1�ڂ̖ޓx
		accumulation_value = weight_observation_state.at(loop_i);

		//�v�Z
		do {

			//A<=B
			//��r�p�֐�
			if (comparison_long_double_value_function(&resumpling_value, &accumulation_value) == true) {

				//B�̒l���̗p
				weight_numkber.at(loop_k) = loop_i;

				//A��1���₷
				loop_k++;

				//�`
				resumpling_value = small_accumulation_func(resumpling_value, update_step_value);
			}
			else {

				//A>B


				//B�̒l�𑝂₷
				loop_i++;

				//B
				accumulation_value = small_accumulation_func(accumulation_value, weight_observation_state.at(loop_i));

			}

			//k(A)��N�Ɠ����Ȃ�������߂�
		} while (loop_k < max_particle);


		//�X�V
		//�k��̃A���S���Y����K�p
		//weight.size()�̕]�����֐��̂��߁A���[�v��D��
		rep(loop_j, weight_numkber.size())rep(loop_i, max_state_dimension)rep(loop_k, max_lag_day_puls_initial)update_sampling.at(loop_i).at(loop_j).at(loop_k) = now_state_value_xt.at(loop_i).at(weight_numkber.at(loop_j)).at(loop_k);


		//���̏o�́i�����j
		//�t�B���^�����O���U�̕��ϒl���o��

		//�t�@�C���̎w��
		std::ofstream csv_filter(data_filter_file, std::ios::app);

		//�ϐ����ꂼ��Ōv�Z
		rep(loop_i, max_state_dimension) {

			//���ϒl���Z�o���邽�߁@0�ilong double�^�j
			temporary_value = 0.0L;

			//���[�v�Ōv�Z����
			rep(loop_j, max_particle) temporary_value += update_sampling.at(loop_i).at(loop_j).at(0);


			//���ώZ�o
			temporary_value /= max_particle;

			//�t�@�C���o��
			csv_filter << temporary_value << ",";

		}

		//���s�T���v���T�C�Y
		//���s
		csv_filter << effective_sample_size << std::endl;


		//�R�s�[
		//���T���v�����O�p�z����v�Z�p�̔z��ɃR�s�[
		now_state_value_xt = update_sampling;

		////�f�o�b�O�p
		////�z��̒��g
		//rep(loop_k, max_lag_day_puls_initial) {
		//	rep(loop_j, max_particle) {
		//		rep(loop_i, max_state_dimension) {
		//			std::cout << now_state_value_xt.at(loop_i).at(loop_j).at(loop_k) << " ";
		//		}

		//		std::cout << std::endl;
		//	}
		//	std::cout << std::endl;
		//}

		//�v�Z���̓��t
		std::cout << calculating_now_day_t << "����\n";
	}

	//�I���t�߂̃f�[�^
	//�f�[�^��T�������Ȃ����߁A��������t+L��T�𒴂��邱�Ƃ��ł��Ȃ�����
	//�c��̊֐��l���o�͂���
	rep(loop_k, max_lag_day_puls_initial) {
		rep(loop_i, max_state_dimension) {
			rep(loop_j, max_particle) {

				//���ϒl�E���U�E�ŕp�l�𒲂ׂ邽�߂ɓ����
				//now_state_value_xt�̒l�͉��̕����Â�
				//30-0�܂Ōv�Z
				update_bacis_variable.at(loop_j) = now_state_value_xt.at(loop_i).at(loop_j).at(max_lag_day - loop_k);

			}

			//�N���X�Ŋ�{���v�ʂ��v�Z
			vector_answer_output.claculate_basic_statistics_func(update_bacis_variable);

			//��ł�-1�����Ă����B
			// ��ł̍ő�l��max_day_puls_ititail-2
			// ��̂�max_day���猩���max_day-1�Ȃ̂ŁAmax_day����n�߂��炿�傤�ǂ���
			//5���ڂɓ�������4���ڂ̏�񂾂���
			//����͑Ώۂ̂��̓��̃f�[�^������

			//�l���
			//���ϒl
			result_state_value.at(loop_i).at(loop_k + max_day) = vector_answer_output.average_value;

			//�s�Ε��U
			result_state_value.at(loop_i + max_state_dimension).at(loop_k + max_day) = vector_answer_output.unbaised_standard_deviation_value;

			//�����l
			result_state_value.at(loop_i + 2 * max_state_dimension).at(loop_k + max_day) = vector_answer_output.median_value;

			//�ŕp�l
			result_state_value.at(loop_i + 3 * max_state_dimension).at(loop_k + max_day) = vector_answer_output.mode_value;

			//���z�`�o�͔���
			//�f�[�^�C���t, �t�@�C�����i�O�j�C�t�@�C�����i��j,�Ώۓ�
			if (distribution_output == true) distribution_func(now_state_value_xt, max_day_puls_initial + loop_k, distribution_file_name_front, distribution_file_name_back, max_lag_day - loop_k);

		}
	}

	//�t�@�C���o�͊֐�
	write_data_func(result_state_value, data_weite_file);


	//�]���i���ʋK���j
	auto likelihood = sum_of_likelihood_importance_weight - max_day * std::logl((long double)max_particle);

	//�p�����[�^���ς���
	//1���_�̏�ԕϐ�+�n�C�p�[�p�����[�^��
	auto aic = -2 * likelihood + (long double)2.0L * (max_state_dimension + 1LL);
	auto bic = -2 * likelihood + (long double)1.0L * max_state_dimension * std::logl((long double)max_particle);

	//�o��
	//�L������10��
	std::cout << std::scientific << likelihood << "\n" << aic << "\n" << bic << std::endl;

	//�I���
	//�Q�l�Fttp://vivi.dyndns.org/tech/cpp/timeMeasurement.html
	auto end_time_main = std::chrono::system_clock::now();
	auto time_main = end_time_main - start_time_main;
	auto ans_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_main).count();
	std::cout << ans_time << " milli sec \n";

	//�I���
	return likelihood;

}
