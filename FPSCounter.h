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
#pragma once

#if WIN32
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <string>

#if WIN32
#define FPS_COUNTER_TICK_TYPE DWORD
#define FPS_COUNTER_TICK_PRECISION 1000
#endif

class FPSCounter
{
public:
	FPSCounter(const std::string &name = "FPSCounter", const int &check_count = 100, const bool &debug_output = false);
	FPSCounter(const FPSCounter &obj);
	FPSCounter& operator=(const FPSCounter &obj);
	static void copy(const FPSCounter &src, FPSCounter &dst);
	virtual ~FPSCounter();

	void clear();

	std::string name() const;
	void name(const std::string &val);

	int check_count() const;
	void check_count(const int &val);

	bool debug_output() const;
	void debug_output(const bool &flag);

	float t() const;
	float fps() const;

	void check();

	void output_status_string() const;
	std::string status_string() const;

protected:
	FPS_COUNTER_TICK_TYPE get_tick_count_();

protected:
	std::string name_;
	int check_count_;
	bool debug_output_;

	FPS_COUNTER_TICK_TYPE st_;
	int count_;
	float t_;
	float fps_;
};

