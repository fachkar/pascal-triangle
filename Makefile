CC=gcc
CFLAGS="-Wall"

debug:clean
# 	@echo "\033[92mHello World\033[0m" #only work for shell not through kdevelop cshell!
	$(warning ************  debug version ************)
	$(CC) $(CFLAGS) -std=gnu11 -g3 -fno-omit-frame-pointer -o c99testbench main.c -lpthread -lm
stable:clean
	$(info ************  stable version ************)
	$(CC) $(CFLAGS) -O3 -std=gnu11 -o c99testbench main.c -lpthread -lm
clean:
	rm -vfr *~ c99testbench
