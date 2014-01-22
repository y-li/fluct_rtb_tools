#include        <iostream>
#include        <fstream>
#include        <string>

#include        "fluct_site_bid_request.pb.h"
#include        "fluct_app_bid_request.pb.h"
#include        "fluct_bid_response.pb.h"

int
generate_site_bid_request_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return 1;
    }

    FluctSiteBidRequest         sreq;

    sreq.set_version(1);
    sreq.mutable_imp()->set_impid("a test imp");
    sreq.mutable_imp()->set_h(250);
    sreq.mutable_imp()->set_w(300);
    sreq.mutable_imp()->set_ip("8.8.8.8");
    sreq.mutable_imp()->set_ua("fluct user agent");
    sreq.mutable_imp()->set_cat(1);
    FluctSiteBidRequest_BCat    *sreq_bcat = NULL;
    sreq_bcat = sreq.mutable_imp()->add_bcat();
    sreq_bcat->set_iab(1);
    sreq_bcat = sreq.mutable_imp()->add_bcat();
    sreq_bcat->set_iab(2);
    sreq.mutable_imp()->set_pos(1);
    sreq.mutable_imp()->set_frameid("a test frameid");

    sreq.mutable_site()->set_sid("a test sid");
    sreq.mutable_site()->set_page("http://fluct.jp/test/page.html");
    sreq.mutable_site()->set_sdomain("http://fluct.jp");
    sreq.mutable_site()->set_ref("http://fluct.jp/referrer/page.html");

    sreq.mutable_user()->set_uid("a test uid");
    sreq.mutable_user()->set_dspuid("a test dspuid");

    FluctSiteBidRequest         sreq_parse;
    std::string                 outstring;

    sreq.SerializeToString(&outstring);
    if (not sreq_parse.ParseFromString(outstring)) {
        std::cerr << "ParseFromString(FluctSiteBidRequest) Error!" << std::endl;
        return 1;
    }
    outfile << outstring;
    outfile.close();

    return 0;
}

int
generate_app_bid_request_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return 1;
    }

    FluctAppBidRequest         areq;

    areq.set_version(1);
    areq.mutable_imp()->set_impid("a test imp");
    areq.mutable_imp()->set_h(250);
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
        return 1;
    }
    outfile << outstring;
    outfile.close();

    return 0;
}

int
generate_bid_response_sample(const std::string &filename)
{
    std::ofstream               outfile(filename.c_str(), std::ios_base::binary);
    if (not outfile.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        return 1;
    }

    FluctBidResponse            resp;

    resp.set_impid("a test impid");
    resp.set_bidid("a test bidid");
    resp.set_nbr(1);
    resp.set_cur("USD");

    resp.mutable_bid()->set_price(11.11);
    resp.mutable_bid()->set_adm("a test adm");
    resp.mutable_bid()->set_adid("a test adid");
    resp.mutable_bid()->set_adcat(1);
    resp.mutable_bid()->set_adomain("www.example.com");

    FluctBidResponse            resp_parse;
    std::string                 outstring;

    resp.SerializeToString(&outstring);
    if (not resp_parse.ParseFromString(outstring)) {
        std::cerr << "ParseFromString(FluctBidResponse) Error!" << std::endl;
        return 1;
    }
    outfile << outstring;
    outfile.close();

    return 0;
}

int
main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    generate_site_bid_request_sample("fluct_site_bid_request_sample.bin");
    generate_app_bid_request_sample("fluct_app_bid_request_sample.bin");
    generate_bid_response_sample("fluct_bid_response_sample.bin");

    return 0;
}
