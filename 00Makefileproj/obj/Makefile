$(BINDIR)/$(BIN) : $(OBJ)
	$(GXX) $^ -o $@ $(OBJHEAD) $(OBJLINK)
	@echo "==========build end=============="

cube.o : $(SRCDIR)/cube.cpp
	$(GXX) $(CFLAGS) -c $(SRCDIR)/cube.cpp  -I $(INCPATH)
sphere.o : $(SRCDIR)/sphere.cpp
	$(GXX) $(CFLAGS) -c $(SRCDIR)/sphere.cpp  -I $(INCPATH)
main.o : $(SRCDIR)/main.cpp
	$(GXX) $(CFLAGS) -c $(SRCDIR)/main.cpp  -I $(INCPATH)
	@echo "==========build object=========="
