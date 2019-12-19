# Makefile for the smash program
CC = g++ $(CFLAGS)
CFLAGS = -g -Wall -pthread
CCLINK = $(CC)
OBJS = main.o Protection.o Bank.o Account.o Caspomat.o listAccount.o
RM = rm -f
# Creating the executable
Bank: $(OBJS)
	$(CCLINK) $(ClFLAGS)-o Bank $(OBJS)
# Creating the object files
main.o: main.cpp Bank.hpp Caspomat.hpp Account.hpp listAccount.hpp
Bank.o: Bank.cpp Bank.hpp
Accounts.o: account.cpp account.hpp
Protection.o: Protection.cpp Protection.hpp
Caspomat.o: Caspomat.cpp Caspomat.hpp
listAccount.o: listAccount.cpp listAccount.hpp

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

