
include "../../../include.mak"

LogUtils.obj : LogUtils.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c LogUtils.cpp

