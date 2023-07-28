################################################################################

CC		= gcc
CFLAGS		= -mcmodel=large -O3 -march=native -funroll-loops
REASON		= @if [ -f $@ ]; then echo "[$@: $?]"; else echo "[$@]"; fi

.c.o:
	$(REASON)
	$(COMPILE.c) $< $(OUTPUT_OPTION)

all: solver

################################################################################

mktab8: mktab8.o diff8.o key.o puzzle.o
	$(REASON)
	$(LINK.c) -o $@ $^ $(LDLIBS)

table8.c: mktab8
	$(REASON)
	mktab8 > table8.c

mktab7: mktab7.o diff7.o key.o puzzle.o
	$(REASON)
	$(LINK.c) -o $@ $^ $(LDLIBS)

table7.c: mktab7
	$(REASON)
	mktab7 > table7.c

################################################################################

ckkey: ckkey.o key.o puzzle.o
	$(REASON)
	$(LINK.c) -o $@ $^ $(LDLIBS)

ckbound: ckbound.o bound.o table8.o table7.o diff8.o diff7.o key.o puzzle.o
	$(REASON)
	$(LINK.c) -o $@ $^ $(LDLIBS)

test: ckkey ckbound
	$(REASON)
	ckkey
	ckbound

solver: solver.o bound.o table8.o table7.o diff8.o diff7.o key.o puzzle.o
	$(REASON)
	$(LINK.c) -o $@ $^ $(LDLIBS)

################################################################################

deps depend:
	$(REASON)
	$(CC) -MM $(CFLAGS) *.c > deps

tags:
	$(TAGS) $(TAGSFLAGS) -o $@ *.h *.cc

clean:
	$(RM) *.o mktab8 mktab7 table8.c table7.c ckkey ckbound

distclean: clean
	$(RM) core err deps tags *~ solver

-include deps

################################################################################
