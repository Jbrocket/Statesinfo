CMP = gcc -std=c11
FUNC = statesfunc
MAIN = statesmain
EXEC = runstates

$(EXEC): $(FUNC).o $(MAIN).o
	$(CMP) $(FUNC).o $(MAIN).o -o $(EXEC) -lm

$(FUNC).o: $(FUNC).c $(FUNC).h
	$(CMP) -c $(FUNC).c -o $(FUNC).o

$(MAIN).o: $(MAIN).c $(FUNC).h
	$(CMP) -c $(MAIN).c -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)