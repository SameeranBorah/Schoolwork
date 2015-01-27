all: test_prog1 calc ccalc

test_prog1: test_prog1.cxx stack.h
	$(CXX) $< -o $@

calc: calc.cxx stack.h
	$(CXX) $< -o $@

ccalc: ccalc.cxx stack.h
	$(CXX) $< -o $@

clean:
	rm -rf calc ccalc *.exe *.o *.dSYM *~
