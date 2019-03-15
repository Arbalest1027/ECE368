CFLAGS = -Wall -Werror -O3 -g
GCC = gcc $(CFLAGS)
SRCSH = huff.c
SRCSU = unhuff.c
OBJSH = $(SRCSH:%.c=%.o)
OBJSU = $(SRCSU:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log
huff:$(OBJSH)
	$(GCC) $(OBJSH) -o huff
unhuff:$(OBJSU)
	$(GCC) $(OBJSU) -o unhuff

test1:huff
	./huff text1.txt
test2:unhuff
	./unhuff text1.txt.huff
test3:huff
	./huff text2.txt
test4:unhuff
	./unhuff text2.txt.huff
test5:huff
	./huff text3.txt
test6:unhuff
	./unhuff text3.txt.huff
test7:huff
	./huff text4.txt
test8:unhuff
	./unhuff text4.txt.huff

test9:huff
	$(VALGRIND) ./huff text1.txt
test10:unhuff
	$(VALGRIND) ./unhuff text1.txt.huff
test11:huff
	$(VALGRIND) ./huff text2.txt
test12:unhuff
	$(VALGRIND) ./unhuff text2.txt.huff
test13:huff
	$(VALGRIND) ./huff text3.txt
test14:unhuff
	$(VALGRIND) ./unhuff text3.txt.huff
test15:huff
	$(VALGRIND) ./huff text4.txt
test16:unhuff
	$(VALGRIND) ./unhuff text4.txt.huff

clean:
	/bin/rm -f huff unhuff *.o *.txt.huff *.txt.huff.unhuff *.log
