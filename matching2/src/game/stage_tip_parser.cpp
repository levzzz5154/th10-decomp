#include "th10/game/stage_tip_parser.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <sstream>
namespace th10::stage_tips { namespace {
std::string trim(std::string s){while(!s.empty()&&std::isspace((unsigned char)s.front()))s.erase(s.begin());while(!s.empty()&&std::isspace((unsigned char)s.back()))s.pop_back();return s;}
std::pair<std::string,std::string> kv(const std::string&s){auto p=s.find(':');if(p==std::string::npos)return{trim(s),{}};return{trim(s.substr(0,p)),trim(s.substr(p+1))};}
int num(const std::string&s){return std::strtol(s.c_str(),nullptr,10);} float real(const std::string&s){return std::strtof(s.c_str(),nullptr);}
std::vector<std::string> split(const std::string&s){std::vector<std::string>v;std::stringstream q(s);std::string x;while(std::getline(q,x,','))v.push_back(trim(x));return v;}
}
// Semantic reconstruction of retail 0x00419960. The stdcall arguments in the
// IDA listing are manager, resource name, and duplicate-suppression mode.
ParseResult ParseStageTips(const std::string&text,bool suppress){ParseResult out;out.opened=true;std::istringstream in(text);std::string line;int stage=-1,count=0;while(std::getline(in,line)){auto [k,v]=kv(line);if(k.empty())continue;if(k=="Version"){if(v!="0.0"){out.version_ok=false;break;}}else if(k=="Stage"){stage=num(v);count=0;if(stage<1||stage>7)stage=-1;}else if(k=="StageEnd")stage=-1;else if(k=="Tips"&&stage>0){if(count>=255){stage=-1;continue;}ParsedTip t;t.stage=stage;t.scale=1;t.list_index=stage*3+6;++count;while(std::getline(in,line)){auto [a,b]=kv(line);if(a=="End")break;if(a=="Pos"){auto x=split(b);if(x.size()>1){t.x=float(num(x[0]));t.y=float(num(x[1]));}}else if(a=="Text"){auto p=b.find('"'),q=b.rfind('"');if(p!=std::string::npos&&q>p)t.text=b.substr(p+1,std::min<std::size_t>(64,q-p-1));}else if(a=="Count")t.count=num(b);else if(a=="Time")t.time=num(b);else if(a=="Base")t.base=num(b);else if(a=="Align")t.align=num(b);else if(a=="Remain")t.remain=num(b);else if(a=="Scale")t.scale=std::clamp(real(b),-4.0f,4.0f);else if(a=="Color"){auto x=split(b);if(x.size()>2){t.r=(uint8_t)num(x[0]);t.g=(uint8_t)num(x[1]);t.b=(uint8_t)num(x[2]);}}else if(a=="Alpha")t.a=(uint8_t)num(b);}
t.rendered_width=float(t.text.size())*t.scale*.5f;out.tips.push_back(t);if(!suppress){t.list_index=stage*3+30;out.tips.push_back(t);}}
}return out;}
}
