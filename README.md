Fluct RTB Tools
=========================

* This is a collection of tools for Fluct RTB development:
    * Bid request/response samples generator in protobuf
    * Default fluct price encription samples generator
    * A script & some commands for integration test
    * JSON bid request/response sample files
* PREREQUISITES: Please make sure you have the following things installed:
    * UNIX/Linux environment
    * g++ or clang++ (C++03 supported)
    * protobuf 2.5.0 or above
    * Erlang R16B01 or above
    * curl
    * tcpdump
* How to generate bid request/response samples?
    * `make` before you do anything
    * Run `./generate_bid_sample.out` after a successful `make`
    * The following binary files will be generated:
        * `fluct_site_bid_request_sample.bin`
        * `fluct_app_bid_request_sample.bin`
        * `fluct_bid_response_sample.bin`
* JSON bid request/response sample files?
    * `fluct_bid_response_sample.json`
    * `fluct_site_bid_request_sample.json`
* How to generate price encryption samples?
    * Run `./fluct_price_encryption.escript Text1 Text2...`
* How to do integration test?
    * Run `make bid_request_[json|protobuf] ENDPOINT=[ENDPOINT_URL] DATA=[DATA_FILE] TRACE=[TRACE_FILE]`, and check the TRACE_FILE for the result.
    * Run `make capture_packets DSP_HOST=[DSP_HOST]` for packets capturing.
