CC = gcc
CFLAGS = -shared
LIBS = -lole32 -lcomdlg32

all: dialog.dll

dialog.dll: windialog.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f dialog.dll