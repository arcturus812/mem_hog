OBJDIR=./obj

all:
	cd $(OBJDIR) && make

clean:
	cd $(OBJDIR) && make clean
	rm -rf cscope.files cscope.out

depend:
	cd $(OBJDIR) && make depend
