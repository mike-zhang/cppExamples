CC = g++
CFLAGS = -g -O2 -Wall
SRC_DIR=.
DST_DIR=libs

all:
	make genproto
	make writer
	make reader

genproto:
	mkdir -p $(DST_DIR)
	protoc -I=$(SRC_DIR) --cpp_out=$(DST_DIR) addr.book.proto	

writer:
	$(CC) -o writer writer.cpp $(DST_DIR)/addr.book.pb.cc -I$(DST_DIR) -lprotobuf

reader:
	$(CC) -o reader reader.cpp $(DST_DIR)/addr.book.pb.cc -I$(DST_DIR) -lprotobuf

clean:
	rm -rf $(DST_DIR)
	rm -f writer reader log
	rm -f *.o



