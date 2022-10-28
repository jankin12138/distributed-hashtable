using namespace std;
#include"hash_node.h"

unsigned int hs(const void* key) {
    const unsigned int m = 0x5bd1e995;//
    const int r = 24;
    const int seed = 97;
    int len = 32;
    unsigned int h = seed ^ len;
    //cout << key << endl;
    // Mix 4 bytes at a time into the hash
    const unsigned char* data = (const unsigned char*)key;
    //cout << data << endl;
    while (len >= 4) {
        unsigned int k = *(unsigned int*)data;
       // cout << len<<":" << k << endl;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch (len) {
    case 3:
        h ^= data[2] << 16;
    case 2:
        h ^= data[1] << 8;
    case 1:
        h ^= data[0];
        h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

void HashRing::check()
{
    int count = 0;
    int sum = 0;
    int a;
    string node_name;
    vector<string> load_name;
    vector<int> load_num;
    for (auto it = ServerNodes.begin(); it != ServerNodes.end(); it++) {
        int is_find = 0;
        if (it->second.getCliNodesize() > 0)
        {
            if (it->second.getCNode().find(":")!=-1) {
                a = it->second.getCNode().find(":");
                node_name = it->second.getCNode().substr(0, a);
                if (load_name.size() == 0) {
                    load_name.push_back(node_name);
                    load_num.push_back(0);
                }
                for (int i = 0; i < load_name.size(); i++) {
                    //cout << node_name << load_name[i] << endl;
                    if (node_name == load_name[i]) {
                        load_num[i] += count;
                        is_find = 1;
                    }
                }
                if (is_find == 0) {
                    load_name.push_back(node_name);
                    load_num.push_back(count);
                }
            }
            it->second.printNode();
            cout << "\t包含数据个数:" << count << endl;
            sum += count;
            count = 0;
        }
        else {
            count++;
        }
    }
    for (int i = 0; i < load_name.size(); i++) {
        cout << "节点名称" << load_name[i] << "个数" << load_num[i] << endl;
    }
    //cout << "total:" << sum << endl;
}
