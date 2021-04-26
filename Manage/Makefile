cc   = g++
prom = manage
deps = $(shell find ./ -name "*.h")
src  = $(shell  find ./ -name "*.cpp")
obj  = $(src:%.cpp=%.o)

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -lpthread -std=c++17 -lpcap

%.o: %.cpp $(deps)
	$(cc) -c $< -o $@ -lpthread -std=c++17 -lpcap

clean:
	rm -rf $(obj)