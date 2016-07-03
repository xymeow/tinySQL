CC = g++
CFLAGS = -Isrc -Isrc/Interpreter -Isrc/Catalog -Isrc/Record -Iinclude -O2
OBJSDIR = .objs
VPATH = src:src/Interpreter:src/Catalog:src/Record:include
OBJS = main.o interpreter.o catalog.o record.o
TARGET = minisql 
$(OBJSDIR):
	mkdir -p ./$@
$(TARGET):$(OBJSDIR) $(OBJS)
	$(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS) -g
$(OBJS):%.o:%.cpp
	$(CC) -c $(CFLAGS) $< -o $(OBJSDIR)/$@ -g
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJSDIR)/*.o
