using namespace std;
#include"hash_node.h"

int main()
{
	HashRing hr;
	for (int i = 0; i < 100; i++) {
		string a;
		a = to_string(i);
		hr.addNode(a);
	}
	hr.distributionNode("127.0.0.1");//�����ڵ�
	hr.distributionNode("110.0.3.1");
	hr.distributionNode("113.51.15.48");
	hr.distributionNode("114.48.96.125");
	hr.distributionVirtualNode("115.47.12.35",4);//��������ڵ�
	hr.distributionVirtualNode("116.87.95.62",4);
	//hr.printHashRingState();
	hr.check();
	system("pause");
}
