#pragma once
#include <typeinfo>
#include <array>
#include <ostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <random>

// --------------------------------------------------------------------------------
//				DEFINES/USING
// --------------------------------------------------------------------------------

#define fn auto
#define let auto
#define in :
#define each auto
#define any_type template <typename any>

// Alias for std::string
using str = std::string;



// --------------------------------------------------------------------------------
//				PRINT FUNCTION
// --------------------------------------------------------------------------------

// Prints multiple arguments and ending with a line-break
template <typename... T>
void println(const T &...t)
{
	((std::cout << t << (sizeof...(T) > 1 ? ' ' : '\n')), ...);
	std::cout << std::endl;
}

// Prints empty line
void println()
{
	std::cout << std::endl;
}

// Prints to a line without creating a line-break
template <typename... T>
void print(const T &...t)
{
	((std::cout << t << (sizeof...(T) > 1 ? ' ' : '\0')), ...);
}



// --------------------------------------------------------------------------------
//				RANGE FUNCTION
// --------------------------------------------------------------------------------

template <typename IntType>
// Returns vector with integers starting at, ending up to value provided, increasing/decreasing at given step
std::vector<IntType> range(IntType start, IntType stop, IntType step)
{
	if (step == IntType(0))
	{
		throw std::invalid_argument("step for range must be non-zero");
	}

	std::vector<IntType> result;
	IntType i = start;
	while ((step > 0) ? (i < stop) : (i > stop))
	{
		result.push_back(i);
		i += step;
	}

	return result;
}

// Returns vector with integers starting at and ending up to value provided
template <typename IntType>
std::vector<IntType> range(IntType start, IntType stop)
{
	return range(start, stop, IntType(1));
}

// Returns vector with integers up to value provided
template <typename IntType>
std::vector<IntType> range(IntType stop)
{
	return range(IntType(0), stop, IntType(1));
}



// --------------------------------------------------------------------------------
//				VECTOR FUNCTIONS
// --------------------------------------------------------------------------------
// ostream << operator overloading

// Overwrites printing to allow vectors
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << '[';
	for (size_t i = 0; i < vec.size(); ++i)
	{
		os << vec[i];
		if (i < vec.size() - 1)
			os << ", ";
	}
	os << ']';
	return os;
}

// reverse function
// Returns reversed vector
template <typename T>
std::vector<T> reverse(std::vector<T> vec)
{
	std::reverse(vec.begin(), vec.end());
	return vec;
}

// Vector initializer function
// Creates and returns a vector with multiple values provided
template <typename... Args>
auto vector(Args &&...args) -> std::vector<typename std::common_type<Args...>::type>
{
	std::vector<typename std::common_type<Args...>::type> vec;
	vec.reserve(sizeof...(Args)); // Reserve space for the number of elements

	(vec.emplace_back(std::forward<Args>(args)), ...);

	return vec;
}

// Empty Vector initializer function
// Creates and returns an empty vector
template <typename T>
std::vector<T> vector()
{
	return std::vector<T>();
}

// max function
// Return largest element in vector
template <typename T>
T max(std::vector<T> vec)
{
	return *std::max_element(vec.begin(), vec.end());
}

// min function
// Return smallest element in vector
template <typename T>
T min(std::vector<T> vec)
{
	return *std::min_element(vec.begin(), vec.end());
}



// --------------------------------------------------------------------------------
//				SORTING FUNCTIONS
// --------------------------------------------------------------------------------
// sort function
// Sort a vector in ascending order by default
template <typename T>
std::vector<T> sort(std::vector<T> vec, bool (*algorithm)(const T&, const T&) = ascending<T>)
{
	std::sort(vec.begin(), vec.end(), algorithm);
	return vec;
}

// ascending sort algorithm
// Ascending sorting algorithm
template <typename T>
bool ascending(const T& a, const T& b)
{
	return a < b;
}

// descending sort algorithm
// Descending sorting algorithm
template <typename T>
bool descending(const T& a, const T& b)
{
	return a > b;
}

// randomize function
// Randomizes vector element positions
template <typename T>
std::vector<T> randomize(std::vector<T> vec)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	for (size_t i = vec.size() - 1; i > 0; --i)
	{
		std::uniform_int_distribution<size_t> dist(0, i);
		size_t j = dist(gen);
		std::swap(vec[i], vec[j]);
	}
	return vec;
}



// --------------------------------------------------------------------------------
//				PAIR FUNCTIONS
// --------------------------------------------------------------------------------
// pair initializer function
// Creates and returns pair from 2 values provided
template <typename T1, typename T2>
auto pair(T1&& first, T2&& second)
{
	return std::make_pair(std::forward<T1>(first), std::forward<T2>(second));
}



// --------------------------------------------------------------------------------
//				RANDOM FUNCTIONS
// --------------------------------------------------------------------------------
// Namespaced to avoid overloading errors with <random>
namespace random
{
	// randint function for ints
	// Returns random whole number between 0 and max
	int randint(int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, max);
		return dist(gen);
	}

	// randint function for ints
	// Returns random whole number between min and max
	int randint(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(gen);
	}

	// rand function for floats
	// Returns random floating point number between 0 and num
	float rand(float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.0f, max);
		return dist(gen);
	}

	// rand function for floats
	// Returns random floating point number between min and max
	float rand(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	}

	// randrange function
	// Returns a vector of random numbers between 0 and max
	std::vector<int> randrange(int max, std::size_t amount)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, max);

		std::vector<int> vec(amount);
		for (auto &num : vec)
			num = dist(gen);
		return vec;
	}

	// randrange function
	// Returns a vector of random numbers between min and max
	std::vector<int> randrange(int min, int max, std::size_t amount)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(min, max);

		std::vector<int> vec(amount);
		for (auto& num : vec)
			num = dist(gen);
		return vec;
	}
}

// --------------------------------------------------------------------------------
//				TYPE FUNCTIONS
// --------------------------------------------------------------------------------
// type_of function
// Prints the type name of the value provided
template <typename T>
void type_of(const T& t)
{
	println(typeid(t).name());
}