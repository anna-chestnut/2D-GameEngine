#pragma once
namespace Engine {

	template<typename T>
	inline void Swap(T& i_first, T& i_second)
	{
		T tmp = i_first;
		i_first = i_second;
		i_second = tmp;
	}

	inline bool IsZeroF(float i_f) {

		return fabs(i_f) <= 0.000001f;
	}
}
