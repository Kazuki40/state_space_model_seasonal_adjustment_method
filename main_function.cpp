#pragma once

//パッケージ
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


//自作関数定義
#include"homemade_function_header_files.h"

//マクロ
//ループ
#define rep(i,n) for(i=0;i<n;i++)

//円周率
#define pi() std::acos(-1.0L)

//変更する値
//事前に決めるもの↓

//状態変数の次元
#define max_state_dimension 8

//推定時の日にち
#define max_day 730

//固定ラグ平滑の日
#define max_lag_day 30

//粒子数
//1以下は計算出来ない
#define max_particle 10000
//50000-10000-100000 まで

//ファイル名
//データファイル
#define data_read_file "input/newly_confirmed_cases_daily.csv"

//フィルタ分布の出力フォルダ
#define data_filter_file "output/ans_filter5.csv"

//最終の解の出力フォルダ
#define data_weite_file "output/ans_smoothing5.csv"

//分布形出力ファイル
#define distribution_file_name_front "output/distribution_"
#define distribution_file_name_back "_5.csv"

#define distribution_output true
//事前に決めるもの↑

//メイン
//実行ファイル
long double main_function(long double sd_random_inital, long double sd_random_inital_week, long double trend_a_e, long double  trend_b_e, long double trend_week_e, long double observation_e) {

	//実行時間記録
	//参考：ttp://vivi.dyndns.org/tech/cpp/timeMeasurement.html
	auto start_time_main = std::chrono::system_clock::now();

	//準備↓

	//変数定義（要件等）
	unsigned long long int loop_i, loop_j, loop_k, calculating_now_day_t, now_particle, state_variables_being_calculayed, move_day;
	long double temporary_value, obsevation_ome, sum_of_likelihood_importance_weight, resumpling_value, accumulation_value, effective_sample_size;


	//初期値を含めた日数
	//不変値
	//コンパイル時定数
	//最大値+1日
	constexpr unsigned long long int max_day_puls_initial = 1 + max_day;

	//最大値+ラグ最大値
	constexpr unsigned long long int max_day_puls_initial_puls_lag = max_day_puls_initial + max_lag_day;

	//ラグ最大値+1日
	constexpr unsigned long long int max_lag_day_puls_initial = max_lag_day + 1;

	//状態変数の4倍（平均値、不偏分散、中央値、最頻値用）
	constexpr unsigned long long int max_output_data_column = max_state_dimension * 4;

	//系統リサンプリング用の更新幅
	constexpr long double  update_step_value = (long double)1.0L / max_particle;

	//データ読み取り 
	//ファイル読み取り
	//観測変数
	std::vector<long double>data_observation_varuable_y_vector;
	data_observation_varuable_y_vector.resize(max_day_puls_initial);

	//関数定義より
	data_observation_varuable_y_vector = read_data_file_func(data_observation_varuable_y_vector.size(), data_read_file);


	//最終状態変数の定義
	std::vector<std::vector<long double>>result_state_value;
	result_state_value.resize(max_output_data_column);
	rep(loop_i, max_output_data_column)result_state_value.at(loop_i).resize(max_day_puls_initial_puls_lag);

	//状態変数の定義
	std::vector<std::vector<std::vector<long double>>>now_state_value_xt(max_state_dimension, std::vector < std::vector < long double>>(max_particle, std::vector<long double>(max_lag_day_puls_initial, 0.0L)));

	//状態更新用仮変数の定義
	std::vector<std::vector<std::vector<long double>>>update_sampling(max_state_dimension, std::vector < std::vector < long double>>(max_particle, std::vector<long double>(max_lag_day_puls_initial, 0.0L)));

	//状態計算用仮ベクトル
	std::vector<long double> update_bacis_variable(max_particle);

	//smpling-Importance-resmpling
	//重みの定義
	std::vector<long double>weight_observation_state;
	weight_observation_state.resize(max_particle);
	rep(loop_i, max_particle)weight_observation_state.at(loop_i) = 0.0L;

	//重みの番号用
	std::vector<unsigned long long int> weight_numkber;
	weight_numkber.resize(max_particle);

	//自作定義クラスの表示
	class basic_statistics vector_answer_output;
	class importance_weight partice_importance_weight_answer;


	//モデル変更時・変更する値

	//乱数の定義
	//ランダム(完全ランダム)
	//std::random_device random_device_seed_initial;

	//初期乱数のシード値 0
	//std::mt19937_64 seed_value(random_device_seed_initial());
	std::mt19937_64 seed_value(0);

	//乱数の定義
	//初期パラメータ

	std::normal_distribution<>random_inital_state(0.0L, sd_random_inital);
	std::normal_distribution<>random_inital_state_week(0.0L, sd_random_inital_week);

	//ハイパーパラメータの推定
	std::normal_distribution<>random_trend_a(0.0L, trend_a_e);
	std::normal_distribution<>random_trend_b(0.0L, trend_b_e);
	std::normal_distribution<>random_week(0.0L, trend_week_e);
	//ハイパーハイパーパラメータ


	//リサンプリング
	// 系統リサンプリング
	// 0.0以上1.0未満の値を等確率で発生させる
	std::uniform_real_distribution<>random_system_sampling(0.0L, ((long double)1.0L / max_particle));


	//準備終了


	//計算開始

	//初期乱数
	//状態（ハイパーパラメータ）
	//now_day=0の値

	//x_0
	rep(loop_i, 2)rep(loop_j, max_particle)now_state_value_xt.at(loop_i).at(loop_j).at(0) = std::abs(random_inital_state(seed_value));

	for (loop_i = 2; loop_i < 8; loop_i++)rep(loop_j, max_particle)now_state_value_xt.at(loop_i).at(loop_j).at(0) = random_inital_state_week(seed_value);

	//自己組織化状態空間モデルの時に必要


	//尤度計算用
	sum_of_likelihood_importance_weight = 0.0L;

	//1日から
	//状態空間モデルの推定開始
	for (calculating_now_day_t = 1; calculating_now_day_t < max_day_puls_initial; calculating_now_day_t++) {


		//分布形出力判定
		//データ，日付, ファイル名（前），ファイル名（後）,対象日
		if (distribution_output == true) {
			distribution_func(now_state_value_xt, calculating_now_day_t, distribution_file_name_front, distribution_file_name_back, max_lag_day);
		}

		//状態モデル更新ステップ
		//たぶん、変更しなくても拡張できると思う
		rep(state_variables_being_calculayed, max_state_dimension) {

			//記録用
			rep(now_particle, max_particle) {


				//北川アルゴリズム

				//平均値・分散・最頻値を調べるために入れる
				//now_state_value_xtの引数は、変数、粒子、日付
				//日付はmax_lag_day_puls_initallで定義している
				//最終日の値は-1なので、max_lag_day
				//前の時点で最終日の値は更新によって消えるので、その粒子を答えにするため、ベクトル化
				update_bacis_variable.at(now_particle) = now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(max_lag_day);

				//値をスライド
				for (move_day = max_lag_day; move_day > 0; move_day--) {

					//max←max-1、...3←2、2←1、1←0で値が動かせる様に記述
					now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(move_day) = now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(move_day - 1);

				}

				//これから計算する項目を0にする
				now_state_value_xt.at(state_variables_being_calculayed).at(now_particle).at(0) = 0.0L;

			}

			//クラスで基本統計量を計算
			vector_answer_output.claculate_basic_statistics_func(update_bacis_variable);


			//記入

			//ここでは値を-1する
			// 2日目に1日目の記録をするから
			// 最終日(5だとすると）は4に入れる
			// 最大値はmax_day_puls_ititail-2
			//値代入
			//平均値
			result_state_value.at(state_variables_being_calculayed).at(calculating_now_day_t - 1) = vector_answer_output.average_value;

			//不偏分散
			result_state_value.at(state_variables_being_calculayed + max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.unbaised_standard_deviation_value;

			//中央値
			result_state_value.at(state_variables_being_calculayed + 2 * max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.median_value;

			//最頻値
			result_state_value.at(state_variables_being_calculayed + 3 * max_state_dimension).at(calculating_now_day_t - 1) = vector_answer_output.mode_value;

		}



		////重みの和
		//weight_sum = 0.0L;

		//推定
		//並列化
		//配列以外はプライベート変数
		//仮に置く変数はprivateで定義することでそれぞれで活用
		//スレッド別々で個別の変数的な感じ
		rep(now_particle, max_particle) {

			//モデルの変更

			//状態空間モデルのコードを変更した時はここから下を変更
			//状態空間モデル
			//状態更新
			//システムモデル

			//P(x_t|x_t-1)

			//パラメーター更新
			//変更必要

			//パラメータの設定

			//周期変動成分
			//6つのうち5つを移動
			for (loop_i = 7; loop_i > 2; loop_i--) {
				now_state_value_xt.at(loop_i).at(now_particle).at(0) = now_state_value_xt.at(loop_i - 1).at(now_particle).at(1);
			}

			//1週間の和はconst.
			//t1+t2+t3+t4+t5+t6+t7=0
			//t1=-(t2+t3+t4+t5+t6+t7)
			temporary_value = 0.0L;
			rep(loop_i, 6) {
				temporary_value += now_state_value_xt.at(2 + loop_i).at(now_particle).at(1);
			}

			//トレンド a
			now_state_value_xt.at(0).at(now_particle).at(0) = now_state_value_xt.at(0).at(now_particle).at(1) + random_trend_a(seed_value);
			//トレンド b
			now_state_value_xt.at(1).at(now_particle).at(0) = now_state_value_xt.at(0).at(now_particle).at(1) + now_state_value_xt.at(1).at(now_particle).at(1) + random_trend_b(seed_value);

			//制約条件付き周期変動成分
			now_state_value_xt.at(2).at(now_particle).at(0) = -temporary_value + random_week(seed_value);




			//観測モデル


			//P(y_t|x_t)


			//尤度
			//効用
			//解は対数尤度
			temporary_value = 0.0L;

			//観測モデルの誤差
			obsevation_ome = observation_e;

			//効用
			temporary_value = now_state_value_xt.at(1).at(now_particle).at(0) + now_state_value_xt.at(2).at(now_particle).at(0);

			//尤度
			weight_observation_state.at(now_particle) = ((long double)1.0L / ((std::sqrtl(2 * pi() * std::powl(obsevation_ome, 2.0L))))) * std::expl(-((std::powl((data_observation_varuable_y_vector[calculating_now_day_t] - temporary_value), 2.0L)) / (2 * std::powl(obsevation_ome, 2.0L))));

			//モデルの変更



		}


		//重み計算
		//重みクラス
		//正規化
		weight_observation_state = partice_importance_weight_answer.importance_weight_func(weight_observation_state);

		//対数尤度の和
		sum_of_likelihood_importance_weight += std::logl(partice_importance_weight_answer.likelihood);


		//実行サンプルサイズ
		effective_sample_size = partice_importance_weight_answer.effective_sample_size_func(weight_observation_state);

		//リサンプリング
		//フィルタリング
		//AとBを比べる
		//Aは系統サンプリングによる取得の重さ（0から1の範囲）
		//Ｂは対象の尤度の正規化済み（0から1の範囲）

		//AとBを比べる
		//A>Bの時,Bを1つ増やす
		//A<=Bの時,その時のBの値を採用する
		//Aを1つ増やす
		//Aが1を超えるまで繰り返す（1/N）ずつ増えるから

		//n=0から始める
		//初期乱数を一様分布(0,1/N)
		//を加えるため0スタートではない（期待）

		//N=Nの時
		//初期乱数+1より1の範囲を超えるはず
		//よってN-1まででやめる


		//初期化
		loop_k = 0;
		loop_i = 0;

		//Ａ
		//初期乱数
		resumpling_value = random_system_sampling(seed_value);

		//B
		//1つ目の尤度
		accumulation_value = weight_observation_state.at(loop_i);

		//計算
		do {

			//A<=B
			//比較用関数
			if (comparison_long_double_value_function(&resumpling_value, &accumulation_value) == true) {

				//Bの値を採用
				weight_numkber.at(loop_k) = loop_i;

				//Aを1つ増やす
				loop_k++;

				//Ａ
				resumpling_value = small_accumulation_func(resumpling_value, update_step_value);
			}
			else {

				//A>B


				//Bの値を増やす
				loop_i++;

				//B
				accumulation_value = small_accumulation_func(accumulation_value, weight_observation_state.at(loop_i));

			}

			//k(A)のNと同じなった時やめる
		} while (loop_k < max_particle);


		//更新
		//北川のアルゴリズムを適用
		//weight.size()の評価が関数のため、ループを優先
		rep(loop_j, weight_numkber.size())rep(loop_i, max_state_dimension)rep(loop_k, max_lag_day_puls_initial)update_sampling.at(loop_i).at(loop_j).at(loop_k) = now_state_value_xt.at(loop_i).at(weight_numkber.at(loop_j)).at(loop_k);


		//解の出力（逐次）
		//フィルタリング分散の平均値を出力

		//ファイルの指定
		std::ofstream csv_filter(data_filter_file, std::ios::app);

		//変数それぞれで計算
		rep(loop_i, max_state_dimension) {

			//平均値を算出するため　0（long double型）
			temporary_value = 0.0L;

			//ループで計算する
			rep(loop_j, max_particle) temporary_value += update_sampling.at(loop_i).at(loop_j).at(0);


			//平均算出
			temporary_value /= max_particle;

			//ファイル出力
			csv_filter << temporary_value << ",";

		}

		//実行サンプルサイズ
		//改行
		csv_filter << effective_sample_size << std::endl;


		//コピー
		//リサンプリング用配列を計算用の配列にコピー
		now_state_value_xt = update_sampling;

		////デバッグ用
		////配列の中身
		//rep(loop_k, max_lag_day_puls_initial) {
		//	rep(loop_j, max_particle) {
		//		rep(loop_i, max_state_dimension) {
		//			std::cout << now_state_value_xt.at(loop_i).at(loop_j).at(loop_k) << " ";
		//		}

		//		std::cout << std::endl;
		//	}
		//	std::cout << std::endl;
		//}

		//計算中の日付
		std::cout << calculating_now_day_t << "日目\n";
	}

	//終わり付近のデータ
	//データがT日しかないため、平滑化はt+LがTを超えることができないため
	//残りの関数値を出力する
	rep(loop_k, max_lag_day_puls_initial) {
		rep(loop_i, max_state_dimension) {
			rep(loop_j, max_particle) {

				//平均値・分散・最頻値を調べるために入れる
				//now_state_value_xtの値は下の方が古い
				//30-0まで計算
				update_bacis_variable.at(loop_j) = now_state_value_xt.at(loop_i).at(loop_j).at(max_lag_day - loop_k);

			}

			//クラスで基本統計量を計算
			vector_answer_output.claculate_basic_statistics_func(update_bacis_variable);

			//上では-1をしていた。
			// 上での最大値はmax_day_puls_ititail-2
			// 上のをmax_dayから見るとmax_day-1なので、max_dayから始めたらちょうどいい
			//5日目に入れる情報は4日目の情報だから
			//今回は対象のその日のデータを入れる

			//値代入
			//平均値
			result_state_value.at(loop_i).at(loop_k + max_day) = vector_answer_output.average_value;

			//不偏分散
			result_state_value.at(loop_i + max_state_dimension).at(loop_k + max_day) = vector_answer_output.unbaised_standard_deviation_value;

			//中央値
			result_state_value.at(loop_i + 2 * max_state_dimension).at(loop_k + max_day) = vector_answer_output.median_value;

			//最頻値
			result_state_value.at(loop_i + 3 * max_state_dimension).at(loop_k + max_day) = vector_answer_output.mode_value;

			//分布形出力判定
			//データ，日付, ファイル名（前），ファイル名（後）,対象日
			if (distribution_output == true) distribution_func(now_state_value_xt, max_day_puls_initial + loop_k, distribution_file_name_front, distribution_file_name_back, max_lag_day - loop_k);

		}
	}

	//ファイル出力関数
	write_data_func(result_state_value, data_weite_file);


	//評価（情報量規準）
	auto likelihood = sum_of_likelihood_importance_weight - max_day * std::logl((long double)max_particle);

	//パラメータ数変える
	//1時点の状態変数+ハイパーパラメータ数
	auto aic = -2 * likelihood + (long double)2.0L * (max_state_dimension + 1LL);
	auto bic = -2 * likelihood + (long double)1.0L * max_state_dimension * std::logl((long double)max_particle);

	//出力
	//有効数字10桁
	std::cout << std::scientific << likelihood << "\n" << aic << "\n" << bic << std::endl;

	//終わり
	//参考：ttp://vivi.dyndns.org/tech/cpp/timeMeasurement.html
	auto end_time_main = std::chrono::system_clock::now();
	auto time_main = end_time_main - start_time_main;
	auto ans_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_main).count();
	std::cout << ans_time << " milli sec \n";

	//終わり
	return likelihood;

}
