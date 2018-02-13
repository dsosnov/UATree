SRC=../src
INTERFACE=../interface
OBJ=../lib

CXXFLAGS+=$(shell root-config --cflags) -Wall -I../../../ -I$(SRC) -I$(INTERFACE) -ggdb3 -fPIC -O2
LDFLAGS+=$(shell root-config --glibs)  -ggdb3 

LINKD=$(INTERFACE)/LinkDef

#HEAD=$(filter-out $(SRC)/$(LINKD) $(SRC)/uaplot_dict.h, $(wildcard $(SRC)/*.h))
CODE=$(wildcard $(SRC)/*.cc)
OBJS=$(subst $(SRC),$(OBJ),$(CODE:.cc=.o) $(OBJ)/eventdict.o)

all: $(OBJ) $(OBJ)/libUADataFormat.so 

$(OBJ)/libUADataFormat.so: $(OBJS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS) # order important for Ubuntu
	if [ ! -s $(OBJ)/eventdict_rdict.pcm ] ; then ln -s ../eventdict_rdict.pcm $(OBJ)/ ; fi
	@echo ""
	#to load the library to CINT one needs X connection
	@echo ""

$(OBJ)/%.o: $(SRC)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ""

$(SRC)/eventdict.cc:
	cd ../; sh dictionary.sh
	@echo ""

$(LINKD).h:
	#compatibility with cmssw
	mv $(LINKD)h  $(LINKD).h
	@echo ""

info:
	@echo "CXX:     $(CXX)"
	@echo "HEADERS: $(HEAD)"
	@echo "SOURCES: $(CODE)"
	@echo "OBJECTS: $(OBJS)"

$(OBJ): 
	mkdir -p $(OBJ)

clean:
	rm -rf $(OBJ)

