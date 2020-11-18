CC = gcc
CFLAGS=-g -Wall -Werror -Wextra -I. -D_GNU_SOURCE
LDLIBS=-g -pthread -lrt



#Defining sources and objects
SRC_USER= fail_reply.c logging_user.c user_parser.c user.c log.c show_info.c
SRC_SERVER= authentication.c e_counter.c logging_server.c process_request.c request_queue.c server_parser.c server.c log.c show_info.c
OBJ_USER = $(SRC_USER:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
SRV = server
USR = user

DEPS = $(patsubst %.c,%.d,$(wildcard *.c))

.PHONY: all clean

all: $(SRV) $(USR)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(SRV): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SERVER) $(LDLIBS)

$(USR): $(OBJ_USER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_USER) $(LDLIBS)

clean:
	rm -rf $(SRV) $(USR) *.o *.d

distclean: clean
	$(RM) *~ $(DEPFILE)

include $(DEPFILE)
