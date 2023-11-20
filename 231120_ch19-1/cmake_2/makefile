# 변수를 선언할 수 있다. 쓸땐 $()로 묶기
CC = g++				# CC: 사용하는 컴파일러 이름
CXXFLAGS = -Wall -O2	# CXXFLAGS: 컴파일러 옵션
## 옵션 - Wall(모든 컴파일 경고를 표시), O2(최적화 레벨 2) => 주의 알파벳 대문자 'O' 임.
OBJS = foo.o bar.o main.o

foo.o : foo.h foo.cc
	$(CC) $(CXXFLAGS) -c foo.cc

bar.o : bar.h bar.cc
	$(CC) $(CXXFLAGS) -c bar.cc

main.o : main.cc foo.h bar.h
	$(CC) $(CXXFLAGS) -c main.cc

main : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o main

.PHONY: clean	#clean 파일의 유무와 상관없이 언제나 해당 타겟의 명령을 싱행하게 된다.
clean:		# 흔히 추가하는 기능으로 빌드 관련된 파일들 (.o 파일들)을 모두 제거하는 명령	=> 모든 목적파일과 main 파일을 삭제함.
	rm -f $(OBJS) main