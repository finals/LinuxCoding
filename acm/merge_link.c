#include <stdio.h>
#include <malloc.h>

struct link_list {
	int data;
	struct link_list *next;
};

struct link_list * merge_link (struct link_list *head1, struct link_list *
head2)
{
	struct link_list *head, *pcur;

	if (head1 == NULL && head2 == NULL) 
		return NULL;
	else if( head2 == NULL)
		return head1;
	else if(head1 == NULL)
		return head2;

	head = (struct link_list *)malloc(sizeof(struct link_list));
	pcur = head;

	while (head1 != NULL && head2 != NULL) {
		if (head1->data > head2->data) {
			pcur->next = head2;
			head2 = head2->next;
			pcur = pcur->next;
		}
		else {
			pcur->next = head1;
			head1 = head1->next;
			pcur = pcur->next;
		}
	}
	if (head1 != NULL)
		pcur->next = head1;
	if (head2 != NULL)
		pcur->next = head2;

	return head->next;
}

int main()
{ 
	int arr1[] = {1,3,5,7,9};
	int arr2[] = {2,4,6,8};
	int i;
	struct link_list *head1 = (struct link_list *)malloc(sizeof(struct link_list)
); 
	struct link_list *p1 = head1;
	struct link_list *head2 = (struct link_list *)malloc(sizeof(struct link_list)
);
	struct link_list *p2 = head2;
	for(i = 0; i < sizeof(arr1)/sizeof(int); ++i) {
		p1->next = (struct link_list *)malloc(sizeof(struct link_list));
		p1 = p1->next;
		p1->data = arr1[i];
		p1->next = NULL;
	}
	for(i = 0; i < sizeof(arr2)/sizeof(int); ++i) {
		p2->next = (struct link_list *)malloc(sizeof(struct link_list));
		p2 = p2->next;
		p2->data = arr2[i];
		p2->next = NULL;
	}

	head1 = merge_link(head1->next, head2->next);
	return 0;
}