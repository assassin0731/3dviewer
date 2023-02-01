UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=leaks -quiet -atExit --
endif
CCFLAGS=-Wall -Werror -Wextra -std=c11
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES=C-files/myMain.c

all: clean s21_viewer gcov_report dist clean

style:
	clang-format -n CalcFiles/*.c CalcFiles/*.h QCfiles/*.cpp QCfiles/*.h *.c

style_force:
	clang-format -i CalcFiles/*.c CalcFiles/*.h QCfiles/*.cpp QCfiles/*.h

s21_viewer: clean
	gcc $(CFLAGS) -c $(SOURCES)
	ar rc s21_viewer.a *.o
	ranlib s21_viewer.a
	rm -f *.o

build: clean
	mkdir ../build/
	cp Viewer3.pro ../build/
	cd ../build/; qmake Viewer3.pro
	make -C ../build/

install: build
	mkdir 3DViewer
	cp -rf ../build/Viewer3.app 3DViewer
	make clean

uninstall:
	rm -rf 3DViewer

dvi:
	pdflatex document.tex

dist: uninstall install
	tar -zcvf Viewer_Archive.tar 3DViewer

gcov_report: clean
	gcc $(GFLAGS) $(CFLAGS) $(SOURCES) test.c $(LFLAGS) -o test
	-./test > test.log
	bash test_log.sh
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
test: s21_viewer
	gcc $(CFLAGS) test.c s21_viewer.a -L. $(LFLAGS) -o test
	-./test > test.log
	bash test_log.sh

leaks: s21_viewer
	gcc $(CFLAGS) test.c s21_viewer.a -L. $(LFLAGS) -o test
	CK_FORK=no $(LEAK) ./test > leak.log
	bash test_leak.sh

rebuild: clean gcov_report

clean:
	rm -f test s21_viewer.a *.gc* test.info log.xml test.log leak.log
	rm -f -rf report
	rm -f document.aux document.log document.pdf document.out
	rm -rf ../build
