/*
 * Sample.h
 *
 *  Created on: 17.09.2018
 *      Author: rhe
 */
#pragma once

struct Sample {
	int measValue;
	int refValue;

	Sample() :
		measValue(0),
		refValue(0)
	{}

	void reset()
	{
		measValue = 0;
		refValue = 0;
	}

	void preset(int value)
	{
		measValue = value;
		refValue = value;
	}

	Sample operator+(Sample a) {
		Sample res;
		res.measValue = a.measValue + this->measValue;
		res.refValue = a.refValue + this->refValue;
		return res;
	}

	Sample operator+(int iA) {
		Sample res;
		res.measValue = iA + this->measValue;
		res.refValue = iA + this->refValue;
		return res;
	}

	Sample& operator+=(Sample a) {
		measValue += a.measValue;
		refValue += a.refValue;
		return *this;
	}

	Sample& operator+=(int iA) {
		measValue += iA;
		refValue += iA;
		return *this;
	}

	Sample operator-(Sample a) {
		Sample res;
		res.measValue = a.measValue - this->measValue;
		res.refValue = a.refValue - this->refValue;
		return res;
	}

	Sample operator-(int iA) {
		Sample res;
		res.measValue = iA - this->measValue;
		res.refValue = iA - this->refValue;
		return res;
	}

	Sample& operator-=(Sample a) {
		measValue -= a.measValue;
		refValue -= a.refValue;
		return *this;
	}

	Sample& operator-=(int iA) {
		measValue -= iA;
		refValue -= iA;
		return *this;
	}

	Sample operator*(Sample a) {
		Sample res;
		res.measValue = a.measValue * this->measValue;
		res.refValue = a.refValue * this->refValue;
		return res;
	}

	Sample operator*(int iA) {
		Sample res;
		res.measValue = iA * this->measValue;
		res.refValue = iA * this->refValue;
		return res;
	}

	Sample& operator*=(Sample a) {
		measValue *= a.measValue;
		refValue *= a.refValue;
		return *this;
	}

	Sample& operator*=(int iA) {
		measValue *= iA;
		refValue *= iA;
		return *this;
	}

	Sample operator/(Sample a) {
		Sample res;
		res.measValue = a.measValue / this->measValue;
		res.refValue = a.refValue / this->refValue;
		return res;
	}

	Sample operator/(int iA) {
		Sample res;
		res.measValue = iA / this->measValue;
		res.refValue = iA / this->refValue;
		return res;
	}

	Sample& operator/=(Sample a) {
		measValue /= a.measValue;
		refValue /= a.refValue;
		return *this;
	}

	Sample& operator/=(int iA) {
		measValue /= iA;
		refValue /= iA;
		return *this;
	}
};
