#pragma once

#include"include.h"

/**
 * Cau truc cua mot node - danh sach lien ket don.
 */
struct Node
{
	int value;
	Node* next;
};

/**
 * Cau truc danh sach lien ket don.
 */
struct linkedList
{
	Node* head;
};