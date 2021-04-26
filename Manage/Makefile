cc   = g++
prom = manage
deps = $(shell find ./ -name "*.h")
src  = $(shell  find ./ -name "*.cpp")
obj  = $(src:%.cpp=%.o)

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -lpthread

%.o: %.cpp $(deps)
	$(cc) -c $< -o $@ -lpthread

clean:
	rm -rf $(obj)