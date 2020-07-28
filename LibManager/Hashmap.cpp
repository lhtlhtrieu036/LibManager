#include"include.h"

hashMap* createHashMap() {
	hashMap* newHashMap = (hashMap*)malloc(sizeof(hashMap));
	newHashMap->firstNode = NULL;
	return newHashMap;
}

hashNode* createHashNode(const char* hash) {
	hashNode* newHashNode = (hashNode*)malloc(sizeof(hashNode));
	strcpy(newHashNode->hash, hash);
	newHashNode->count = 1;
	newHashNode->nextNode = NULL;
	return newHashNode;
}

hashNode* findInHashMap(hashMap* map, const char* hash) {
	hashNode* thisNode = map->firstNode;
	while (thisNode != NULL) {
		if (strcmp(thisNode->hash, hash) == 0) return thisNode;
		thisNode = thisNode->nextNode;
	}
		
	return NULL;
}

void pushToHashMap(hashMap*& map, const char* hash) {
	hashNode* newNode = createHashNode(hash);
	if (map->firstNode == NULL) {
		map->firstNode = newNode;
		map->lastNode = newNode;
	}
	else {
		map->lastNode->nextNode = newNode;
		map->lastNode = newNode;
	}
}

void releaseHashMap(hashMap*& map) {
	while (map->firstNode != NULL) deleteFirstHashmapNode(map);
	free(map);	
}

void deleteFirstHashmapNode(hashMap*& map) {
	hashNode* thisNode = map->firstNode;
	if (map->firstNode == map->lastNode) {
		map->firstNode = NULL;
		map->lastNode = NULL;
	} else {
		map->firstNode = thisNode->nextNode;
	}

	free(thisNode);
}