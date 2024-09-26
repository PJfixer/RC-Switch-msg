# Defines the RPI variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DRPI
RCSWITCH_LIB_PATH=./rc-switch

all: silvercrest

silvercrest: $(RCSWITCH_LIB_PATH)/RCSwitch.o silvercrest.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o silvercrest
