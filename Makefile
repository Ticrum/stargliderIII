out=volume
src=$(shell find src/ -name "*.c")
tem=$(shell find objects/label -name "*.so")
header=$(shell find include -name "*.h")
obj=$(src:.c=.o)
lib=lib$(out).so
sta=lib$(out).a
libpath= -I ./include/
tempath=-L./objects/label/
rpath=-Wl, -rpath,/objects/label/
flag= -W -Wall -llapin -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++ -lm -ldl -lpthread -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_core -lavcall -lusb -std=c11 -g 

cc: $(obj)
	gcc $(obj) -o $(out) $(libpath) $(flag)

exh:
	sudo cp $(header) ~/../../usr/$(header)

li: exh $(obj)
	gcc -shared -o $(lib) $(obj)
	sudo cp $(lib) ~/../../usr/lib/$(lib)

sta: $(obj)
	ar cr $(sta) $(obj)
	ranlib libclickodrome.a

cli: cl
	sudo rm -f ~/../../usr/$(header)
	sudo rm -f ~/../../usr/lib/$(lib)

cl:
	@rm -f $(out)
	@rm -f src/*~
	@rm -f include/*~
	@rm -f *~
	@rm -f $(obj)
	@rm -f $(lib)
	@rm -f $(sta)

.c.o:
	gcc -c $< $(libpath) -o $@ $(flag)

re: cl cc

resta: cl sta

reli: cli cl li
