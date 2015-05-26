#define _CRT_SECURE_NO_WARNINGS

/* ������������ ������ 11. ���������. ������������ ��������� ������. ��������� ����������� �������
 *
 * �������
 * ��������� � ������ �������������� ����� ����������� � ���� ������.
 * ������ ��������� �� � ����������� �������.
 * ������� ������ �������� ���������� ������� �
 * � ��������� ����������� ��� ���� �������
 * (� ������ �� ������ ���� ��������� � ����������� ���������).
 * ��������� ���������, ���������� ������ ��������� � ������� �������,
 * ������� �������� � ������ ������ �� �����.
 * ������ ��� ������ ������ ������������ �� ������ �� ��������� � �����.
 *
 * 27 �������
 * �������� �������, ����������� ���������(������)
 * �� ���� ����������� L1, L2 �� ���������� �������:
 * � ����� ��������� ���������� �� �������� �� L2,
 * ������� ������� �� ����������� ����������� ������� �� L1.
 *
 * �������� ����� �������, ������ ��-13
 */

#include <stdio.h>
#include <stdlib.h>

struct polynomial
{
	int coeff;  // ����������� ����������
	int degree; // ������� ����������
	struct polynomial *next;
};

typedef struct polynomial* list;

void create(list*);
list find_same_degree(list*, int);
void display(list);
void delete_zero_coeff(list*);
int min_degree(list);
void create_third_polynomial(list*, list*, int);
void merge_sort(list*);
void split(list, list*, list*);
void merge(list*, list, list);

main()
{
	list head1 = NULL, head2 = NULL, head3 = NULL;

	// ������ ������ � ������ ���������.
	puts("Put here the FIRST polynomial.\nEnd by entering a zero coefficient element.");
	create(&head1);
	system("cls");
	puts("Put here the SECOND polynomial\nEnd by entering a zero coefficient element.");
	create(&head2);
	system("cls");

	// ������� ��������� �������� � ������� �������������.
	delete_zero_coeff(&head1);
	delete_zero_coeff(&head2);

	// ��������� �������� ������ �� �������� ������.
	merge_sort(&head1);
	merge_sort(&head2);

	// ������� �� ����� ��� ������������ ����������.
	printf("FIRST polynomial:   ");
	display(head1);
	printf("SECOND polynomial:  ");
	display(head2);

	// ������� ������ ��������� �������� �������
	create_third_polynomial(&head2, &head3, min_degree(head1));

	// ������� �� ����� ������ �������������� ���������.
	printf("THIRD polynomial:   ");
	display(head3);

	system("PAUSE");
}

/* ������� ����� ����������. ������� ������
* � ������� �� ����������� ������.
*/
void create(list *head)
{
	list current, same_deg, tail = NULL;

	while (1)
	{
		current = (list)malloc(sizeof(struct polynomial));

		// ���� ������������.
		do
		{
			fflush(stdin);
			printf("Put a coefficient: ");
		} while (scanf("%d", &current->coeff) != 1);

		/* ���� ������������, ����� ������������ ������ �������
		* � ������� �������������.
		*/
		if (current->coeff == 0)
		{
			free(current);
			break;
		}

		// ���� �������.
		do
		{
			fflush(stdin);
			printf("Put a degree: ");
		} while (scanf("%d", &current->degree) != 1);
		printf("\n");

		/* ���� ������������ ������ ������� �� ��������,
		* ������� ��� ���� � ������, �� ������������ ��� ����
		* �������� ������������.
		*/
		if (same_deg = find_same_degree(head, current->degree))
		{
			same_deg->coeff += current->coeff;
			continue;
		}

		// ����� ������� ������ � ����� ������.
		if ((*head == NULL) && (tail == NULL))
			*head = current;
		else
			tail->next = current;
		tail = current;
		tail->next = NULL;
	}
}

/* ������� ������� �������� ������� � �������� ����������.
* ���������� ��������� �� ������� ������ � ������� �������.
* ���� ��������� � ���� �������� ���, �� ���������� NULL.
*/
list find_same_degree(list *head, int x)
{
	list current;
	for (current = *head; current != NULL; current = current->next)
		if (current->degree == x)
			return current;
	return NULL;
}

/* ������� ������ ������ �� ����� �� ������ ��� ������� ��������.
* ��������� ��������� ������� ��������������� ���������
* ��� ����������� ������������ ����������, ��������,
* ���������� �����������/�������, ���� ��/��� ����� �������,
* ���������� ����, ������� �������� ���� � �.�.
*/
void display(list head)
{
	list current;

	if (head == NULL)
	{
		puts("Polinomial doesn't exist!");
	}

	for (current = head; current != NULL; current = current->next)
	{
		// ������� ��� ������ ������������
		if ((current->coeff == 1) && (current == head))
			printf("", current->coeff);
		else
		{
			if ((current->coeff > 1) && (current == head))
				printf("%d", current->coeff);
			else
			{
				if ((current->coeff == 1) && (current != head))
					printf("+", current->coeff);
				else
				{
					if (current->coeff == -1)
						printf("-", current->coeff);
					else
						printf("%+d", current->coeff);
				}
			}

		}
		// ������� ��� ������ �������
		if (current->degree == 1)
			printf("x");
		else
		{
			if (current->degree < 0)
				printf("x^(%d)", current->degree);
			else
			{
				if (current->degree == 0)
					printf("");
				else
					printf("x^%d", current->degree);
			}
		}
	}
	printf("\n\n");
}

