

objs = a.o c.o b.o

dep_fils := $(patsubst %, .%.d, $(objs))
dep_fils := $(wildcard $(dep_fils))

CFLAGS = -Werror -I include/

test: $(objs)
	gcc -o test $^

ifneq ($(dep_fils),)  #如果该变量不为空就包含进来
include $(dep_fils)
endif

c.o: c.c c.h

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< -MD -MF .$@.d

clean:
	rm *.o test

distclean:
	rm $(dep_fils)

.PHONY: clean