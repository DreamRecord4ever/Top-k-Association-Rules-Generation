CXX = g++
CXXFLAGS = -pedantic -Wall
CPPFLAGS = 
LDFLAGS = -s

compile: fpgrowth ruleGen

fpgrowth: 
	make -C ./FPgrowth/fpgrowth/src/

ruleGen: double_map.o ruleGen.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

clean:
	make clean -C ./FPgrowth/fpgrowth/src/
	rm -f *.o ruleGen 

