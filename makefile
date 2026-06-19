outfile:main.o utils.o add.o view.o update.o remove.o issue.o persist.o
	cc main.c utils.c add.c view.c update.c remove.c issue.c persist.c -o outfile
main.o:main.c
	cc -c main.c
utils.o:utils.c
	cc -c utils.c
add.o:add.c
	cc -c add.c
view.o:view.c
	cc -c view.c
update.o:update.c
	cc -c update.c
remove.o:remove.c
	cc -c remove.c
issue.o:issue.c
	cc -c issue.c
persist.o:persist.c
	cc -c persist.c
