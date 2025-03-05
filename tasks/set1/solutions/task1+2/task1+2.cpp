#include <iostream>

struct Vector3d {
	float x;
	float y;
	float z;
};

// f-n for creating a 3d vector
Vector3d createVector3d(float x, float y, float z) {
	return { x, y, z };
}

// f-n for printing a 3d vector on the console
void printVector3d(const Vector3d& v) {
	std::cout << '[' << v.x << ", " << v.y << ", " << v.z << ']';
}

// f-n for adding two 3d vectors
Vector3d addVectors3d(const Vector3d& v1, const Vector3d& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// f-n for subtracting two 3d vectors
Vector3d subtractVectors3d(const Vector3d& v1, const Vector3d& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// f-n for multiplying a vector with a scalar
Vector3d scaleVector(const Vector3d& v, const float& lambda) {
	return { lambda * v.x, lambda * v.y, lambda * v.z };
}

// f-n for finding the dot product of two vectors 
float dotProduct3d(const Vector3d& v1, const Vector3d& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// f-n that checks if any 3 of n user inputted 3d vectors are perpendicular
void arePerpendicular3d(const int& n) {
	Vector3d* vectorArray = new Vector3d[n];

	std::cout << "Enter " << n << " vectors in the format x y z: \n";
	for (int i = 0; i < n; i++) {
		float x, y, z;
		std::cin >> x >> y >> z; 
		Vector3d v = createVector3d(x, y, z);
		vectorArray[i] = v;
	}

	for (int i = 0; i < n; i++) {
		Vector3d v1 = vectorArray[i];
		
		for (int j = i + 1; j < n; j++) {
			Vector3d v2 = vectorArray[j];

			for (int k = j + 1; k < n; k++) {
				Vector3d v3 = vectorArray[k];

				if (dotProduct3d(v1, v2) == 0 && dotProduct3d(v2, v3) == 0 && dotProduct3d(v1, v3) == 0) {
					std::cout << "The vectors ";
					printVector3d(v1);
					std::cout << ", ";
					printVector3d(v2);
					std::cout << " and ";
					printVector3d(v3);
					std::cout << " are perpendicular.";

					delete[] vectorArray;
					return;
				}
			}
		}
	}

	std::cout << "No perpendicular vectors in this set.";
	delete[] vectorArray;
}

int main() {
	
	Vector3d v1 = createVector3d(3.14f, 2.71f, 1.61f); 
	Vector3d v2 = createVector3d(1.41f, 1.73f, 2.23f); 

	Vector3d sum = addVectors3d(v1, v2);
	Vector3d diff = subtractVectors3d(v1, v2);
	Vector3d doubled_v1 = scaleVector(v1, 2.0f);
	float dotProd = dotProduct3d(v1, v2);

	std::cout << "Sum of the two vectors is: "; 
	printVector3d(sum);
	std::cout << '\n';
	std::cout << "The result of subtracting the second vector from the first one is: ";
	printVector3d(diff);
	std::cout << '\n';
	std::cout << "The first vector, multiplied with the scalar 2: ";
	printVector3d(doubled_v1);
	std::cout << '\n';
	std::cout << "The dot product of the two vectors is: ";
	std::cout << dotProd << '\n';

	int n = 0;
	std::cout << "Now enter how many vectors you want to input (at least 3). The program will check if any 3 of them are perpendicular: ";
	std::cin >> n;
	arePerpendicular3d(n);

	return 0;
}
