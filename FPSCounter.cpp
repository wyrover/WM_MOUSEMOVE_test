//
//	FPSCounter.{h|cpp} - simple performance check class for fps (frame per second).
//
// github:
//     https://github.com/yoggy/FPSCounter
//
// license:
//     Copyright (c) 2015 yoggy <yoggy0@gmail.com>
//     Released under the MIT license
//     http://opensource.org/licenses/mit-license.php
//
#include "FPSCounter.h"

#include <iostream>
#include <sstream>
#include <limits>

FPSCounter::FPSCounter(const std::string &name, const int &check_count, const bool &debug_output)
	: name_(name), check_count_(check_count), debug_output_(debug_output)
{
	clear();
}

FPSCounter::FPSCounter(const FPSCounter &obj)
{
	copy(obj, *this);
}

FPSCounter& FPSCounter::operator=(const FPSCounter &obj)
{
	copy(obj, *this);
	return *this;
}

void FPSCounter::copy(const FPSCounter &src, FPSCounter &dst)
{
	dst.name_ = src.name_;
	dst.check_count_ = src.check_count_;
	dst.debug_output_ = src.debug_output_;

	dst.st_ = src.st_;
	dst.count_ = src.count_;
	dst.t_ = src.t_;
	dst.fps_ = src.fps_;
}

FPSCounter::~FPSCounter()
{

}

void FPSCounter::clear()
{
	st_ = get_tick_count_();
	count_ = 0;
	t_ = 0;
	fps_ = 0;
}

std::string FPSCounter::name() const
{
	return name_;
}

void FPSCounter::name(const std::string &val)
{
	name_ = val;
}

int FPSCounter::check_count() const
{
	return check_count_;
}

void FPSCounter::check_count(const int &val)
{
	if (val <= 0) {
		printf("ERROR : FPSCounter::check_count(const int &val) : invalid val...val=%d\n", val);
		return;
	}
	check_count_ = val;
	clear();
}

bool FPSCounter::debug_output() const
{
	return debug_output_;
}

void FPSCounter::debug_output(const bool &flag)
{
	debug_output_ = flag;
}

float FPSCounter::t() const
{
	return t_;
}

float FPSCounter::fps() const
{
	return fps_;
}

void FPSCounter::check()
{
	count_++;
	if (count_ == check_count_) {
		FPS_COUNTER_TICK_TYPE et = get_tick_count_();
		FPS_COUNTER_TICK_TYPE diff_tick = et - st_;

		float diff_sec = diff_tick / (float)FPS_COUNTER_TICK_PRECISION;

		t_ = diff_sec / (float)check_count_;
		fps_ = 1.0f / t_;

		st_ = et;
		count_ = 0;

		if (debug_output_) {
			output_status_string();
		}
	}
}

void FPSCounter::output_status_string() const
{
	std::cout << status_string() << std::endl;
}

std::string FPSCounter::status_string() const
{
	std::stringstream ss;
	ss.precision(4);
	ss << name() << " : " << "t=" << t() << ", fps=" << fps();

	return ss.str();
}

FPS_COUNTER_TICK_TYPE FPSCounter::get_tick_count_()
{
	return ::GetTickCount();
}

