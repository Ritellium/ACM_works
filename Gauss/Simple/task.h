#pragma once

#include "../GaussMethod/MatrixTemp.h"

template <class num>
class task {
	Matrix<num> c; // a-ka coeffishients
	Matrix<num> A; // a-ka resourses
	Matrix<num> b; // a-ka costs
	Matrix<num> d_min; // bottom limits
	Matrix<num> d_max; // top limits

	bool ended;
	bool sol_exists;
	bool logging;
	ofstream of_log;

	vector<int> base_ind;
	vector<int> non_base_ind;
	Matrix<num> plan; // a-ka x
	Matrix<num> u;
	Matrix<num> deltas;
	Matrix<num> l;
	Matrix<num> tetha;


	task() = default;

	task<num>& init_function(Matrix<num> const& _c) {
		c = _c;
	}
	task<num>& init_resources(Matrix<num> const& _A) {
		A = _A;
	}
	task<num>& init_costs(Matrix<num> const& _b) {
		b = _b;
	}
	task<num>& init_limits_min(Matrix<num> const& _d_min) {
		d_min = _d_min;
	}
	task<num>& init_limits_max(Matrix<num> const& _d_max) {
		d_max = _d_max;
	}

	task<num>& init_start_plan(Matrix<num> const& _x) {
		plan = _x;
	}

	task<num>& set_logging(string const& filename) {
		logging = true;
		of_log.open(filename);
	}

	void first_fase_task();
	void iterate();
	void find_optimum();

	void count_potentials();
	void count_deviations();
	bool is_optimal();
	void build_direction();
	bool find_direction_step();
	void change_plan();
};

template <class num>
void count_potentials() {
	auto At = A.transponent();
	u = solveSystemColumn(At, c);
}
template <class num>
void count_deviations() {
	auto buf = A.transponent() * u;
	deltas = c - buf;
}
template <class num>
bool is_optimal() {

}
template <class num>
void build_direction() {

}
template <class num>
bool find_direction_step() {

}
template <class num>
void change_plan() {

}

{
	/*auto At = A.transponent();
	auto u = solveSystemColumn(At, c);
	auto buf = At * u;
	auto delta = c - buf;

	bool optimal = true;
	size_t index_to_change = 0;
	for (size_t i = 0; i < plan.rows(); i++)
	{
		if (plan[i] == d_min[i] && delta[i] > 0)
		{
			optimal = false;
			index_to_change = i;
		}
		if (plan[i] == d_max[i] && delta[i] < 0)
		{
			optimal = false;
			index_to_change = i;
		}
	}
	if (optimal)
	{
		ended = true;
		sol_exists = true;
		return *this;
	}*/
}

template <class num>
void task<num>::find_optimum() {
	while (!ended)
	{
		iterate();
	}
}

template <class num>
void task<num>::iterate() {
	if (plan.rows() == 0)
	{
		first_fase_task();
	}

	count_potentials();
	count_deviations();
	if (is_optimal())
	{
		ended = true;
		sol_exists = true;
	}
	build_direction();
	if (!find_direction_step())
	{
		ended = true;
		sol_exists = false;
	}
	change_plan();
}