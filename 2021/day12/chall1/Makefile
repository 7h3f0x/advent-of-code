all: solve

run: all sample_1 sample_2 sample_3 input
	./solve sample_1
	@echo "----------------------------------"
	./solve sample_2
	@echo "----------------------------------"
	./solve sample_3
	@echo "----------------------------------"
	./solve input

format:
	clang-format -i *.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $^

solve: solve.o
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	-rm *.o solve


