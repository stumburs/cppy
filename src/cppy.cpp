#include "cppy.hpp"

// Create functions that can take any data type
any_type fn add(any a, any b)
{
	return a + b;
}

int main()
{
	// Creates a new vector
	let vec = vector(10, 20, 30, 40, 69, 20);

	// Simple for-each loop
	for (each elem in vec)
		print(elem, ' ');

	println();

	// Reversed range loop
	for (each i in reverse(range(10)))
		print(i, ' ');

	// Multiple print arguments, including vectors
	println("\nWow, it printed this:", vec, ":)", 12.34);

	// Useful functions - finding largest element in vector
	let max_num = max(vec);
	println("Largest element in vec:", max_num);

	// Create simple pairs
	let text_pair = pair("Min:", "Max:");
	let value_pair = pair(min(vec), max(vec));
	println(text_pair.first, value_pair.first, text_pair.second, value_pair.second);

	// Use the any_type'd function
	let result = add(str("3"), str("54"));
	let result2 = add(2.0, 40.5);
	println(result);
	println(result2);

	// Sort vectors
	println("Unsorted:", vec);
	println("Sorted:", sort(vec));
	println("Sorted descending:", sort(vec, descending)); // Specify algorithm
}
