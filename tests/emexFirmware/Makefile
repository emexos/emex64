# Makefile
ASM = emex64asm
LD = emex64ld
VM = emex64vm

# firmware headers
INCDIR = $(abspath ./inc)

ASMFLAGS = -fno_page_align -I$(INCDIR) -DPUT_DRAW_LOGO="1"
LDSCRIPT = $(abspath ./emex64.e64ld)

SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/emex64fw

SRCS = $(wildcard $(SRCDIR)/*.e64)
OBJS = $(patsubst $(SRCDIR)/%.e64,$(BUILDDIR)/%.e64o,$(SRCS))

LINK_ORDER = \
    $(BUILDDIR)/start.e64o    \
    $(BUILDDIR)/exc.e64o      \
    $(BUILDDIR)/interrupt.e64o \
    $(BUILDDIR)/uart.e64o     \
    $(BUILDDIR)/put.e64o      \
    $(BUILDDIR)/mc.e64o       \
    $(BUILDDIR)/mem.e64o      \
    $(BUILDDIR)/pmm.e64o      \
    $(BUILDDIR)/slab.e64o     \
    $(BUILDDIR)/rtc.e64o      \
    $(BUILDDIR)/gui.e64o      \
    $(BUILDDIR)/font.e64o     \
    $(BUILDDIR)/string.e64o

all: compile execute

compile: $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.e64o: $(SRCDIR)/%.e64 | $(BUILDDIR)
	$(ASM) $(ASMFLAGS) -o $@ $<

$(TARGET): $(LINK_ORDER) $(LDSCRIPT)
	$(LD) -T $(LDSCRIPT) -o $@ $(LINK_ORDER)

execute:
	$(VM) --firmware $(TARGET) --memory 1

clean:
	rm -rf $(BUILDDIR)
