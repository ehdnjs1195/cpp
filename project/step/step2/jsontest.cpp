#include "jsonparser.hpp"

using boost::property_tree::ptree;
using namespace boost::json;

int main(){
    ptree props;    // json을 담을 tree 객체
    boost::property_tree::read_json("protocol.json", props);

    // InterID 값 가져오기
    int InterID = props.get<int>("InterID");
    std::cout << "InterID: " << InterID << std::endl;

    // 첫 번째 Plan 배열 가져오기
    const ptree &Plan = props.get_child("Plan").front().second; // front 첫번째 배열을 뜻하고, second는 그 값

    // 첫 번째 Level 배열 가져오기
    const ptree &level = Plan.get_child("Level").begin()->second;

    // 첫 번째 phase 배열 가져오기
    const ptree &phase_1 = level.get_child("phase").front().second;

    // 세 번째 RingA 값 가져오기
    int RingA = phase_1.get<int>("RingA");
    int RingB = phase_1.get<int>("RingB");
    std::cout << "RingA: " << RingA << " | RingB: " << RingB << std::endl;

}