// ������� ������� ��� �������� � ������� �������������
void delete_zero_coeff(list *head)
{
	list current = NULL, zero = NULL;
	while (1)
		/* �� ���� ���� ������� ������� ���� �������.
		* ���� ������������, ���� �� ����� ����� ������
		* �� ������� �� ������ �������� � ������� �������������.
		*/
	{
		// ������� ������� � ������� �������������.
		for (current = *head, zero = NULL; current != NULL; current = current->next)
			if (current->coeff == 0)
				zero = current;

		// ���� ��� ��������� � ������� �������������, �� ����� �� �������.
		if (zero == NULL)
			break;

		/* ������� �������, �������������� �������� � ������� �������������.
		* �������� �������� ����� �������, ����� ��������� ������ �������.
		* ���� ������� � ������� ������������� ����� � ������ ������,
		* �� ��� ���� ����������� ��������� ����������.
		*/
		for (current = *head; current != NULL; current = current->next)
		{
			// ���� ������ ������� ������ ����� ������� �����������.
			if ((current == *head) && (current == zero))
			{
				*head = (*head)->next;
				free(current);
				break;
			}
			// ���� ������� � ������� ������������� �� �������� ������ � ������.
			if (current->next == zero)
			{
				current->next = zero->next;
				free(zero);
			}
		}
	}
}

// ������� ������� ����������� ������� � �������� ������ � ���������� �.
int min_degree(list head)
{
	list current = head;
	int degree = current->degree;

	if (head == NULL)
	{
		puts("min_degree: Can't find any elements");
		return;
	}

	for (current = current->next; current != NULL; current = current->next)
	{
		if (current->degree < degree)
			degree = current->degree;
	}

	return degree;
}

/* ������� ��������� ����� ������ �� ��������� ������� ������,
* ������� ������� �� ����������� ����������� �� ������� ������.
* ����������� ������� ���������� ��������� �������, �������
* ���������� � ��������� ������� � �������� �������� ���������.
*/
void create_third_polynomial(list *head2, list *head3, int min_degree)
{
	list current = NULL, tail = NULL, element;

	for (current = *head2; current != NULL; current = current->next)
		if (current->degree <= min_degree)
		{
			element = (list)malloc(sizeof(struct polynomial));
			element->coeff = current->coeff;
			element->degree = current->degree;
			if ((*head3 == NULL) && (tail == NULL))
				*head3 = element;
			else
				tail->next = element;
			tail = element;
			tail->next = NULL;
		}
}

/* ������� ���������� �������� ���� ����,
* ��������� ����� ������. ���� � ������� ������ ������
* ������� ����� ���� ���������, �� �������� ������������.
* ����� ��� �������� ������ ������. ������� �� ���� �������,
* ������ �� ������� ������ ���� �������, ��������
* ��������������� ������, ����� �� ����� ������� ����������
* ����� ��������������� ������, ���� ��� �������� �� ����� ��������.
*/
void merge_sort(list *head)
{
	list *low = NULL, *high = NULL;

	if ((*head == NULL) || ((*head)->next == NULL))
		return;

	split(*head, &low, &high);
	merge_sort(&low);
	merge_sort(&high);
	merge(head, low, high);
}

// ������� ������� ������ �� 2 �����
void split(list head, list *low, list *high)
{
	list fast = NULL, slow = NULL;

	if (head == NULL || head->next == NULL)
	{
		(*low) = head;
		(*high) = NULL;
		return;
	}

	slow = head;
	fast = head->next;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}

	(*low) = head;
	(*high) = slow->next;
	slow->next = NULL;
}

// ������� ������� �������.
void merge(list *c, list a, list b)
{
	struct polynomial tmp;
	{

	};

	*c = NULL;
	if (a == NULL)
	{
		*c = b;
		return;
	}
	if (b == NULL)
	{
		*c = a;
		return;
	}

	if (a->degree > b->degree)
	{
		*c = a;
		a = a->next;
	}
	else
	{
		*c = b;
		b = b->next;
	}

	tmp.next = *c;

	while (a && b)
	{
		if (a->degree > b->degree)
		{
			(*c)->next = a;
			a = a->next;
		}
		else
		{
			(*c)->next = b;
			b = b->next;
		}
		(*c) = (*c)->next;
	}
	if (a)
	{
		while (a)
		{
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}
	if (b)
	{
		while (b)
		{
			(*c)->next = b;
			(*c) = (*c)->next;
			b = b->next;
		}
	}

	*c = tmp.next;
}
