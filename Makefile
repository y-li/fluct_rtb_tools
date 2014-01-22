CC = clang
CXX = clang++
CFLAGS = -Wall -c
OFLAGS = -lprotobuf
PROTOC = protoc
PROTOHDRS = fluct_site_bid_request.pb.h fluct_app_bid_request.pb.h fluct_bid_response.pb.h
PROTOSRCS = fluct_site_bid_request.pb.cc fluct_app_bid_request.pb.cc fluct_bid_response.pb.cc
OBJECTS = fluct_site_bid_request.pb.o fluct_app_bid_request.pb.o fluct_bid_response.pb.o test.o
TARGETS = test.out

all: ${TARGETS}

%.pb.h: %.proto
	${PROTOC} --cpp_out=. $^

%.pb.cc: %.proto
	${PROTOC} --cpp_out=. $^

fluct_site_bid_request.pb.o: fluct_site_bid_request.pb.h fluct_site_bid_request.pb.cc
	${CXX} ${CFLAGS} -o $@ fluct_site_bid_request.pb.cc

fluct_app_bid_request.pb.o: fluct_app_bid_request.pb.h fluct_app_bid_request.pb.cc
	${CXX} ${CFLAGS} -o $@ fluct_app_bid_request.pb.cc

fluct_bid_response.pb.o: fluct_bid_response.pb.h fluct_bid_response.pb.cc
	${CXX} ${CFLAGS} -o $@ fluct_bid_response.pb.cc

test.o: test.cc ${PROTOHDRS}
	${CXX} ${CFLAGS} -o $@ test.cc

test.out: ${OBJECTS}
	${CXX} ${OFLAGS} -o $@ $^

checkbin: test.out
	./test.out
	cat fluct_site_bid_request_sample.bin | protoc --decode=FluctSiteBidRequest fluct_site_bid_request.proto
	cat fluct_app_bid_request_sample.bin | protoc --decode=FluctAppBidRequest fluct_app_bid_request.proto
	cat fluct_bid_response_sample.bin | protoc --decode=FluctBidResponse fluct_bid_response.proto

clean:
	rm -f *.bin
	rm -f ${PROTOSRCS} ${PROTOHDRS} ${OBJECTS} ${TARGETS}
