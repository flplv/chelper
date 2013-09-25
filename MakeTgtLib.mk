include Makerules.mk

CFLAGS= $(TGT_CFLAGS) \
		-Wall

LDLIBS = $(TGT_LDLIBS)
LDFLAGS= $(TGT_LDFLAGS)
		
OBJDIR = obj_tgt
SRCDIR = $(SOURCE_FOLDER)

CPPSRCS    = $(shell find -L $(SRCDIR) -name '*.cpp')
CSRCS    = $(shell find -L $(SRCDIR) -name '*.c')
SRCDIRS = $(shell find -L $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
CPPOBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPSRCS))
COBJS    = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CSRCS))

TGT_TARGET =  lib$(TARGET)-tgt.a

all: target

target: $(TGT_TARGET)

$(TGT_TARGET): buildrepo $(CPPOBJS) $(COBJS)
	@rm lib/$@ -f
	$(TGT_AR) rvs lib/$@ $(CPPOBJS) $(COBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(TGT_CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(TGT_CC) $(CFLAGS) -c $< -o $@
	
printversions:
	@echo FWVersion: ${FIRWMARE_VERSION}
	@echo BuildTag: ${BUILDTAG}
	
clean:
	rm lib/$(TGT_TARGET) $(OBJDIR) -Rf
	
buildrepo:
	@$(call make-repo)
	@mkdir -p lib

# Create obj directory structure
define make-repo
	mkdir -p $(OBJDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef
