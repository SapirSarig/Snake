#include "List.h"

bool List::isEmpty()
{
	return (head == NULL);
}
void List::insertNodeToTail(Node* node)
{
	if (isEmpty())
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = tail->next;
	}
}
Node* List::creatNewNode(Bullet bullet, Node* next)
{
	Node* res = new Node;
	res->bullet = bullet;
	res->next = next;
	return res;
}
Node* List::removeNodeFromList(int shotNum)
{
	if (head->bullet.getShotNum() == shotNum)
	{
		Node* temp;
		temp = head;
		head = head->next;
		delete temp;
		return head;
	}

	else
	{
		Node* curr = head;

		while (curr->next != NULL)
		{
			if (curr->next->bullet.getShotNum() == shotNum)
			{
				Node* temp;
				temp = curr->next;
				curr->next = temp->next;
				delete temp;
				return curr->next;
			}
			else
				curr = curr->next;

		}
	}
}
Node* List::removeNodeFromList(Node* curr)
{
	Node* temp;
	temp = curr;
	curr = curr->next;
	delete temp;
	return curr;
}