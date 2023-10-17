#pragma once
#include <cassert>
#include <algorithm>
template <typename T>

class Range
{
public:
	// min, maxの初期化
	Range(T min, T max) :
		min_(min),
		max_(max)
	{
		assert(min_ <= max_);
	}

	/// <summary>
	/// 範囲内か？
	/// </summary>
	/// <param name="value">確認したい値</param>
	/// <returns>min 最小値 max 最大値</returns>
	bool IsInside(T value) const
	{
		return (min_ <= value) && (value <= max_);
	}

	// 範囲内にクランプする
	T Clamp(T value) const
	{
		return std::clamp(value, min_, max_);
	}

	// 範囲内でラップアラウンドする
	T Wrap(T value) const
	{
		return wrap(value, min_, max_);
	}

	// 下限値の取得
	T GetMin() const
	{
		return min_;
	}

	// 上限値の取得
	T GetMax() const
	{
		return max_;
	}

private:
	T min_;	// 下限値
	T max_; // 上限値
};