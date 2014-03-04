.PHONY: all clean check_samples check_site_bid_request_sample check_app_bid_request_sample check_bid_response_sample generate_encryption_samples capture_packets bid_request_json bid_request_protobuf

CC = clang
CXX = clang++
CFLAGS = -Wall -c
OFLAGS = -lprotobuf
PROTOC = protoc
PROTOHDRS = fluct_site_bid_request.pb.h fluct_app_bid_request.pb.h fluct_bid_response.pb.h
PROTOSRCS = fluct_site_bid_request.pb.cc fluct_app_bid_request.pb.cc fluct_bid_response.pb.cc
OBJECTS = fluct_site_bid_request.pb.o fluct_app_bid_request.pb.o fluct_bid_response.pb.o generate_bid_sample.o
TARGETS = generate_bid_sample.out fluct_site_bid_request.out fluct_app_bid_request.out fluct_bid_response.out

all: ${TARGETS}

%.pb.h %.pb.cc: %.proto
	${PROTOC} --cpp_out=. $^

%.pb.o: %.pb.cc %.pb.h
	${CXX} ${CFLAGS} -o $@ $<

generate_bid_sample.o: generate_bid_sample.cc ${PROTOHDRS}
	${CXX} ${CFLAGS} -o $@ generate_bid_sample.cc

generate_bid_sample.out: ${OBJECTS}
	${CXX} ${OFLAGS} -o $@ $^

generate_schemas: fluct_site_bid_request.out fluct_app_bid_request.out fluct_bid_response.out

fluct_site_bid_request.out: fluct_site_bid_request.proto
	protoc -o$@ $^

fluct_app_bid_request.out: fluct_app_bid_request.proto
	protoc -o$@ $^

fluct_bid_response.out: fluct_bid_response.proto
	protoc -o$@ $^

check_samples: check_site_bid_request_sample check_app_bid_request_sample check_bid_response_sample

check_site_bid_request_sample: generate_bid_sample.out
	./generate_bid_sample.out -s
	cat fluct_site_bid_request_sample.bin | protoc --decode=fluct_rtb.FluctSiteBidRequest fluct_site_bid_request.proto

check_app_bid_request_sample: generate_bid_sample.out
	./generate_bid_sample.out -a
	cat fluct_app_bid_request_sample.bin | protoc --decode=fluct_rtb.FluctAppBidRequest fluct_app_bid_request.proto

check_bid_response_sample: generate_bid_sample.out
	./generate_bid_sample.out -r
	cat fluct_bid_response_sample.bin | protoc --decode=fluct_rtb.FluctBidResponse fluct_bid_response.proto

TXT1 = "123.456e-06"
TXT2 = "USD123.456e+07"
TXT3 = "JPY123.456e-06"

generate_encryption_samples:
	./fluct_price_encryption.escript ${TXT1} ${TXT2} ${TXT3}

TCPDUMP = ${shell which tcpdump}
TRACE = ./trace-ascii.log

bid_request_json:
	sh bid_request.sh ${ENDPOINT} ${DATA} JSON ${TRACE}

bid_request_protobuf:
	sh bid_request.sh ${ENDPOINT} ${DATA} PROTOBUF ${TRACE}

capture_packets:
	sudo ${TCPDUMP} -vvv -XX -e -s 0 host ${DSP_HOST}

clean:
	rm -f *.bin
	rm -f ${PROTOSRCS} ${PROTOHDRS} ${OBJECTS} ${TARGETS}
