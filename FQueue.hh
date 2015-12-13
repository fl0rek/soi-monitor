#define FQnext(x) ((x+1)%Size)

#include <stdexcept>
#include <array>
#include <memory>
#include <sstream>

template<typename T, unsigned Size>
class FQueue {
public:
	FQueue() { }

	T&& pop() {
		if(this->empty())
			throw std::out_of_range("pop");

		auto ret = q.at(start);
		start = FQnext(start);
		return std::move(ret);
	}

	void push(T&& v) {
		if(this->full())
			throw std::out_of_range("push");

		q.at(end) = v;
		end = FQnext(end);
	}

	bool full() {
		return FQnext(end) == (start);
	}

	bool empty() {
		return (start) == (end);
	}

	void print_debug(std::ostringstream& o) const {
		for(unsigned i = start; i != end; i = FQnext(i)) {
			o << "\t" << i << " : " << *q.at(i) << "\n";
		}
	}
private:
	unsigned start = 0, end = 0;
	std::array<T, Size> q;

};
