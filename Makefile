################################
##############ZeOS #############
################################
########## Makefile ############
################################

# package dev86 is required
AS86 = as86 -0 -a
LD86 = ld86 -0

HOSTCFLAGS = -Wall -Wstrict-prototypes -g
HOSTCC = gcc
CC = gcc
AS = as --32
LD = ld
OBJCOPY = objcopy -O binary -R .note -R .comment -S

INCLUDEDIR = include
idt = idt

CFLAGS = -m32 -O2  -g -fno-omit-frame-pointer -ffreestanding -Wall -I$(INCLUDEDIR) -fno-PIC
ASMFLAGS = -I$(INCLUDEDIR)
LDFLAGS = -g -melf_i386

SYSOBJ = \
	interrupt.o \
	entry.o \
	sys_call_table.o \
	io.o \
	sched.o \
	sys.o \
	mm.o \
	devices.o \
	utils.o \
	hardware.o \
	list.o \
	interrupt_handler.o\
	writeMSR.o\
  task_switch.o\
  get_current_ebp.o\
  load_esp.o\
  get_fork_ebp.o\
  libauxjp.a\
	
LIBZEOS = -L . -l zeos -l auxjp

#add to USROBJ any object files required to complete the user program
USROBJ = \
	libc.o \
	write.o\
	gettime.o\
	fast_write.o\
  getpid.o\
  fork.o\
  exit.o\
  get_stats.o\
	libjp.a\

all:zeos.bin

zeos.bin: bootsect system build user
	$(OBJCOPY) system system.out
	$(OBJCOPY) user user.out
	./build bootsect system.out user.out > zeos.bin

build: build.c
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $<

bootsect: bootsect.o
	$(LD86) -s -o $@ $<

bootsect.o: bootsect.s
	$(AS86) -o $@ $<

bootsect.s: bootsect.S
	$(CPP) $(ASMFLAGS) -traditional $< -o $@

entry.s: entry.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

load_esp.s: load_esp.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<


get_current_ebp.s: get_current_ebp.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

get_fork_ebp.s: get_fork_ebp.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<


current.s: current.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

fast_write.s: $(idt)/fast_write.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

get_stats.s: $(idt)/get_stats.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<


exit.s: $(idt)/exit.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

fork.s: $(idt)/fork.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

getpid.s: $(idt)/getpid.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<


interrupt_handler.s: $(idt)/interrupt_handler.S $(INCLUDEDIR)/asm.h 
	$(CPP) $(ASMFLAGS) -o $@ $<

write.s: $(idt)/write.S $(INCLUDEDIR)/asm.h 
	$(CPP) $(ASMFLAGS) -o $@ $<

gettime.s: $(idt)/gettime.S $(INCLUDEDIR)/asm.h 
	$(CPP) $(ASMFLAGS) -o $@ $<


sys_call_table.s: $(idt)/sys_call_table.S $(INCLUDEDIR)/asm.h $(INCLUDEDIR)/segment.h
	$(CPP) $(ASMFLAGS) -o $@ $<

writeMSR.s: $(idt)/writeMSR.S $(INCLUDEDIR)/asm.h 
	$(CPP) $(ASMFLAGS) -o $@ $<

task_switch.s: task_switch.S $(INCLUDEDIR)/asm.h 
	$(CPP) $(ASMFLAGS) -o $@ $<


user.o:user.c interrupt_handler.s $(INCLUDEDIR)/libc.h 
	gcc -m32 -O0  -g -fno-omit-frame-pointer -ffreestanding -Wall -Iinclude -fno-PIC   -c -o user.o user.c


interrupt.o: $(idt)/interrupt.c $(INCLUDEDIR)/interrupt.h $(INCLUDEDIR)/segment.h $(INCLUDEDIR)/types.h 
	gcc -m32 -O0  -g -fno-omit-frame-pointer -ffreestanding -Wall -Iinclude -fno-PIC   -c -o interrupt.o $(idt)/interrupt.c


io.o:io.c $(INCLUDEDIR)/io.h

sched.o:sched.c $(INCLUDEDIR)/sched.h

libc.o:libc.c $(INCLUDEDIR)/libc.h

mm.o:mm.c $(INCLUDEDIR)/types.h $(INCLUDEDIR)/mm.h

sys.o:sys.c $(INCLUDEDIR)/devices.h
	gcc -m32 -O0  -g -fno-omit-frame-pointer -ffreestanding -Wall -Iinclude -fno-PIC   -c -o sys.o sys.c


utils.o:utils.c $(INCLUDEDIR)/utils.h


system.o:system.c $(INCLUDEDIR)/hardware.h system.lds $(SYSOBJ) $(INCLUDEDIR)/segment.h $(INCLUDEDIR)/types.h $(INCLUDEDIR)/interrupt.h $(INCLUDEDIR)/system.h $(INCLUDEDIR)/sched.h $(INCLUDEDIR)/mm.h $(INCLUDEDIR)/io.h $(INCLUDEDIR)/mm_address.h 


system: system.o system.lds $(SYSOBJ)
	$(LD) $(LDFLAGS) -T system.lds -o $@ $< $(SYSOBJ) $(LIBZEOS)

user: user.o user.lds $(USROBJ) 
	$(LD) $(LDFLAGS) -T user.lds -o $@ $< $(USROBJ)


clean:
	rm -f *.o *.s bochsout.txt parport.out system.out system bootsect zeos.bin user user.out *~ build 

disk: zeos.bin
	dd if=zeos.bin of=/dev/fd0

emul: zeos.bin
	bochs -q -f .bochsrc

gdb: zeos.bin
	bochs -q -f .bochsrc_gdb &
	gdb -x .gdbcmd system
ddd: zeos.bin
	bochs -q -f .bochsrc_ddd &
	ddd -x .dddcmd system

emuldbg: zeos.bin
	bochs_nogdb -q -f .bochsrc
