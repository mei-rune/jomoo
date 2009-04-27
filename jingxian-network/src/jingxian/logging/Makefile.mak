

ifdef TM_PROJECT_DIRECTORY
	BASE_PATH=$(TM_PROJECT_DIRECTORY)
else
	BASE_PATH="."
endif

#include $(BASE_PATH)/include.mak

.PHONY : clean
clean :
	echo *.obj
    
LogUtils.obj : LogUtils.cpp
	$(CC) -I$(BASE_PATH) $(INCLUDES) $(CFLAGS) -c LogUtils.cpp
    

all : clean
