#include <fstream>
#include <iostream>
#include <string>
#include "messages/mytype.pb.h"
#include <google/protobuf/message.h>

using namespace google;
using namespace std;


int serialize(const google::protobuf::Message& msg, void* pdata, unsigned int nsize)
{
	if (msg.SerializeToArray(pdata, nsize)) {
		return msg.ByteSize();
	}
	return -1;
}

int unserialize(google::protobuf::Message& msg, void* pdata, unsigned int nsize)
{
	if (msg.ParseFromArray(pdata, nsize)) {
		return msg.ByteSize();
	}
	return -1;
}

int main(int argc, char* argv[])
{
	int nsize = 1024*8;
	char buffer[1024*8] = {0};
	string name = "binfile";
	fstream bf(name, ios::in|ios::binary);
	MyType myt;
	int ret = -1;

	if (bf.is_open()) {
		cout<<"read from:"<<name<<endl;
		do 
		{
			bf.read(buffer, nsize);
		} while (!bf.eof());
		if (myt.ParseFromArray(buffer, bf.gcount())) {
			;	
		}
		myt.PrintDebugString();
		string strmsg = myt.strmessage();
		cout<<strmsg<<endl;
	}else{
		bf.open(name.c_str(), ios::out|ios::binary);
		if (bf.is_open())
		{
			myt.set_id(102);
			myt.set_longid(201);
			myt.set_strmessage("这是个中文字符串！");
			string data = myt.SerializeAsString();
			const char* pdata = data.data();
			int nsize = data.size();
			bf.write(pdata, nsize);
			myt.PrintDebugString();
			cout<<myt.strmessage()<<endl;
		}
	}
	return 0;
}

