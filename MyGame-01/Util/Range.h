#pragma once
#include <cassert>
#include <algorithm>
template <typename T>

class Range
{
public:
	// min, max�̏�����
	Range(T min, T max) :
		min_(min),
		max_(max)
	{
		assert(min_ <= max_);
	}

	/// <summary>
	/// �͈͓����H
	/// </summary>
	/// <param name="value">�m�F�������l</param>
	/// <returns>min �ŏ��l max �ő�l</returns>
	bool IsInside(T value) const
	{
		return (min_ <= value) && (value <= max_);
	}

	// �͈͓��ɃN�����v����
	T Clamp(T value) const
	{
		return std::clamp(value, min_, max_);
	}

	// �͈͓��Ń��b�v�A���E���h����
	T Wrap(T value) const
	{
		return wrap(value, min_, max_);
	}

	// �����l�̎擾
	T GetMin() const
	{
		return min_;
	}

	// ����l�̎擾
	T GetMax() const
	{
		return max_;
	}

private:
	T min_;	// �����l
	T max_; // ����l
};