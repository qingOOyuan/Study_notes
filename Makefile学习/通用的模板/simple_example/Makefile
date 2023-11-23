
## VERSION 1：改动一个文件，每次都会重新编译所有源文件，当文件很多的时候，做了很多无用功

##hello: main.c print.c calc.c
##	gcc -o hello main.c print.c calc.c

######################################################################

## VERSION 2：改进了VERSION1的缺点，并且加入了类似于宏定义这样的变量，但是没有清理的功能
##CXX = gcc
##TARGET = hello
##OBJ = main.o print.o calc.o

##$(TARGET): $(OBJ)
##	$(CXX) -o $(TARGET) $(OBJ)

##main.o: main.c
##	$(CXX) -c main.c

##print.o: print.c
##	$(CXX) -c print.c

##calc.o: calc.c
##	$(CXX) -c calc.c

######################################################################


#Makefile有三个非常有用的变量。分别是$@，$^，$<
#$@ − 目标文件，$^ 所有的依赖 $< 第一个依赖

## VERSION 3：加上了清理功能，并加上了编译选项CXXFLAGS，引入通配符，但是每次新加源文件还得手动加在OBJ中
##CXX = gcc
##TARGET = hello
##OBJ = main.o print.o calc.o

##CXXFLAGS = -c -Wall

##$(TARGET): $(OBJ)
##	$(CXX) -o $@ $^ 

#在这里$<虽然是第一个依赖，实际上就是所有的依赖(%.c)
##%.o: %.c
##	$(CXX) $(CXXFLAGS) -o $@ $< 

##.PHONY: clean
##clean:
##	rm -f *.o $(TARGET)

######################################################################

## VERSION 4  引入函数，不用手动增加新加入的源文件，但是这个版本还有缺点：改变头文件后察觉不到，也即再次make，还是显示is up to date
CXX = gcc
TARGET = hello

#获取工作目录下的所有的.c文件列表
SRC = $(wildcard *.c)

#将列表中所有文件名的后缀.c替换为.o
OBJ = $(patsubst %.c, %.o, $(SRC))

CXXFLAGS = -c -Wall

#实际测试这里不能用$<，也即不能这样写：$(CXX) -o $@ $<
# 因为 $<  依赖目标中的第一个目标名字。如果依赖目标是以模式（即"%"）定义的，那么"$<"将是符合模式的一系列的文件集。注意，其是一个一个取出来的。
#但是我们这里的依赖目标在上面已经被wildcard和patsubst展开了，所以不能这个依赖目标集不能被一个个取出来
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ 

#在这里$<虽然是第一个依赖，实际上就是所有的依赖(%.c),实际上$(CXX) $(CXXFLAGS) -o $@ $< 不写也可以
#因为GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令
#只要make看到一个[.o]文件，它就会自动的把[.c]文件加在依赖关系中，
#如果make找到一个whatever.o，那么whatever.c，就会是whatever.o的依赖文件。并且 gcc -c whatever.c 也会被推导出来

#静态模式：
#    <targets ...>: <target-pattern>: <prereq-patterns ...>
#            <commands>
#            ...
#
#    targets定义了一系列的目标文件，可以有通配符。是目标的一个集合。
#
#    target-parrtern是指明了targets的模式，也就是的目标集模式。
#
#    prereq-parrterns是目标的依赖模式，它对target-parrtern形成的模式再进行一次依赖目标的定义。

#这是简化版本，完整的写法应该是：$(OBJ) : %.o: %.c
#指明了咱们的目标从$(OBJ)中获取，%.o 代表要全部以.o结尾的目标，也就是变量$(OBJ)集合的模式
#而依赖模式 %.c 则取模式 %.o 的 %，并为其加上.c的后缀
%.o : %.c
	$(CXX) $(CXXFLAGS) -o $@ $< 

.PHONY: clean
clean:
	rm -f *.o $(TARGET)

