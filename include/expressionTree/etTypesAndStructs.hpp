#pragma once

enum class EtNodeType { num_node, oper_node };

struct etNode {
	etNode* parent;
	etNode* left;
	etNode* right;
	EtNodeType type;
	union
	{
		float num;
		char oper;
	};
};