#include "FQueue.hh"
#include "monitor.h"

#include <sstream>

template<typename T, unsigned Size, unsigned Priorities>
class FMultiQueue : protected Monitor {
public:
	T&& recv() {
		enter();

		if(!msg_count)
			wait(notEmpty);
		msg_count--;

		T ret; 
		for(unsigned i = 0; i < Size; i++) {
			if(!qs.at(i).empty()) {
				ret = qs.at(i).pop();
				notFull.at(i).signal();
				break;
			}
		}

		leave();
		return std::move(ret);
	}

	void send(T&& v, unsigned priority) {
		enter();

		if(qs.at(priority).full())
			wait(notFull.at(priority));

		qs.at(priority).push(std::move(v));

		if(!msg_count++) 
			signal(notEmpty);
		
		leave();
	}

	std::string print_debug() { // cannot be const, because enter/leave 
		enter();
		std::ostringstream out;
		out << "Queue ====\n";
		for(unsigned i = 0; i < Size; i++) {
			out << "pri : " << i << "\n";
			qs.at(i).print_debug(out);
		}
		leave();
		return out.str();
	}
private:
	unsigned msg_count = 0;
	Condition notEmpty;
	typedef FQueue<T, Size> FQueue_type;

	std::array<FQueue_type, Priorities> qs;
	std::array<Condition, Priorities> notFull;

};
