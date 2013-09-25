include Makerules.mk

CFLAGS= $(DEV_CFLAGS) \
		-Wall

LDLIBS = $(DEV_LDLIBS)
LDFLAGS= $(DEV_LDFLAGS)
		
OBJDIR = obj_dev
SRCDIR = $(SOURCE_FOLDER)

CPPSRCS    = $(shell find -L $(SRCDIR) -name '*.cpp')
CSRCS    = $(shell find -L $(SRCDIR) -name '*.c')
SRCDIRS = $(shell find -L $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
CPPOBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPSRCS))
COBJS    = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CSRCS))

DEV_TARGET =  lib$(TARGET)-dev.a

all: target

target: $(DEV_TARGET)

$(DEV_TARGET): buildrepo $(CPPOBJS) $(COBJS)
	@rm lib/$@ -f
	$(AR) rvs lib/$@ $(CPPOBJS) $(COBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
printversions:
	@echo FWVersion: ${FIRWMARE_VERSION}
	@echo BuildTag: ${BUILDTAG}
	
clean:
	rm lib/$(DEV_TARGET) $(OBJDIR) -Rf
	
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
