foo.o   :   foo.h foo.cc
            g++ -c  foo.cc

bar.o   :   bar.h bar.cc
            g++ -c  bar.cc

main.o  :   main.cc foo.h   bar.h
            g++ -c  main.cc
    
main    :   foo.o   bar.o   main.o
            g++ foo.o   bar.o   main.o  -o  main