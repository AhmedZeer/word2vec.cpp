#include <string>
#include <vector>

class Vector {

	public:
		Vector();
		Vector(Vector &&) = default;
		Vector(const Vector &) = default;
		Vector &operator=(Vector &&) = default;
		Vector &operator=(const Vector &) = default;
		~Vector();

	private:
	
};
