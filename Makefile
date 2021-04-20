NAME		=	myftp
TNAME		=	unit_tests

SRCPATH		=	src
TESTPATH	=	tests

SRC 		= 	$(SRCPATH)/server.c						\
				$(SRCPATH)/client.c						\
				$(SRCPATH)/server_close.c				\
				$(SRCPATH)/server_init.c				\
				$(SRCPATH)/accept_client.c				\
				$(SRCPATH)/commands.c					\
				$(SRCPATH)/commands/cwd.c				\
				$(SRCPATH)/commands/mode.c				\
				$(SRCPATH)/commands/pass.c				\
				$(SRCPATH)/commands/rein.c				\
				$(SRCPATH)/commands/user.c				\
				$(SRCPATH)/commands/quit.c				\
				$(SRCPATH)/commands/dump.c				\
				$(SRCPATH)/commands/pasv.c				\
				$(SRCPATH)/commands/syst.c				\
				$(SRCPATH)/commands/feat.c				\
				$(SRCPATH)/commands/pwd.c				\
				$(SRCPATH)/commands/type.c				\
				$(SRCPATH)/commands/port.c				\
				$(SRCPATH)/commands/list.c				\
				$(SRCPATH)/commands/cdup.c				\
				$(SRCPATH)/commands/retr.c				\
				$(SRCPATH)/commands/dele.c				\
				$(SRCPATH)/str_split.c					\



MAIN		=	$(SRCPATH)/main.c

TESTS		=	$(TESTPATH)/test_client.c				\
				$(TESTPATH)/test_server.c

OBJ			=	$(SRC:%.c=%.o)
OBJMAIN		=	$(MAIN:%.c=%.o)
OBJTESTS	=	$(TESTS:%.c=%.o)

INCLUDE		=	-I includes/
CFLAGS		=	$(INCLUDE) --coverage -g

all:			$(NAME)
$(NAME):		$(OBJ) $(OBJMAIN)
				gcc -o $(NAME) $(OBJ) $(OBJMAIN) $(CFLAGS)
clean:
				rm -rf $(OBJ) $(OBJTESTS)
fclean:			clean
				rm -rf $(NAME) $(TNAME) $(OBJ) $(OBJMAIN) $(OBJTESTS)
re:				fclean all

tests_run:		$(OBJTESTS) $(OBJ)
				gcc -o $(TNAME) $(OBJTESTS) $(OBJ) $(TFLAGS) -L. -lcriterion -lgcov
				./unit_tests