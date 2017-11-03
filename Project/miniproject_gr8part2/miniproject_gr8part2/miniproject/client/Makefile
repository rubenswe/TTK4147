# program executable name
TARGET = test
# compiler flags
CFLAGS = -g -Wall 
# linker flags
LDFLAGS = -g -lpthread
# list of sources
SOURCES = $(shell find -name "*.c")
# default rule, to compile everything
all: $(TARGET)
# define object files
OBJECTS = $(SOURCES:.c=.o)
# link programs
$(TARGET): $(OBJECTS)
	/home/student/Desktop/buildroot-avr32-v3.0.0_TTK4147/output/staging/usr/bin/avr32-linux-gcc  -o $@ $^ $(LDFLAGS)
	cp test /export/nfs/home
# compile
%.o : %.c
	/home/student/Desktop/buildroot-avr32-v3.0.0_TTK4147/output/staging/usr/bin/avr32-linux-gcc $(CFLAGS) -c -o $@ $<
# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS) 