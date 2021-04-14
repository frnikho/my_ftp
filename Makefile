NAME		=	myftp
TNAME		=	unit_tests

SRCPATH		=	src
TESTPATH	=	tests

SRC 		= 	$(SRCPATH)/server.c						\
				$(SRCPATH)/client.c

MAIN		=	$(SRCPATH)/main.c

TESTS		=	$(TESTPATH)/test_get_argv.c				\

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
