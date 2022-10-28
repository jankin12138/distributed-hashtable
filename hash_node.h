#pragma once
#include<string>
#include<iostream>
#include<vector>
#include <map>

unsigned int hs(const void* key);
class Node
{
public:
	Node(string _addr) :NodeAddr(_addr)
	{
	}
	string getNode()
	{
		return NodeAddr;
	}
	string getCNode()
	{
		return CliNodes[0].getNode();
	}
	void setNodeAddr(string _addr)
	{
		this->NodeAddr = _addr;
	}
	void addCliNode(Node cli)
	{
		CliNodes.push_back(cli);
	}
	int getCliNodesize()
	{
		return CliNodes.size();
	}
	void printNodeState()
	{
		cout << "当前节点地址：" << NodeAddr << "   \t哈希值：" << hs(NodeAddr.c_str()) << endl;
		for (Node& n : CliNodes)
		{
			cout << "客户端节点地址：" << n.getNode() << "   \t哈希值：" << hs(n.getNode().c_str()) << endl;
		}
		//cout << endl << endl << endl;
	}
	void printNode()
	{
		for (Node& n : CliNodes)
		{
			cout << "客户端节点地址：" << n.getNode() << "   \t哈希值：" << hs(n.getNode().c_str()) ;
		}
	}
private:
	string NodeAddr;
	vector<Node> CliNodes;
	size_t NodeHashValue;
};


class HashRing//一致性实现
{
public:
	void addNode(string _addr)
	{
		Node newNode(_addr);
		ServerNodes.insert(make_pair(hs(_addr.c_str()), move(newNode)));
	}
	void removeNode(string _addr)
	{
		size_t hashvalue = hs(_addr.c_str());
		ServerNodes.erase(hashvalue);
	}
	void distributionNode(string _addr)
	{
		auto it = ServerNodes.lower_bound(hs(_addr.c_str()));
		if (it == ServerNodes.end())
		{
			it = ServerNodes.begin();
		}
		it->second.addCliNode(Node(_addr));
	}
	void distributionVirtualNode(string _addr,int num)
	{
		string temp = _addr;
		for (int i = 0; i < num; i++)
		{
			string s1 = ":" + to_string(i+1);
			distributionNode(_addr.append(s1));
			_addr = temp;
		}
	}
	void printHashRingState()
	{
		for (auto it = ServerNodes.begin(); it != ServerNodes.end(); ++it)
		{
			it->second.printNodeState();
		}
	}
	void check();
private:
	map<size_t, Node> ServerNodes;
};

