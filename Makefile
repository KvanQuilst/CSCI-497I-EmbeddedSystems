PROGRAM=potdisp

CC=gcc-arm
CFLAGS=-g -mcpu=Cortex-m0 -O0

LD=ld-arm
LDFLAGS=-g -Tlpc1114.ld

OCD=openocd
OCDFLAGS=-f interface/stlink-v2.cfg -f target/lpc11xx.cfg

all: ${PROGRAM}

.SUFFIXES:.o

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

.s.o:
	${CC} ${CFLAGS} -o $@ -c $<

${PROGRAM}: vector.o bootstrap.o irq.o thread.o lock.o svc.o list.o ${PROGRAM}.o lpc1114.o
	${LD} ${LDFLAGS} -o $@ $^

program:
	${OCD} ${OCDFLAGS} -c "program ${PROGRAM} verify reset exit"

clean:
	-rm *.o || true
