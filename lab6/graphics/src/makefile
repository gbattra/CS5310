# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc

# use this line on the engin linux machines
# CC = gcc296

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -I/opt/local/include -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations
CPPFLAGS = $(CFLAGS)

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -limageIO -lm
LFLAGS = -L$(LIBDIR) -L/opt/local/lib

# put all of the relevant include files here
_DEPS = ppmIO.h graphics.h image.h fractals.h noise.h line.h point.h circle.h elipse.h polyline.h stack.h \
		floodfill.h polygon.h vector.h matrix.h view.h

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = ppmtest lab1 mask composite image_api fractalstest fractalmain perlinnoise \
			  test3d circletest elipsetest test3a test3b test3c illustration testbench \
			  floodfilltest polygontest test4a test4c test4b rocket barycentricimg test5a \
			  test5b test5c scene2d scene3d aliens2d test6a test6b lab6cube restaurant

LAB1_EXECUTABLES = lab1 \
				   mask \
				   composite

LAB2_EXECUTABLES = image_api fractalstest perlinnoise fractalmain

LAB3_EXECUTABLES = test3d circletest elipsetest test3a test3b test3c illustration testbench floodfilltest

LAB4_EXECUTABLES = polygontest test4a test4c test4b rocket barycentricimg

LAB5_EXECUTABLES = test5a test5b test5c scene2d scene3d aliens2d

LAB6_EXECUTABLES = test6a test6b lab6cube restaurant

# put a list of all the object files here for all executables (with .o endings)
_OBJ = tiffmain.o ppmmain.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all:
	for i in $(EXECUTABLES); do (make $$i) ; done

lab1execs:
	for i in $(LAB1_EXECUTABLES); do (make $$i); done

lab2execs:
	for i in $(LAB2_EXECUTABLES); do (make $$i); done

lab3execs:
	for i in $(LAB3_EXECUTABLES); do (make $$i); done

lab4execs:
	for i in $(LAB4_EXECUTABLES); do (make $$i); done

lab5execs:
	for i in $(LAB5_EXECUTABLES); do (make $$i); done

lab6execs:
	for i in $(LAB6_EXECUTABLES); do (make $$i); done

# put the specific executable rules here
ppmtest: $(ODIR)/ppmmain.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

lab1: $(ODIR)/lab1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

mask: $(ODIR)/mask.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

composite: $(ODIR)/composite.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

image_api: $(ODIR)/image_api.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

fractalstest: $(ODIR)/fractalstest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

fractalmain: $(ODIR)/fractalmain.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

perlinnoise: $(ODIR)/perlinnoise.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3d: $(ODIR)/test3d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

circletest: $(ODIR)/circletest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

elipsetest: $(ODIR)/elipsetest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3a: $(ODIR)/test3a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3b: $(ODIR)/test3b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3c: $(ODIR)/test3c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

illustration: $(ODIR)/illustration.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testbench: $(ODIR)/testbench.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

floodfilltest: $(ODIR)/floodfilltest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

polygontest: $(ODIR)/polygontest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4a: $(ODIR)/test4a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4b: $(ODIR)/test4b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4c: $(ODIR)/test4c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

rocket: $(ODIR)/rocket.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

barycentricimg: $(ODIR)/barycentricimg.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5a: $(ODIR)/test5a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5b: $(ODIR)/test5b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5c: $(ODIR)/test5c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

scene2d: $(ODIR)/scene2d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

aliens2d: $(ODIR)/aliens2d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

scene3d: $(ODIR)/scene3d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test6a: $(ODIR)/test6a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test6b: $(ODIR)/test6b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

lab6cube: $(ODIR)/lab6cube.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

restaurant: $(ODIR)/restaurant.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

