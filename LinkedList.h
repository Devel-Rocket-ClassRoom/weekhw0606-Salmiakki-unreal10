#pragma once
struct ListNode
{
	int Data = 0;				// 데이터 부분. 이 노드가 관리할 실제 데이터
	ListNode* Next = nullptr;	// 링크 부분. 다음 노드의 주소(null이면 이 노드는 Tail)

	ListNode(int InData) : Data(InData) {}
};

class LinkedList
{
public:
	LinkedList() = default;
	~LinkedList();

	void Add(int InData);						// 리스트의 마지막에 데이터를 추가하는 함수
	void InsertAt(int InData, int InPosition);	// 리스트의 중간에 데이터를 추가하는 함수
	void Remove(int InData);					// 특정 데이터를 가지는 노드를 제거하는 함수
	void RemoveAt(int InPosition);				// 특정 번째의 노드를 제거하는 함수
	ListNode* Search(int InData) const;			// 특정 데이터가 있는지 확인하는 함수. 리턴이 null이면 없다. null이 아니면 찾은 노드
	void Clear();								// 모든 노드를 제거하는 함수
	void PrintList() const;						// 리스트의 현재 상황을 출력하는 함수

private:
	ListNode* Head = nullptr;	// 시작 노드(null이면 리스트가 비어있다.)
	ListNode* Tail = nullptr;	// 마지막 노드
	int Size = 0;	// 해드부터 이어지는 전체 노드의 개수
};