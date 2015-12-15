TARGET_LIB = libutf8v.so
TARGET_BIN = test_utf8v
all: $(TARGET_LIB) $(TARGET_BIN)

COVERAGE_FLAGS=--coverage

LIB_OBJS=utf8v.o
BIN_OBJS=thc.o \
		 test_utf8v.o

$(TARGET_LIB): $(LIB_OBJS)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

$(TARGET_BIN): $(TARGET_LIB) $(BIN_OBJS)
	$(CC) $(CFLAGS) -o $@ -L. -lutf8v $(BIN_OBJS)

test: clean
	@gcc -g -I src/ src/utf8v.c src/thc.c tests/test_utf8v.c $(CFLAGS) \
	-o test -DDEBUG=1
	@./test

coverage:
	gcc -g -I src/ src/utf8v.c src/thc.c \
		  tests/test_utf8v.c \
		  $(CFLAGS) $(COVERAGE_FLAGS) $(LIBS) -o coverage_utf8v -DDEBUG=0 -DTEST=1
	      ./coverage_utf8v
		  lcov --directory . --capture --output-file app.info
		  genhtml --output-directory coverage/ app.info

%.o:%.c
	    $(CC) -I. -fpic -shared -c -o $@ $< 

clean:
	rm -f *.o
	rm -f *.a
	rm -rf coverage/
	rm -f  *.gcno *.gcda
	rm -f app.info
	rm -f  test
	rm -f  coverage_utf8v
