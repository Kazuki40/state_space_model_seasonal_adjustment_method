//���d��`
#pragma once

//���C�u����
#include<iostream>
#include<cmath>
#include<algorithm>

//�������l���m�̘a
long double small_accumulation_func(long double one_value, long double two_value) {

	//�ϐ���`
	long double ans;
	long double max_val;
	long double min_val;
	long double one_val_temp;
	long double two_val_temp;

	//�ϐ���ΐ���
	one_val_temp = std::logl(one_value);
	two_val_temp = std::logl(two_value);

	// log(0)=-inf �̔���
	if ((std::isinf(one_val_temp) == true) || (std::isinf(two_val_temp) == true)) {

		//�ق�0�̉��Z
		ans = one_value + two_value;

	}
	else
	{

		//��E���̔���
		max_val = std::max(one_val_temp, two_val_temp);
		min_val = std::min(one_val_temp, two_val_temp);

		//a+b=exp(ln(a))+exp(ln(b))��W�J
		//exp(ln(exp(ln(a)-ln(b))+1)+ln(b))
		ans = std::expl(max_val + std::log1pl(std::expl(min_val - max_val)));

	}

	//����
	return ans;

}