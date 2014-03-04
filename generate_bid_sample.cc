#include        <iostream>
#include        <fstream>
#include        <string>
#include        <unistd.h>

#include        "fluct_site_bid_request.pb.h"
#include        "fluct_app_bid_request.pb.h"
#include        "fluct_bid_response.pb.h"

using namespace fluct_rtb;

static bool
generate_site_bid_request_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return false;
    }

    FluctSiteBidRequest         sreq;

    sreq.set_version(1);
    sreq.mutable_imp()->set_impid("49f492c2-6226-49f5-87f7-1b8098f37d5e");
    sreq.mutable_imp()->set_h(90);
    sreq.mutable_imp()->set_w(728);
    sreq.mutable_imp()->set_ip("220.110.139.200");
    sreq.mutable_imp()->set_ua("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.89 Safari/537.1");
    sreq.mutable_imp()->set_cat(1);
    FluctSiteBidRequest_BCat    *sreq_bcat = NULL;
    sreq_bcat = sreq.mutable_imp()->add_bcat();
    sreq_bcat->set_iab(1);
    sreq_bcat = sreq.mutable_imp()->add_bcat();
    sreq_bcat->set_iab(2);
    sreq.mutable_imp()->set_pos(1);
    sreq.mutable_imp()->set_frameid("a_test_frameid");

    sreq.mutable_site()->set_sid("0001");
    sreq.mutable_site()->set_page("http://adingo.jp/top.html");
    sreq.mutable_site()->set_sdomain("http://adingo.jp");
    sreq.mutable_site()->set_ref("https://www.google.co.jp/#fp=6b2ad3809afae70f&q=adingo");

    sreq.mutable_user()->set_uid("60f492c2-6226-49f5-87f7-1b8098f37d5e");
    sreq.mutable_user()->set_dspuid("a_test_dspuid");

    FluctSiteBidRequest         sreq_parse;
    std::string                 outstring;

    sreq.SerializeToString(&outstring);
    if (not sreq_parse.ParseFromString(outstring)) {
        std::cerr << "ParseFromString(FluctSiteBidRequest) Error!" << std::endl;
        return false;
    }
    outfile << outstring;
    outfile.close();

    return true;
}

static bool
generate_app_bid_request_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return false;
    }

    FluctAppBidRequest         areq;

    areq.set_version(1);
    areq.mutable_imp()->set_impid("a test imp");
    areq.mutable_imp()->set_h(50);
    areq.mutable_imp()->set_w(300);
    areq.mutable_imp()->set_ip("8.8.8.8");
    areq.mutable_imp()->set_ua("fluct user agent");
    areq.mutable_imp()->set_cat(1);
    FluctAppBidRequest_BCat     *areq_bcat = NULL;
    areq_bcat = areq.mutable_imp()->add_bcat();
    areq_bcat->set_iab(1);
    areq_bcat = areq.mutable_imp()->add_bcat();
    areq_bcat->set_iab(2);
    areq.mutable_imp()->set_pos(1);
    areq.mutable_imp()->set_frameid("a test frameid");

    areq.mutable_app()->set_aid("a test aid");
    areq.mutable_app()->set_aname("a test aname");

    areq.mutable_user()->set_uid("a test uid");
    areq.mutable_user()->set_dspuid("a test dspuid");

    FluctAppBidRequest          areq_parse;
    std::string                 outstring;

    areq.SerializeToString(&outstring);
    if (not areq_parse.ParseFromString(outstring)) {
        std::cerr << "ParseFromString(FluctAppBidRequest) Error!" << std::endl;
        return false;
    }
    outfile << outstring;
    outfile.close();

    return true;
}

static bool
generate_bid_response_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return false;
    }

    FluctBidResponse            resp;

    resp.set_impid("49f492c2-6226-49f5-87f7-1b8098f37d5e");
    resp.set_bidid("a_test_bidid");
    resp.set_nbr(1);
    resp.set_cur("USD");

    resp.mutable_bid()->set_price(11.11);
    resp.mutable_bid()->set_adm("a_test_adm");
    resp.mutable_bid()->set_adid("a_test_adid");
    resp.mutable_bid()->set_adcat(1);
    resp.mutable_bid()->set_adomain("toyota.co.jp");

    FluctBidResponse            resp_parse;
    std::string                 outstring;

    resp.SerializeToString(&outstring);
    if (not resp_parse.ParseFromString(outstring)) {
        std::cerr << "ParseFromString(FluctBidResponse) Error!" << std::endl;
        return false;
    }
    outfile << outstring;
    outfile.close();

    return true;
}

void
usage(const std::string &cmd, std::ostream &out)
{
    out << cmd << " [-s [FILENAME]] [-a [FILENAME]] [-r [FILENAME]]" << std::endl
        << "\t-s [FILENAME]: site bid request sample file name for output" << std::endl
        << "\t-a [FILENAME]: app bid request sample file name for output" << std::endl
        << "\t-r [FILENAME]: bid response sample file name for output" << std::endl;

    return;
}

int
main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::string         site_bid_request_filename = "fluct_site_bid_request_sample.bin";
    std::string         app_bid_request_filename = "fluct_app_bid_request_sample.bin";
    std::string         bid_response_filename = "fluct_bid_response_sample.bin";
    bool                has_error = false;

    if (argc > 1) {
        int     opt;
        while((opt = getopt(argc, argv, "hs::a::r::")) != -1) {
            switch (opt) {
            case 'h':
                usage(argv[0], std::cout);
                exit(EXIT_SUCCESS);
                break;
            case 's':
                if (optarg != NULL)
                    site_bid_request_filename = optarg;
                if (not generate_site_bid_request_sample(site_bid_request_filename))
                    has_error = true;
                break;
            case 'a':
                if (optarg != NULL)
                    app_bid_request_filename = optarg;
                if (not generate_app_bid_request_sample(app_bid_request_filename))
                    has_error = true;
                break;
            case 'r':
                if (optarg != NULL)
                    bid_response_filename = optarg;
                if (not generate_bid_response_sample(bid_response_filename))
                    has_error = true;
                break;
            default:
                usage(argv[0], std::cerr);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        if (not generate_site_bid_request_sample(site_bid_request_filename))
            has_error = true;
        if (not generate_app_bid_request_sample(app_bid_request_filename))
            has_error = true;
        if (not generate_bid_response_sample(bid_response_filename))
            has_error = true;
    }

    exit(has_error ? EXIT_FAILURE : EXIT_SUCCESS);
}
